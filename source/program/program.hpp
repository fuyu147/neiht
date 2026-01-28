#include <raylib.h>
#include <raymath.h>
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

                DrawText("Hey", 20, 20, 30, BLACK);

                EndDrawing();
        }

        int update()
        {
                int key = GetCharPressed();

                if (key != 0) printf("key pressed: %c\n", key);

                switch (key)
                {
                        case KEY_ACTION_QUIT:
                                return 1;
                        case KEY_ACTION_OPEN_FILE_DIALOG:
                                break;
                        default:
                                break;
                }

                return 0;
        }
};

std::vector<std::string> getFileFromDialog();

} // namespace proj
