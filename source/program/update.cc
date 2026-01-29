#include "program.hpp"

int proj::program::update()
{
        int key = GetCharPressed();

        if (key != 0) printf("key pressed: %c\n", key);

        this->tick++;

        return handleKeys(key);
}
