#include QMK_KEYBOARD_H

// Macro keys for some apps
#define SLACKUP LALT(LSFT(KC_UP))
#define SLACKDN LALT(LSFT(KC_DOWN))
#define RELOAD  LGUI(KC_R)

enum custom_keycodes {
  PAWFIVE = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    QK_BOOT, PAWFIVE, RELOAD ,
    SLACKUP, KC_UP  , KC_PGUP,
    SLACKDN, KC_DOWN, KC_PGDN
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
        SEND_STRING("+:pawfive:\n");
        return false;
      }
  }

  return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      // Tab right
      tap_code16(LSFT(LGUI(KC_RBRC)));
    } else {
      // Tab left
      tap_code16(LSFT(LGUI(KC_LBRC)));
    }
  }
  else if (index == 1) {
    if (clockwise) {
      // History forward
      tap_code16(LGUI(KC_RBRC));
    } else {
      // History back
      tap_code16(LGUI(KC_LBRC));
    }
  }
    return true;
}
