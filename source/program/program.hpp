#include <raylib.h>
#include <raymath.h>
#include <sstream>
#include <stdio.h>

#include <cstdio>
#include <string>
#include <vector>

enum KEY_ACTION
{
        KEY_ACTION_QUIT             = 'q',
        KEY_ACTION_OPEN_FILE_DIALOG = 'o',
};

namespace proj
{

class program
{
        std::vector<std::string> files;
        int                      tick = 0;

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
        void draw()
        {
                BeginDrawing();

                ClearBackground(WHITE);

                std::stringstream strs;
                strs << this->tick;
                DrawText(strs.str().c_str(), 20, 20, 30, BLACK);

                if (!this->files.empty())
                        DrawText(this->files[0].c_str(), 40, 40, 30, BLACK);

                EndDrawing();
        }

        int update()
        {
                int key = GetCharPressed();

                if (key != 0) printf("key pressed: %c\n", key);

                this->tick++;

                return handleKeys(key);
        }

        int handleKeys(int key);

        // this blocks the flow
        std::vector<std::string> getFileFromDialog();
};

} // namespace proj
