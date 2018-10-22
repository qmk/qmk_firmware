#include QMK_KEYBOARD_H

// My layout is practically the default HHKB layout.
#define _DEFAULT 0
#define _ALTFN 1
#define _MOUSEFN 2
#define _FN 3
#define _LIGHTS 4


#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


 /* BASE LAYER
 *
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \| | ~ ` |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
 * |-----------------------------------------------------------------------------------------+
 * | CTRL    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  RShift   |  FN |
 * |-----------------------------------------------------------------------------------------+
 * |              Win  |      Alt  |            Space       |   Alt     |    LIGHTS          |
 * `-----------------------------------------------------------------------------------------'
 */


	[_DEFAULT] = LAYOUT_60_hhkb(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSLS, KC_GRV,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSPC,
		KC_LCTL,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT, MO(_FN),
		            KC_LGUI,             KC_LALT,                      KC_SPC,                    MO(_ALTFN),           MO(_LIGHTS)),





/* ALTFN LAYER
 *
 *  ,---------------------------------------------------------------------------------------------------------------------
 * |         | F1   | F2   | F3   | F4    | F5    | F6    | F7   | F8    | F9   | F10   | F11   | F12   | INSERT  |  _   |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | CAPS     |   _  |   _  |   _   |    _  |    _  |    _  |    _  |    _   |    _   |  UP  |  V_DEC   |  V_INC  | DEL  |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | CTRL       |   _   |   _   |   _   |   _   |   _    |   _  | HOME |   END    | LEFT | DOWN | RIGHT  |    _          |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | Shift         |  _   |  _   |  _   |  _   |  _   |  _   |  _   |  PREV  |    NEXT  |  PLAY  |    _       |   _      |
 * |---------------------------------------------------------------------------------------------------------------------+
 * |                          _    |      _     |               _               |     _      |     _                     |
 * `---------------------------------------------------------------------------------------------------------------------'
 */

	[_ALTFN] = LAYOUT_60_hhkb(

		MO(_MOUSEFN),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  ______,  KC_PSCR,
		KC_CAPS,          ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  KC_UP,  KC_VOLD,   KC_VOLU,  KC_DEL,
		______,             ______,  ______,  ______,  ______,  ______,  ______,  KC_HOME,  KC_END, KC_LEFT,   KC_DOWN,   KC_RIGHT, ______,
		______,            ______,  ______,  ______, ______, ______,   ______,  ______,  KC_MPRV,  KC_MNXT, KC_MPLY,     ______,  ______,
		         ______,           ______,                    ______,                              ______,            ______),







/* MOUSEFN LAYER
 *
 *  ,---------------------------------------------------------------------------------------------------------------------
 * |        |  ACC_1  |  ACC_2  |  ACC_3  |  _    |  _    |  _    |  _   |  _    |  _   |  _   |  _   |  _   | _  |  _   |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | CAPS     |   _  |   _  |   _   |    _  |    _  |    _  |    _  |    _   |  _  |  WHEEL_UP  |   _   |    _   |   _   |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | CTRL       |   _   |   _   |   _   |   _   |   _    |   _  | _ |   _    |  WH_LEFT |  WH_DOWN |  WH_RIGHT  |    _   |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | Shift         |  _   |  _   |  _   |  _   |  _   |  _   |  _   |   _    |    _    |    _    |    _       |   _      |
 * |---------------------------------------------------------------------------------------------------------------------+
 * |                          _    |      _     |               _               |     _      |     _                     |
 * `---------------------------------------------------------------------------------------------------------------------'
 */


	[_MOUSEFN] = LAYOUT_60_hhkb(

		______,  KC_ACL0,   KC_ACL1,   KC_ACL2,   ______,   ______,   ______,   ______,   ______,   ______,   ______,  ______,   ______,  ______,  ______,
		______,          ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  KC_MS_UP,    ______,   ______,  ______,
		______,             ______,  ______,  ______,  ______,  ______,  ______,  ______,   ______,  KC_MS_LEFT,   KC_MS_DOWN,  KC_MS_RIGHT,   ______,
		______,            ______,  ______,  ______, ______, ______,   ______,  ______,  ______,  ______, ______,     ______,  ______,
		         ______,           ______,                    ______,                              ______,            ______),







/* FN LAYER
 *
 *  ,------------------------------------------------------------------------------------------------------
 * |         | F1  | F2  | F3  | F4   | F5   | F6   | F7  | F8   | F9  | F10  | F11  | F12  |INSERT |  _  |
 * |------------------------------------------------------------------------------------------------------+
 * | CAPS     |  _  |  _  |  _   |  _  |  _  |  _  |  _  |  PRSC  |  SLOCK |  PAUSE |  UP   |  _  | DEL   |
 * |------------------------------------------------------------------------------------------------------+
 * | CTRL       |  _  |  VOLDOWN  |  VOLUP  |  VOLMUTE  | _ | _ | _ | HOME | PGUP  | LEFT | IGHT |   _    |
 * |------------------------------------------------------------------------------------------------------+
 * | Shift         |  _   |  _   |  _   |  _   |  _   |  _   |  _   |  END  |  PGDN  | DOWN  |  _  |   _  |
 * |------------------------------------------------------------------------------------------------------+
 * |                 _    |      _     |               _               |     _      |     _               |
 * `------------------------------------------------------------------------------------------------------'
 */



	[_FN] = LAYOUT_60_hhkb(
		______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_INS,  ______,
		KC_CAPS,          ______,  ______,  ______,  ______,  ______,  ______,  ______,  KC_PSCR, KC_SLCK, KC_PAUS,  KC_UP,   ______,  KC_DEL,
		______,           KC_VOLD, KC_VOLU, KC_MUTE, ______,  ______,  KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT,  KC_RGHT, ______,
		______,           KC_MPRV, KC_MPLY, KC_MNXT, ______,  ______,  KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN,           ______,  ______,
		         ______,           ______,                    ______,                                      ______,            ______),







