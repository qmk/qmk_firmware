#pragma once
#include QMK_KEYBOARD_H

typedef struct {
  uint16_t keycode;
  uint16_t pressTime;
  uint16_t releaseTime;
} Keystroke;
