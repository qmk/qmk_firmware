/*
 * Keyboard: Ergodox
 * Keymap:   replicaJunction
 * Version:  1.2
 *
 * This keymap is designed to complement my Atreus keyboard layout, found in keyboards/atreus.
 * The Atreus keyboard is a 40% board whose design was heavily influenced by the Ergodox, and I now
 * have both keyboards, so I've designed these layouts in an effort to make switching between the
 * two as easy as possible.
 *
 * I've also tried to make use of the extra keys on the Ergodox in as logical of a manner as possible,
 * adding to the layers in the Atreus config without disturbing what's there already. This allows for
 * things like F11-F20, the Application (Menu) key, and better media key placement.
 *
 * The default key layout in this keymap is Colemak-ModDH. Information on that layout can be found
 * here: https://colemakmods.github.io/mod-dh/
 */

#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define _CO 0 // Colemak
#define _QW 1 // QWERTY
#define _ME 2 // media keys
#define _NU 3 // numpad
#define _EX 4 // extend
#define _GA 5 // mouse overlay for gaming

// Some quick aliases, just to make it look pretty
#define _______ KC_TRNS
#define KCX_CGR LCTL(KC_GRV)
#define KX_STAB LSFT(KC_TAB)
#define KX_COPY LCTL(KC_C)
#define KX_CUT  LCTL(KC_X)
#define KX_PAST LCTL(KC_V)
#define KX_UNDO LCTL(KC_Z)

; // This doesn't do anything. It's just for VSCode because its syntax highlighting is weird for the above #define statements.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Keymap: Colemak-ModDH
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   `    |   1  |   2  |   3  |   4  |   5  |  Esc |           |      |   6  |   7  |   8  |   9  |   0  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  LCtrl |   Q  |   W  |   F  |   P  |   B  | Home |           | BkSp |   J  |   L  |   U  |   Y  |   ;  |   -    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |  Tab   |   A  |   R  |   S  |   T  |   G  |------|           |------|   M  |   N  |   E  |   I  |   O  |   '    |
     * |--------+------+------+------+------+------| Hyper|           |  \   |------+------+------+------+------+--------|
     * | LShft  |   Z  |   X  |   C  |   D  |   V  |      |           |      |   K  |   H  |   ,  |   ,  |   /  | RShft  |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | LGui |   [  |   ]  |CtlShf| LAlt |                                       | _EX  |   -  |   '  |   =  |   \  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | LCtrl|  ~GA |       | Left | Right|
     *                                 ,------|------|------|       |------+------+------.
     *                                 |LCtrl/| LAlt/| Home |       |  Up  |  Alt/| _NU/ |
     *                                 | BkSp |  Del |------|       |------| Enter| Space|
     *                                 |      |      | _NU  |       | Down |      |      |
     *                                 `--------------------'       `--------------------'
     */
