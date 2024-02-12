/*
 * Copyright 2024 João Silva @https://github.com/Ghost-Spot
 *
 * This is an adaptation of several pieces of code
 * I found online, starting from a copy of a sofle,
 * as it as the same layout (minus 2 thumb keys),
 * an OLED and an encoder, on each half.
 *
 * Use this at your own discretion!
 *
 */

#include QMK_KEYBOARD_H
#include "keymap_portuguese.h"

bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

//ALT TAB Encoder Timer
void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      unregister_code(KC_LSHIFT);
      is_alt_tab_active = false;
      is_alt_shift_tab_active = false;
    }
  }
};


enum custom_keycodes {
  ZEROx3 = SAFE_RANGE,
};

/* I'll try with macro's for the encoder, but save this for later
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),           ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),           ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),           ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)}
};
#endif
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  ´   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ç  |  ~   |
 * |------+------+------+------+------+------|WIN+TAB|    |  Play |------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |  º   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(1)  /       \OSL(2)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */

[0] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PSCR,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    PT_ACUT,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    PT_CCED, PT_TILD,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    PT_COMM, PT_DOT,  KC_MINS, PT_MORD,
                    KC_ENT,  KC_SPC,  MO(1),   LGUI(KC_TAB)              KC_MPLY, OSL(2),  KC_BSPC, KC_DEL
),
/*
 * NUMPAD + Navigation
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |NUMLCK|   /  |   *  |   ^  |                    |      |      |      |      |      | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   €  |   7  |   8  |   9  |   -  |                    |      | PGUP |  UP  | PGDN |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   0  |   4  |   5  |   6  |   +  |-------.    ,-------|      | LEFT | DOWN | RIGHT|      |      |
 * |------+------+------+------+------+------|WIN+TAB|    |  Play |------+------+------+------+------+------|
 * | Ctrl |  000 |   1  |   2  |   3  |   .  |-------|    |-------|      | HOME | INSRT|  END |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(0)  /       \OSL(2)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */

[1] = LAYOUT(
  KC_ESC,   ____,   KC_NUM,  KC_PSLS, KC_PAST, S(PT_TILD),               ____,     ____,    ____,     ____,    ____,  KC_PSCR,
  KC_TAB,   PT_EURO,KC_P7,   KC_P8,   KC_P9,   KC_MINS,                  ____,     KC_PGUP, KC_UP,    KC_PGDN, ____,  ____,
  KC_LSFT,  KC_P0,  KC_P4,   KC_P5,   KC_P6,   KC_PLUS,                  ____,     KC_LEFT, KC_DOWN,  KC_RIGHT,____,  ____,
  KC_LCTL,  ZEROx3, KC_P1,   KC_P2,   KC_P3,   PT_DOT,                   ____,     KC_HOME, KC_INSERT,KC_END,  ____,  ____,
                    KC_ENT,  KC_SPC,  MO(0),   LGUI(KC_TAB)              KC_MPLY,  OSL(2),  KC_BSPC,  KC_DEL
),
/* Symbols
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |      |                    |      |      |      |      |      | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |      |   «  |   \  |  [   |                    |   ]  |   /  |   »  |   ¨  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   #  |   @  |   <  |   !  |  (   |-------.    ,-------|   )  |   ?  |   >  |   =  |  |   |      |
 * |------+------+------+------+------+------|WIN+TAB|    |  Play |------+------+------+------+------+------|
 * | Ctrl |      |      |   -  |   "  |  {   |-------|    |-------|   }  |   '  |   _  |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(1)  /       \ MO(0)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */
[2] = LAYOUT(
  KC_ESC,    ____,   ____,      ____,    ____,    ____,                  ____,      ____,       ____,       ____,         ____,       KC_PSCR,
  KC_TAB,    ____,   ____,      PT_LDAQ, PT_BSLS, ALGR(PT_8),            ALGR(PT_9),S(PT_7),    S(PT_LDAQ), ALGR(PT_PLUS),____,       ____,
  KC_LSFT,   S(PT_3),ALGR(PT_2),PT_LABK, S(PT_1), S(PT_8),               S(PT_9),   S(PT_QUOT), S(PT_LABK), S(PT_0),      S(PT_BSLS), ____,
  KC_LCTL,   ____,   ____,      KC_MINS, S(PT_2), ALGR(PT_7),            ALGR(PT_0),PT_QUOT,    S(PT_MINS), ____,         ____,       ____,
                     KC_ENT,    KC_SPC,  MO(1),   LGUI(KC_TAB)           KC_MPLY,   MO(0),      KC_BSPC,    KC_DEL
),
/* F Keys
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |  F10 |  F11 |  F12 |      |                    |      |  F22 |  F23 |  F24 |      | Pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  F7  |  F8  |  F9  |      |                    |      |  F19 |  F20 |  F21 |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|      |  F4  |  F5  |  F6  |      |-------.    ,-------|      |  F16 |  F17 |  F18 |      |      |
 * |------+------+------+------+------+------|WIN+TAB|    |  Play |------+------+------+------+------+------|
 * | Ctrl |      |  F1  |  F2  |  F3  |      |-------|    |-------|      |  F13 |  F14 |  F15 |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | Enter|Space | /MO(1)  /       \OSL(2)\  |Bcksp | Del  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */
[3] = LAYOUT(
  KC_ESC,  ____,   KC_F10, KC_F11, KC_F12, ____,                 ____,    KC_F22, KC_F23,  KC_F24, ____, KC_PSCR,
  KC_TAB,  ____,   KC_F7,  KC_F8,  KC_F9,  ____,                 ____,    KC_F19, KC_F20,  KC_F21, ____, ____,
  KC_LSFT, ____,   KC_F4,  KC_F5,  KC_F6,  ____,                 ____,    KC_F16, KC_F17,  KC_F18, ____, ____,
  KC_LCTL, ____,   KC_F1,  KC_F2,  KC_F3,  ____,                 ____,    KC_F13, KC_F14,  KC_F15, ____, ____,
                   KC_ENT, KC_SPC, MO(1),  LGUI(KC_TAB)          KC_MPLY, OSL(2), KC_BSPC, KC_DEL
)
};

/* Behaviour of the ENCODERS  */

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_highest_layer(layer_state|default_layer_state) == 0) {
        if (index == 0) { // Alt+TAB and Alt+Shift+TAB
            register_code(KC_LALT);
            is_alt_tab_active = true;
            if (clockwise) {
                tap_code(KC_TAB);
            } else {
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT); // this fixes the getting stuck problem
            }
            alt_tab_timer = timer_read();
        } else if (index == 1) {
            if (clockwise) { // Scroll horizontally words
                tap_code(C(KC_LEFT));
            } else {
                tap_code(C(KC_RIGHT));
            }
        }
    } else if (get_highest_layer(layer_state|default_layer_state) == 1) {
        if (index == 0) { // PGUP and PGDN
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        } else if (index == 1) { // Scroll tabs
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(S(C(KC_TAB)));
            }
        }
    } else if (get_highest_layer(layer_state|default_layer_state) == 2) {
        if (index == 0) { // PGUP and PGDN
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        } else if (index == 1) { // Scroll tabs
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(S(C(KC_TAB)));
            }
        }
    } else if (get_highest_layer(layer_state|default_layer_state) == 3) {
        if (index == 0) { // History Scrubbing
            if (clockwise) {
                tap_code(C(KC_Y));
            } else {
                tap_code(C(KC_Z));
            }
        } else if (index == 1) {
            if (clockwise) { // Volume Control
                tap_code16(KC_VOLU);
            } else {
                tap_code16(KC_VOLD);
            }
        }
    }
    return false;
};
