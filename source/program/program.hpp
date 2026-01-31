#include <raylib.h>
#include <raymath.h>

#include <string>
#include <vector>

#include "../tab/tab.hpp"

typedef std::vector<std::string> vstring;

namespace proj
{
const Color C_PROGAM_COLOR_BACKGROUND = (Color){0x21, 0x20, 0x1F, 0xFF};
const Color C_PROGAM_COLOR_TEXT       = (Color){255, 255, 255, 255};

const float C_SCROLL_SPEED            = 40.f;
const int   C_TEXT_LINE_HEIGHT        = 50;
const float C_TEXT_VIEW_MARGIN        = 40;

enum KEY_ACTION
{
        KEY_ACTION_QUIT             = 'q',
        KEY_ACTION_OPEN_FILE_DIALOG = 'o',
};

enum PROGRAM_STATE
{
        PROGRAM_STATE_CLOSE,
        PROGRAM_STATE_RUN,
};

class program
{
        vtab          tabs;
        int           selectedTabID = -1;
        int           tick          = 0;
        PROGRAM_STATE state;
        Rectangle     textView = {
            C_TEXT_VIEW_MARGIN,                // x
            C_TEXT_VIEW_MARGIN + C_TAB_HEIGHT, // y
            800,                               // width
            500                                // height
        };

public:
        program() : tabs(), state(PROGRAM_STATE_RUN)
        {
                InitWindow(1200, 700, "This is certainly a title of all times");
                SetExitKey(KEY_Q);
                SetWindowState(FLAG_WINDOW_RESIZABLE);
        }

        void run()
        {
                while (!WindowShouldClose() &&
                       this->state != PROGRAM_STATE_CLOSE)
                {
                        int err = this->update();
                        if (err != 0) break;
                        this->draw();
                }
        }

        const vtab &getTabs() const
        {
                return this->tabs;
        }

private:
        int     getNextID();
        int     update();
        void    checkMouse();
        void    draw();
        void    handleKeys(int key);
        void    setTabsFromFiles(std::vector<std::string> files);
        void    spawnFileDialogThread();
        vstring getFileFromDialog();
};

} // namespace proj
