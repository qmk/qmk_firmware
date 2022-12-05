// This keymap was designed to close to the default kc60 layout, with some useful changes, such as adding media keys.
// It also moves the reset key off the base layer, as in the default kc60 layout for this firmware.
// I have swapped FN and RGUI as my rainbow keyset has them in the opposite order.

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   /* Basic QWERTY
	* ,-----------------------------------------------------------.
	* |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
	* |-----------------------------------------------------------|
	* |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
	* |-----------------------------------------------------------|
	* |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
	* |-----------------------------------------------------------|
	* |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
	* |-----------------------------------------------------------|
	* |Ctrl|Gui |Alt |      Space            |Alt |FN  |Gui |Ctrl |
	* `-----------------------------------------------------------'
	*/
  [0] = LAYOUT(
      KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   \
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,   \
      KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NO,    KC_ENT,    \
      KC_LSFT,  KC_NO,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,    KC_RSFT,   \
      KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 KC_NO,    KC_RALT,  MO(1),    KC_RGUI,  KC_RCTL    \
      ),

   /*
	* ,-----------------------------------------------------------.
	* | `  |F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Del   |
	* |-----------------------------------------------------------|
	* |     |   | Up|   |   |   |   |   |   |   | PS|   |   |     |
	* |-----------------------------------------------------------|
	* |       |Lft|Dwn|Rgt|   |BL-|BL+|   |   |   |   |   |       |
	* |-----------------------------------------------------------|
	* |        |Prv| PP|Nxt|   |   |   |   |Hom|End|   |          |
	* |-----------------------------------------------------------|
	* | Rst|    |    |          BL           |    |    |    |     |
	* `-----------------------------------------------------------'
	* PS = Print Screen
	* PP = Play/Pause
	*/
  [1] = LAYOUT( /* Function Layer */
      KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DELETE, \
      KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_PSCR,  KC_TRNS,  KC_TRNS,  KC_TRNS,   \
      KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,  BL_DOWN,  BL_UP,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   \
      KC_TRNS,  KC_TRNS,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_HOME,  KC_END,   KC_TRNS,  KC_TRNS,  KC_TRNS,   \
      QK_BOOT,  KC_TRNS,  KC_TRNS,                      BL_TOGG,                                KC_NO,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS    \
      ),
};
