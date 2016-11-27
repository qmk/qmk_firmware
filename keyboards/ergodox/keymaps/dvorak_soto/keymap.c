#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   '  |   ,  |   .  |   P  |   Y  |  L1  |           |  L1  |   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |S / L2|   -    |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |:/Ctrl|   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |Z/Ctrl| RShift |
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
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_LEFT,
        KC_TAB,   KC_QUOT, KC_COMM, KC_DOT,  KC_P,   KC_Y,   TG(SYMB),
        KC_BSPC,  KC_A,    KC_O,    KC_E,    KC_U,   KC_I,
        KC_LSFT,  KC_SCLN, KC_Q,    KC_J,    KC_K,   KC_X,   TG(MDIA),
        MO(SYMB), KC_ESC,  KC_LBRC, KC_DOWN, KC_UP,
        // left thumb
                        KC_LGUI,       KC_LCTL,
                                       KC_LALT,
        GUI_T(KC_BSPC), CTL_T(KC_DEL), MO(SYMB),
        // right hand
        KC_RGHT,  KC_6,   KC_7,     KC_8,     KC_9,    KC_0,    KC_EQL,
        TG(SYMB), KC_F,   KC_G,     KC_C,     KC_R,    KC_L,    KC_SLSH,
                  KC_D,   KC_H,     KC_T,     KC_N,    KC_S,    KC_MINS,
        TG(MDIA), KC_B,   KC_M,     KC_W,     KC_V,    KC_Z,    KC_RSFT,
                          KC_LEFT,  KC_RIGHT, KC_RBRC, KC_BSLS, MO(SYMB),
        // right thumb
        KC_RCTL,  KC_RGUI,
        KC_RALT,
        MO(SYMB), CTL_T(KC_ENT), GUI_T(KC_SPC)
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
[SYMB] = KEYMAP(
       // left hand
       KC_NO,   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO,
       KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
       KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO,
       // left thumb
                KC_NO, KC_NO,
                       KC_NO,
       KC_TRNS, KC_NO, KC_TRNS,
       // right hand
       KC_NO  , KC_F6, KC_F7,   KC_F8,   KC_F9 , KC_F10, KC_F11 ,
       KC_TRNS, KC_NO, KC_LBRC, KC_RBRC, KC_NO , KC_NO,  KC_F12 ,
                KC_NO, KC_LPRN, KC_RPRN, KC_NO,  KC_NO,  KC_NO,
       KC_NO,   KC_NO, KC_LCBR, KC_RCBR, KC_NO,  KC_NO,  KC_NO,
                       KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_TRNS,
       // right thumb
       KC_NO, KC_NO,
       KC_NO,
       KC_TRNS, KC_NO, KC_NO
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
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_MS_U, KC_NO,   KC_NO, KC_TRNS,
       KC_NO,   KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_MS_D, KC_NO,   KC_NO, KC_TRNS,
       KC_NO,   KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU,
                                           KC_NO,   KC_NO,
                                                    KC_NO,
                                  KC_NO,   KC_NO,   KC_NO,
    // right hand
       KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_POWER,
       KC_TRNS,  KC_NO,   KC_VOLU, KC_MS_U, KC_VOLD, KC_NO,   KC_NO,
                 KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN4, KC_MPLY,
       KC_TRNS,  KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,
                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_ENT, KC_NO
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
