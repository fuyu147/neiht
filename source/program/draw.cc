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
#ifdef DEBUG
        std::println("line: {}\n", tab.lines[0].c_str());
#endif
        BeginScissorMode(this->textView.x, this->textView.y,
                         this->textView.width, this->textView.height);

        for (int i = 0; i < tab.lines.size(); i++)
        {
          float y =
              this->textView.y + i * C_TEXT_LINE_HEIGHT - tab.scrollOffset.y;

          if (y + C_TEXT_LINE_HEIGHT < this->textView.y ||
              y > this->textView.y + this->textView.height)
            continue;

          DrawText(tab.lines[i].c_str(), this->textView.x - tab.scrollOffset.x,
                   y, 30, WHITE);
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