[_CO] = KEYMAP(
        // left hand
        KC_GRV, KC_1,   KC_2,      KC_3,            KC_4,   KC_5,   KC_ESC,
        KC_LCTL,KC_Q,   KC_W,      KC_F,            KC_P,   KC_B,   KC_HOME,
        KC_TAB, KC_A,   KC_R,      KC_S,            KC_T,   KC_G,
        KC_LSFT,KC_Z,   KC_X,      KC_C,            KC_D,   KC_V,   ALL_T(KC_NO),
        KC_LGUI,KC_LBRC,KC_RBRC,   LCTL(KC_LSFT),   KC_LALT,

                                                                KC_LCTL,        TG(_GA),
                                                                                KC_HOME,
                                                CTL_T(KC_BSPC), ALT_T(KC_DEL),  MO(_NU),
        // right hand
             KC_ESC,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_EQL,
             KC_BSPC,  KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,KC_MINS,
                       KC_M,   KC_N,   KC_E,   KC_I,   KC_O,   KC_QUOT,
             KC_BSLS,  KC_K,   KC_H,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
                               MO(_EX),KC_MINS,KC_QUOT,KC_EQL, KC_BSLS,

        KC_LEFT, KC_RGHT,
        KC_UP,
        KC_DOWN, ALT_T(KC_ENT), LT(_NU,KC_SPC)
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
     * |   `    |   1  |   2  |   3  |   4  |   5  |  Esc |           |      |   6  |   7  |   8  |   9  |   0  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | LCtrl  |   Q  |   W  |   E  |   R  |   T  | Home |           | BkSp |   Y  |   U  |   I  |   O  |   P  |   -    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------| Hyper|           |  \   |------+------+------+------+------+--------|
     * | LShft  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShft  |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | LGui |   `  |  \   |CtlShf| _NU  |                                       |  _EX |   -  |  '   |   =  |   \   |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | LCtrl| ~GA  |       | Left | Right|
     *                                 ,------|------|------|       |------+------+------.
     *                                 |LCtrl/| LAlt/| Home |       |  Up  |  Alt/| _NU/ |
     *                                 | BkSp |  Del |------|       |------| Enter| Space|
     *                                 |      |      | _NU  |       | Down |      |      |
     *                                 `--------------------'       `--------------------'
     */
[_QW] = KEYMAP(  // Layer1: QWERTY
        // left hand
        KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_ESC,
        KC_LCTL,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_HOME,
        KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        KC_LGUI,KC_GRV, KC_SLSH,LCTL(KC_LSFT),  MO(_NU),

                                                                KC_LCTL,TG(_GA),
                                                                        KC_HOME,
                                        CTL_T(KC_BSPC), ALT_T(KC_DEL),  MO(_NU),
        // right hand
        KC_ESC,  KC_6,  KC_7,   KC_8,   KC_9,   KC_0,   KC_EQL,
        KC_BSPC, KC_Y,  KC_U,   KC_I,   KC_O,   KC_P,   KC_MINS,
                 KC_H,  KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
        KC_BSLS, KC_N,  KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
                        MO(_EX),KC_MINS,KC_QUOT,KC_EQL, KC_BSLS,

        KC_LEFT, KC_RGHT,
        KC_UP,
        KC_DOWN, ALT_T(KC_ENT), LT(_NU,KC_SPC)
    ),

    /*
     * Keymap: Numbers and symbols
     *
     * Note that the number keys here are actually numpad keystrokes. This often doesn't matter, but it may be relevant in a few cases.
     * That's why the Num Lock key exists on this layer - just in case.
     *
     * This layer also contains the layout switches.
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |   !  |   @  |   {  |   }  |   &  |      |           |      |   /  |   7  |   8  |   9  |   *  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   #  |   $  |   (  |   )  |   ~  |------|           |------|   |  |   4  |   5  |   6  |   -  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   %  |   ^  |   [  |   ]  |   `  |      |           |      |   \  |   1  |   2  |   3  |   +  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |QWERTY|Colemk|      |      |                                       |   0  |   .  |   =  |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |NumLck| RESET|       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
[_NU] = KEYMAP(
        // left hand
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
        _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR, _______,
        _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_TILD,
        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_GRV,  _______,
        _______, DF(_QW), DF(_CO), _______, _______,

                                                KC_NLCK,RESET,
                                                        _______,
                                        _______,_______,_______,
        // right hand
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, KC_SLSH, KC_P7,   KC_P8,   KC_P9,   KC_PAST, _______,
                 KC_PIPE, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______,
        _______, KC_BSLS, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, _______,
                          KC_P0,   KC_PDOT, KC_EQL,  _______, _______,

       _______, _______,
       _______,
       _______, _______, _______
    ),

    /*
     * Keymap: Extend
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |  F11 |  F12 |  F13 |  F14 |  F15 | Mute |           |      |  F16 |  F17 |  F18 |  F19 |  F20 |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      | Ctrl`|  Vol |           |      | PgUp | Home |  Up  |  End |  Del |        |
     * |--------+------+------+------+------+------|  Up  |           |      |------+------+------+------+------+--------|
     * |        |      |  Gui |  Alt | Ctrl |      |------|           |------| PgDn | Left | Down | Right| BkSp |  Menu  |
     * |--------+------+------+------+------+------|  Vol |           |      |------+------+------+------+------+--------|
     * |        | Undo |  Cut | Copy |      | Paste| Down |           |      |      | ^Tab |  Tab |      |Insert| PrntScr|
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     *
     * Ctrl+` is a keyboard shortcut for the program ConEmu, which provides a Quake-style drop-down command prompt.
     *
     */
[_EX] = KEYMAP(
        // left hand
        _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_MUTE,
        _______, _______, _______, _______, _______, KCX_CGR, KC_VOLU,
        _______, _______, KC_LGUI, KC_LALT, KC_LCTL, _______,
        _______, KX_UNDO, KX_CUT,  KX_COPY, _______, KX_PAST, KC_VOLD,
        _______, _______, _______, _______, _______,

                                                _______,_______,
                                                        _______,
                                        _______,_______,_______,
        // right hand
        _______,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
        _______,  KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  _______,
                  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_MENU,
        _______,  _______, KX_STAB, KC_TAB,  _______, KC_INS,  KC_PSCR,
                           _______, _______, _______, _______, _______,
        _______, _______,
        _______,
        _______, _______, _______
    ),

    /*
     * Keymap: Gaming
     *
     * Provides a mouse overlay for the right hand, and also moves some "gamer friendly" keys to the left, such as space.
     * This layer also removes a lot of dual-role keys, as when gaming, it's nicer not to need to keep track of those.
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
     *   | LCtrl|      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      | ~_GA |       |      |MClick|
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 | Space|      |------|       |------|RClick|LClick|
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
[_GA] = KEYMAP(
        // left hand
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL, _______, _______, _______, _______,

                                        _______,_______,
                                                _______,
                                        KC_SPC, _______,_______,

        // right hand
        _______,  _______, _______, _______, _______, _______, _______,
        _______,  _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______,
                  _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______,
                           _______, _______, _______, _______, _______,
        _______, KC_BTN3,
        _______,
        _______, KC_BTN2, KC_BTN1
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(_NU)                // FN1 - Momentary Layer 1 (Numbers and symbols)
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
    // uint8_t default_layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (layer) {
        case _CO:
            ergodox_right_led_1_on();
            break;
        case _QW:
            ergodox_right_led_2_on();
            break;
        case _NU:
            ergodox_right_led_3_on();
            break;
        case _GA:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
        default:
            // none
            break;
    }

};
