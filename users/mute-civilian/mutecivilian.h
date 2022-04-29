#pragma once
#include QMK_KEYBOARD_H
#include <stdio.h>

#include "process_records.h"

enum userspace_layers{
  _BASE,
  _MOUSE,
  _MISC,
  _NAV,
  _SYMBOLS,
  _WORDS
};
