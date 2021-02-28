// Media keys work on OSX, but not on Windows.
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define BASE 0  // Default layer
#define AUXI 1  // Auxiliary layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ~`   |   1  |   2  |   3  |   4  |   5  |   6  |           |   7  |   8  |   9  |   0  |   -_ |   += |  Bkspc |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   Tab  |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  Del |   Y  |   U  |   I  |   O  |   P  |   |\   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   L1   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;:  |  Enter |
 * |--------+------+------+------+------+------| {[   |           | }]   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   <, |   >. |  ?/  |   "'   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |      |      |      |  Esc |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |Power |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | LGui | LAlt |------|       |------|  Bkspc |Space |
 *                                 |      |      |      |       |  Del |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   MO(1),
        MO(1),      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSHIFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LBRC,
        KC_LCTL,    KC_TRNS,KC_TRNS,KC_TRNS,KC_ESC,
                                                    KC_TRNS,KC_TRNS,
                                                            KC_TRNS,
                                            KC_LGUI,KC_LALT,KC_TRNS,

        // right hand
        KC_7,       KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,
        KC_DELETE,  KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSLASH,
                    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_ENT,
        KC_RBRC,    KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_QUOT,
                         KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_PWR,    KC_TRNS,
        KC_TRNS,
        KC_DELETE,    KC_BSPC, KC_SPC
    ),
/* Keymap 1: Auxiliary Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  | F12  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      | TRNS |           |      | Mute | VolDn| VolUp| Play |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   TRNS |      |LShift| LCtrl|      |      |------|           |------| LEFT | DOWN | UP   |RIGHT |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |      |      |      |      |      |      |           |      | MPrv | MNxt |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | LGui | LAlt |------|       |------| Bkspc| Space|
 *                                 |      |      |      |       |  Del |      |      |
 *                                 `--------------------'       `--------------------'
 */
// AUXILIARY
[AUXI] = LAYOUT_ergodox(
       // left hand
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_LSHIFT,KC_LCTL, KC_TRNS, KC_TRNS,
       KC_LSHIFT,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_LGUI, KC_LALT, KC_TRNS,
       // right hand
       KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,
       KC_TRNS,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_TRNS, KC_TRNS,
                 KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_PWR, KC_TRNS,
       KC_TRNS,
       KC_DELETE, KC_BSPC, KC_SPC
),
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

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
        default:
            // none
            break;
    }

};
