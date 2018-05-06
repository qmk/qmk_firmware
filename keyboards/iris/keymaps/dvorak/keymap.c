#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Colours
#define rgblight_set_blue        rgblight_sethsv (0xFF,  0xFF, 0xFF);
#define rgblight_set_red         rgblight_sethsv (0x00,  0xFF, 0xFF);
#define rgblight_set_green       rgblight_sethsv (0x78,  0xFF, 0xFF);
#define rgblight_set_orange      rgblight_sethsv (0x1E,  0xFF, 0xFF);
#define rgblight_set_teal        rgblight_sethsv (0xC3,  0xFF, 0xFF);
#define rgblight_set_magenta     rgblight_sethsv (0x12C, 0xFF, 0xFF);
#define rgblight_set_yellow      rgblight_sethsv (0x3C,  0xFF, 0xFF);
#define rgblight_set_purple      rgblight_sethsv (0x10E, 0xFF, 0xFF);
#define rgblight_set_white       rgblight_sethsv (0x00,  0x00, 0xFF);

// Layers
#define _DVORAK 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
	DVORAK = SAFE_RANGE,
	LOWER,
	RAISE,
	ADJUST
};

// Keycodes
#define KC_LOWERSPACE LT(_LOWER, KC_SPACE)
#define KC_RAISESPACE LT(_RAISE, KC_SPACE)

// Tap dance sequences
enum {
  SHIFT_CAPS = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSHIFT, KC_CAPSLOCK)
};

// State variables
bool state_is_shift_held = false;
bool state_is_caps_lock = false;
static uint32_t state_current = 0;

#include "dist/_keymap.c"

uint32_t layer_state_set_user(uint32_t state) {
  state_current = state;

  if (state_is_caps_lock) {
    rgblight_set_red;
    return state;
  }

  if (state_is_shift_held) {
    rgblight_set_yellow;
    return state;
  }

  switch (biton32(state)) {

    case _LOWER:
      rgblight_set_orange;
      break;

    case _RAISE:
      rgblight_set_teal;
      break;

    default:
      //rgblight_disable();
      rgblight_set_white;
      rgblight_mode(1);
      break;

  }

  return state;
}

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    state_is_caps_lock = true;
  }else{
    state_is_caps_lock = false;
  }
  layer_state_set_user(state_current);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case KC_LSHIFT:
    case TD(SHIFT_CAPS):
      if (record->event.pressed) {
        state_is_shift_held = true;
      } else {
        state_is_shift_held = false;
      }
      break;

  }

  // Trigger layer state change for all keys, so modifier keys
  // and caps lock can trigger backlight changes.
  layer_state_set_user(state_current);

  return true;
}
