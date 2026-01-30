#include "program.hpp"
#include <raylib.h>

int proj::program::update()
{
        int key = GetCharPressed();

        this->checkMouse();

        if (key != 0) printf("key pressed: %c\n", key);

        if (this->tick++ > 10000) this->tick = 0;

        for (auto tab : this->tabs)
        {
                if (this->selectedTabID == tab.id)
                {
                        int err = tab.update();
                        if (err)
                        {
                                printf("error updating tab");
                                return 1;
                        }

                        printf("line count : %zu\n", tab.lines.size());
                        printf("first line: <%s>", tab.lines[0].c_str());
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
