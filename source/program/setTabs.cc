#include "program.hpp"

void proj::program::setTabs()
{
        this->tabs = this->getTabsFromFiles(this->getFileFromDialog());
}
