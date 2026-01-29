#include "program.hpp"
#include <atomic>
#include <thread>

std::atomic<bool> dialogOpen{false};

int proj::program::handleKeys(int key)
{
        switch (key)
        {
                case KEY_ACTION_QUIT:
                        return 1;
                case KEY_ACTION_OPEN_FILE_DIALOG:
                        if (!dialogOpen.exchange(true))
                        {
                                this->spawnFileDialogThread();
                        }
                        break;
                default:
                        break;
        }
        return 0;
}

void proj::program::spawnFileDialogThread()
{
        std::thread([this] {
                this->getTabsFromFiles(this->getFileFromDialog());
                dialogOpen = false;
        }).detach();
}
