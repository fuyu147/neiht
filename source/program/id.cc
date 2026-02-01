#include "program.hpp"

int proj::program::getNextID()
{
  int maxId = -1;
  for (const auto &tab : tabs)
    if (tab.id > maxId) maxId = tab.id;
  return maxId + 1;
}
