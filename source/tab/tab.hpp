#pragma once

#include "raylib.h"

#include <string>
#include <vector>

namespace proj
{

typedef std::vector<std::string> vstring;

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
  int         contentWidth = 0;
  int         id           = -1;
  Rectangle   rect;
  std::string file;
  std::string title;
  TAB_ACTION  action;
  TAB_STATE   state;
  Vector2     scrollOffset;
  vstring     lines;

  Tab(int id, std::string file, std::string title, Rectangle rect)
      : rect(rect), file(file), title(title), action(TAB_ACTION_NONE),
        state(TAB_STATE_DEFAULT), lines()
  {
  }

  void  draw();
  void  getContentWidth();
  void  getLines();
  void  updateState(bool isHoveredByMouse, bool isSelected);
  Color getBackgroundColorFromState();
};

typedef std::vector<Tab> vtab;
}; // namespace proj
