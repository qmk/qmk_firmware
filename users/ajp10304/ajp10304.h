#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_uk.h"
#include QMK_KEYBOARD_H

enum ajp10304_layers {
  _QWERTY,
  _MAC,
  _LOWER,
  _MLWR,
  _RAISE,
  _MRSE,
  _FUNC,
  _MFNC,
  _FUNC2,
  _MFNC2,
  _ADJUST,
  _MOUSE,
  _NUMPAD
};

enum ajp10304_keycodes {
  QWERTY = SAFE_RANGE,
  MAC,
  FUNC,
  MFNC,
  FUNC2,
  MFNC2,
  LOWER,
  MLWR,
  RAISE,
  MRSE,
  MOUSE,
  NUMPAD,
  DYNAMIC_MACRO_RANGE
};
