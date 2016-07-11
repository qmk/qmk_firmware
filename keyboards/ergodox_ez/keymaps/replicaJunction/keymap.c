#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

/*
 * Keyboard: Ergodox
 * Keymap:   replicaJunction
 * Version:  1.0
 *
 * This keymap is designed to complement my Atreus keyboard layout, found in keyboards/atreus.
 * The Atreus keyboard is a 40% board whose design was heavily influenced by the Ergodox, and I now
 * have both keyboards, so I've designed these layouts in an effort to make switching between the
 * two as easy as possible.
 *
 * The default key layout in this keymap is Colemak-ModDH. Information on that layout can be found
 * here: https://colemakmods.github.io/mod-dh/
 */

#define BASE 0 // default layer
#define CODH 1 // Colemak
#define QWRT 2 // QWERTY layer
#define SYMB 3 // symbols
#define MDIA 4 // media keys
#define UTIL 5 // keyboard utilities
#define NUMP 6 // numpad
#define GAME 7 // mouse overlay for gaming

#define _______ KC_TRNS // Simple alias that just makes the keymaps a bit easier to look at

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
      * Keymap: Colemak-ModDH
      *
      * ,--------------------------------------------------.           ,--------------------------------------------------.
      * |   `    |   1  |   2  |   3  |   4  |   5  |  Esc |           | ~SYMB|   6  |   7  |   8  |   9  |   0  |   '    |
      * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
      * |   \    |   Q  |   W  |   F  |   P  |   B  | Home |           | BkSp |   J  |   L  |   U  |   Y  |   ;  |   =    |
      * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
      * | Tab    |   A  |   R  |   S  |   T  |   G  |------|           |------|   M  |   N  |   E  |   I  |   O  |   -    |
      * |--------+------+------+------+------+------| Hyper|           |  \   |------+------+------+------+------+--------|
      * | LShft  |   Z  |   X  |   C  |   D  |   V  |      |           |      |   K  |   H  |   ,  |   ,  |   /  | RShft  |
      * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
      *   | LGui |   [  |   ]  |CtlShf| SYMB |                                       | Left |  Up  | Down | Right|   \  |
      *   `----------------------------------'                                       `----------------------------------'
      *                                        ,-------------.       ,-------------.
      *                                        | LCtrl| LAlt |       | MDIA | RAlt |
      *                                 ,------|------|------|       |------+------+------.
      *                                 | Ctl/ | Alt/ | Home |       | PgUp |      | SYMB/|
      *                                 | BkSp |  Del |------|       |------| Enter| Space|
      *                                 |      |      | NUMP |       | PgDn |      |      |
      *                                 `--------------------'       `--------------------'
      */

[CODH] = KEYMAP(
        // left hand
        KC_GRV, KC_1,   KC_2,      KC_3,            KC_4,   KC_5,   KC_ESC,
        KC_BSLS,KC_Q,   KC_W,      KC_F,            KC_P,   KC_B,   KC_HOME,
        KC_TAB, KC_A,   KC_R,      KC_S,            KC_T,   KC_G,
        KC_LSFT,KC_Z,   KC_X,      KC_C,            KC_D,   KC_V,   ALL_T(KC_NO),
        KC_LGUI,KC_LBRC,KC_RBRC,   LCTL(KC_LSFT),   MO(SYMB),

                                                                KC_LCTL,        KC_LALT,
                                                                                KC_HOME,
                                                CTL_T(KC_BSPC), ALT_T(KC_DEL),  MO(NUMP),
        // right hand
             TG(SYMB), KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_QUOT,
             KC_BSPC,  KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,KC_EQL,
                       KC_M,   KC_N,   KC_E,   KC_I,   KC_O,   KC_MINS,
             KC_BSLS,  KC_K,   KC_H,   KC_DOT, KC_COMM,KC_SLSH,KC_RSFT,
                               KC_LEFT,KC_UP,  KC_DOWN,KC_RGHT,KC_BSLS,

        MO(MDIA), KC_RALT,
        KC_PGUP,
        KC_PGDN,  KC_ENT, LT(SYMB,KC_SPC)
    ),

    /*
      * Keymap: Dvorak layout
      *
      * The right index backspace is a nod to my TypeMatrix keyboard, which has
      * Backspace in the center.
      *
      * ,--------------------------------------------------.           ,--------------------------------------------------.
      * |   `    |   1  |   2  |   3  |   4  |   5  |  Esc |           | ~SYMB|   6  |   7  |   8  |   9  |   0  |   /    |
      * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
      * |   \    |   '  |   ,  |   .  |   P  |   Y  | Home |           | BkSp |   F  |   G  |   C  |   R  |   L  |   =    |
      * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
      * | Tab    |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  |   -    |
      * |--------+------+------+------+------+------| Hyper|           |  \   |------+------+------+------+------+--------|
      * | LShft  |   ;  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | RShft  |
      * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
      *   | LGui |   [  |   ]  |CtlShf| SYMB |                                       | Left |  Up  | Down | Right|   \  |
      *   `----------------------------------'                                       `----------------------------------'
      *                                        ,-------------.       ,-------------.
      *                                        | LCtrl| LAlt |       | MDIA | RAlt |
      *                                 ,------|------|------|       |------+------+------.
      *                                 | Ctl/ | Alt/ | Home |       | PgUp |      | SYMB/|
      *                                 | BkSp |  Del |------|       |------| Enter| Space|
      *                                 |      |      | NUMP |       | PgDn |      |      |
      *                                 `--------------------'       `--------------------'
      */

