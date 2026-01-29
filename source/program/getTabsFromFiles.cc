#include "program.hpp"

void proj::program::setTabsFromFiles(std::vector<std::string> files)
{
        for (auto file : files)
        {
                bool already_open = false;
                for (const auto &tab : this->tabs)
                {
                        if (tab.file == file)
                        {
                                already_open = true;
                                break;
                        }
                }

                if (!already_open)
                {
                        this->tabs.push_back(Tab(this->getNextID(), file,
                                                 (Vector2){0, 0},
                                                 (Vector2){0, 0}));
                }
        }
}
