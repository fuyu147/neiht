#include "program.hpp"
#ifdef DEBUG
#include <print>
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
                        if (tab.lines.size() > 0)
                        {
                                // how should i get the proper offset and
                                // stuff...
#ifdef DEBUG
                                std::println("line: {}\n",
                                             tab.lines[0].c_str());
#endif

                                DrawText(tab.lines[0].c_str(), 50, 50, 30,
                                         WHITE);
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
