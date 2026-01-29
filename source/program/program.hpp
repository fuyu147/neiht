#include <raylib.h>
#include <raymath.h>

#include <string>
#include <vector>

#include "../tab/tab.hpp"

typedef std::vector<std::string> vstring;

enum KEY_ACTION
{
        KEY_ACTION_QUIT             = 'q',
        KEY_ACTION_OPEN_FILE_DIALOG = 'o',
};

enum PROGRAM_STATE
{
        PROGRAM_STATE_CLOSE,
        PROGRAM_STATE_RUN,
        PROGRAM_STATE_MAIN_MENU, // not sure, might never be a thing
};

namespace proj
{

class program
{
        vtab         tabs;
        int          selectedTabID;
        int          tick = 0;
        PROGRAM_STATE state;

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

                        if (this->state == PROGRAM_STATE_CLOSE) break;
                }
        }

private:
        int     getNextID();
        int     handleKeys(int key);
        int     update();
        void    draw();
        void    setTabsFromFiles(std::vector<std::string> files);
        void    spawnFileDialogThread();
        vstring getFileFromDialog();
};

} // namespace proj
