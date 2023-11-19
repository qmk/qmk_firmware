#include QMK_KEYBOARD_H


/*---default defines-------------------------------------------- */
#define LT1_SPC     LT(1, KC_SPC)
#define LT2_SPC     LT(2, KC_SPC)


#define RGB_STA RGB_M_P		// rgb static
#define RGB_BRE RGB_M_B 	// rgb breathe
#define RGB_RAI RGB_M_R 	// rgb rainbow
#define RGB_SWI RGB_M_SW 	// rgb swirl
#define RGB_SNA RGB_M_SN	// rgb snake9
#define RGB_KNI RGB_M_K 	// rgb knight
#define RGB_GRA RGB_M_G 	// rgb gradient


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default layer
  [0] = LAYOUT_all(
		KC_VOLU, KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		KC_VOLD, MT(MOD_LCTL, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
		KC_MUTE, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, KC_RSFT,
		KC_MPLY, KC_LGUI, KC_LALT, LT2_SPC, LT1_SPC, KC_RALT, MO(3)
  ),
  // Numerals layer
  [1] = LAYOUT_all(
		KC_BRIU, QK_GESC,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL, KC_DEL,
		KC_BRID, KC_CAPS, _______, _______, _______, _______, _______, _______, KC_4, KC_5,    KC_6,   _______, _______, _______,
		RGB_MOD, _______, _______, _______, _______, _______, KC_0, KC_1, KC_2, KC_3, _______, _______, _______, _______,
		RGB_RMOD, _______, _______, _______, _______, _______, _______
  ),
  // FN & Navigation layer
  [2] = LAYOUT_all(
		KC_PGUP, _______,  KC_END, KC_UP, KC_HOME, _______, _______, _______, KC_F1, KC_F2,    KC_F3,   KC_F4,    _______, _______, _______,
		KC_PGDN, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, KC_F5, KC_F6,    KC_F7,   KC_F8, _______, _______,
		KC_PSCR, _______, _______, _______, _______, _______, _______, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, _______,
		KC_RGUI, _______, _______, _______, _______, _______, _______
  ),
  // RGB Control Layer
  [3] = LAYOUT_all(
		RGB_SPI, RGB_TOG, RGB_HUD, RGB_VAI, RGB_HUI, _______, _______, _______, _______, _______,    _______,   _______,    _______, _______, QK_BOOT,
		RGB_SPD, _______, RGB_SAD, RGB_VAD, RGB_SAI, _______, _______, _______, _______, _______,    _______,   _______, _______, _______,
		_______, _______, RGB_STA, RGB_BRE, RGB_RAI, RGB_SWI, RGB_SNA, RGB_KNI, RGB_GRA, VK_TOGG, _______, _______, _______, EE_CLR,
		_______, _______, _______, _______, _______, _______, _______
  )
};