/* LIGHTS LAYER
 *
 *  ,---------------------------------------------------------------------------------------------------------------------+
 * | RGB_TOGGLE  | STATIC | BREATHE | RAINBOW | SWIRL | SNAKE | KNIGHTRIDER | XMAS | STATIC_GRAD | _ |  _ | _ | _ | _ | _ |
 * |----------------------------------------------------------------------------------------------------------------------+
 * | RBG_MOD      |  HUE_INC |  SATURATION_INC  |  BRIGHT_INC   |  _  |  _  |  _  |  _ |  _ |  _ |  _ |  _  |  _  |  _    |
 * |----------------------------------------------------------------------------------------------------------------------+
 * | CTRL           |  HUE_DEC |  SATURATION_DEC  |  BRIGHT_DEC  |  _  |  _  |  _ |  _  |  _  |  _  |  _  |  _  |    _    |
 * |----------------------------------------------------------------------------------------------------------------------+
 * | Shift                |   _   |   _   |   _   |   _   |   _   |   _   |   _   |   _   |   _   |   _   |  _   |    _   |
 * |----------------------------------------------------------------------------------------------------------------------+
 * |                             _    |      _     |               _               |     _      |     _                   |
 * `----------------------------------------------------------------------------------------------------------------------'
 */



	[_LIGHTS] = LAYOUT_60_hhkb(
		RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, ______, ______, ______, ______, ______, ______,
		RGB_MOD,          RGB_HUI, RGB_SAI, RGB_VAI,  ______,   ______,  ______,  ______,  ______, ______, ______, ______, ______, ______,
		______,           RGB_HUD, RGB_SAD, RGB_VAD,  ______,   ______,  ______,  ______,  ______, ______, ______, ______, ______,
		______,           ______,  ______,  ______,   ______,  ______,  ______,  ______,  ______, ______, ______,         ______, ______,
		         ______,           ______,                      ______,                                    ______,         ______),

};


/*

RGB controls

Key       ->  Description
=========================

RGB_TOG   ->  Toggle RGB lighting on or off

RGB_MOD   ->  Cycle through modes, reverse direction when Shift is held

RGB_RMOD  ->  Cycle through modes in reverse, forward direction when Shift is held

RGB_HUI   ->  Increase hue

RGB_HUD   ->  Decrease hue

RGB_SAI   ->  Increase saturation

RGB_SAD   ->  Decrease saturation

RGB_VAI   ->  Increase value (brightness)

RGB_VAD   ->  Decrease value (brightness)

RGB_M_P   ->  Static (no animation) mode

RGB_M_B   ->  Breathing animation mode

RGB_M_R   ->  Rainbow animation mode

RGB_M_SW  ->  Swirl animation mode

RGB_M_SN  ->  Snake animation mode

RGB_M_K   ->  "Knight Rider" animation mode

RGB_M_X   ->  Christmas animation mode

RGB_M_G   ->  Static gradient animation mode

*/

/*
  Mouse controls:

  Key           ->   Aliases  ->  Description
  ==================================================

  KC_MS_UP      ->   KC_MS_U  ->   Mouse Cursor Up

  KC_MS_DOWN    ->   KC_MS_D  ->   Mouse Cursor Down

  KC_MS_LEFT    ->   KC_MS_L  ->   Mouse Cursor Left

  KC_MS_RIGHT   ->   KC_MS_R  ->  Mouse Cursor Right

  KC_MS_BTN1    ->   KC_BTN1  ->   Mouse Button 1

  KC_MS_BTN2    ->   KC_BTN2  ->   Mouse Button 2

  KC_MS_BTN3    ->   KC_BTN3  ->   Mouse Button 3

  KC_MS_BTN4    ->   KC_BTN4  ->   Mouse Button 4

  KC_MS_BTN5    ->   KC_BTN5  ->   Mouse Button 5

KC_MS_WH_UP     ->   KC_WH_U  ->  Mouse Wheel Up

KC_MS_WH_DOWN   ->   KC_WH_D  ->  Mouse Wheel Down

KC_MS_WH_LEFT   ->   KC_WH_L  ->  Mouse Wheel Left

KC_MS_WH_RIGHT  ->   KC_WH_R  ->   Mouse Wheel Right

KC_MS_ACCEL0    ->   KC_ACL0  ->   Set mouse acceleration to 0

KC_MS_ACCEL1    ->   KC_ACL1  ->   Set mouse acceleration to 1

KC_MS_ACCEL2    ->   KC_ACL2  ->   Set mouse acceleration to 2

*/

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {


	switch (id) {

	}
	return MACRO_NONE;
}
