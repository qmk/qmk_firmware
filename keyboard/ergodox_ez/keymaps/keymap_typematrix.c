/* TypeMatrix-2030-like keymap */
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "led.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | Del  |           | Del  |   6  |   7  |   8  |   9  |   0  |   ]    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |Backsp|           |Backsp|   Y  |   U  |   I  |   O  |   P  |   [    |
 * |--------+------+------+------+------+------|ace   |           |ace   |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2| '/Shift|
 * |--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | \/Shift|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl | ~L1  | LGui | Play |App/Alt|                                      | RAlt |   -  | Home |   =  |End/Ctl|
 *   `-----------------------------------'                                      `-----------------------------------'
 *                                       ,--------------.       ,-------------.
 *                                       |Esc/Alt|  L1  |       | Left |Right |
 *                                ,------+-------+------|       |------+------+------.
 *                                |      |       | PgUp |       |  Up  |      |      |
 *                                |Space | Space |------|       |------|Space |Space |
 *                                |      |       | PgDn |       | Down |      |      |
 *                                `---------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_DELT,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_BSPC,
        KC_LSFT,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   KC_ENT,
        KC_LCTL,        KC_FN1,       KC_LGUI,KC_MPLY,ALT_T(KC_APP),

                                              ALT_T(KC_ESC),  TG(1),
                                                              KC_PGUP,
                                             KC_SPC, KC_SPC,  KC_PGDN,

        // right hand
             KC_DELT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_RBRC,
             KC_BSPC,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_LBRC,
                          KC_H,   KC_J,   KC_K,   KC_L,   LT(MDIA, KC_SCLN),SFT_T(KC_QUOT),
             KC_ENT,      KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          SFT_T(KC_BSLS),
                                  KC_RALT,KC_MINS,KC_HOME,KC_EQL,           CTL_T(KC_END),

             KC_LEFT, KC_RGHT,
             KC_UP,
             KC_DOWN, KC_SPC,  KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |Insert|           |Insert|  F6  |  F7  |  Tab |   /  |   *  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F8  |  F9  |  F10 |  F11 |  F12 |VolUp |           | Home |  Up  |  End |   7  |   8  |   9  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| Down | Right|   4  |   5  |   6  |   +    |
 * |--------+------+------+------+------+------|VolDn |           | Left |------+------+------+------+------+--------|
 * |        |      | cut  | copy |paste | Mute |      |           |      |      | Prev |   1  |   2  |   3  |KpEnter |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | Next |   0  |  00  |   .  |KpEnter|
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |n.lock|c.lock|
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Mute |      |      |       |      |      |      |
 *                                 |  /   |      |------|       |------|      |      |
 *                                 | Alt  |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,        KC_F3,       KC_F4,       KC_F5,  KC_INS,
       KC_TRNS,KC_F8,  KC_F9,        KC_F10,      KC_F11,      KC_F12, KC_VOLU,
       KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,     KC_TRNS,     KC_TRNS,
       KC_TRNS,KC_TRNS,LSFT(KC_DELT),LCTL(KC_INS),LSFT(KC_INS),KC_MUTE,KC_VOLD,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                        ALT_T(KC_MUTE),KC_TRNS,KC_TRNS,
       // right hand
       KC_INS,  KC_F6,   KC_F7,   KC_TAB,  KC_PSLS, KC_PAST, KC_PMNS,
       KC_HOME, KC_UP,   KC_END,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
                KC_DOWN, KC_RGHT, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
       KC_LEFT, KC_TRNS, KC_MPRV, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                         KC_MNXT, KC_P0,   M(1),    KC_PDOT, KC_PENT,

       KC_NLCK, KC_CAPS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
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
KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
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
        case 1:
        if (record->event.pressed) {
          return MACRO( I(25), T(P0), T(P0), END );
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
        default:
            // none
            break;
    }
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
      ergodox_right_led_3_on();
    }
};
