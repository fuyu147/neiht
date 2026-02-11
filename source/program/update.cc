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
                        else if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
                        {
                                int fontSizeStep = 1;
                                int newFontSize  = this->fontSize;
                                if (wheel > 0)
                                {
                                        newFontSize = std::min(this->fontSize + fontSizeStep, C_TEXT_MAX_SIZE);
                                }
                                else if (wheel < 0)
                                {
                                        newFontSize = std::max(this->fontSize - fontSizeStep, C_TEXT_MIN_SIZE);
                                }

                                if (newFontSize != this->fontSize)
                                {
                                        this->fontSize = newFontSize;
                                        this->reloadFont(this->fontSize);
                                        // Reset scroll to top when zooming to prevent disorientation
                                        tab.scrollOffset.y = 0;
                                }
                        }
                        else
                        {
                                tab.scrollOffset.y -= wheel * C_SCROLL_SPEED;

                                float contentHeight =
                                    tab.lines.size() * (this->actualFontSize + C_TEXT_LINE_SPACING * 2);
                                float maxScroll    = std::max(0.0f, contentHeight - this->textView.height);

                                tab.scrollOffset.y = std::clamp(tab.scrollOffset.y, 0.0f, maxScroll);
                        }

                        tab.action = TAB_ACTION_READ;
                }

                tab.update();
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
        else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
        {
                for (auto it = this->tabs.begin(); it != this->tabs.end(); ++it)
                {
                        if (CheckCollisionPointRec(mousePosition, it->rect))
                        {
                                if (this->selectedTabID == it->id) this->selectedTabID = -1;
                                this->tabs.erase(it);
                                this->updateTabPositions();
                                break;
                        }
                }
        }

        for (Tab &tab : this->tabs)
        {
                bool isHovered = CheckCollisionPointRec(mousePosition, tab.rect);

                tab.updateState(isHovered, tab.id == this->selectedTabID);
        }
}

void proj::program::updateTabPositions()
{
        float currentX = C_TAB_MARGIN;

        for (Tab &tab : this->tabs)
        {
                tab.rect.x = currentX;
                currentX += tab.rect.width + C_TAB_MARGIN;
        }
}
