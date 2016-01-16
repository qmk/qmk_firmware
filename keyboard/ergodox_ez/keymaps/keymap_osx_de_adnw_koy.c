// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_extras/keymap_german.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define ADNW 3 // media keys
#define NUMB 4 // number keys



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  |CMD-V |           |CMD-C |   6  |   7  |   8  |   9  |   0  |   ß    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   Q  |   W  |   E  |   R  |   T  | CMD  |           | CMD  |   Z  |   U  |   I  |   O  |   P  |   ü    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  ADNW  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ö  |  ä/L2  |
 * |--------+------+------+------+------+------| LALT |           | RALT |------+------+------+------+------+--------|
 * | LShift |Y/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |-/Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |</L1|  ^°  |AltShf| Left | Right|                                       |  Up  | Down | CMD-SHIFT |  +  | #/L1 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | MDIA | Meh  |       | Hyper|  NUM   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Back-|  Del |------|       |------|  Enter | Space|
 *                                 | Space|      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,                  KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   LGUI(KC_V),
        KC_TAB,                  KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_LGUI,
        TG(3),                   KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,                 CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   KC_LALT,
        LT(SYMB,KC_GRV),         DE_LESS,      LALT(KC_LSFT),  KC_LEFT,KC_RGHT,
                                               TG(2),  MEH_T(LSFT(DE_ACUT)),
                                                              KC_HOME,
                                               KC_BSPC,KC_DEL,KC_END,
        // right hand
             LGUI(KC_C),     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
             KC_RGUI,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             DE_UE,
                          KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,LT(MDIA,DE_AE),
             KC_RALT,KC_N,   KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_UP,  KC_DOWN,LGUI(KC_LSFT),KC_RBRC,          LT(SYMB,KC_BSLS),
             ALL_T(DE_ACUT),        TG(4),
             KC_PGUP,
             KC_PGDN,KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |   !  |  ?   |      |      |           |      |   \  |   [  |   ]  |   |  |   #  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   \  |   /  |   .  |------|           |------|   /  |   (  |   )  |   {  |   }  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |   ^  |   %  |   |  |   ~  |      |           |      |   &  |   <  |   >  |   "  |   '  |    ?   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |   .  |   !  |      |
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
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_GRV,LSFT(KC_GRV),DE_EXLM,DE_QST,KC_TRNS,KC_TRNS,
       KC_TRNS,DE_HASH,DE_DLR, LALT(LSFT(KC_7)),DE_SLSH,KC_DOT,
       KC_TRNS,KC_TRNS,DE_LESS,DE_PERC,LALT(KC_7),LALT(KC_N),KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_DEL,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, LALT(LSFT(KC_7)),   LALT(KC_5),   LALT(KC_6),    LALT(KC_7),    DE_HASH, KC_F12,
                DE_SLSH,   DE_LPRN,   DE_RPRN,    LALT(KC_8),    LALT(KC_9), KC_TRNS,
       KC_TRNS, DE_AMPR, KC_GRV,   LSFT(KC_GRV),    DE_DQOT,    DE_QUOT, DE_QST,
                         KC_TRNS,KC_DOT,  KC_EXLM,    KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |        |
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
KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_BTN3, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_MUTE, KC_MPRV, KC_MNXT, KC_UP,   KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_LEFT, KC_DOWN, KC_RIGHT,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
/* Keymap 3: ADNW-Koy layer
 * ADNW-Koy is a special layout designed to be ergonomic. Was created using software to determine the most ergonomic way to type German and English texts.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  |Lctrl |           |Rctrl |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   K  |   .  |   O  |   ,  |   Y  | CMD  |           | CMD  |   V  |   G  |   C  |   L  |   ß  |   Z    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  ADNW  |   H  |   A  |   E  |   I  |   U  |------|           |------|   D  |   T  |   R  |   N |   S  |  F/L2  |
 * |--------+------+------+------+------+------| LALT |           | RALT |------+------+------+------+------+--------|
 * | LShift |X/Ctrl|   Q  |   Ä  |   Ü  |   Ö  |      |           |      |   B  |   P  |   W  |   M  |J/Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |</L1|  ^  |AltShf| Left | Right|                                       |  Up | Down | CMD-SHIFT |  ´  | //L1 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | L1 | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Enter | Space|
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_K,    KC_DOT,  KC_O,    KC_COMM, KC_Z,    KC_TRNS,
       KC_TRNS, KC_H,    KC_A,    KC_E,    KC_I,    KC_U,
       KC_TRNS, CTL_T(KC_X),KC_Q,    DE_AE,   DE_UE,   DE_OE,   KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLSH,
       KC_TRNS,  KC_V,    KC_G,    KC_C,    KC_L,    KC_MINS, KC_Y,
                 KC_D,    KC_T,    KC_R,    KC_N,    KC_S, LT(MDIA,KC_F),
       KC_TRNS,  KC_B,    KC_P,    KC_W,    KC_M,    CTL_T(KC_J), KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    LSFT(KC_RBRC), KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_RBRC, KC_TRNS,
       KC_TRNS, LSFT(KC_6), KC_1,   KC_2,    KC_3,    LSFT(KC_7), KC_TRNS,
                         KC_0,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),                // FN1 - Momentary Layer 1 (Symbols)
    [2] = ACTION_LAYER_TAP_TOGGLE(ADNW)                // FN2 - Momentary Layer 2 (ADNW)
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
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

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
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
	    ergodox_right_led_1_on();
            ergodox_right_led_3_on();
	    //ergodox_board_led_on();
            break;
        default:
            // none
            break;
    }

};
