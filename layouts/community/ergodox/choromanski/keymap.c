#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Colemak
 * ,--------------------------------------------------.         ,--------------------------------------------------.
 * |   ` ~  |  1 ! | 2 @  | 3 #  | 4 $  | 5 %  |  6 ^ |         | 7 &  |  8 * | 9 (  |  0 ) | - _  | = +  | BSPACE |
 * |--------+------+------+------+------+-------------|         |------+------+------+------+------+------+--------|
 * |   TAB  |   Q  |   W  |   F  |   P  |   G  |      |         |      |   J  |   L  |   U  |   Y  |  ; : |  \ |   |
 * |--------+------+------+------+------+------|  (   |         |   )  |------+------+------+------+------+--------|
 * |   ESC  |   A  |   R  |   S  |   T  |   D  |------|         |------|   H  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------|  {   |         |   }  |------+------+------+------+------+--------|
 * | Shift  |CTR(Z)|GUI(X)|ALT(C)|   V  |   B  |  [   |         |   ]  |   K  |   M  |  , < |ALT(.)|CTR(/)| Shift  |
 * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
 *   |OSL(3)| TG(2)| TO(5)| TO(1)| CAPS |                                      | LEFT | DOWN |  UP  |RIGHT |TG(4)|
 *   `----------------------------------'                                      `---------------------------------'
 *                                      ,--------------.       ,--------------.
 *                                      | LCTR | LALT  |       | RALT | RCTR  |
 *                               ,------|------|-------|       |------+-------+------.
 *                               |      |      | MUTE  |       |SCROLU|       |      |
 *                               |BSPACE|DELETE|-------|       |------| ENTER |SPACE |
 *                               |      |      |  GUI  |       |SCROLD|       |      |
 *                               `---------------------'       `---------------------'
 */
  [0] = LAYOUT_ergodox(
	KC_GRV,		KC_1,			KC_2,			KC_3,			KC_4,		KC_5,		KC_6,
	KC_TAB,		KC_Q,			KC_W,			KC_F,			KC_P,		KC_G,		KC_LPRN,
	KC_ESC,		KC_A,			KC_R,			KC_S,			KC_T,		KC_D,
	KC_LSFT,	CTL_T(KC_Z),	GUI_T(KC_X),	ALT_T(KC_C),	KC_V,		KC_B,		KC_LBRC,
	OSL(3),		TG(2),			TO(5),			TO(1),			KC_CAPS,
																			KC_LCTL,	KC_LALT,
																						KC_MUTE,
																KC_BSPC,	KC_DEL,		KC_LGUI,

	KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,		KC_EQL,			KC_BSPC,
	KC_RPRN,	KC_J,		KC_L,		KC_U,		KC_Y,			KC_SCLN,		KC_BSLS,
				KC_H,		KC_N,		KC_E,		KC_I,			KC_O,			KC_QUOT,
	KC_RBRC,	KC_K,		KC_M,		KC_COMM,	ALT_T(KC_DOT),	CTL_T(KC_SLSH),	KC_RSFT,
							KC_LEFT,	KC_DOWN,	KC_UP,			KC_RGHT,		TG(4),
	KC_RALT,	KC_RCTL,
	KC_WH_U,
	KC_WH_D,	KC_ENT,		KC_SPC
  ),