// BASE
[BASE] = KEYMAP(
        // left hand
        KC_GRV, KC_1,   KC_2,      KC_3,            KC_4,   KC_5,   KC_ESC,
        KC_BSLS,KC_QUOT,KC_COMM,   KC_DOT,          KC_P,   KC_Y,   KC_HOME,
        KC_TAB, KC_A,   KC_O,      KC_E,            KC_U,   KC_I,
        KC_LSFT,KC_SCLN,KC_Q,      KC_J,            KC_K,   KC_X,   ALL_T(KC_NO),
        KC_LGUI,KC_LBRC,KC_RBRC,   LCTL(KC_LSFT),   MO(SYMB),

                                                                KC_LCTL,        KC_LALT,
                                                                                KC_HOME,
                                                CTL_T(KC_BSPC), ALT_T(KC_DEL),  MO(NUMP),
        // right hand
             TG(SYMB), KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_SLSH,
             KC_BSPC,  KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_EQL,
                       KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_MINS,
             KC_BSLS,  KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   KC_RSFT,
                               KC_LEFT,KC_UP,  KC_DOWN,KC_RGHT,KC_BSLS,

        MO(MDIA), KC_RALT,
        KC_PGUP,
        KC_PGDN,  KC_ENT, LT(SYMB,KC_SPC)
    ),

    /*
     * Keymap: QWERTY layout.
     *
     * This is optimized for gaming, not typing, so there aren't as many macros
     * as the Dvorak layer. Some of the keys have also been moved to "game-
     * like" locations, such as making the spacebar available to the left thumb,
     * and repositioning the arrow keys at the bottom right corner.
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   `    |   1  |   2  |   3  |   4  |   5  |  Esc |           |~SYMB |   6  |   7  |   8  |   9  |   0  |   -    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | LShift |   Q  |   W  |   E  |   R  |   T  | +L1  |           | BkSp |   Y  |   U  |   I  |   O  |   P  |   ]    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------| FN2  |           | ~L1  |------+------+------+------+------+--------|
     * | LShft  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  Up  | RShft  |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | LCtrl|   `  |  \   |CtlShf| SYMB |                                       | SYMB |  /  | Left  | Down | Right|
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | LCtrl| LAlt |       | MDIA | ~GAME|
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | Home |       | PgUp |      | SYMB/
     *                                 | Space| LAlt |------|       |------| Enter| Space|
     *                                 |      |      | End  |       | PgDn |      |      |
     *                                 `--------------------'       `--------------------'
     */
