#include "program.hpp"

#include <iomanip>
#include <raylib.h>
#include <sstream>

#ifdef DEBUG
#include <print>
#endif

void proj::program::draw()
{
        BeginDrawing();

        ClearBackground(C_PROGAM_COLOR_BACKGROUND);

        for (auto &tab : this->tabs)
        {
                Font &tabFont = this->getFont(C_TAB_TEXT_SIZE);
                tab.draw(tabFont, C_TAB_TEXT_SIZE);

                if (tab.id == this->selectedTabID)
                {
                        if (tab.lines.size() > 0)
                        {
#ifdef DEBUG
                                std::println("line: {}\n", tab.lines[0].c_str());
#endif
                                BeginScissorMode(this->textView.x, this->textView.y, this->textView.width,
                                                 this->textView.height);

                                for (int i = 0; i < tab.lines.size(); i++)
                                {
                                        float y = this->textView.y + i * (this->actualFontSize + C_TEXT_LINE_SPACING) -
                                                  tab.scrollOffset.y;

                                        if (y + this->actualFontSize < this->textView.y ||
                                            y > this->textView.y + this->textView.height)
                                                continue;

                                        std::stringstream strs;
                                        strs << std::setw(3) << std::setfill(' ') << i + 1;

                                        std::string line  = strs.str() + " > " + tab.lines[i];

                                        Font &contentFont = this->getFont(this->actualFontSize);
                                        DrawTextEx(contentFont, line.c_str(),
                                                   (Vector2){this->textView.x - tab.scrollOffset.x, y},
                                                   this->actualFontSize, 0, WHITE);
                                }

                                EndScissorMode();
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
