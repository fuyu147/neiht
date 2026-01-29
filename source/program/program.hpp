#include <raylib.h>
#include <raymath.h>

#include <string>
#include <vector>

#include "tab.hpp"

typedef std::vector<std::string> vstring;

enum KEY_ACTION
{
        KEY_ACTION_QUIT             = 'q',
        KEY_ACTION_OPEN_FILE_DIALOG = 'o',
};

enum PROGAM_STATE
{
        PROGAM_STATE_CLOSE,
        PROGAM_STATE_RUN,
        PROGAM_STATE_MAIN_MENU, // not sure, might never be a thing
};

namespace proj
{

class program
{
        vtab         tabs;
        int          selectedTabID;
        int          tick = 0;
        PROGAM_STATE state;

public:
        program()
        {
                InitWindow(1200, 700, "This is certainly a title of all times");
                SetExitKey(KEY_Q);
        }

        void run()
        {
                while (!WindowShouldClose())
                {
                        int err = this->update();
                        if (err != 0) break;
                        this->draw();

                        if (this->state == PROGAM_STATE_CLOSE) break;
                }
        }

private:
        void    draw();
        int     update();
        int     handleKeys(int key);
        vstring getFileFromDialog();
        void    spawnFileDialogThread();
        void    setTabs();
        void    getTabsFromFiles(std::vector<std::string> files);
        int     getNextID();
};

} // namespace proj
