// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMBOLS 1 // symbols
#define MEDIA 2 // media keys

enum {
  TD_BSPC = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   /    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Ctl/Esc|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|  LGui  |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*

[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // Left hand
        KC_EQL,              KC_1,               KC_2,            KC_3,     KC_4,            KC_5,               KC_LEFT,
        KC_SLSH,             KC_QUOT,            KC_COMM,         KC_DOT,   KC_P,            KC_Y,               KC_NO,
        CTL_T(KC_ESC),       KC_A,               KC_O,            KC_E,     KC_U,            KC_I,
        KC_LSPO,             KC_SCLN,            KC_Q,            KC_J,     KC_K,            KC_X,               ALL_T(KC_NO),
        LT(SYMBOLS,KC_GRV),  KC_QUOT,            KC_SLSH,         KC_LALT,  SFT_T(KC_RGHT),
                                                                                             KC_HOME,            KC_END,
                                                                                                                 KC_PGUP,
                                                                            GUI_T(KC_SPC),   TD(TD_BSPC),     LGUI(KC_SPC),

        // Right hand
        KC_RGHT,        KC_6,              KC_7,                KC_8,        KC_9,        KC_0,                LGUI(KC_SPC),
        KC_NO,          KC_F,              KC_G,                KC_C,        KC_R,        KC_L,                LT(MEDIA, KC_BSLS),
                        KC_D,              KC_H,                KC_T,        KC_N,        KC_S,                KC_MINS,
        MEH_T(KC_NO),   KC_B,              KC_M,                KC_W,        KC_V,        KC_Z,                KC_RSPC,
                                           ALT_T(KC_UP),        KC_DOWN,     KC_LBRC,     KC_RBRC,             KC_NO,
        KC_PGUP,        CTL_T(KC_ESC),
        KC_PGDN,
        LCTL(KC_B),     LT(MEDIA, KC_TAB), LT(SYMBOLS, KC_ENT)
    ),


/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS

[SYMBOLS] = LAYOUT_ergodox(
       // left hand
       _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
       _______,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,_______,
       _______,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       _______,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,_______,
       _______,_______,_______,_______,_______,
                                       _______,_______,
                                               _______,
                               _______,_______,_______,
       // right hand
       _______, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       _______, KC_EQL,  KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_MINS, KC_4,   KC_5,    KC_6,    KC_PLUS, _______,
       _______, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_SLSH, _______,
                         _______,KC_0,    KC_DOT,  KC_EQL,  _______,
       _______, _______,
       _______,
       _______, _______, _______
),

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |  ↑   |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|VolUp |   ←  |   ↓  |  →   |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |VolDn | Prev | Play | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       | Mute |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MEDIA] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_MS_U, _______, _______, _______,
       _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_BTN1, KC_BTN2,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, KC_HOME,   KC_UP,  KC_END, KC_PGUP, _______,
                KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_MPLY,
       KC_MUTE, KC_VOLD, KC_MPRV, KC_MPLY, KC_MFFD, _______, _______,
                          _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______,  KC_WBAK
),
};

enum {
  BSPC_LETTER = 0,
  BSPC_WORD = 1,
  HOLD_CTRL = 2
};

typedef struct {
  int a;
  int b;
  int state;
} fib_tap;

static fib_tap fib_bspc = {
  .a = 0,
  .b = 1,
  .state = BSPC_LETTER
};

void cur_backspace (qk_tap_dance_state_t *state) {
  int next_fib = fib_bspc.a + fib_bspc.b;
  fib_bspc.a = fib_bspc.b;
  fib_bspc.b = next_fib;
  for (int i=0; i < next_fib; i++) {
    unregister_code(KC_BSPC);
    register_code(KC_BSPC);
  }
}

void dance_backspace (qk_tap_dance_state_t *state, void *user_data) {
  // If we're at the fifth tap, switch to deleting by words, and reset the fib
  // counter
  if (state->count == 4) {
    register_code(KC_LALT);
    fib_bspc.state = BSPC_WORD;
    fib_bspc.a = 0;
    fib_bspc.b = 1;
  }
  // If we're on the first press, wait to find out if it's being held
  // If we're on the second tap, process the first tap, because we're past
  // holding for ctrl now, then act normally
  if (state->count == 2) {
    register_code(KC_BSPC);
  }
  if (state->count > 1) {
    cur_backspace(state);
  }
};

void dance_backspace_ended (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->pressed) {
      fib_bspc.state = HOLD_CTRL;
      register_code(KC_LCTRL);
    } else {
      register_code(KC_BSPC);
    }
  }
};

void dance_backspace_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (fib_bspc.state) {
    case HOLD_CTRL: unregister_code(KC_LCTRL); break;
    case BSPC_WORD: unregister_code(KC_BSPC); unregister_code(KC_LALT); break;
    case BSPC_LETTER: unregister_code(KC_BSPC); break;
  }
  fib_bspc.a = 0;
  fib_bspc.b = 1;
  fib_bspc.state = BSPC_LETTER;
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_BSPC] = ACTION_TAP_DANCE_FN_ADVANCED (dance_backspace, dance_backspace_ended, dance_backspace_reset)
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

};
