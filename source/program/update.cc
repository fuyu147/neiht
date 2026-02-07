#include "program.hpp"

#include <algorithm>
#include <raylib.h>

#ifdef DEBUG
#include <print>
#endif

void proj::program::update()
{
        this->checkMouse();

#ifdef DEBUG
        for (auto &tab : this->tabs)
        {
                std::print("{}, ", tab.id);
        }
        std::println();
#endif

        this->textView.x      = C_TEXT_VIEW_MARGIN;
        this->textView.y      = C_TEXT_VIEW_MARGIN + C_TAB_HEIGHT;
        this->textView.width  = GetScreenWidth() - C_TEXT_VIEW_MARGIN * 2;
        this->textView.height = GetScreenHeight() - C_TEXT_VIEW_MARGIN * 2 - C_TAB_HEIGHT;

        if (this->tick++ > 10000) this->tick = 0;

        for (auto &tab : this->tabs)
        {
                if (this->selectedTabID == tab.id)
                {

                        float wheel = GetMouseWheelMove();
                        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
                        {
                                tab.scrollOffset.x -= wheel * C_SCROLL_SPEED;

                                float contentWidth = 50000; // how should i get the content
                                                            // width??
                                float maxScroll    = std::max(0.0f, contentWidth - this->textView.width);

                                tab.scrollOffset.x = std::clamp(tab.scrollOffset.x, 0.0f, maxScroll);
                        }
                        else
                        {
                                tab.scrollOffset.y -= wheel * C_SCROLL_SPEED;

                                float contentHeight = tab.lines.size() * C_TEXT_LINE_HEIGHT;
                                float maxScroll     = std::max(0.0f, contentHeight - this->textView.height);

                                tab.scrollOffset.y  = std::clamp(tab.scrollOffset.y, 0.0f, maxScroll);
                        }

                        tab.getLines();
                }
        }
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
                                if (this->selectedTabID == tab.id)
                                {
                                        this->selectedTabID = -1;
                                        break;
                                }
                                else
                                {
                                        this->selectedTabID = tab.id;
                                        break;
                                }
                        }
                }
        }

        for (Tab &tab : this->tabs)
        {
                bool isHovered = CheckCollisionPointRec(mousePosition, tab.rect);

                tab.updateState(isHovered, tab.id == this->selectedTabID);
        }
}
