#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DEFAULT 0
#define _FN_1 1
#define _FN_2 2

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default Layer
 * ,-----------------------------------------------.
 * |  FN_2 |   2   |TSKMGR |CALTDEL|  ESC  |  FN_1 |
 * `-----------------------------------------------'
 */
[_DEFAULT] = LAYOUT(
  MO(_FN_2), KC_2, TSKMGR, CALTDEL, KC_ESC, MO(_FN_1)
),

/* FN 1 Layer
 * ,-----------------------------------------------.
 * |UG_TOGG|UG_HUED|UG_HUEU|UG_SATD|UG_SATU|  FN_1 |
 * `-----------------------------------------------'
 */
[_FN_1] = LAYOUT(
  UG_TOGG, UG_HUED, UG_HUEU, UG_SATD, UG_SATU, _______
),

/* FN 2 Layer
 * ,-----------------------------------------------.
 * |  FN_2 |UG_VALD|UG_VALU|UG_NEXT|TSKMGR | QK_BOOT |
 * `-----------------------------------------------'
 */
[_FN_2] = LAYOUT(
  _______, UG_VALD, UG_VALU, UG_NEXT, TSKMGR, QK_BOOT
)

};
