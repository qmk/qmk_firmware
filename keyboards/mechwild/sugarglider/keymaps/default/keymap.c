// Copyright 2022 Kyle McCreery
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}


enum layer_names {
    _QWERTY,
	_LOWER,
	_RAISE,
    _ADJUST
};

/*
k00, k01, k02, k03, k04, k05,     k30, k31, k32, k33, k34, k35, \
k10, k11, k12, k13, k14, k15,     k40, k41, k42, k43, k44, k45, \
k20, k21, k22, k23, k24, k25,     k50, k51, k52, k53, k54, k55, \
               k63, k64, k65,     k60, k61, k62                 \
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
                                                                                 
  [_QWERTY] = LAYOUT(                                                            
    KC_Q, KC_W,    KC_E, KC_R,    KC_T,    KC_ENT,                       KC_NLCK,    KC_BSPC, KC_Y,    KC_U, KC_I,    KC_O,    KC_P,
    KC_A, KC_S,    KC_D, KC_F,    KC_G,    KC_ENT,           KC_MUTE,    KC_CLCK,    KC_BSPC, KC_H,    KC_J, KC_K,    KC_L,    KC_SCLN,
    KC_Z, KC_X,    KC_C, KC_V,    KC_B,    KC_GESC,                      KC_SLCK,    KC_RGUI, KC_N,    KC_M, KC_COMM, KC_DOT,  KC_SLSH,
          KC_MUTE,       KC_LCTL, KC_LALT, MO(_LOWER), KC_H, KC_H, KC_H, MO(_RAISE), KC_SPC,  KC_RSFT,                KC_MUTE
  ),

  [_LOWER] = LAYOUT(                                                 
    KC_1,        KC_2,    KC_3,    KC_4,    KC_5,    KC_6,         KC_TRNS,  KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS,   KC_EQL,         
    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_LBRC, KC_RBRC, KC_BSLS,   KC_QUOT,
    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,  KC_DEL,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,   KC_TRNS,
                       KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,     KC_TRNS,  KC_TRNS, KC_TRNS,              KC_TRNS            
  ),                                                                                                                 
                                                                                                                     
  [_RAISE] = LAYOUT(                                                                                                 
    KC_EXLM,     KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,       KC_TRNS, KC_AMPR,  KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,   KC_PLUS,           
    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_LCBR, KC_RCBR, KC_PIPE,   KC_DQUO,
    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TAB,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
                       KC_TRNS,            KC_TRNS, TG(_QWERTY), KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,          KC_TRNS       
  ),                                                                                                                 
                                                                                                                     
  [_ADJUST] = LAYOUT(                                                                                                
    KC_F1,       KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        KC_TRNS,  KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,         
    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, RGB_VAD, RGB_RMOD,  RGB_TOG,
    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, RGB_VAI, RGB_MOD,   KC_TRNS,
                         KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,KC_TRNS,KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS,      KC_TRNS
  )
};
  
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


#ifdef OLED_ENABLE
	oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		return OLED_ROTATION_270;       // flips the display 270 degrees
	}

	static void render_logo(void) {     // Render MechWild "MW" Logo
		static const char PROGMEM logo_1[] = {0x8A, 0x8B, 0x8C, 0x8D, 0x00};
		static const char PROGMEM logo_2[] = {0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0x00};
		static const char PROGMEM logo_3[] = {0xCA, 0xCB, 0xCC, 0xCD, 0x00};
		static const char PROGMEM logo_4[] = {0x20, 0x8E, 0x8F, 0x90, 0x00};
		oled_set_cursor(0,0);
		oled_write_P(logo_1, false);
		oled_set_cursor(0,1);
		oled_write_P(logo_2, false);
		oled_set_cursor(0,2);
		oled_write_P(logo_3, false);
		oled_set_cursor(0,3);
		oled_write_P(logo_4, false);
	}

	bool oled_task_user(void) {
		render_logo();
		oled_set_cursor(0,6);

		oled_write_ln_P(PSTR("Layer"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("FN 1"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("FN 2"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("FN 3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
	oled_write_ln_P(PSTR(""), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    return false;
	}
#endif
