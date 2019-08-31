#pragma once
#include "ninjonas.h"

enum custom_keycodes {
  // Layer Macros
  QWERTY = SAFE_RANGE,
  DVORAK,
  COLEMAK,
  // Custom Macros
  M_ZOOM,
  M_PYNV,
  M_SHFT,
  M_MAKE,
  M_FLSH,
  M_VRSN,
  M_CODE,
};

#ifdef SSD1306OLED
void set_keylog(uint16_t keycode, keyrecord_t *record);
#endif

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
