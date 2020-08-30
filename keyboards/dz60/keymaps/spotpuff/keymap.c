#include QMK_KEYBOARD_H

//Layers
enum layer_names {
	_QWERTY,
	_FN,
	_MEDIA,
};

//Custom Keymap Definitions
#define KC_CAD LALT(LCTL(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty Base layer
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | BSpc| Del |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \    |
 * |-----------------------------------------------------------------------------------------+
 * | `/_Media|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |PgUp | Up  |PgDn |
 * |-----------------------------------------------------------------------------------------+
 * | LCtrl | LGui  | LAlt  |     Space     |  Fn  |    Space   |Home | End |Left |Down |Right|
 *  `----------------------------------------------------------------------------------------'
 */

	[_QWERTY] = LAYOUT_directional(
		KC_ESC,  KC_1,    KC_2,    KC_3,  KC_4,    KC_5,   KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL, 
		KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,    KC_T,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, 
		LT(_MEDIA,KC_GRV),KC_A,    KC_S,  KC_D,    KC_F,   KC_G,    KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, 
		KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,    KC_B,   KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_PGUP, KC_UP,   KC_PGDN,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,MO(_FN), KC_SPC, KC_HOME, KC_END, KC_LEFT, KC_DOWN, KC_RGHT 
		),

/* F-Key/Lighting/whatever layer
 * ,-----------------------------------------------------------------------------------------.
 * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F0  | F11 | F12 |     | Ins |
 * |-----------------------------------------------------------------------------------------+
 * |       |R_Tog|R_HUI|R_SAI|R_VAI|     |     |     |     |     |     |     |     |  KC_CAD |
 * |-----------------------------------------------------------------------------------------+
 * |  Caps  |     |R_HUD|R_SAD|     |      |     |     |     |     | SLCK|PAUSE| Print Screen|
 * |-----------------------------------------------------------------------------------------+
 * |          |R_M_P|R_M_B|R_M_R|R_M_SW|R_M_S|R_M_K|R_M_X|R_M_G|     |     |     |BLUP |     |
 * |-----------------------------------------------------------------------------------------+
 * |       |       |       |               |      |            |     |     |BLTog|BLDN |BLInc|
 *  `----------------------------------------------------------------------------------------'
 */

	[_FN] = LAYOUT_directional( 
		KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_NO, KC_INS,
		KC_NO,   RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,  KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_CAD, 
		KC_CAPS, KC_NO,   RGB_HUD, RGB_SAD, RGB_VAD,  KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,  KC_SLCK, KC_PAUS, KC_PSCR, 
		KC_TRNS, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_M_X, RGB_M_G, KC_NO,  KC_NO,   KC_NO,   BL_INC, KC_NO, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS,  KC_NO,    KC_NO,    KC_NO,   BL_TOGG, BL_DEC, BL_STEP 
		),

/* SFX/Multimedia/Numpad layer
 * ,-----------------------------------------------------------------------------------------.
 * |     |     |     |     |     |     |NumLk|     |  /  |  *  |  -  |  =  |     |Trns |Trns |
 * |-----------------------------------------------------------------------------------------+
 * |        |     | Prev | Play| Next|     |     |  7  |  8  |  9  |  +  |     |     | RESET |
 * |-----------------------------------------------------------------------------------------+
 * |         |     |Mute | VUp | VDn |     |     |  4  |  5  |  6  |  +  |     |    Trns     |
 * |-----------------------------------------------------------------------------------------+
 * |           |     |     |     |     |     |     |  1  |  2  |  3  |NumEN|     |     |     |
 * |-----------------------------------------------------------------------------------------+
 * | Trns  | Trns  | Trns  |    Trns       |      |     0      |  .  |     |     |     |     |
 *  `----------------------------------------------------------------------------------------'
 */
	[_MEDIA] = LAYOUT_directional(
		KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NLCK, KC_NO, KC_PSLS, KC_PAST, KC_PMNS, KC_PEQL, KC_NO,   KC_TRNS, KC_TRNS,
		KC_NO,   KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO,   KC_P7, KC_P8,   KC_P9,   KC_PPLS, KC_NO,   KC_NO,   RESET,
		KC_TRNS, KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO,   KC_P4, KC_P5,   KC_P6,   KC_PPLS, KC_NO,   KC_TRNS,
		KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_P1, KC_P2,   KC_P3,   KC_PENT, KC_NO,   KC_NO,   KC_NO,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PDOT, KC_NO, KC_NO,   KC_NO,   KC_NO
		)
};