/* Keymap 1: QWERTY
 *
 * ,--------------------------------------------------.         ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |         |      |      |      |      |      |      |   ESC  |
 * |--------+------+------+------+------+-------------|         |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |         |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
 * |  CAPS  |   A  |   S  |   D  |   F  |   G  |------|         |------|   H  |   J  |   K  |   L  |   ;  |        |
 * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
 * |        |CTL(Z)|GUI(X)|ALT(C)|   V  |   B  |      |         |      |   N  |   M  |  , < |ALT(.)|CTL(/)|        |
 * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
 *   |OSL(3)| TG(2)| TO(5)| TO(0)|      |                                     |      |      |      |      | TG(4)|
 *   `----------------------------------'                                     `----------------------------------'
 *                                      ,-------------.        ,--------------.
 *                                      |      |      |        |      |       |
 *                               ,------|------|------|        |------+-------+------.
 *                               |      |      |      |        |      |       |      |
 *                               |      |      |------|        |------|       |      |
 *                               |      |      |      |        |      |       |      |
 *                               `--------------------'        `---------------------'
 */
  [1] = LAYOUT_ergodox(
	KC_TRNS,	KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_Q,			KC_W,			KC_E,			KC_R,		KC_T,		KC_TRNS,
	KC_CAPS,	KC_A,			KC_S,			KC_D,			KC_F,		KC_G,
	KC_TRNS,	CTL_T(KC_Z),	GUI_T(KC_X),	ALT_T(KC_C),	KC_V,		KC_B,		KC_TRNS,
	OSL(3),		TG(2),			TO(5),			TO(0),			KC_TRNS,
																			KC_TRNS,	KC_TRNS,
																						KC_TRNS,
													KC_TRNS,				KC_TRNS,	KC_TRNS,

	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_TRNS,		KC_ESC,
	KC_RPRN,	KC_Y,		KC_U,		KC_I,		KC_O,			KC_P,			KC_TRNS,
				KC_H,		KC_J,		KC_K,		KC_L,			KC_SCLN,		KC_TRNS,
	KC_RBRC,	KC_N,		KC_M,		KC_COMM,	ALT_T(KC_DOT),	CTL_T(KC_SLSH),	KC_TRNS,
							KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_TRNS,		TG(4),
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS
  ),

/* Keymap 2: Function Row
 *
 * ,--------------------------------------------------.         ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |         |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|         |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |         |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|         |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |         |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                     |      |      |      |      |      |
 *   `----------------------------------'                                     `----------------------------------'
 *                                      ,-------------.        ,--------------.
 *                                      |      |      |        |      |       |
 *                               ,------|------|------|        |------+-------+------.
 *                               |      |      |      |        |      |       |      |
 *                               |      |      |------|        |------|       |      |
 *                               |      |      |      |        |      |       |      |
 *                               `--------------------'        `---------------------'
 */
  [2] = LAYOUT_ergodox(
	KC_TRNS,		KC_F1,			KC_F2,			KC_F3,			KC_F4,			KC_F5,			KC_F6,
	KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,
	KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,
	KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,
	KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,
																					KC_TRNS,		KC_TRNS,
																									KC_TRNS,
																	KC_TRNS,		KC_TRNS,		KC_TRNS,

	KC_F7,			KC_F8,			KC_F9,			KC_F10,			KC_F11,			KC_F12,			KC_TRNS,
	KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,
					KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,
	KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,
									KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,		KC_TRNS,
	KC_TRNS,		KC_TRNS,
	KC_TRNS,
	KC_TRNS,		KC_TRNS,		KC_TRNS
  ),

  /* Keymap 3: Symbols
 *
 * ,--------------------------------------------------.         ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |         |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|         |------+------+------+------+------+------+--------|
 * |        |  |   |  +   |  <   |  >   |  #   |      |         |      |   ~  |   (  |   )  |   \  |   :  |        |
 * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
 * |        |  !   |  -   |  =   |  %   |  @   |------|         |------|   _  |   {  |   }  |   /  |   ?  |        |
 * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
 * |        |  *   |  &   |  /   |  $   |  ^   |      |         |      |   |  |   [  |   ]  |      |      |        |
 * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                     |      |      |      |      |      |
 *   `----------------------------------'                                     `----------------------------------'
 *                                      ,-------------.        ,--------------.
 *                                      |      |      |        |      |       |
 *                               ,------|------|------|        |------+-------+------.
 *                               |      |      |      |        |      |       |      |
 *                               |      |      |------|        |------|       |      |
 *                               |      |      |      |        |      |       |      |
 *                               `--------------------'        `---------------------'
 */
  [3] = LAYOUT_ergodox(
	KC_TRNS,	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,
	KC_TRNS,	KC_PIPE,	KC_PLUS,	KC_LABK,	KC_RABK,	KC_HASH,	KC_TRNS,
	KC_TRNS,	KC_EXLM,	KC_MINS,	KC_EQL,		KC_PERC,	KC_AT,
	KC_TRNS,	KC_ASTR,	KC_AMPR,	KC_SLSH,	KC_DLR,		KC_CIRC,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
																KC_TRNS,	KC_TRNS,
																			KC_TRNS,
														KC_TRNS,KC_TRNS,	KC_TRNS,

	KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_TRNS,
	KC_TRNS,	KC_TILD,	KC_LPRN,	KC_RPRN,	KC_BSLS,	KC_COLN,	KC_TRNS,
				KC_UNDS,	KC_LCBR,	KC_RCBR,	KC_SLSH,	KC_QUES,	KC_TRNS,
	KC_TRNS,	KC_PIPE,	KC_LBRC,	KC_RBRC,	KC_TRNS,	KC_TRNS,	KC_TRNS,
							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS
  ),

