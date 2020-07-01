/*
 * This is built out of frustration with OSX / Sierra caps lock delay.
 * Fake it till you make it!
 */

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "timer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

#define BLINK_BASE  150U // timer threshold for blinking on MDIA layer

typedef enum onoff_t {OFF, ON} onoff;

#define caps_led_on  ergodox_right_led_2_on
#define caps_led_off ergodox_right_led_2_off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |   6  |           |   `  |   7  |   8  |   9  |   0  |   -  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   [  |           |   ]  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CapsL  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   "    |
 * |--------+------+------+------+------+------| ~L1  |           |  ~L1 |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl | Opt  | Cmd  | Left | Right|                                       | Down | Up   | Ctrl | Cmd  | Opt  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      | L1   |       | Alt  | Ctrl   ]
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 |Backsp| Del  |------|       |------|  Enter | Spc  |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */

    [BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,     KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_TAB,     M(KC_Q),  M(KC_W), M(KC_E), M(KC_R), M(KC_T), KC_LBRC,
        M(KC_CAPS), M(KC_A),  M(KC_S), M(KC_D), M(KC_F), M(KC_G),
        KC_LSFT,    M(KC_Z),  M(KC_X), M(KC_C), M(KC_V), M(KC_B), MO(SYMB),
        KC_LCTL,    KC_LALT,  KC_LGUI, KC_LEFT, KC_RGHT,
                                                         KC_TRNS, KC_FN1,
                                                                  KC_HOME,
                                                KC_BSPC, KC_DEL,  KC_END,
        // right hand
        KC_GRV,     KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_RBRC,    M(KC_Y),  M(KC_U), M(KC_I), M(KC_O), M(KC_P), KC_BSLS,
                    M(KC_H),  M(KC_J), M(KC_K), M(KC_L), KC_SCLN, KC_QUOT,
        MO(SYMB),   M(KC_N),  M(KC_M), KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                              KC_DOWN, KC_UP,   KC_RCTL, KC_RGUI, KC_RALT,
        KC_RALT,    KC_RCTL,
        KC_PGUP,
        KC_PGDN,    KC_ENT,   KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |      |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
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
 *                                        |   L0 |  L2  |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
    [SYMB] = LAYOUT_ergodox(
       // left hand
       KC_GRV ,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                               KC_FN3, KC_FN2,
                                                       KC_TRNS,
                                       KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,
       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),
/* Keymap 2: Media and tenkey
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  BOOTL |      | Mute | Vol- | Vol+ | F14  | F15  |           |      |      | NumLk|   /  |  *   |  -   |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |  7   |  8   |  9   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+-----+-------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |  4   |  5   |  6   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |  1   |  2   |  3   | Enter|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  0   |  0   |  .   | Enter|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  L1  |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
    // MEDIA AND TENKEY
    [MDIA] = LAYOUT_ergodox(
       KC_NO,   KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_F14,  KC_F15,
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,
                                                    KC_FN4,  KC_NO,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_NO,   KC_NO,   KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_NO,
       KC_NO,   KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_NO,
                KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_NO,
       KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_NO,
                         KC_P0,   KC_P0,   KC_PDOT, KC_PENT, KC_NO,
       KC_NO,   KC_NO,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_ON(SYMB,ON_RELEASE),           // FN1 - Enable Layer 1 (Symbols)
    [2] = ACTION_LAYER_ON(MDIA,ON_RELEASE),           // FN2 - Enable Layer 2 (Media)
    [3] = ACTION_LAYER_OFF(SYMB,ON_RELEASE),          // FN3 - Disable Layer 1 (Symbols)
    [4] = ACTION_LAYER_OFF(MDIA,ON_RELEASE),          // FN4 - Disable Layer 2 (MMedia)
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    static onoff caps_state = OFF;
    switch(id) {
    case KC_CAPS:
        if (record->event.pressed) {
            // Toggle caps state;
            if (caps_state == OFF) {
                // Turn it on then!
                caps_led_on();
                caps_state = ON;
            } else {
                caps_led_off();
                caps_state = OFF;
            }
        }
        break;
    default:
        if (record->event.pressed) {
            bool shifted = false;
            if (caps_state == ON && get_mods() == 0) {
                register_code(KC_LSFT);
                shifted = true;
            }
            register_code(id);
            if(shifted) {
                unregister_code(KC_LSFT);
            }
        } else {
            unregister_code(id);
        }
        break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

}
// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    static onoff board_led_state = OFF;
    static uint16_t dt = 0;
    static uint8_t oldlayer = 0;

    if(oldlayer != layer) {
        // Layer was just toggled.
        if(layer == BASE) {
            ergodox_board_led_off();
            board_led_state = OFF;
        } else {
            ergodox_board_led_on();
            board_led_state = ON;
        }
    } else if (layer >= MDIA) {
        // We need to do blinking.
        if(timer_elapsed(dt) > BLINK_BASE) {
            // toggle
            dt = timer_read();
            if(board_led_state == OFF) {
                ergodox_board_led_on();
                board_led_state = ON;
            } else {
                ergodox_board_led_off();
                board_led_state = OFF;
            }
        }
    }
    oldlayer = layer;
}
