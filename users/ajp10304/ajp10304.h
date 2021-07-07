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
  M_CUSTOM,
  M_WORD_SEL,
  M_WORD_SEL_MAC,
  M_LINE_SEL,
  M_LINE_SEL_MAC,
  M_LINE_DEL,
  M_LINE_DEL_MAC,
  M_DUP,
  M_DUP_MAC,
  M_JOIN,
  M_JOIN_MAC,
  M_MODE,
  M_MODE_MAC
};
