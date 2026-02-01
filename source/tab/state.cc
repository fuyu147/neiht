#include "tab.hpp"

void proj::Tab::updateState(bool isHoveredByMouse, bool isSelected)
{
  if (isSelected)
    this->state = TAB_STATE_SELECTED;
  else if (isHoveredByMouse)
    this->state = TAB_STATE_HOVERED;
  else
    this->state = TAB_STATE_DEFAULT;
}
