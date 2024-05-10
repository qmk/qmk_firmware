#include QMK_KEYBOARD_H
#include "version.h"
#ifndef MIDI_ENABLE
#error "Midi is not enabled"
#endif
#define QWERTY 0 // qwerty layer
#define HALFQWERTY 1 // mirrored qwerty layer
#define DVORAK 2 // dvorak layer
#define HALFDVORAK 3 // mirrored dvorak layer
//no layer 4
#define SYMB 5 // symbols
#define HALFSYMB 6 // media keys
#define PLVR 7 // steno plover layout
#define SHORTCUTS 8 //layer with shortcut keys and other layer nav
#define FUNCTION 9 //all F-keys, all day
#define PROPERSTENO 10 //real steno layout

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: qwerty
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  | RMB  |           | \    |   6  |   7  |   8  |   9  |   0  |  BSPC  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  [   |           | ]    |   Y  |   U  |   I  |   O  |   P  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |ENTER   |
 * |--------+------+------+------+------+------| -    |           | =    |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL|ALT  |CTLShTab|CTL-TAB| LGui|                                       |  RGui| UP   | DOWN |  ALT | RCTRL  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Symbol|LMB   |       |Plover|HalfSymb|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |MU_TOG|       | PgUp |        |      |
 *                                 | Space|DELETE|------|       |------|  Tab   |Enter |
 *                                 |mirror|      | End  |       | PgDn |        |mirror|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[QWERTY] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_BTN2,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_EQL,
        KC_BSPC,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,  		  KC_X,   KC_C,   KC_V,   KC_B,   KC_MINUS,
        KC_LCTL, 		KC_LALT,	  LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),  MO(SHORTCUTS),
                                              KC_LGUI,  KC_BTN1,
                                                              MU_ON,
                                         KC_SPACE,KC_DEL,KC_END,
        // right hand
             KC_BTN2,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_BSPC,
             KC_RBRC,    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_SLASH,
                          KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,		   KC_ENT,
             KC_EQL,KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLASH,   	   KC_RSFT,
                                  MO(SHORTCUTS), KC_UP,KC_DOWN,KC_RALT,           KC_RCTL,
             KC_BTN1,        KC_RGUI,
             MU_OFF,
             KC_PGDN,KC_TAB, LT(HALFQWERTY, KC_ENT)
    ),
