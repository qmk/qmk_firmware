#include QMK_KEYBOARD_H

// readability
#define _______ KC_TRNS
#define XXXXXXX KC_NO
enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _NUMPAD,
  _RGB
};

enum keycodes {
  LOWER,
  RAISE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Layer QWERTY
	 * ,-----------------------------------------------------------------------------------.
	 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |  
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | GUI |  Ctrl | ALT  |ADJUST|LOWER |    Space    |RAISE |  /   |  {   |   }  |   |  |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_QWERTY] = LAYOUT_planck_mit(
		KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,      KC_BSPC,
		KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN,   KC_QUOT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH,   KC_ENT,
		KC_LGUI, KC_LCTL, KC_LALT, MO(_NUMPAD), LOWER,KC_SPC,RAISE, KC_UP ,  KC_LCBR, KC_RCBR,   KC_PIPE
  ),

   /* LOWER
    Think about creating a colummn for the underscore equal brackets semi, period 
	that way you wouldn't have to think as much about where those keys are at.
		
	* ,-----------------------------------------------------------------------------------.
	* |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   Up |   (  |   )  | Bksp |
	* |------+------+------+------+------+-------------+------+------+------+------+------|
	* | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | Left | Down |Right |   }  |  |   |
	* |------+------+------+------+------+------|------+------+------+------+------+------|
	* |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
	* |------+------+------+------+------+------+------+------+------+------+------+------| 
	* |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
	* `-----------------------------------------------------------------------------------'
	*/
	[_LOWER] = LAYOUT_planck_mit(
	KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_UP,    KC_LPRN, KC_RPRN, KC_BSPC,
	KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LEFT,    KC_DOWN,    KC_RIGHT, KC_RCBR, KC_PIPE,
	_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
	_______, _______, _______, _______, _______,     _______,      _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
	),

   /* RAISE
	* ,-----------------------------------------------------------------------------------.
	* |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
	* |------+------+------+------+------+-------------+------+------+------+------+------|
	* | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
	* |------+------+------+------+------+------|------+------+------+------+------+------|
	* |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |   -  |  =   |      |
	* |------+------+------+------+------+------+------+------+------+------+------+------|
	* |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
	* `-----------------------------------------------------------------------------------'
	*/

	[_RAISE] = LAYOUT_planck_mit(
	KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
	KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
	_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_MINS, KC_EQL,  _______,
	_______, _______, _______, _______, _______,     _______,      _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
	),

  	/* NUMPAD 
	 * ,-----------------------------------------------------------------------------------.
	 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |   4  |   5  |   6  |      |      |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |   1  |   2  |   3  |      |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |   0  |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_NUMPAD] = LAYOUT_planck_mit(
		_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
		_______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3, _______, _______,
		_______, _______, _______, _______, _______,     _______,   _______,    KC_0, _______, _______, _______
  ),

    /* RGB control. Raise and Lower at the same time. 
   * ,-----------------------------------------------------------------------------------.
   * |      | Reset|      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      |BLtogg|BLstep|      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |RGBtog|RGBmod|RGBhud|RGBhui|RGBsai|RGBsad|      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |             |      |      |      |      | RESET|
   * `-----------------------------------------------------------------------------------'
   */
  [_RGB] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, BL_TOGG, BL_STEP, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, RESET
  )
};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _RGB);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _RGB);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _RGB);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _RGB);
      }
      return false;
      break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
