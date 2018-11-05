#include "scrabblepad.h"
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
          register_code(KC_LSHIFT);
        }
        register_code(keystroke);
      } else {
        if (shift_pressed > 0) {
          unregister_code(KC_LSHIFT);
        }
        unregister_code(keystroke);
      }

      return false;

    default:
        return true;
  }

  return true;
}

// This layout is supposed to work with the Teensy controller pointing
// to the side
// left 6 columns are Workman layout mirrored (rotate the board around)
// right 6 columns are dvorak layout
// middle three columns are for RGB control and other system functions

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT( /* Base */
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RESET, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, \
  RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY, RND_KEY
),
};


const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
