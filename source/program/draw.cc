#include "program.hpp"
#include <cstdio>
#ifdef DEBUG
#include <sstream>
#endif

void proj::program::draw()
{
        BeginDrawing();

        ClearBackground(C_PROGAM_COLOR_BACKGROUND);

        for (auto &tab : this->tabs)
        {
                tab.draw();

                if (tab.id == this->selectedTabID)
                {
                        if (tab.lines.size() != 0)
                        {
                                printf("line: %s\n", tab.lines[0].c_str());
                        }
                }
        }

#ifdef DEBUG
        std::stringstream strs;
        strs << this->tick;
        DrawText(strs.str().c_str(), 20, 20, 30, BLACK);
#endif

        EndDrawing();
}
