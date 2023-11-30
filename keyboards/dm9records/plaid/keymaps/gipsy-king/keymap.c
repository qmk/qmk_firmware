/* Copyright 2020 Benjamin Große <ste3ls@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum plaid_layers {
  _QWERTY,
  _XMONAD,
  _RAISE,
  _LOWER,
};

enum plaid_keycodes {
  AUTOCLICK = SAFE_RANGE
};

static bool autoclick = false;
static bool autoclick_state = false;
static uint16_t autoclick_timer = 0;

#define XMONAD LM(_XMONAD, MOD_LGUI)
#define SPC_LWR LT(_LOWER, KC_SPACE)
#define ENT_RSE LT(_RAISE, KC_ENT)
#define LOWER LT(_LOWER, KC_BSPC)

#define LS_ESC LSFT_T(KC_ESC)
#define RS_QUOT RSFT_T(KC_QUOT)

#define LCT_MINS LCTL_T(KC_MINS)
#define RCT_EQL RCTL_T(KC_EQL)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Bckspc|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   -  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |XMONAD|LShift|    Space    |Ent/RA|RShift|LOWER | RAlt |RCtrl |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_plaid_grid( // Base QWERTY
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    LS_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RS_QUOT,
    LCT_MINS,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RCT_EQL,
    KC_LCTL, KC_LALT, KC_LGUI, XMONAD,  SC_LSPO, KC_SPACE,_______, ENT_RSE, SC_RSPC, LOWER,   KC_RALT, KC_RCTL
),

[_XMONAD] = LAYOUT_plaid_grid( // Xmonad with MOD4
    KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_P,    _______,
    KC_LSFT, _______, _______, _______, _______, _______, KC_H,    KC_J,    KC_K,    KC_L,    _______, _______,
    KC_LSFT, _______, _______, KC_C,    _______, KC_B,    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_ENT,  _______, _______, _______, _______
),

/* Raised
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   {  | PgUp | PgDn |  End | Home | Left | Down |  Up  | Right|  }   |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   [  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  ]   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |VolDn |VolUp |Mute  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_plaid_grid( // Numbers, arrows, symbols
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
    KC_TILD, KC_LCBR, KC_PGUP, KC_PGDN, KC_END,  KC_HOME, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCBR, KC_PIPE,
    KC_LBRC, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_RBRC,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE
),

[_LOWER] = LAYOUT_plaid_grid( // F, media keys, reset
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, MU_NEXT, AU_ON,   AU_OFF,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, QK_BOOT,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, AUTOCLICK
)
};

#define BLINKEN_RANDOM_STARTLE false
static uint16_t blinken_timer = 0;
static uint16_t next_timeout = 1000;
enum blinken_modes {
  BLINK_HOLD,
  BLINK_STARTLED,
  BLINK_STARTLED_LAYER
};
static uint16_t blinken_mode = BLINK_HOLD;
static uint16_t blinken_timer_startled = 0;
static uint16_t blinken_startled_state = 0;

void matrix_init_user(void) {
  // https://github.com/hsgw/plaid/issues/15#issuecomment-534677102
  eeconfig_init();
}

void keyboard_post_init_user(void) {
  writePinHigh(LED_RED);
  writePinHigh(LED_GREEN);
  blinken_timer = timer_read();
}

void matrix_scan_user(void) {
  if (blinken_mode != BLINK_STARTLED_LAYER && timer_elapsed(blinken_timer) > next_timeout) {
    blinken_timer = timer_read();
    if (BLINKEN_RANDOM_STARTLE && rand() % 5 == 0) {
      blinken_mode = BLINK_STARTLED;
      blinken_timer_startled = timer_read();
      blinken_startled_state = 0;
    } else {
      blinken_mode = BLINK_HOLD;

      if(rand() % 2 == 0) {
        next_timeout = 1000;
      } else if(rand() % 2 == 0) {
        next_timeout = 500;
      } else {
        next_timeout = 300;
      }

      if(rand() % 2 == 0) {
        writePinLow(LED_RED);
      } else {
        writePinHigh(LED_RED);
      }
      if(rand() % 2 == 0) {
        writePinLow(LED_GREEN);
      } else {
        writePinHigh(LED_GREEN);
      }
    }
  } else if ((blinken_mode == BLINK_STARTLED || blinken_mode == BLINK_STARTLED_LAYER)
      && timer_elapsed(blinken_timer_startled) > 50) {
      blinken_timer_startled = timer_read();
      switch (blinken_startled_state) {
        case 0:
          writePinLow(LED_GREEN);
          blinken_startled_state += 1;
          break;
        case 1:
          writePinHigh(LED_RED);
          blinken_startled_state += 1;
          break;
        case 2:
          writePinHigh(LED_GREEN);
          blinken_startled_state += 1;
          break;
        case 3:
          writePinLow(LED_RED);
          blinken_startled_state = 0;
          break;
      }
  }
  if (autoclick && timer_elapsed(autoclick_timer) > (autoclick_state ? 20 : 100)) {
    if (!autoclick_state) {
      mousekey_on(KC_MS_BTN1);
    } else {
      mousekey_off(KC_MS_BTN1);
    }
    mousekey_send();
    autoclick_state = !autoclick_state;
    autoclick_timer = timer_read();
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
  case _RAISE:
      blinken_mode = BLINK_STARTLED_LAYER;
      break;
  case _XMONAD:
      blinken_mode = BLINK_STARTLED_LAYER;
      break;
  case _LOWER:
      blinken_mode = BLINK_STARTLED_LAYER;
      break;
  default:
      blinken_mode = BLINK_HOLD;
      break;
  }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case AUTOCLICK:
        if (record->event.pressed) {
            autoclick = !autoclick;
            autoclick_timer = timer_read();
        }
        break;
    }
    return true;
};
