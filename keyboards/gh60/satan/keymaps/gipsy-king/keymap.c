#include QMK_KEYBOARD_H
#include "rgblight.h"

enum layer_names {
  _BL,
  _FL
};

/**
 * HHKB style.
 * Esc on capslock, space-hold is fn.
 * Fn layer has hjkl arrows, home on backspace, rgb stuff.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_60_ansi(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
    _______, KC_LCTL, KC_LALT,                            LT(_FL,KC_SPC),                     KC_LGUI, KC_RALT, KC_RCTL, _______
  ),

  [_FL] = LAYOUT_60_ansi(
    QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME,
    RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_DOWN, BL_UP,   BL_TOGG,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
    _______,          RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______,          _______,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______
  )
};

/**
 * Terminal Prompt
 * Mimicks a terminal prompt. On keystrokes, the led bar is filled. Backspace
 * removes from bar. Enter clears bar. After some timeout, the bar is also cleared.
 * A blinking cursor is displayed at the right of the bar.
 * This can't be defined as an animation, because animations only are called on an
 * interval, not on keypress. In the future all animations could be enhanced to
 * react to keystrokes in QMK.
 */

uint8_t cursor_pos;

uint16_t interval_time = 10; // maybe too short...
uint16_t reset_time = 10000;
uint16_t last_timer = 0;
uint16_t timer_pos = 0;
uint16_t reset_timer = 0;

void reset_chars(void);
void add_char(bool space);
void remove_char(void);
void animate_cursor(uint16_t);

// animate, like the built-in animations, with timer_* functions
void matrix_scan_user(void) {
  if (timer_elapsed(reset_timer) > reset_time) {
      reset_chars();
      reset_timer = timer_read();
      return;
  }
  if (timer_elapsed(last_timer) < interval_time) {
    return;
  }
  last_timer += interval_time;
  timer_pos += 4;
  if (timer_pos >= 255) {
    timer_pos = 0;
    last_timer = timer_read();
  }
  animate_cursor(timer_pos);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }
  switch (keycode) {
    case KC_A ... KC_Z:
    case KC_1 ... KC_0:
    case KC_LBRC:
    case KC_RBRC:
    case KC_SCLN:
    case KC_QUOT:
    case KC_COMM:
    case KC_DOT:
    case KC_SLSH:
    case KC_BSLS:
      if (record->event.pressed) {
        add_char(false);
      }
      break;
    case KC_ENTER:
    case KC_ESC:
      if (record->event.pressed) {
        reset_chars();
      }
      break;
    case KC_BSPC:
      if (record->event.pressed) {
        remove_char();
      }
      break;
    case KC_SPACE:
      if (!record->event.pressed) {
        add_char(true);
      }
      break;
  }
  reset_timer = timer_read();
  return true;
}

void keyboard_post_init_user(void) {
  // reset the bar and animation
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  cursor_pos = 0;
  reset_chars();
  reset_timer = last_timer = timer_read();
}


void reset_chars(void) {
  // flush the whole thing, gets rid of previous animations
  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    // don't flicker the cursor if bar was empty on reset_timer
    if (i == 0 && cursor_pos == 0) {
        continue;
    }
    rgblight_sethsv_at(0, 0, 0, i);
  }
  cursor_pos = 0;
}

void add_char(bool space) {
  if (cursor_pos == RGBLED_NUM - 1) {
    cursor_pos = 0;
    reset_chars();
    return;
  }

  if (space) {
    rgblight_sethsv_at(0, 0, 0, cursor_pos);
  } else {
    rgblight_sethsv_at(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), cursor_pos);
  }
  cursor_pos += 1;
}

void remove_char(void) {
  if (cursor_pos == 0) return;

  rgblight_sethsv_at(0, 0, 0, cursor_pos);
  rgblight_sethsv_at(0, 0, 0, cursor_pos - 1);
  cursor_pos -= 1;
}

void animate_cursor(uint16_t pos) {
  uint16_t value = pos < 196 ? fmin(255, pos * 16) : (255 - (pos * 2));
  rgblight_sethsv_at(rgblight_get_hue(), rgblight_get_sat(), value, cursor_pos);
}
