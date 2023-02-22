#include QMK_KEYBOARD_H
#include "keymap_dvorak.h"
#include "debug.h"
#include "action_layer.h"

/******************************************************************************************
 * DVORAK LAYOUT (see http://djelibeibi.unex.es/dvorak/)
 * Layer 1: auxiliary keys
 * Layer 2: full qwerty layout
 *****************************************************************************************/

// LAYERS
#define BASE    0 // dvorak layout (default)
#define AUX     1 // auxiliary keys

// MACROS
/* #define OBRACE 0 // key { or shift */
/* #define CBRACE 1 // key } or shift */
/* #define OBRACK 2 // key [ or left alt */
/* #define CBRACK 3 // key ] or left alt */
/* #define CAPS   4 // caps lock */

// LEDS
#define USB_LED_NUM_LOCK    0
#define USB_LED_CAPS_LOCK   1
#define USB_LED_SCROLL_LOCK 2
#define USB_LED_COMPOSE     3
#define USB_LED_KANA        4

// TIMERS
#define KEY_TAP_FAST 85
#define KEY_TAP_SLOW 95

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base layer
 * Keys with double values (like Esc/Ctrl) correspond to the 'tapped' key and the 'held' key, respectively
 *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |  Esc |           |  Esc |   6  |   7  |   8  |   9  |   0  | = / +  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   ~    |" / ' |, / < |. / > |   P  |   Y  |   [  |           |   ]  |   F  |   G  |   C  |   H  |   L  | / / ?  |
 * |--------+------+------+------+------+------|   {  |           |   }  |------+------+------+------+------+--------|
 * |  Tab   |   A  |   O  |   E  |U/LSft| I/L1 |------|           |------|  D/L1|R/RSft|   T  |   N  |   S  | - / _  |
 * |--------+------+------+------+------+------| LGUI |           | LGUI |------+------+------+------+------+--------|
 * | {/LSft |; / : |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | }/RSft |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | ~L1  |                                       | ~L1  |      |      | \ / ||        |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | HOME |  END |       | LEFT | RIGHT|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 | BSPC |  DEL | PGUP |       |  UP  | SPACE  |RETURN|
 *                                 |  /   |  /   |------|       |------|   /    |  /   |
 *                                 | LCTL | LALT |PGDWN |       | DOWN | LALT   | LCTL |
 *                                 `--------------------'       `----------------------'
 *
 */
[BASE] = LAYOUT_ergodox(
        // left hand
        KC_NO,          KC_1,     KC_2,   KC_3,   KC_4,          KC_5,           KC_ESC,
        KC_TILD,        DV_QUOT,  DV_COMM,DV_DOT, DV_P,          DV_Y,           DV_LBRC,
        KC_TAB,         DV_A,     DV_O,   DV_E,   SFT_T(DV_U),   LT(AUX, DV_I),
        SFT_T(DV_LBRC), DV_SCLN,  DV_Q,   DV_J,   DV_K,          DV_X,           KC_LGUI,
        KC_NO,          KC_NO,    KC_NO,  KC_NO,  MO(AUX),
                                                            KC_HOME, KC_END,
                                                                     KC_PGUP,
                                      CTL_T(KC_BSPC), ALT_T(KC_DEL), KC_PGDN,
        // right hand
        KC_ESC,         KC_6,         KC_7,   KC_8,   KC_9,   KC_0,   DV_EQL,
        DV_RBRC,        DV_F,         DV_G,   DV_C,   DV_R,   DV_L,   DV_SLSH,
        LT(AUX, DV_D),  SFT_T(DV_H),  DV_T,   DV_N,   DV_S,   DV_MINS,
        KC_LGUI,        DV_B,         DV_M,   DV_W,   DV_V,   DV_Z,   SFT_T(DV_RBRC),
                                                                 MO(AUX), KC_NO,   KC_NO,  KC_BSLS, KC_NO,
        KC_LEFT, KC_RIGHT,
        KC_UP,
        KC_DOWN, ALT_T(KC_ENT), CTL_T(KC_SPC)
    ),
/* Keymap 1: Aux layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  VolUp |      |      |      |      |      | SLEEP            | PWR  |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  VolDn |  F1  |  F2  |  F3  |  F4  |      |      |           |      |      |   7  |   8  |   9  |   *  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  | TRANS|------|           |------|TRANS |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |PSCR  |------+-----aan+------+------+------+--------|
 * |  TRANS |  F9  |  F10 |  F11 |  F12 |      |      |           |      |      |   1  |   2  |   3  |   /  |  TRANS |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |CTRL-S|CTRL-Z|CTRL-X|CTRL-C| TRANS|                                       | TRANS|    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | TRANS| TRANS|       | TRANS| TRANS|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | TRANS|       | TRANS|      |      |
 *                                 |TRANS |TRANS |------|       |------| TRANS| TRANS|
 *                                 |      |      | TRANS|       | TRANS|      |      |
 *                                 `--------------------'       `--------------------'
 */
[AUX] = LAYOUT_ergodox(
       // left hand
       KC_VOLU, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_SLEP,
       KC_VOLD, KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_NO,   KC_NO,
       KC_NO  , KC_F5, KC_F6,  KC_F7,  KC_F8,  KC_TRNS,
       KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,   KC_NO,
       LCTL(DV_S), LCTL(DV_Z), LCTL(DV_X), LCTL(DV_C), KC_TRNS,
                                                            KC_TRNS  , KC_TRNS,
                                                                     KC_TRNS,
                                                KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
            KC_PWR,  KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_7,   KC_8,   KC_9,    KC_PAST, KC_NO,
                     KC_TRNS, KC_4,   KC_5,   KC_6,    KC_PPLS, KC_NO,
            KC_PSCR, KC_NO,   KC_1,   KC_2,   KC_3,    KC_PSLS, KC_TRNS,
                              KC_TRNS,KC_DOT, KC_0,    KC_PEQL, KC_NO,
       KC_TRNS  , KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
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
}
