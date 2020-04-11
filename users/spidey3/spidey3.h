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

enum custom_keycodes {
  SPI_GLO = SAFE_RANGE,
  SPI_LNX,
  SPI_OSX,
  SPI_WIN,
};

#ifdef RGBLIGHT_ENABLE

enum layer_base {
  LAYER_BASE_DEFAULT = _BASE,
  LAYER_BASE_REGULAR = _NUMPAD,
  LAYER_BASE_END     = _FN+1,
};

#define RGB_LAYER_ACK_DURATION 500
#define RGB_LAYER_WELCOME_DURATION 750

void eeconfig_init_user_rgb(void);
void matrix_init_user_rgb(void);
void keyboard_post_init_user_rgb(void);
bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void post_process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_user_rgb(layer_state_t state);
layer_state_t default_layer_state_set_user_rgb(layer_state_t state);
bool led_update_user_rgb(led_t led_state);
void rgb_layer_ack(bool yn);
void clear_rgb_layers(void);
#endif

#ifdef UNICODEMAP_ENABLE
void eeconfig_init_user_unicode(void);
#endif

