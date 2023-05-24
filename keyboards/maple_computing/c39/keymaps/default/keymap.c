#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN1 1

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,----------------------------------------------------------------------------.  ,-------------.
 * |   Q  |   W  |   E  |   R  |   T  | Bksp |   Y  |   U  |   I  |   O  |   P  |  |  M1  |  M2  |
 * |------+------+------+------+------+------+------+------+------+------+------+  |------+------|
 * |   A  |   S  |   D  |   F  |   G  | Enter|   H  |   J  |   K  |   L  |   ;  |  |  M3  |  M4  |
 * |------+------+------+------+------+------+------+------+------+------+------+  |------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  FN1 |   N  |   M  |   ,  |   .  |   /  |  |  M5  |  M6  |
 * `----------------------------------------------------------------------------'  `-------------'
 */
[_QWERTY] = LAYOUT(
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_BSPC,                KC_Y, KC_U, KC_I,    KC_O,   KC_P,      KC_1, KC_2,
    KC_A, KC_S, KC_D, KC_F, KC_G, MT(MOD_LSFT, KC_ENT),   KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,   KC_3, KC_4,
    KC_Z, KC_X, KC_C, KC_V, KC_B, LT(_FN1, KC_SPC),       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,   KC_5, KC_6
),

/* FN1
 * ,----------------------------------------------------------------------------.  ,-------------.
 * |   1  |   2  |   3  |   4  |   5  | Bksp |   6  |   7  |   8  |   9  |   0  |  |  M1  |  M2  |
 * |------+------+------+------+------+------+------+------+------+------+------+  |------+------|
 * |   4  |   5  |   6  |   +  |      | Enter|      |      |      |      |      |  |  M3  |  M4  |
 * |------+------+------+------+------+------+------+------+------+------+------+  |------+------|
 * |   7  |   8  |   9  |   0  |      |  FN1 |      |      |      |      |      |  |  M5  |  M6  |
 * `----------------------------------------------------------------------------'  `-------------'
 */
[_FN1] = LAYOUT(
    KC_1, KC_2, KC_3, KC_4,    KC_5,    KC_BSPC, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_1, KC_2,
    KC_4, KC_5, KC_6, KC_PLUS, _______, KC_ENT,  _______, _______, _______, _______, _______,   KC_3, KC_4,
    KC_7, KC_8, KC_9, KC_0,    _______, _______, _______, _______, _______, _______, _______,   KC_5, KC_6
),
};
