#pragma once
#include QMK_KEYBOARD_H

extern bool is_win;

enum custom_keycodes_art {
  CTRL_CTV = SAFE_RANGE,

  TOG_OS,

  NEW_SAFE_RANGE  //use "NEW_SAFE_RANGE" for keymap specific codes
};