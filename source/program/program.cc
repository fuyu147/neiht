#include "program.hpp"

std::vector<Tab> proj::program::getTabsFromFiles(std::vector<std::string> files)
{
        std::vector<Tab> tabs = {};
        for (auto file : files)
        {
                bool already_open = false;
                for (const auto &tab : this->tabs)
                {
                        if (tab.file == file)
                        {
                                already_open = true;
                                break;
                        }
                }

                if (!already_open)
                {
                        tabs.push_back(Tab(file));
                }
        }
        return tabs;
}
