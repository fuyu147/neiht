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
      break;
    case KEY_ACTION_OPEN_FILE_DIALOG:
      if (!dialogOpen.exchange(true))
      {
        this->spawnFileDialogThread();
      }
      break;
    default:
      break;
  }
  return;
}

void proj::program::spawnFileDialogThread()
{
  std::thread([this] {
    this->state = PROGRAM_STATE_FILEDIALOG;
    this->setTabsFromFiles(this->getFileFromDialog());
    dialogOpen  = false;
    this->state = PROGRAM_STATE_RUN;
  }).detach();
}
