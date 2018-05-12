#ifndef USERSPACE
#define USERSPACE

#include QMK_KEYBOARD_H
#include "action_layer.h"

#define X_____X KC_NO

bool process_record_xtonhasvim(uint16_t keycode, keyrecord_t *record);

enum xtonhasvim_keycodes {
  DUMMY = SAFE_RANGE,
  VIM_START, // bookend for vim states
  VIM_A,
  VIM_B,
  VIM_C,
  VIM_CI,
  VIM_D,
  VIM_DI,
  VIM_E,
  VIM_H,
  VIM_G,
  VIM_I,
  VIM_J,
  VIM_K,
  VIM_L,
  VIM_O,
  VIM_P,
  VIM_S,
  VIM_U,
  VIM_V,
  VIM_VS, // visual-line
  VIM_VI,
  VIM_W,
  VIM_X,
  VIM_Y,
  VIM_PERIOD, // to support indent/outdent
  VIM_COMMA,  // and toggle comments
  VIM_SHIFT, // avoid side-effect of supporting real shift.
  VIM_ESC, // bookend
  VIM_SAFE_RANGE // start other keycodes here.
};

enum xtonhasvim_layers {
  _EDIT = 12,
  _CMD
};


#endif
