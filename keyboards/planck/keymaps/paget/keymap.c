//Keymap I created to suit my working style

#include QMK_KEYBOARD_H

//Define the layers
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |Enter | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
*/

[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_ENT, KC_LGUI, KC_LALT, MO(1), KC_SPC, KC_SPC, MO(2), KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
),

/*
 * ,-----------------------------------------------------------------------------------.
 * |  1   |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   _  |  =   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |      |      |      |      |      |      |      |      |      |   [  |  ]   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   \  |      |      |      |      |      |      |      |      |   #  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      |      |      |Lower |    Space    |Raise |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
[_LOWER] = LAYOUT_planck_grid(
    KC_1,    KC_2,    KC_3,  KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,  KC_0,  KC_MINS, KC_EQL,
    KC_GRV,  KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_LBRC, KC_RBRC,
    KC_TRNS, KC_NUBS, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NUHS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO,   KC_NO
),

/*
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CAPS |      |      |      |      |      |      |      |PrtScr| Lock |Break |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |Insert| Home | PgUp |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      |      | Alt  |Lower |    Space    |Raise |Delete| End  | PgDn |      |
 * `-----------------------------------------------------------------------------------'
*/

[_RAISE] = LAYOUT_planck_grid(
    KC_F1,   KC_F2, KC_F3, KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_CAPS, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PSCR, KC_SLCK, KC_PAUS, KC_NO,
    KC_TRNS, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_INS,  KC_HOME, KC_PGUP, KC_TRNS,
    KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,  KC_END,  KC_PGDN, KC_NO
)

};
