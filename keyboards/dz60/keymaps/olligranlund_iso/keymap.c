#include QMK_KEYBOARD_H

/* ISO 60 layout by olligranlund
*
* This layout starts from a standard ISO 60% layout, and adds one function layer.
* If you wish to only have one wide spacebar, you can easily do that by dismissing the "side" spacebar switches.
*
* Default Layer
* ,-----------------------------------------------------------------------------------------.
* | Esc | 1 ! | 2 " | 3 § | 4 $ | 5 % | 6 & | 7 / | 8 ( | 9 ) | 0 = | ß ? | ´ ` | Del | BSPC|
* |-----------------------------------------------------------------------------------------|
* | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  Ä  | + * | Enter  |
* |----------------------------------------------------------------------------------       |
* | FN      |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Ö  |  Ü  | # ' |       |
* |-----------------------------------------------------------------------------------------|
* | Shift | < > |  Z  |  X  |  C  |  V  |  B  |  N  |  M  | , ; | . : | - _ |  Shift  |Shift|
* |-----------------------------------------------------------------------------------------|
* | LCtl  | LGUI  | LAlt  |  Space      | Space |  Space      | RAlt  | FN    | App  | RCtl |
* `-----------------------------------------------------------------------------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT_60_iso_split_space_bs_rshift(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL, KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
		MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
		KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_PSCR,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, MO(1),    KC_APP,  KC_RCTL),

	LAYOUT_60_iso_split_space_bs_rshift(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,
		KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,   KC_NO,   KC_PGDOWN,KC_UP,   KC_PGUP, KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,   KC_NO,   KC_HOME,  KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_END,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT, KC_CAPS,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, MO(1),    KC_APP,  KC_RCTL),

};
