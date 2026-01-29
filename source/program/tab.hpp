#pragma once

#include <string>
#include <vector>

enum TAB_ACTION
{
        TAB_ACTION_NONE,
        TAB_ACTION_WRITE_TO_FILE,
        TAB_ACTION_READ_FROM_FILE,
        TAB_ACTION_CLOSE_FILE,
};

struct Tab
{
        std::string              file;
        std::vector<std::string> lines;
        TAB_ACTION               actionToDo;

        Tab(std::string file)
        {
                this->file       = file;
                this->lines      = {};
                this->actionToDo = TAB_ACTION_NONE;
        }
};
