#pragma once

#include "raylib.h"

#include <string>
#include <vector>

namespace proj
{
const int   C_TAB_MARGIN                    = 10;
const int   C_TAB_HEIGHT                    = 45;
const int   C_TAB_MAX_WIDTH                 = 200;
const Color C_TAB_COLOR_BACKGROUND_DEFAULT  = (Color){0x3E, 0x3B, 0x39, 0xFF};
const Color C_TAB_COLOR_BACKGROUND_HOVERED  = (Color){0x3C, 0x38, 0x36, 0xFF};
const Color C_TAB_COLOR_BACKGROUND_SELECTED = (Color){0x8E, 0xC0, 0x7C, 0xFF};
const Color C_TAB_COLOR_TEXT                = (Color){255, 255, 255, 255};

enum TAB_ACTION
{
  TAB_ACTION_NONE,
  TAB_ACTION_WRITE,
  TAB_ACTION_READ,
  TAB_ACTION_CLOSE,
};

enum TAB_STATE
{
  TAB_STATE_DEFAULT,
  TAB_STATE_HOVERED,
  TAB_STATE_SELECTED,
};

struct Tab
{
  Font                    *font;
  int                      contentWidth;
  int                      id;
  Rectangle                rect;
  std::string              file;
  std::string              title;
  std::vector<std::string> lines;
  TAB_ACTION               action;
  TAB_STATE                state;
  Vector2                  scrollOffset;

  Tab(int id, std::string file, std::string title, Rectangle rect, Font *pfont)
  {
    this->font         = pfont;
    this->contentWidth = 0;
    this->id           = id;
    this->rect         = rect;
    this->file         = file;
    this->title        = title;
    this->lines        = {};
    this->action       = TAB_ACTION_NONE;
    this->state        = TAB_STATE_DEFAULT;
    this->scrollOffset = {};
  }

  void  draw();
  void  getContentWidth();
  void  getLines();
  void  updateState(bool isHoveredByMouse, bool isSelected);
  Color getBackgroundColorFromState();
};
}; // namespace proj
