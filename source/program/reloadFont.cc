#include "program.hpp"

Font &proj::program::getFont(int fontSize)
{
        // Check if font already exists in pool
        auto it = fontPool.find(fontSize);
        if (it != fontPool.end())
        {
                return it->second;
        }

        // Load new font and add to pool
        Font newFont = LoadFontEx("assets/Miracode.ttf", fontSize, 0, 250);
        if (newFont.texture.id > 0) // Check if font loaded successfully
        {
                fontPool[fontSize] = newFont;
                return fontPool[fontSize];
        }

        // Fallback to default font if loading fails
        return this->font;
}

void proj::program::reloadFont(int newFontSize)
{
        if (newFontSize == this->actualFontSize) return;

        this->fontSize       = newFontSize;
        this->actualFontSize = newFontSize;
        this->font           = getFont(newFontSize);
}
