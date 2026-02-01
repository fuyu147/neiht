#include "program.hpp"
#include <raylib.h>
#include <string>

Rectangle calculateTabRectangle(proj::program *program, const std::string &file)
{
  const proj::vtab &tabs = program->getTabs();
  Rectangle         rect = {};

  if (tabs.empty())
  {
    rect.x = proj::C_TAB_MARGIN;
    rect.y = proj::C_TAB_MARGIN;
  }
  else
  {
    const proj::Tab &lastTab       = tabs.back();
    const Rectangle &lastRectangle = lastTab.rect;
    rect.x = lastRectangle.x + lastRectangle.width + proj::C_TAB_MARGIN;
    rect.y = proj::C_TAB_MARGIN;
  }

  rect.height          = proj::C_TAB_HEIGHT;

  int         position = file.find_last_of("/");
  std::string title    = file.substr(position + 1);

  rect.width           = MeasureText(title.c_str(), 30) + 10;
  if (rect.width > proj::C_TAB_MAX_WIDTH) rect.width = proj::C_TAB_MAX_WIDTH;

  return rect;
}

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
      int         position = file.find_last_of("/");
      std::string title    = file.substr(position + 1);
      this->tabs.push_back(Tab(this->getNextID(), file, title,
                               calculateTabRectangle(this, file)));
    }
  }
}