/* Keymap 4: Numlock
 *
 * ,--------------------------------------------------.         ,--------------------------------------------------.
 * | POWER  |SLEEP |      |MOUSE3|      |      | QK_BOOT|         |QK_BOOT |SCROL | NUML |  /   |  *   |  -   |        |
 * |--------+------+------+------+------+-------------|         |------+------+------+------+------+------+--------|
 * |        |      |MOUSE1|MOUSEU|MOUSE2|SCROLU|      |         |      |      |  7   |  8   |  9   |  +   | ACCEL0 |
 * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
 * |        |      |MOUSEL|MOUSED|MOUSER|SCROLD|------|         |------|      |  4   |  5   |  6   |  +   | ACCEL1 |
 * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
 * |        |      |ACCEL0|ACCEL1|ACCEL2|      |      |         |      |      |  1   |  2   |  3   |ENTER | ACCEL2 |
 * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                     |  0   |  0   |  .   |ENTER |      |
 *   `----------------------------------'                                     `----------------------------------'
 *                                      ,-------------.        ,-------------.
 *                                      | VOL+ | VOL- |        |MEDIA<|MEDIA>|
 *                               ,------|------|------|        |------+------+------.
 *                               |      |      | MUTE |        |Pause |      |      |
 *                               |      |      |------|        |------|      |      |
 *                               |      |      |FILES |        | CALC |      |      |
 *                               `--------------------'        `--------------------'
 */
  [4] = LAYOUT_ergodox(
	KC_PWR,		KC_SLEP,	KC_TRNS,	KC_BTN3,	KC_TRNS,	KC_TRNS,	QK_BOOT,
	KC_TRNS,	KC_TRNS,	KC_BTN1,	KC_MS_U,	KC_BTN2,	KC_WH_U,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_WH_D,
	KC_TRNS,	KC_TRNS,	KC_ACL0,	KC_ACL1,	KC_ACL2,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
																KC_VOLD,	KC_VOLU,
																			KC_MUTE,
													KC_TRNS,	KC_TRNS,	KC_MYCM,

	QK_BOOT,	KC_SCRL,	KC_NUM,		KC_SLSH,	KC_ASTR,	KC_MINS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_7,		KC_8,		KC_9,		KC_PLUS,	KC_ACL2,
				KC_TRNS,	KC_4,		KC_5,		KC_6,		KC_PLUS,	KC_ACL1,
	KC_TRNS,	KC_TRNS,	KC_1,		KC_2,		KC_3,		KC_ENT,		KC_ACL0,
							KC_0,		KC_0,		KC_DOT,		KC_ENT,		KC_TRNS,
	KC_MPRV,	KC_MNXT,
	KC_MPLY,
	KC_CALC,	KC_TRNS,	KC_TRNS
  ),

