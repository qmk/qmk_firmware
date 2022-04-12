/* 
   Last updated: 3 Aug 2019
   DZ60 Layout by ottodokto

   This layout is a modification of the 60 tsangan hhkb layout, 
   with an additional layer to update the arrow keys and 
   */

#include QMK_KEYBOARD_H

/*---Layers-------------------------------------------- */
#define _base 0 // default, tsangan layout with split backspace
#define _func 1 // media controls and reset buttons

/*---defines-------------------------------------------- */
#define KC_CTOG LT(_func, KC_CAPS)
#define KC_TTAP TT(_func)

#define RGB_STA RGB_M_P		// rgb static
#define RGB_BRE RGB_M_B 	// rgb breathe
#define RGB_RAI RGB_M_R 	// rgb rainbow
#define RGB_SWI RGB_M_SW 	// rgb swirl
#define RGB_SNA RGB_M_SN	// rgb snake
#define RGB_KNI RGB_M_K 	// rgb knight
#define RGB_GRA RGB_M_G 	// rgb gradient


/*---Layout-------------------------------------------- */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_base] = LAYOUT_60_tsangan_hhkb(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, \
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, \
		KC_CTOG, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_TTAP, \
		KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_RCTL 
	),
    [_func] = LAYOUT_60_tsangan_hhkb(
		RGB_TOG, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, RESET, \
		_______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, RGB_SPI, RGB_HUD, RGB_VAI, RGB_HUI, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL, \
		_______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, RGB_SPD, RGB_SAD, RGB_VAD, RGB_SAI, KC_BRID, KC_BRIU, _______, \
		_______, RGB_STA, RGB_BRE, RGB_RAI, RGB_SWI, RGB_SNA, RGB_KNI, RGB_GRA, VLK_TOG, _______, _______, _______, _______, \
		_______, _______, _______,                            _______,                            _______, _______, _______
    )
};