#include QMK_KEYBOARD_H
#include "tetris_text.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _CL 2

enum custom_keycodes {
    TETRIS_START = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = LAYOUT(
  KC_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,  KC_BSPC,          KC_PGUP,
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,                   KC_PGDN,
  KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,
  KC_LSFT, KC_NUBS, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  KC_RO,    KC_RSFT,          KC_UP,
  KC_LCTL, KC_LGUI, KC_LALT, KC_MHEN,          KC_SPC,KC_SPC,                        KC_HENK,  KC_RALT,  KC_RCTL,  MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______, KC_DEL,           BL_STEP,
  _______, _______, _______,_______,_______,F(1)    ,_______,_______,KC_PSCR,KC_SLCK, KC_PAUS,  _______,  _______,  _______,                   _______,
  _______, _______, MO(_CL),_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,          KC_PGUP,
  _______, _______, _______, _______,        _______,_______,                        _______,  _______,  _______,  MO(_FL), KC_HOME, KC_PGDN, KC_END),

  /* Keymap _CL: Control layer
   */
[_CL] = LAYOUT(
  _______, _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______, RGB_TOG,             RGB_VAI,
  _______, _______, _______,_______,RESET,  _______,_______,_______,_______,_______, _______,  _______,  _______,  _______,                   RGB_VAD,
  _______, _______, MO(_CL),_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  _______,
  MO(_FL), _______, _______,_______,_______,_______,_______,_______,_______,_______, _______,  _______,  _______,  MO(_FL),          RGB_SAI,
  _______, _______, _______,_______,        RGB_MOD,   RGB_MOD,                            _______,  _______,  _______,  _______, RGB_HUD,    RGB_SAD,    RGB_HUI),
};

static uint8_t tetris_key_presses = 0;
static uint16_t tetris_timer = 0;
static uint8_t tetris_running = 0;
static int tetris_keypress = 0;

/*
 * Set up tetris
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    tetris_key_presses++;
  }

  if (tetris_running && record->event.pressed) {
    tetris_keypress = 0;
    switch (keycode) {
    case KC_UP: tetris_keypress = 1; break;
    case KC_LEFT: tetris_keypress = 2; break;
    case KC_DOWN: tetris_keypress = 3; break;
    case KC_RIGHT: tetris_keypress = 4; break;
    // Make ESC stop tetris (on keyboards other than clueboard)
    // case KC_ESC: tetris_running = 0; return false;
    }
    if (tetris_keypress != 0) {
      return false;
    }
  }

  switch (keycode) {
    case KC_GESC:
      // clueboard specific hook to make escape quite tetris
      if (tetris_running) {
        tetris_running = 0;
        return false;
      }
      break;
    case TETRIS_START:
      if (record->event.pressed) {
        tetris_running = 1;
        tetris_timer = 0;
        tetris_keypress = 0;
        // set randomness using total number of key presses
        tetris_start(tetris_key_presses);
      }
      return false;
  }

  return true;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  if (tetris_running) {
    tetris_timer++;
    if (tetris_timer > 1000) {
      // every 1000 times this is run is about 100 ms.
      if (!tetris_tick(100)) {
        // game over
        tetris_running = 0;
      }
      tetris_timer = 0;
    }
  }      
}

void tetris_send_up(void) {
  tap_code(KC_UP);
}
void tetris_send_left(void) {
  tap_code(KC_LEFT);
}
void tetris_send_down(void) {
  tap_code(KC_DOWN);
}
void tetris_send_right(void) {
  tap_code(KC_RGHT);
}
void tetris_send_backspace(void) {
  tap_code(KC_BSPC);
}
void tetris_send_delete(void) {
  tap_code(KC_DEL);
}

void tetris_send_string(const char *s) {
  for (int i = 0; s[i] != 0; i++) {
    if (s[i] >= 'a' && s[i] <= 'z') {
      tap_code(KC_A + (s[i] - 'a'));
    } else if (s[i] >= 'A' && s[i] <= 'Z') {
      tap_code16(S(KC_A + (s[i] - 'A')));
    } else if (s[i] >= '1' && s[i] <= '9') {
      tap_code(KC_1 + (s[i] - '1'));
    } else {
      switch (s[i]) {
      case ' ': tap_code(KC_SPACE); break;
      case '.': tap_code(KC_DOT); break;
      case '0': tap_code(KC_0); break;
      }
    }
  }
}

void tetris_send_newline(void) {
  tap_code(KC_ENT);
}

int tetris_get_keypress(void) {
  int out = tetris_keypress;
  tetris_keypress = 0;
  return out;
}
