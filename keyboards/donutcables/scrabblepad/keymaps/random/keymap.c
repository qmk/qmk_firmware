#include QMK_KEYBOARD_H
#include <stdlib.h>

static uint16_t keystroke;
static bool shift_pressed;

static int lower = (int) KC_A;
static int upper = (int) KC_Z;

uint16_t random_keycode(void) {
  return lower + (rand() % (upper - lower + 1));
};

enum custom_keycodes {
  RND_KEY = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case RND_KEY:
      if (record->event.pressed) {
        keystroke = random_keycode();
        if (rand() % 2 > 0) {
          shift_pressed = 1;
          register_code(KC_LSFT);
        }
        register_code(keystroke);
      } else {
        if (shift_pressed > 0) {
          unregister_code(KC_LSFT);
        }
        unregister_code(keystroke);
      }

      return false;

    default:
        return true;
  }

  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT( /* Base */
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, QK_BOOT, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY,
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY
),
};
