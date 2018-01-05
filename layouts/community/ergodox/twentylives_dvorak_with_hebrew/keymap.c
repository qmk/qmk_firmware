#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Keymap 0: Basic Dvorak layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Hebrew |   1  |   2  |   3  |   4  |   5  |ALT+S |           |B.tick|  6   |   7  |   8  |   9  |   0  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   '  |   ,  |   .  |   P  |   Y  | LCK2 |           |      |   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | ESC    |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  |   -    |
 * |--------+------+------+------+------+------| LCK1 |           |      |------+------+------+------+------+--------|
 * | LShift |   ;  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | RSHIFT |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |FN2   | COPY | CUT  | PASTE| FN1  |                                       |   [  |   ]  |   \  | UNDO | CTRL+A |
 *   `----------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
*                                         | DEL  |      |       | END  | HOME   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | SUPER|       | PgUp |        |      |
 *                                 | BACK | CTRL |------|       |------|  Enter |SPACE |
 *                                 | SPACE|      | ALT  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[0] = LAYOUT_ergodox(
	TG(1),     KC_1,       KC_2,       KC_3,       KC_4,  KC_5, LALT(KC_LSHIFT),
	KC_TAB,    KC_QUOTE,   KC_COMMA,   KC_DOT,     KC_P,  KC_Y, TG(3),
	KC_ESCAPE, KC_A,       KC_O,       KC_E,       KC_U,  KC_I,
	KC_LSHIFT, KC_SCOLON,  KC_Q,       KC_J,       KC_K,  KC_X, TG(2),
	MO(3),     LCTL(KC_C), LCTL(KC_X), LCTL(KC_V), MO(2),
	                                          KC_DELETE, KC_TRNS,
	                                                     KC_LGUI,
	                              KC_BSPACE,CTL_T(KC_NO),KC_LALT,
	
	KC_TILD,   KC_6,    KC_7,        KC_8,        KC_9,      KC_0,     KC_EQUAL,
	KC_TRNS,   KC_F,    KC_G,        KC_C,        KC_R,      KC_L,     KC_SLASH,
	KC_D,      KC_H,    KC_T,        KC_N,        KC_S,      KC_MINUS,
	KC_TRNS,   KC_B,    KC_M,        KC_W,        KC_V,      KC_Z,     KC_LSHIFT,
	                    KC_LBRACKET, KC_RBRACKET, KC_BSLASH, KC_UNDO,  LCTL(KC_A),
	KC_END,    KC_HOME,
	KC_PGUP,
	KC_PGDOWN, KC_ENTER, KC_SPACE
),

 /* Keymap 1: Hebrew layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
 */
[1] = LAYOUT_ergodox(
	KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_W,    KC_QUOTE, KC_SLASH, KC_R,    KC_T,    KC_TRNS,
	KC_TRNS, KC_A,    KC_S,     KC_D,     KC_F,    KC_G,
	KC_TRNS, KC_Z,    KC_X,     KC_C,     KC_V,    KC_B,    KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
	                                               KC_TRNS, KC_TRNS,
	                                                        KC_TRNS,
	                                      KC_TRNS, KC_TRNS, KC_TRNS,
	
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
	KC_TRNS, KC_Y,    KC_U,    KC_E,     KC_O,      KC_P,      KC_TRNS,
	         KC_H,    KC_J,    KC_K,     KC_L,      KC_SCOLON, KC_TRNS,
	KC_TRNS, KC_N,    KC_M,    KC_COMMA, KC_DOT,    KC_I,      KC_TRNS,
                    KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
	KC_TRNS, KC_TRNS,
	KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Arrows ,Mouse Navigation and F Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |  F11 |      |      |  UP  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | LEFT | DOWN | RIGHT|      |        |
 * |--------+------+------+------+------+------|      |           |  F12 |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | Lclk | Rclk |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[2] = LAYOUT_ergodox(
	KC_TRNS, KC_F1,   KC_F2,      KC_F3,      KC_F4,       KC_F5,   KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS,    KC_MS_UP,   KC_TRNS,     KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,
	                                                       KC_TRNS, KC_TRNS,
	                                                                KC_TRNS,
	                                              KC_TRNS, KC_TRNS, KC_TRNS,

	KC_TRNS,    KC_F6,      KC_F7,      KC_F8,      KC_F9,   KC_F10,  KC_TRNS,
	KC_F11,     KC_TRNS,    KC_TRNS,    KC_UP,      KC_TRNS, KC_TRNS, KC_TRNS, 
	KC_TRNS,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_TRNS, KC_TRNS,
	KC_F12,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
	                        KC_MS_BTN1, KC_MS_BTN2, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS,    KC_TRNS,
	KC_TRNS, 
	KC_TRNS,    KC_TRNS,    KC_TRNS
),

 /* Keymap 3: Numpad Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      | NMLK |  P/  |  P*  |  P-  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |  7   |   8  |  9   |  P+  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |  4   |   5  |  6   |  P+  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |  1   |   2  |  3   | ENTER|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  0   |   0  |  .   | ENTER|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[3] = LAYOUT_ergodox(
	// Left Hand
	KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS, 
	KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,
	KC_TRNS,KC_TRNS,
	KC_TRNS,
	KC_TRNS,KC_TRNS,KC_TRNS,
	// Right Hand
	KC_TRNS, KC_TRNS,  KC_LOCKING_NUM, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, KC_TRNS, 
	KC_TRNS, KC_TRNS,  KC_KP_7,        KC_KP_8,     KC_KP_9,        KC_KP_PLUS,  KC_TRNS,
	         KC_TRNS,  KC_KP_4,        KC_KP_5,     KC_KP_6,        KC_KP_PLUS,  KC_TRNS,     
	KC_TRNS, KC_TRNS,  KC_KP_1,        KC_KP_2,     KC_KP_3,        KC_ENTER,    KC_TRNS,
	                   KC_KP_0,        KC_KP_0,     KC_KP_DOT,      KC_ENTER,    KC_TRNS,
	KC_TRNS,  KC_TRNS, 
	KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS
),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

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
        case 3:
            ergodox_right_led_3_on();
        default:
            break;
    }

};
