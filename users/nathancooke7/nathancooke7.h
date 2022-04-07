#pragma once
#include QMK_KEYBOARD_H
#include <stdio.h>

#include "features/pointing.h"
#include "process_records.h"

enum userspace_layers{
  _BASE,
  _DRAGSCRL,
  _MOUSE,
  _MOUSE_MAN,
  _MISC,
  _NAV,
  _SYMBOLS,
  _WORDS
};
