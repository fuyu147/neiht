#include "program.hpp"
#include <sstream>

void proj::program::draw()
{
        BeginDrawing();

        ClearBackground(WHITE);

        std::stringstream strs;
        strs << this->tick;
        DrawText(strs.str().c_str(), 20, 20, 30, BLACK);

        int initial = 50;
        int offset  = 0;
        int step    = 50;

        for (auto &tab : this->tabs)
        {
                if (tab.id == this->selectedTabID)
                {
                        DrawText(tab.file.c_str(), 40, initial + offset * step,
                                 30, BLACK);
                }
        }

        EndDrawing();
}
