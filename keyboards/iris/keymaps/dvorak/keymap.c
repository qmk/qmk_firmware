#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// TODO: UNICODEMAP_ENABLE , make emoji layer
// TODO: Leader keys
// TODO: shift to be held on tap

#define _DVORAK 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
	DVORAK = SAFE_RANGE,
	LOWER,
	RAISE,
	ADJUST
};

#include "dist/_keymap.c"

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      return false;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      return false;

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;

  }
  return true;
}

#define rgblight_set_blue        rgblight_sethsv (0xFF,  0xFF, 0xFF);
#define rgblight_set_red         rgblight_sethsv (0x00,  0xFF, 0xFF);
#define rgblight_set_green       rgblight_sethsv (0x78,  0xFF, 0xFF);
#define rgblight_set_orange      rgblight_sethsv (0x1E,  0xFF, 0xFF);
#define rgblight_set_teal        rgblight_sethsv (0xC3,  0xFF, 0xFF);
#define rgblight_set_magenta     rgblight_sethsv (0x12C, 0xFF, 0xFF);
#define rgblight_set_yellow      rgblight_sethsv (0x3C,  0xFF, 0xFF);
#define rgblight_set_purple      rgblight_sethsv (0x10E, 0xFF, 0xFF);
#define rgblight_set_white       rgblight_sethsv (0x00,  0x00, 0xFF);

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_disable();
#endif
}

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (biton32(state)) {
    case _RAISE:
      rgblight_set_blue;
      rgblight_enable();
      break;
    case _LOWER:
      rgblight_set_orange;
      rgblight_enable();
      break;
    case _ADJUST:
      rgblight_set_green;
      rgblight_enable();
      break;
    default: //  for any other layers, or the default layer
      rgblight_disable();
      break;
    }
#endif
  return state;
}
