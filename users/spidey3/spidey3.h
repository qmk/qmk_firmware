#pragma once

#include QMK_KEYBOARD_H

#ifdef UNICODEMAP_ENABLE
#include "unicode.h"
#endif

enum userspace_layers {
  _BASE = 0,
  _OSX,
  _NUMPAD,
  _FN,
};

enum rgb_base_layer {
  RGB_LAYER_BASE_DEFAULT = _BASE,
  RGB_LAYER_BASE_REGULAR = _NUMPAD,
  RGB_LAYER_BASE_ACKS = _FN+1,
};

enum custom_keycodes {
  SPI_GLO = SAFE_RANGE,
  SPI_LNX, // Mode: Linux
  SPI_OSX, // Mode: Mac
  SPI_WIN, // Mode: Windows
  AL_CTRL, // AL Control Panel
  AL_ASST, // AL Context-aware Desktop Assistant
};

#ifdef RGBLIGHT_ENABLE
void eeconfig_init_user_rgb(void);
void matrix_init_user_rgb(void);
void keyboard_post_init_user_rgb(void);
bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_user_rgb(layer_state_t state);
layer_state_t default_layer_state_set_user_rgb(layer_state_t state);
bool led_update_user_rgb(led_t led_state);
void clear_rgb_layers(void);
#endif

#ifdef UNICODEMAP_ENABLE
void eeconfig_init_user_unicode(void);
#endif

