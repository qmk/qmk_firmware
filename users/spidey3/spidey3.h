#pragma once

#include QMK_KEYBOARD_H

enum userspace_layers {
  _BASE = 0,
  _OSX,
  _FN,
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
bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
#endif

#ifdef UNICODEMAP_ENABLE
void eeconfig_init_user_unicode(void);
#endif


