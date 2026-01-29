#pragma once

#include "raylib.h"

#include <string>
#include <vector>

namespace proj
{

typedef std::vector<std::string> vstring;

enum TAB_STATE
{
        TAB_STATE_NONE,
        TAB_STATE_WRITE,
        TAB_STATE_READ,
        TAB_STATE_CLOSE,
};

struct Tab
{
        int         id;    // used to check if the tab is selected
        std::string file;  // filepath
        std::string title; // filename
        vstring     lines; // content
        TAB_STATE   state; // next action todo
        Rectangle   rectangle;

        Tab(int id, std::string file, Vector2 position, Vector2 scale)
            : id(id), file(file), lines(), state(TAB_STATE_NONE)
        {
                this->rectangle.x      = position.x;
                this->rectangle.y      = position.y;
                this->rectangle.width  = scale.x;
                this->rectangle.height = scale.y;
        }
};

typedef std::vector<Tab> vtab;
}; // namespace proj
