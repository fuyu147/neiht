#include <map>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

#include "../tab/tab.hpp"

namespace proj
{
const Color C_PROGAM_COLOR_BACKGROUND = (Color){0x21, 0x20, 0x1F, 0xFF};
const Color C_PROGAM_COLOR_TEXT       = (Color){255, 255, 255, 255};

const float C_SCROLL_SPEED            = 40.f;
const int   C_TEXT_LINE_SPACING       = 2;
const float C_TEXT_VIEW_MARGIN        = 40;
const int   C_TEXT_DEFAULT_SIZE       = 12;
const int   C_TEXT_MAX_SIZE           = 72;
const int   C_TEXT_MIN_SIZE           = 4;

enum KEY_ACTION
{
        KEY_ACTION_QUIT             = 'q',
        KEY_ACTION_OPEN_FILE_DIALOG = 'o',
};

enum PROGRAM_STATE
{
        PROGRAM_STATE_CLOSE,
        PROGRAM_STATE_RUN,
        PROGRAM_STATE_FILEDIALOG,
};

class program
{
        std::vector<Tab>    tabs;
        int                 selectedTabID = -1;
        int                 fontSize;
        int                 actualFontSize;
        int                 tick = 0;
        PROGRAM_STATE       state;
        Rectangle           textView = {C_TEXT_VIEW_MARGIN, C_TEXT_VIEW_MARGIN + C_TAB_HEIGHT, 800, 500};
        Font                font;
        std::map<int, Font> fontPool;

public:
        program() : tabs(), state(PROGRAM_STATE_RUN)
        {
                InitWindow(1200, 700, "This is certainly a title of all times");
                SetWindowState(FLAG_WINDOW_RESIZABLE);
                SetExitKey({});

                this->font           = LoadFontEx("assets/Miracode.ttf", C_TEXT_DEFAULT_SIZE, 0, 250);
                this->fontSize       = C_TEXT_DEFAULT_SIZE;
                this->actualFontSize = C_TEXT_DEFAULT_SIZE;
        }
        ~program()
        {
                UnloadFont(this->font);
                for (auto &pair : fontPool)
                {
                        UnloadFont(pair.second);
                }
        }

        void run()
        {
                while (!WindowShouldClose())
                {
                        handleKeys(GetCharPressed());
                        if (this->state == PROGRAM_STATE_CLOSE) return;
                        if (this->state == PROGRAM_STATE_RUN) this->update();
                        this->draw();
                }
        }

        const std::vector<Tab> &getTabs() const
        {
                return this->tabs;
        }

private:
        int                      getNextID();
        void                     checkMouse();
        void                     draw();
        void                     handleKeys(int key);
        Font                    &getFont(int fontSize);
        void                     reloadFont(int newFontSize);
        void                     setTabsFromFiles(std::vector<std::string> files);
        void                     spawnFileDialogThread();
        void                     update();
        void                     updateTabPositions();
        std::vector<std::string> getFileFromDialog();
};

} // namespace proj
