#include "program.hpp"
#include <atomic>
#include <thread>

std::atomic<bool> dialogOpen{false};

void proj::program::handleKeys(int key)
{
        switch (key)
        {
                case KEY_ACTION_QUIT:
                        this->state = PROGRAM_STATE_CLOSE;
                case KEY_ACTION_OPEN_FILE_DIALOG:
                        if (!dialogOpen.exchange(true))
                        {
                                this->spawnFileDialogThread();
                        }
                        break;
                default:
                        this->state = PROGRAM_STATE_RUN;
                        break;
        }
        return;
}

void proj::program::spawnFileDialogThread()
{
        std::thread([this] {
                this->setTabsFromFiles(this->getFileFromDialog());
                dialogOpen = false;
        }).detach();
}
