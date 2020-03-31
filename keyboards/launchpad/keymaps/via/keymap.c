// Below layout is based upon /u/That-Canadian's planck layout
#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FUNC 1
#define _LAYER2 2
#define _LAYER3 3

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------.
 * |   1  |  2   |
 * |------+------|
 * |   3  |  4   |
 * |------+------|
 * |   5  |  6   |
 * |------+------|
 * | FUNC |  8   |
 * `-------------'
 */
[_QWERTY] = LAYOUT( \
    KC_1,      KC_2, \
    KC_3,      KC_4, \
    KC_5,      KC_6, \
    MO(_FUNC), KC_8  \
),

/* Function
 * ,-------------.
 * |   Q  |CALDEL|
 * |------+------|
 * |   A  |TSKMGR|
 * |------+------|
 * |   Z  |  X   |
 * |------+------|
 * |      |  C   |
 * `-------------'
 */
[_FUNC] = LAYOUT( \
    KC_Q,    CALTDEL,
    KC_A,    TSKMGR,
    KC_Z,    KC_X,
    KC_TRNS, KC_C
),

/* Layer 2
 * ,-------------.
 * |      |      |
 * |------+------|
 * |      |      |
 * |------+------|
 * |      |      |
 * |------+------|
 * |      |      |
 * `-------------'
 */
[_LAYER2] = LAYOUT(
    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS
),

/* Layer 3
 * ,-------------.
 * |      |      |
 * |------+------|
 * |      |      |
 * |------+------|
 * |      |      |
 * |------+------|
 * |      |      |
 * `-------------'
 */
[_LAYER3] = LAYOUT(
    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS
)

};
