#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define FN1  1 // media layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |  6   |           |   7  |   8  |   9  |   0  |   -  |   =  | BSpace |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | Fwd  |           | Back |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Caps/Ctl|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | Enter  |
 * |--------+------+------+------+------+------| PgUp |           | PgDn |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |   '    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |  Esc | LGui | Alt  | Alt  |                                       | Left |  Up  |  Dn  | Right|  Fn  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Copy |  (   |       |   )  | Paste|
 *                                 ,------|------+------|       |------+------+------.
 *                                 |      |      |  [   |       |   ]  |      |      |
 *                                 |Space | Del  |------|       |------| Enter|BSpace|
 *                                 |      |      |  {   |       |   }  |      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
    [BASE] = KEYMAP(  // layer 0 : default
	// left hand
	KC_GRV,   KC_1,    KC_2,    KC_3,     KC_4,     KC_5,    KC_6,
	KC_TAB,   KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,    KC_WBAK,
	CTL_T(KC_CAPS), KC_A, KC_S, KC_D,     KC_F,     KC_G,
	KC_LSFT,  KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,    KC_PGUP,
	KC_LCTL,  KC_ESC,  KC_LGUI, KC_LALT, KC_LALT,
	LCTL(KC_C), KC_LCBR,
	KC_LPRN,
	KC_SPC,   KC_DEL,  KC_LBRC,
	// right hand
	KC_7,     KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,
	KC_WFWD,  KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,    KC_BSLS,
	KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_ENT,
	KC_PGDN,  KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH, KC_QUOT,
	KC_UP,    KC_LEFT, KC_RIGHT,KC_DOWN,  TG(FN1),
	KC_RCBR,  LCTL(KC_V),
	KC_RPRN,
	KC_RBRC,  KC_ENT,  KC_BSPC
	),
/* Keymap 1: Fn Keys, media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | BSpace |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Teensy|      |      | Lclk | Rclk |                                       |      |VolUp |VolDn | Mute |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------+------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// FN1 Layer
    [FN1] = KEYMAP(
	KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
	KC_TRNS, KC_TRNS,
	KC_TRNS,
	RESET,   KC_TRNS, KC_TRNS,
	// right hand
	KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS,
	KC_TRNS, KC_TRNS,
	KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS
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
