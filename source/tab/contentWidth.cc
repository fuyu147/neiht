#include "tab.hpp"
#include <algorithm>
#include <raylib.h>

void proj::Tab::getContentWidth()
{
  for (auto &line : this->lines)
  {
    this->contentWidth =
        std::max(this->contentWidth, MeasureText(line.c_str(), 30));
  }
}
