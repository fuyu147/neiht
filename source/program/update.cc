#include "program.hpp"
#include <raylib.h>

#ifdef DEBUG
#include <print>
#endif

int proj::program::update()
{
        int key = GetCharPressed();

        this->checkMouse();

#ifdef DEBUG
        if (key != 0) std::println("key pressed: {}\n", (char)key);
#endif

        if (this->tick++ > 10000) this->tick = 0;

        for (auto &tab : this->tabs)
        {
                if (this->selectedTabID == tab.id)
                {
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

        return handleKeys(key);
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
