#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define DFLT 0 // Default
#define FCTN 1 // Function

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ~    |   1  |   2  |   3  |   4  |   5  |   -  |           |   =  |   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |   }  |   Y  |   U  |   I  |   O  |   P  |   {    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Caps   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   "    |
 * |--------+------+------+------+------+------|  Fn  |           |  Fn  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   ?  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Left |Right |LCTRL | LALT | LGUI |                                       | RGUI | RALT |RCTRL |  Up  | Down |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | ESC  |      |       |      |  ESC   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | BS   | DEL  |------|       |------|  Ret   |Space |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */

// Default
[DFLT] = KEYMAP(

// Left Keyboard
KC_GRV,   KC_1,      KC_2,     KC_3,     KC_4,     KC_5,  KC_MINS,
KC_TAB,   KC_Q,      KC_W,     KC_E,     KC_R,     KC_T,  KC_NO,
KC_CAPS,  KC_A,      KC_S,     KC_D,     KC_F,     KC_G,
KC_LSFT,  KC_Z,      KC_X,     KC_C,     KC_V,     KC_B,  MO(FCTN),
KC_LEFT,  KC_RIGHT,  KC_LCTL,  KC_LALT,  KC_LGUI,

// Left Cluster
KC_ESC,   KC_NO,
KC_HOME,
KC_BSPC,  KC_DEL,  KC_END,

// Right Keyboard
KC_EQL,    KC_7,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSLS,
KC_RBRC    KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,
KC_H,      KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
MO(FCTN),  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
KC_RGUI,   KC_RALT,  KC_RCTL,  KC_UP,    KC_DOWN,

// Right Cluster
KC_NO,    KC_ESC,
KC_PGUP,
KC_PGDN,  KC_ENT,  KC_SPC

),

/* Function
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

// Function
[FCTN] = KEYMAP(

// Left Keyboard
KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_TRNS,
KC_TRNS,  KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_TRNS,
KC_TRNS,  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV,
KC_TRNS,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,  KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

// Left Cluster
KC_TRNS,  KC_TRNS,
KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS,
       
// Right Keyboard
KC_TRNS,  KC_F6,    KC_F7,  KC_F8,   KC_F9,    KC_F10,   KC_F11,
KC_TRNS,  KC_UP,    KC_7,   KC_8,    KC_9,     KC_ASTR,  KC_F12,
KC_DOWN,  KC_4,     KC_5,   KC_6,    KC_PLUS,  KC_TRNS,
KC_TRNS,  KC_AMPR,  KC_1,   KC_2,    KC_3,     KC_BSLS,  KC_TRNS,
KC_TRNS,  KC_DOT,   KC_0,   KC_EQL,  KC_TRNS,

// Right Cluster
KC_TRNS,  KC_TRNS,
KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_TRNS

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