[QWRT] = KEYMAP(  // Layer1: QWERTY
        // left hand
        KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_ESC,
        KC_LSFT,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_HOME,
        KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        KC_LCTL,KC_GRV, KC_SLSH,LCTL(KC_LSFT),  MO(SYMB),

                                        KC_LCTL,KC_LALT,
                                                KC_HOME,
                                        KC_SPC, KC_LALT, KC_END,
        // right hand
        TG(SYMB), KC_6, KC_7,   KC_8,   KC_9,   KC_0,   KC_RBRC,
        KC_BSPC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_EQL,
                KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_MINS,
        KC_END, KC_N,   KC_M,   KC_COMM,KC_DOT, KC_UP  ,KC_RSFT,
                        MO(SYMB),KC_UP,  KC_LEFT,KC_DOWN,KC_RGHT,

        MO(MDIA),TG(GAME),
        KC_PGUP,
        KC_PGDN,KC_ENT,LT(SYMB,KC_SPC)
    ),

    /*
      * Keymap: Symbol / navigation Layer
      *
      * Inspired by Atreus.
      * Note the two keys on the left thumb cluster. These change the "default" layer between key layouts.
      * The RESET button also resets the Teensy, but note bug #164.
      *
      * ,--------------------------------------------------.           ,--------------------------------------------------.
      * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
      * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
      * |        |   !  |   @  |  Up  |   {  |   }  |      |           |      |      | Home |  Up  |  End |      |   F12  |
      * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
      * |        |   #  |   /  |  |   |   \  |   $  |------|           |------|      | Left | Down | Right|      |        |
      * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
      * |        |   [  |   ]  |   (  |   )  |   &  |      |           |      |      | PgUp |      | PgDn |      |        |
      * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
      *   |      |      |      |      | SYMB |                                       |      |      |      |      |      |
      *   `----------------------------------'                                       `----------------------------------'
      *                                        ,-------------.       ,-------------.
      *                                        |Dvorak|QWERTY|       |      | RESET|
      *                                 ,------|------|------|       |------+------+------.
      *                                 |      |      |Colemk|       |      |      |      |
      *                                 |      |      |------|       |------|      | SYMB |
      *                                 |      |      |      |       |      |      |      |
      *                                 `--------------------'       `--------------------'
      */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
       _______,KC_EXLM,KC_AT,  KC_UP,  KC_LCBR,KC_RCBR,_______,
       _______,KC_HASH,KC_SLSH,KC_PIPE,KC_BSLS,KC_DLR,
       _______,KC_LBRC,KC_RBRC,KC_LPRN,KC_RPRN,KC_AMPR,_______,
       _______,_______,_______,_______,_______,

                                            DF(BASE),DF(QWRT),
                                                     DF(CODH),
                                   _______, _______, _______,

       // right hand
        _______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
        _______,_______,KC_HOME,KC_UP,  KC_END, _______,KC_F12,
                _______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,
        _______,_______,KC_PGUP,_______,KC_PGDN,_______,_______,
                        _______,_______,_______,_______,_______,

        _______, RESET,
        _______,
        _______, _______, _______
),
/* Keymap: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
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
[MDIA] = KEYMAP(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_MS_U, _______, _______, _______,
       _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_BTN1, KC_BTN2,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
        _______,  _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, KC_MPLY,
        _______,  _______, _______, KC_MPRV, KC_MNXT, _______, _______,
                          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
        _______, _______,
        _______,
        _______, _______, KC_WBAK
),

/*
     * Keymap: Number pad.
     *
     * Note that the number keys here are actually numpad keystrokes. This often doesn't matter, but it may be relevant in a few cases.
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |   7  |   8  |   9  |   *  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |------|           |------|      |   4  |   5  |   6  |   +  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |   1  |   2  |   3  |   /  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |   0  |   .  |   0  |   =  |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      | Enter|
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
[NUMP] = KEYMAP(
        // left hand
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,

                                        _______,_______,
                                                _______,
                                        _______,_______,_______,
        // right hand
        _______,_______,_______,_______,_______,_______,_______,
        _______,KC_UP,  KC_P7,  KC_P8,  KC_P9,  KC_PAST,KC_F12,
                KC_DOWN,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,_______,
        _______,KC_AMPR,KC_P1,  KC_P2,  KC_P3,  KC_PSLS,_______,
                        KC_P0,  KC_PDOT,KC_P0,  KC_EQL, _______,

       _______, _______,
       _______,
       _______, _______, KC_PENT
    ),

    /*
     * Keymap: Gaming
     *
     * This is mostly a mouse overlay for the right hand while the left hand uses the QWERTY layout.
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |WhlUp | MsUp |WhlDn |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |------|           |------|      |MsLeft|MsDown|MsRght|      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |MClick|      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      | ~GAME|
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|RClick|LClick|
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
[GAME] = KEYMAP(
        // left hand
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,

                                        _______,_______,
                                                _______,
                                        _______,_______,_______,

        // right hand
        _______,  _______, _______, _______, _______, _______, _______,
        _______,  _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______,
                  _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______,
                           KC_BTN3, _______, _______, _______, _______,
        _______, _______,
        _______,
        _______, KC_BTN2, KC_BTN1
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
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

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case BASE:
            ergodox_right_led_1_on();
            break;
        case QWRT:
            ergodox_right_led_2_on();
        case SYMB:
            ergodox_right_led_3_on();
            break;
        case GAME:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
        default:
            // none
            break;
    }

};
