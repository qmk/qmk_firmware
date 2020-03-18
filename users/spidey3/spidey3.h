#pragma once

#include QMK_KEYBOARD_H

enum userspace_layers {
  _BASE = 0,
  _OSX,
  _FN,
};

enum rgb_base_layer {
  RGB_LAYER_BASE_DEFAULT = _BASE,
  RGB_LAYER_BASE_REGULAR = _FN,
};

enum custom_keycodes {
  SPI_GLO = SAFE_RANGE,
  SPI_LNX,
  SPI_OSX,
  SPI_WIN,
};

#ifdef RGBLIGHT_ENABLE
void eeconfig_init_user_rgb(void);
void matrix_init_user_rgb(void);
void keyboard_post_init_user_rgb(void);
bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
layer_state_t layer_state_set_user_rgb(layer_state_t state);
layer_state_t default_layer_state_set_user_rgb(layer_state_t state);
bool led_update_user_rgb(led_t led_state);
#endif

#ifdef UNICODEMAP_ENABLE
void eeconfig_init_user_unicode(void);
#endif

