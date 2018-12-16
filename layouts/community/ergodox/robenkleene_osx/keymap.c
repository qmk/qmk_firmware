#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define DFLT 0 // Default
#define FCTN 1 // Function

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   |    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCTL   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   "    |
 * |--------+------+------+------+------+------| LCTL |           | RCTL |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   ?  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |   ~  |LCTRL | LALT | LGUI |                                       | RGUI | RALT |   {  |   }  | Fn   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | CTRL |  Fn  |       |  Fn  | CTRL |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | BS   | ESC  |------|       |------|  Ret   |Space |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */

// Default
[DFLT] = KEYMAP(


// Left Keyboard
KC_EQL,    KC_1,    KC_2,     KC_3,     KC_4,     KC_5,  KC_NO,
KC_TAB,    KC_Q,    KC_W,     KC_E,     KC_R,     KC_T,  KC_RBRC,
KC_LCTL,   KC_A,    KC_S,     KC_D,     KC_F,     KC_G,
KC_LSFT,   KC_Z,    KC_X,     KC_C,     KC_V,     KC_B,  KC_LCTL,
MO(FCTN),  KC_GRV,  KC_LCTL,  KC_LALT,  KC_LGUI,

// Left Cluster
KC_LCTL,  MO(FCTN),
KC_HOME,
KC_BSPC,  KC_ESC,  KC_END,

// Right Keyboard
KC_NO,    KC_6,     KC_7,     KC_8,     KC_9,      KC_0,     KC_MINS,
KC_NO,    KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_BSLS,
KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,
KC_RCTL,  KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,  KC_RSFT,
KC_RGUI,  KC_RALT,  KC_LBRC,  KC_RBRC,  MO(FCTN),

// Right Cluster
MO(FCTN), KC_RCTL,
KC_PGUP,
KC_PGDN,  KC_ENT,  KC_SPC

),

/* Function
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | TNSY   |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           | VolU |  FF  | Mute |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| Play |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           | VolD |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |  RW  | PgUp |      |  UP  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | PgDn | LEFT | DOWN |RIGHT |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

// Function
[FCTN] = KEYMAP(

// Left Keyboard
RESET,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
// Left Cluster
KC_TRNS,  KC_TRNS,
KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS,

// Right Keyboard
KC_TRNS,  KC_F6,    KC_F7,    KC_F8,     KC_F9,    KC_F10,   KC_F11,
KC_VOLU,  KC_MNXT,  KC_MUTE,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
KC_MPLY,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,
KC_VOLD,  KC_MPRV,  KC_TRNS,  KC_TRNS,   KC_UP,    KC_TRNS,  KC_TRNS,
KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_TRNS,

// Right Cluster
KC_TRNS,  KC_TRNS,
KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS

),


};

const uint16_t PROGMEM fn_actions[] = {
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