/* Keymap 5: Gaming
 * ,--------------------------------------------------.        ,--------------------------------------------------.
 * |   ` ~  |  1 ! | 2 @  | 3 #  | 4 $  | 5 %  |  6 ^ |        | 7 &  |  8 * | 9 (  |  0 ) | - _  | = +  |  ESC   |
 * |--------+------+------+------+------+-------------|        |------+------+------+------+------+------+--------|
 * |   TAB  |   Q  |   W  |   E  |   R  |   T  |      |        |      |   Y  |   U  |   I  |   O  |  P   |  \ |   |
 * |--------+------+------+------+------+------|  (   |        |   )  |------+------+------+------+------+--------|
 * |   LCTR |   A  |   S  |   D  |   F  |   G  |------|        |------|   H  |   J  |   K  |   L  |  ; : |  ' "   |
 * |--------+------+------+------+------+------| MEDIA|        |   }  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |  P/P |        |   ]  |   K  |   M  |  UP  |  . > |  / ? | Shift  |
 * `--------+------+------+------+------+-------------'        `-------------+------+------+------+------+--------'
 *   | LCTR |ALTTAB| TO(0)| ALT  | SPACE|                                    | LEFT | DOWN | RIGHT|  , < |TO(0) |
 *   `----------------------------------'                                    `----------------------------------'
 *                                      ,--------------.       ,--------------.
 *                                      |MEDIA<| MEDIA>|       | RALT | RCTR  |
 *                               ,------|------|-------|       |------+-------+------.
 *                               |      |      | VOL+  |       | PGUP |       |      |
 *                               |SPACE |ENTER |-------|       |------|BSPACE |DELETE|
 *                               |      |      | VOL-  |       | PGDWN|       |      |
 *                               `---------------------'       `---------------------'
 */
  [5] = LAYOUT_ergodox(
	KC_GRV,		KC_1,			KC_2,	KC_3,		KC_4,		KC_5,		KC_6,
	KC_TAB,		KC_Q,			KC_W,	KC_E,		KC_R,		KC_T,		KC_TRNS,
	KC_LCTL,	KC_A,			KC_S,	KC_D,		KC_F,		KC_G,
	KC_LSFT,	KC_Z,			KC_X,	KC_C,		KC_V,		KC_B,		KC_MPLY,
	KC_LCTL,	LALT(KC_TAB),	TO(0),	KC_LALT,	KC_SPC,
																KC_MPRV,	KC_MNXT,
																  			KC_VOLU,
										  			KC_SPC,		KC_ENT,		KC_VOLD,

	KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,	KC_EQL,		KC_ESC,
	KC_TRNS,	KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_BSLS,
				KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOTE,
	KC_TRNS,	KC_N,		KC_M,		KC_UP,		KC_DOT,		KC_SLSH,	KC_LSFT,
							KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_COMM,	TO(0),
	KC_LALT,	KC_LCTL,
	KC_PGUP,
	KC_PGDN,	KC_BSPC,	KC_DEL
  ),
};

void matrix_scan_user(void) {

	uint8_t layer = get_highest_layer(layer_state);

	ergodox_board_led_off();
	ergodox_right_led_1_off();
	ergodox_right_led_2_off();
	ergodox_right_led_3_off();
	switch (layer) {
		case 1:
			ergodox_right_led_1_on();
			break;
		case 2:
			ergodox_right_led_2_on();
			break;
		case 3:
			ergodox_right_led_3_on();
			break;
		case 4:
			ergodox_right_led_1_on();
			ergodox_right_led_2_on();
			break;
		case 5:
			ergodox_right_led_1_on();
			ergodox_right_led_3_on();
			break;
		case 6:
			ergodox_right_led_2_on();
			ergodox_right_led_3_on();
			break;
		default:
			break;
	}

};
