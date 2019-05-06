#include QMK_KEYBOARD_H

// Fillers to make layering more clear
#define _______ KC_TRNS
#define _LAYER_ KC_TRNS
#define XXXXXXX KC_NO

// Macro keys for some apps
#define SLACKUP LALT(LSFT(KC_UP))
#define SLACKDN LALT(LSFT(KC_DOWN))
#define RELOAD  LGUI(KC_R)

enum {
  PAWFIVE = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    RESET  , PAWFIVE, RELOAD , \
    SLACKUP, KC_UP  , KC_PGUP, \
    SLACKDN, KC_DOWN, KC_PGDN \
  ),
};

void keyboard_post_init_user(void) {
    // Call the post init code.
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL); // sets mode to Slow breathing without saving
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PAWFIVE:
      if (record->event.pressed) {
        SEND_STRING("+:pawfive:");
        return false;
      }
  }

  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      // Tab right
      register_code(KC_LGUI);
      register_code(KC_LSFT);
      tap_code(KC_RBRC);
      clear_keyboard();
    } else {
      // Tab left
      register_code(KC_LGUI);
      register_code(KC_LSFT);
      tap_code(KC_LBRC);
      clear_keyboard();
    }
  }
  else if (index == 1) {
    if (clockwise) {
      // History forward
      register_code(KC_LGUI);
      tap_code(KC_RBRC);
      clear_keyboard();
    } else {
      // History back
      register_code(KC_LGUI);
      tap_code(KC_LBRC);
      clear_keyboard();
    }
  }
}
