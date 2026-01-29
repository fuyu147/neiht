#include "program.hpp"
#include <raylib.h>

int proj::program::update()
{
        int key = GetCharPressed();

        this->checkMouse();

        if (key != 0) printf("key pressed: %c\n", key);

        if (this->tick++ > 10000) this->tick = 0;

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
