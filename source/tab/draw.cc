#include "tab.hpp"

#include "raylib.h"

Color proj::Tab::getBackgroundColorFromState()
{
  switch (this->state)
  {
    case TAB_STATE_DEFAULT:
      return proj::C_TAB_COLOR_BACKGROUND_DEFAULT;
    case TAB_STATE_HOVERED:
      return proj::C_TAB_COLOR_BACKGROUND_HOVERED;
    case TAB_STATE_SELECTED:
      return proj::C_TAB_COLOR_BACKGROUND_SELECTED;
  }

  return BLACK;
}

void proj::Tab::draw()
{
  DrawRectangleRec(this->rect, this->getBackgroundColorFromState());

  float       textPadding    = 10.0f; // 5px left, 5px right
  float       availableWidth = this->rect.width - textPadding;
  const char *originalTitle  = this->title.c_str();
  int         fontSize       = 30;

  // Check if the full title fits
  if (MeasureText(originalTitle, fontSize) <= availableWidth)
  {
    // DrawText(originalTitle, this->rect.x + 5, this->rect.y + 5, fontSize,
    //          C_TAB_COLOR_TEXT);
    DrawTextEx(*this->font, originalTitle,
               (Vector2){this->rect.x + 5, this->rect.y + 5}, 30, 0,
               C_TAB_COLOR_TEXT);
    return;
  }

  // If not, truncate the title
  std::string truncated     = this->title;
  const char *ellipsis      = "...";
  float       ellipsisWidth = MeasureText(ellipsis, fontSize);

  // Loop until the truncated string + ellipsis fits
  while (!truncated.empty() &&
         MeasureText(truncated.c_str(), fontSize) + ellipsisWidth >
             availableWidth)
  {
    truncated.pop_back();
  }

  std::string finalTitle = truncated + ellipsis;
  DrawTextEx(*this->font, finalTitle.c_str(),
             (Vector2){this->rect.x + 5, this->rect.y + 5}, fontSize, 0,
             C_TAB_COLOR_TEXT);
}