/* Keymap 1: mirrored qwerty
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  BSPC  |   0  |   9  |   8  |   7  |   6  | \    |           |   `  |   5  |   4  |   3  |   2  |   1  |  ESC  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  '     |   P  |   O  |   I  |   U  |   Y  |  ]   |           |  [   |   T  |   R  |   E  |   W  |   Q  |   TAB  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ENTER  |   ;  |   L  |   K  |   J  |   H  |------|           |------|   G  |   F  |   D  |   S  |   A  | BSPC   |
 * |--------+------+------+------+------+------| -    |           | =    |------+------+------+------+------+--------|
 * | LShift |   /  |   .  |   ,  |   M  |   N  |      |           |      |   B  |   V  |   C  |   X  |   Z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL|ALT  |CTLShTab|CTL-TAB| LGui|                                       |  RGui| UP   | DOWN |  ALT | RCTRL  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|DELETE|------|       |------|  Tab   |Enter |
 *                                 |mirror|      | End  |       | PgDn |        |mirror|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[HALFQWERTY] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_BSPC,        KC_0,         KC_9,   KC_8,   KC_7,   KC_6,   KC_TRNS,
        KC_BSLS,         KC_P,         KC_O,   KC_I,   KC_U,   KC_Y,   KC_LBRC,
        KC_ENT,        KC_SCLN,      KC_L,   KC_K,   KC_J,   KC_H,
        KC_LSFT,        KC_SLASH,  	  KC_DOT, KC_COMM,KC_M,   KC_N,   KC_RBRC,
        KC_LCTL, 		KC_LALT,	   LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),  KC_TRNS,
                                              KC_TRNS,  KC_TRNS,
                                                              KC_TRNS,
                                         KC_TRANSPARENT,KC_DEL,KC_END,
        // right hand
             KC_TRNS,     KC_5,   KC_4,  KC_3,   KC_2,   KC_1,             KC_BSPC,
             KC_MINUS,    KC_T,   KC_R,  KC_E,   KC_W,   KC_Q,             KC_BSLS,
                          KC_G,   KC_F,  KC_D,   KC_S,   KC_A,  		   KC_ENT,
             KC_EQL,KC_B,   KC_V,  KC_C,   KC_X,   KC_Z,		   	   KC_RSFT,
                                  KC_TRNS, KC_UP,KC_DOWN,KC_RALT,           KC_RCTL,
             KC_TRANSPARENT,        KC_TRNS,
             KC_TRNS,
             KC_PGDN,KC_TAB, KC_TRANSPARENT
    ),
/* Keymap 2: dvorak
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  | `    |           | \    |   6  |   7  |   8  |   9  |   0  |  BSPC  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   '  |   ,  |   .  |   P  |   Y  |  [   |           |  ]   |   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  |ENTER   |
 * |--------+------+------+------+------+------| -    |           | =    |------+------+------+------+------+--------|
 * | LShift |   ;  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |  Z   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL|ALT  |CTLShTab|CTL-TAB| LGui|                                       | Mouse| UP   | DOWN |  ALT | RCTRL  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Alt  |      |       |      |Alt   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|DELETE|------|       |------|  Tab   |Enter |
 *                                 |mirror|      | End  |       | PgDn |        |mirror|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[DVORAK] = LAYOUT_ergodox(  // layer 2 : dvorak
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_TRNS,
        KC_TAB,         KC_QUOTE,	  KC_COMM,KC_DOT, KC_P,   KC_Y,   KC_MINUS,
        KC_BSPC,        KC_A,         KC_O,   KC_E,   KC_U,   KC_I,
        KC_LSFT,        KC_SCLN,	  KC_Q,   KC_J,   KC_K,   KC_X,   KC_EQL,
        KC_LCTL, 		KC_LALT,	  LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),  KC_TRNS,
                                              KC_TRNS,  KC_TRANSPARENT,
                                                              KC_UP,
                              LT(HALFDVORAK, KC_SPACE),KC_DEL,KC_DOWN,
        // right hand
             KC_TRNS,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_BSPC,
             KC_LBRC,    KC_F,   KC_G,  KC_C,   KC_R,   KC_L,             KC_SLASH,
                          KC_D,   KC_H,  KC_T,   KC_N,   KC_S,		   KC_ENT,
             KC_RBRC,KC_B,   KC_M,  KC_W,	 KC_V,	 KC_Z,		   	   KC_RSFT,
                                  KC_TRNS, KC_UP,KC_DOWN,KC_RALT,           KC_RCTL,
             KC_TRANSPARENT,        KC_TRANSPARENT,
             KC_PGUP,
             KC_PGDN,KC_TAB, LT(HALFDVORAK, KC_ENT)
    ),
/* Keymap 3: mirrored dvorak
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  BSPC  |   0  |   9  |   8  |   7  |   6  | \    |           | `    |   5  |   4  |   3  |   2  |   1  |  ESC  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   	/   |   L  |   R  |   C  |   G  |   F  |  L1  |           |  L1  |   Y  |   P  |   .  |   ,  |   '  |   TAB  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ENTER  |   S  |   N  |   T  |   H  |   D  |------|           |------|   I  |   U  |   E  |   O  |   A  |BSPC    |
 * |--------+------+------+------+------+------| =    |           | -    |------+------+------+------+------+--------|
 * | LShift |   Z  |   V  |   W  |   M  |   B  |      |           |      |   X  |   K  |   J  |   Q  |   ;  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL|ALT  |CTLShTab|CTL-TAB| LGui|                                       | MOUSE| UP   | DOWN |  ALT | RCTRL  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Alt  |      |       |      |Alt   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|DELETE|------|       |------|  Tab   |Enter |
 *                                 |mirror|      | End  |       | PgDn |        |mirror|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[HALFDVORAK] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_BSPC,         KC_0,         KC_9,   KC_8,   KC_7,   KC_6,   KC_TRNS,
        KC_SLASH,         KC_L,         KC_R,   KC_C,   KC_G,   KC_F,   KC_LBRC,
        KC_ENT,        KC_S,         KC_N,   KC_T,   KC_H,   KC_D,
        KC_LSFT,        KC_Z,  		  KC_V,   KC_W,   KC_M,   KC_B,   KC_RBRC,
        KC_LCTL, 		KC_LALT,	  LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),  KC_TRNS,
                                              KC_TRANSPARENT,  KC_TRANSPARENT,
                                                              KC_TRNS,
                                         KC_TRANSPARENT,KC_ENT,KC_TRNS,
        // right hand
             KC_TRNS,     KC_5,   KC_4,  KC_3,   KC_2,   KC_5,             KC_ESC,
             KC_MINUS,    KC_Y,   KC_P,  KC_DOT, KC_COMM,KC_P,             KC_TAB,
                          KC_I,   KC_U,  KC_E,   KC_O,   KC_A,		 	   KC_BSPC,
             KC_EQL,KC_X,   KC_K,  KC_J,	 KC_Q,   KC_SCLN,	   	   KC_RSFT,
                                  KC_TRNS, KC_UP,KC_DOWN,KC_RALT,           KC_RCTL,
             KC_TRANSPARENT,        KC_TRNS,
             KC_TRNS,
             KC_TRNS,KC_TAB, KC_TRANSPARENT
    ),
/* Keymap 5: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |   F6 |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |BkSp    |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   /  |   \  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   /    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   '  |   ;  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   -  | ENTER  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   -  |   =  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   +  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |mirror|      |------|       |------|      |mirror|
 *                                 |space |      |      |       |      |      |enter |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
       KC_NO,KC_SLASH,KC_BSLS,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_NO,KC_QUOT,KC_SCLN, KC_LPRN,KC_RPRN,KC_GRV,
       KC_NO,KC_MINUS,KC_EQL,KC_LBRC,KC_RBRC,KC_TILD,KC_NO,
          EPRM,KC_NO,KC_NO,KC_NO,KC_TRNS,
                                         KC_TRNS,KC_NO,
                                               KC_NO,
                          LT(HALFSYMB, KC_SPACE),KC_NO,KC_NO,
       // right hand
       KC_F7, KC_F8,   KC_F9,  KC_F10,   KC_F11,   KC_F12,  KC_BSPC,
       KC_NO, KC_UP, KC_KP_7, KC_KP_8,  KC_KP_9,KC_KP_ASTERISK, KC_KP_SLASH,
            KC_DOWN, KC_KP_4, KC_KP_5,  KC_KP_6,  KC_KP_MINUS, KC_KP_ENTER,
       KC_NO,KC_AMPR,KC_KP_1, KC_KP_2,  KC_KP_3,   KC_KP_PLUS, KC_NO,
                         KC_TRNS,KC_DOT,  KC_0,    KC_KP_EQUAL,  KC_NO,
       BL_OFF, KC_TRNS,
       BL_ON,
       KC_NO, KC_NO, LT(HALFSYMB, KC_ENT)
),
/* Keymap 6: Mirrored Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |delete   |  F12 |  F11 |  F10 |  F9  |  F8  |   F7 |           |  F6  |  F5  |  F4  |  F3  |  F2  |  F1  |BkSp    |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |   7  |   8  |   9  |   *  |   /  |           |      |   |  |   {  |   }  |   /  |   \  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |   4  |   5  |   6  |   -  |------|           |------|   `  |   (  |   )  |   ;  |   '  |        |
 * |---------+------+------+------+------+------|enter |           |      |------+------+------+------+------+--------|
 * |         |      |   1  |   2  |   3  |   +  |      |           |      |   ~  |   [  |   ]  |   =  |   -  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |   0  |  .   |  =   |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[HALFSYMB] = LAYOUT_ergodox(
       // left hand
       KC_BSPC,   KC_F13,    KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,
       KC_NO,KC_NO,KC_KP_7, KC_KP_8, KC_KP_9,KC_KP_ASTERISK,KC_KP_SLASH,
       KC_ENTER,KC_NO,KC_KP_4, KC_KP_5, KC_KP_6,KC_KP_MINUS,
       KC_NO,KC_NO,KC_KP_1, KC_KP_2, KC_KP_3,KC_KP_PLUS,KC_KP_ENTER,
          EPRM,KC_NO,KC_KP_0,KC_KP_DOT,KC_KP_EQUAL,
                                         KC_TRNS,KC_NO,
                                               KC_TRNS,
                          KC_TRANSPARENT,KC_NO,KC_NO,
       // right hand
       KC_F19, KC_F20,   KC_F21,  KC_F22,   KC_F23,   KC_F24,  KC_BSPC,
       KC_NO,KC_PIPE,KC_LCBR,KC_RCBR, KC_SLASH, KC_BSLS, KC_NO,
             KC_GRV,KC_LPRN,KC_RPRN,  KC_SCLN, KC_QUOT, KC_NO,
       KC_NO, KC_TILD,KC_LBRC,KC_RBRC, KC_EQL,  KC_MINUS, KC_NO,
                         KC_TRNS,KC_NO,  KC_NO,    KC_NO,  KC_NO,
       KC_NO, KC_TRNS,
       KC_TRNS,
       KC_NO, KC_NO, KC_TRANSPARENT
),
/* Keymap 7: Steno for Plover from https://github.com/shayneholmes/tmk_keyboard/commit/11290f8489013018f778627db725160c745e75bd
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |  6   |  7   |   8  |   9  |  0   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   q  |   w  |   e  |   r  |   t  |------|           |------|  y   |  u   |   i  |   o  |  p   |   [    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   a  |   s  |   d  |   f  |   g  |      |           |      |  h   |  j   |   k  |   l  |  ;   |   '    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |   c  |   v  |------|       |------|  n   |  m   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

[PLVR] = LAYOUT_ergodox(  // layout: layer 7: Steno for Plover
        // left hand
        KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
        KC_NO,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_TRNS,
        KC_NO,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,
        KC_NO,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_NO,
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
                                      KC_TRNS, KC_TRNS,
                                           KC_NO,
                                 KC_C,   KC_V,   KC_NO,
        // right hand
             KC_TRNS,  KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_TRNS,
             KC_TRNS,   KC_6,    KC_7,    KC_8,   KC_9,    KC_0,   KC_TRNS,
                        KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    KC_LBRC,
               KC_NO,   KC_H,    KC_J,    KC_K,   KC_L, KC_SCLN,   KC_QUOT,
                              KC_TRNS, KC_TRNS,  KC_NO,   KC_NO,     KC_NO,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_NO,  KC_N,   KC_M
),

/* Keymap 8: shortcuts
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |  BSPC  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |ENTER   |
 * |--------+------+------+------+------+------| -    |           | =    |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL|ALT  |CTLShTab|CTL-TAB|     |                                       |  RGui| UP   | DOWN |  ALT | RCTRL  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |SYMBOLS|Dvorak|       |Steno |Plover|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|DELETE|------|       |------|  Tab   |Enter |
 *                                 |mirror|      | End  |       | PgDn |        |mirror|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[SHORTCUTS] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        RGB_MODE_KNIGHT,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_TAB,   LCTL(KC_Q),   LCTL(KC_W),LCTL(KC_E),LCTL(KC_R),LCTL(KC_T),   KC_NO,
        KC_BSPC,  LCTL(KC_A),   LCTL(KC_S),LCTL(KC_D),LCTL(KC_F),LCTL(KC_G),
        KC_LSFT,  LCTL(KC_Z),  	LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),LCTL(KC_B),   KC_MINUS,
        QK_BOOT, 		KC_LALT,	  LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),  KC_TRANSPARENT,
                                              TG(SYMB),  TG(DVORAK),

                                                              TG(FUNCTION),
                                         KC_NO,KC_NO,KC_NO,
// right hand
             KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_BSPC,
             TG(SYMB),LCTL(KC_Y),LCTL(KC_U),LCTL(KC_I),LCTL(KC_O),LCTL(KC_P),KC_BSLS,
                          LCTL(KC_H),LCTL(KC_J),LCTL(KC_K),LCTL(KC_L),LCTL(KC_SCLN),KC_ENT,
             KC_EQL,LCTL(KC_N),LCTL(KC_M),LCTL(KC_COMM),LCTL(KC_DOT),LCTL(KC_SLASH),KC_RSFT,
                                  KC_TRNS, KC_UP,KC_DOWN,KC_RALT,           QK_BOOT,
             TG(PROPERSTENO),TG(PLVR),
             KC_NO,
             KC_NO,KC_NO, KC_NO
    ),
    /* Keymap 9: Functions
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    F1  |  F2  |  F3  |  F4  |  F5  |   F6 |      |           |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  F7    |  F8  |  F9  |  F10 |  F11 |  F12 |      |           |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  F13   |  F14 |  F15 |  F16 |  F17 |  F18 |------|           |------|  F13 |  F14 |  F15 |  F16 |  F17 |  F18   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  F19   |  F20 |  F21 |  F22 |  F23 |  F24 |      |           |      |  F19 |  F20 |  F21 |  F22 |  F23 |  F24   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |   c  |   v  |------|       |------|  n   |  m   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

[FUNCTION] = LAYOUT_ergodox(  // layout: layer 9
        // left hand
        KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_NO,
        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,
        KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,
        KC_F19,  KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,   KC_NO,
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,
                                      KC_TRNS, KC_TRNS,
                                           KC_TRNS,
                                 KC_NO,   KC_NO,   KC_NO,
        // right hand
             KC_TRNS,  KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
             KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
                     KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,
               KC_NO,KC_F19,  KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,
                              KC_TRNS, KC_TRNS,  KC_NO,   KC_NO,     KC_NO,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_NO,  KC_NO,   KC_NO
),
    /* Keymap 10: Steno
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |  6   |  7   |   8  |   9  |  0   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   q  |   w  |   e  |   r  |   t  |------|           |------|  y   |  u   |   i  |   o  |  p   |   [    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   a  |   s  |   d  |   f  |   g  |      |           |      |  h   |  j   |   k  |   l  |  ;   |   '    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |   c  |   v  |------|       |------|  n   |  m   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

[PROPERSTENO] = LAYOUT_ergodox(  // layout: layer 10
        // left hand
        KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
        STN_N1, STN_N2, STN_N3, STN_N4, STN_N5, STN_N6, KC_NO,
        STN_FN, STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,
        KC_NO,  STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,   KC_NO,
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,
                                      KC_TRNS, KC_TRNS,
                                           KC_TRNS,
                                 STN_A,   STN_O,   KC_NO,
        // right hand
             KC_TRNS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
             KC_TRNS, STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,   STN_NC,
                     STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,   STN_DR,
               KC_NO,STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,   STN_ZR,
                              KC_TRNS, KC_TRNS,  KC_NO,   KC_NO,     KC_NO,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_NO,  STN_E,   STN_U
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
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
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
