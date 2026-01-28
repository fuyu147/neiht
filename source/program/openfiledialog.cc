#include "glib.h"
#include "program.hpp"

#include <gio/gio.h>
#include <string>
#include <vector>

// Struct to hold data for the callback
struct UserData
{
        GMainLoop                *loop;
        std::vector<std::string> *uris;
};

// Callback for the "Response" signal from the portal
static void on_portal_response(GDBusConnection *connection,
                               const gchar     *sender_name,
                               const gchar     *object_path,
                               const gchar     *interface_name,
                               const gchar *signal_name, GVariant *parameters,
                               gpointer user_data)
{
        (void)connection;
        (void)sender_name;
        (void)object_path;
        (void)interface_name;

        if (g_strcmp0(signal_name, "Response") != 0)
        {
                return;
        }

        auto *data = static_cast<UserData *>(user_data);

        guint32   response;
        GVariant *results;
        g_variant_get(parameters, "(u@a{sv})", &response, &results);

        if (response == 0)
        { // Success
                GVariant *uri_list_variant = g_variant_lookup_value(
                    results, "uris", G_VARIANT_TYPE("as"));
                if (uri_list_variant)
                {
                        const gchar **uri_list =
                            g_variant_get_strv(uri_list_variant, nullptr);
                        if (uri_list)
                        {
                                for (const gchar **uri = uri_list; *uri; ++uri)
                                {
                                        data->uris->push_back(*uri);
                                }
                                // g_strfreev(uri_list);
                        }
                        g_variant_unref(uri_list_variant);
                }
        }

        g_variant_unref(results);
        g_main_loop_quit(data->loop);
}

std::vector<std::string> proj::program::getFileFromDialog()
{
        GDBusProxy              *proxy           = nullptr;
        GError                  *error           = nullptr;
        GVariant                *result_variant  = nullptr;
        gchar                   *handle_path     = nullptr;
        GDBusConnection         *connection      = nullptr;
        guint                    subscription_id = 0;
        GMainLoop               *loop            = nullptr;
        std::vector<std::string> uris;
        std::vector<std::string> paths;

        proxy = g_dbus_proxy_new_for_bus_sync(
            G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE,
            nullptr, /* GDBusInterfaceInfo* */
            "org.freedesktop.portal.Desktop", "/org/freedesktop/portal/desktop",
            "org.freedesktop.portal.FileChooser", nullptr, /* GCancellable */
            &error);

        if (error)
        {
                g_error_free(error);
                return {};
        }

        GVariantBuilder options_builder;
        g_variant_builder_init(&options_builder, G_VARIANT_TYPE("a{sv}"));

        GVariantBuilder filters;
        g_variant_builder_init(&filters, G_VARIANT_TYPE("a(sa(us))"));

        GVariantBuilder mime_types;
        g_variant_builder_init(&mime_types, G_VARIANT_TYPE("a(us)"));

        g_variant_builder_add(&mime_types, "(us)",
                              1, // 1 = MIME type
                              "text/plain");

        g_variant_builder_add(&filters, "(s@a(us))", "Text files",
                              g_variant_builder_end(&mime_types));

        g_variant_builder_add(&options_builder, "{sv}", "filters",
                              g_variant_builder_end(&filters));

        g_variant_builder_add(&options_builder, "{sv}", "multiple",
                              g_variant_new_boolean(TRUE));

        result_variant = g_dbus_proxy_call_sync(
            proxy, "OpenFile",
            g_variant_new("(ss@a{sv})",
                          "", // parent_window
                          "Select a file",
                          g_variant_builder_end(&options_builder)),
            G_DBUS_CALL_FLAGS_NONE,
            -1,      // timeout
            nullptr, /* cancellable */
            &error);

        if (error)
        {
                g_error_free(error);
                g_object_unref(proxy);
                return {};
        }

        g_variant_get(result_variant, "(o)", &handle_path);
        g_variant_unref(result_variant);

        connection = g_bus_get_sync(G_BUS_TYPE_SESSION, nullptr, &error);
        if (error)
        {
                g_error_free(error);
                g_free(handle_path);
                g_object_unref(proxy);
                return {};
        }

        loop               = g_main_loop_new(nullptr, FALSE);
        UserData user_data = {loop, &uris};

        subscription_id    = g_dbus_connection_signal_subscribe(
            connection,
            "org.freedesktop.portal.Desktop", // sender
            "org.freedesktop.portal.Request", // interface
            "Response",                       // signal
            handle_path,                      // object path of the request
            nullptr,                          // arg0
            G_DBUS_SIGNAL_FLAGS_NONE, on_portal_response, &user_data,
            nullptr // GDestroyNotify
        );

        g_main_loop_run(loop);

        // Cleanup
        g_dbus_connection_signal_unsubscribe(connection, subscription_id);
        g_object_unref(connection);
        g_free(handle_path);
        g_main_loop_unref(loop);
        g_object_unref(proxy);

        for (const auto &uri : uris)
        {
                gchar *path = g_file_get_path(g_file_new_for_uri(uri.c_str()));
                if (path)
                {
                        paths.push_back(path);
                        g_free(path);
                }
        }

        return paths;
}
