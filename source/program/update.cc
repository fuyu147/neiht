#include "program.hpp"
#include <raylib.h>

#ifdef DEBUG
#include <print>
#endif

int proj::program::update()
{
        int key = GetCharPressed();

        this->checkMouse();

        this->textView.width  = GetScreenWidth() - C_TEXT_VIEW_MARGIN;
        this->textView.height = GetScreenHeight() - C_TEXT_VIEW_MARGIN;

#ifdef DEBUG
        std::println("this->textView: {} {} {} {}", this->textView.x,
                     this->textView.y, this->textView.height,
                     this->textView.width);

        if (key != 0) std::println("key pressed: {}\n", (char)key);
#endif

        if (this->tick++ > 10000) this->tick = 0;

        for (auto &tab : this->tabs)
        {
                if (this->selectedTabID == tab.id)
                {

                        float wheel = GetMouseWheelMove();
                        tab.scrollOffsetY -= wheel * C_SCROLL_SPEED;

                        float contentHeight =
                            tab.lines.size() * C_TEXT_LINE_HEIGHT;
                        float maxScroll = std::max(
                            0.0f, contentHeight - this->textView.height);

                        tab.scrollOffsetY =
                            std::clamp(tab.scrollOffsetY, 0.0f, maxScroll);

                        int err = tab.getLines();
                        if (err)
                        {
#ifdef DEBUG
                                std::println("error updating tab");
#endif
                                return 1;
                        }
#ifdef DEBUG
                        std::println("line count : {}", tab.lines.size());

#endif
                }
        }

        handleKeys(key);

        return 0;
}

void proj::program::checkMouse()
{
        auto mousePosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
                for (Tab &tab : this->tabs)
                {
                        if (CheckCollisionPointRec(mousePosition, tab.rect))
                        {
                                this->selectedTabID = tab.id;
                                break;
                        }
                }
        }

        for (Tab &tab : this->tabs)
        {
                bool isHovered =
                    CheckCollisionPointRec(mousePosition, tab.rect);

                tab.updateState(isHovered, tab.id == this->selectedTabID);
        }
}
