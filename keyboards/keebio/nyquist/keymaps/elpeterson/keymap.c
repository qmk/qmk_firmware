#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _ALPHA 0
#define _FNCRGB 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ALPHA
 * .-----------------------------------------.    .-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |    |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |  "   |
 * |------+------+------+------+------+-------    |------+------+------+------+------+------|
 * | Shift|   A  |   S  |   D  |   F  |   G  |    |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |    |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+    |------+------+------+------+------+------|
 * | Alt  | GUI  |FNCRGB| Del  |    Space    |    | Left |  Up  | Down |Right | GUI  | Ctrl |
 * '-----------------------------------------'    '-----------------------------------------'
 */
[_ALPHA] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,  KC_3,   KC_4,   KC_5,   KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,  KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_QUOT, \
  KC_LSFT, KC_A,    KC_S,  KC_D,   KC_F,   KC_G,   KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT,  \
  KC_LCTL, KC_Z,    KC_X,  KC_C,   KC_V,   KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  KC_LALT, KC_LGUI, TG(1), KC_DEL, KC_SPC, KC_SPC, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_RGUI, KC_LCTL \
),

/* FNCRGB
 * .-----------------------------------------.    .-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |    |  F6  |  F7  |  F8  |  F9  |  F10 | Bksp |
 * |------+------+------+------+------+------+    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+-------    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |RGBMOI|RGBHUI|RGBSAI|RGBVAI|RGBSPI|      |
 * |------+------+------+------+------+------+    |------+------+------+------+------+------|
 * |      |      | ALPHA|      |             |    |RGBMOD|RGBHUC|RGBSAD|RGBVAD|RGBSPD|RGBTOG|
 * '-----------------------------------------'    '-----------------------------------------'
 */
[_FNCRGB] = LAYOUT(
  KC_NO, KC_F1, KC_F2,   KC_F3, KC_F4, KC_F5, KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO, \
  KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
  KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
  KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_NO, \
  KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_TOG \
)

};
