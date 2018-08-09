#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_nordic.h"
#include "keymap_norwegian.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MOUS 2 // mouse keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  | ~MOUS|           |      |   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Å  |   Ä  |   Ö  |   P  |   Y  |      |           |      |   F  |   G  |   C  |   R  |   L  |   ,    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Escape |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  |  -/_   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   .  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *  | LCTRL |      |      |      | Super|                                       | ~SYMB| Left | Down |  Up  | Right |
 *  `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+-------.
 *                                 |      |      |      |       |      |        |       |
 *                                 | BSP  | Tab  |------|       |------|  Enter | Space |
 *                                 |      |      |      |       |      |        |       |
 *                                 `--------------------'       `-----------------------'
 */
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_NO,    KC_1,   KC_2,     KC_3,    KC_4,    KC_5,   MO(MOUS),
        KC_NO,    NO_AA,  NO_AE,    NO_OSLH, KC_P,    KC_Y,   KC_NO,
        KC_ESC,   KC_A,   KC_O,     KC_E,    KC_U,    KC_I,
        KC_LSFT,  KC_DOT, KC_Q,     KC_J,    KC_K,    KC_X,   KC_NO,
        KC_LCTRL, KC_NO,  KC_NO,    KC_NO,   KC_LGUI,
                                                      KC_NO,  KC_NO,
                                                              KC_NO,
                                             KC_BSPC, KC_TAB, KC_NO,
        // right hand
        KC_NO,    KC_6,   KC_7,     KC_8,    KC_9,    KC_0,   KC_BSLASH,
        KC_NO,    KC_F,   KC_G,     KC_C,    KC_R,    KC_L,   KC_COMM,
                  KC_D,   KC_H,     KC_T,    KC_N,    KC_S,   KC_MINUS,
        KC_NO,    KC_B,   KC_M,     KC_W,    KC_V,    KC_Z,   KC_RSFT,
                          MO(SYMB), KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,
        KC_NO,    KC_NO,
        KC_NO,
        KC_NO,    KC_ENT, KC_SPACE
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   {  |   }  |   [  |   ]  |   $  |      |           |      |   "  |   &  |   <  |   >  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   ;  |   /  |   (  |   )  |   |  |------|           |------|   #  |   ^  |   #  |   "  |   ~  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   :  |   =  |   @  |   !  |   \  |      |           |      |   %  |   `  |   '  |   *  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |       |
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
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_NO, KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO, KC_LCBR, KC_RCBR,     KC_LBRC, KC_RBRC, KC_DLR,  KC_NO,
       KC_NO, KC_SCLN, KC_KP_SLASH, KC_LPRN, KC_RPRN, KC_PIPE,
       KC_NO, KC_COLN, KC_PEQL,     KC_AT,   KC_EXLM, KC_BSLS, KC_NO,
       KC_NO, KC_NO,   KC_NO,       KC_NO,   KC_NO,
                                                      KC_NO,   KC_NO,
                                                               KC_NO,
                                             KC_NO,   KC_NO,   KC_NO,
       // right hand
       KC_NO, KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO, KC_DQT,  KC_AMPR,     KC_LT,   KC_GT,   KC_NO,   KC_NO,
              KC_HASH, KC_CIRC,     KC_HASH, KC_DQT,  KC_TILD, KC_NO,
       KC_NO, KC_PERC, KC_GRV,      KC_QUOT, KC_ASTR, KC_NO,   KC_NO,
                       KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_NO,   KC_NO
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |  B1  |  B2  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |  M_L |  M_D |  M_U |  M_R  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MOUS] = LAYOUT_ergodox(
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                KC_NO, KC_NO,
                                                       KC_NO,
                                       KC_NO,   KC_NO, KC_NO,
    // right hand
       KC_NO,  KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,  KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,  KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,
       KC_NO,  KC_NO, KC_NO, KC_NO,   KC_BTN1, KC_BTN2, KC_NO,
                      KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_NO, KC_NO
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
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
