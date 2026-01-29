#include <raylib.h>
#include <raymath.h>

#include <string>
#include <vector>

#include "tab.hpp"

typedef std::vector<Tab>         vtab;
typedef std::vector<std::string> vstring;

enum KEY_ACTION
{
        KEY_ACTION_QUIT             = 'q',
        KEY_ACTION_OPEN_FILE_DIALOG = 'o',
};

namespace proj
{

class program
{
        vtab tabs;
        int  tick = 0;

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
                        this->draw();
                        if (this->update() == 1) return;
                }
        }

private:
        void    draw();
        int     update();
        int     handleKeys(int key);
        vstring getFileFromDialog();
        void    spawnFileDialogThread();
        void    setTabs();
        vtab    getTabsFromFiles(std::vector<std::string> files);
};

} // namespace proj
