// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
	autoshift_disable();
}

enum layers {
    _QWERTY,
    _NUM,
    _FN,
    _SYS,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_NUMERIC,
    KC_FUNCTION,
	KC_SYSTEM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
      KC_ESC, 	 KC_1, 	    KC_2,      KC_3,	   KC_4,     KC_5,  	KC_MPLY,      KC_MPLY,    KC_6,  	 KC_7,   	KC_8,       KC_9,      KC_0,    KC_MINS,
      KC_TAB, 	 KC_Q, 	    KC_W,      KC_E,      KC_R,      KC_T,                     		       KC_Y,     KC_U,      KC_I,      KC_O,       KC_P,    KC_LBRC,
      KC_CAPS, 	 KC_A, 	    KC_S,       KC_D,      KC_F,    KC_G,                     			   KC_H, 	 KC_J,      KC_K,       KC_L,    KC_SCLN,   KC_QUOT,
LCTL_T(KC_LEFT), KC_Z, 	    KC_X,      KC_C,      KC_V,       KC_B,     KC_DOWN,       KC_UP,      KC_N,	KC_M,       KC_COMM,   KC_DOT,    KC_SLSH, RCTL_T(KC_RGHT),
                                      KC_LGUI,   TG(_FN),   KC_LALT, LSFT_T(KC_SPC),RSFT_T(KC_ENT), KC_RALT, TG(_NUM), MT(MOD_RGUI,KC_BSPC)
),

[_NUM] = LAYOUT(
  _______,   KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,  _______,      _______, KC_CIRC,    KC_KP_7,    KC_KP_8,    KC_KP_9, XXXXXXX, XXXXXXX,
  _______, XXXXXXX,   KC_UP,  XXXXXXX, XXXXXXX, XXXXXXX,                         KC_HASH,    KC_KP_4,    KC_KP_5,    KC_KP_6, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, KC_LBRC, KC_RBRC,                         KC_AMPR,    KC_KP_1,    KC_KP_2,    KC_KP_3, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, KC_PAST,  KC_PPLS, KC_PSLS,  KC_EQL, _______,       _______,  KC_DLR,    KC_KP_0, KC_KP_DOT, KC_COLN, KC_PMNS, _______,
							  _______, _______, _______, _______,       _______, _______, _______, _______ 
),

[_FN] = LAYOUT(
	  _______,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     _______,      _______,    KC_F6,    KC_F7,      KC_F8,     KC_F9,    KC_F10,    _______,
     _______,   _______,   _______,   _______,   _______,   _______,                             _______,   _______,   _______,   _______,   _______,   _______,
     _______,   _______,   _______,   _______,   _______,   _______,                             _______,   _______,   _______,   _______,   _______,   _______,
     _______,   _______,   _______,   _______,   _______,   _______,    _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,
            					      _______,   _______,   _______,  _______,         _______,  _______,   _______,   _______
),

[_SYS] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX ,  XXXXXXX, XXXXXXX, XXXXXXX, _______,     _______, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_SAI, RGB_TOG,
  QK_BOOT, XXXXXXX, KC_QWERTY, XXXXXXX, XXXXXXX, AS_TOGG,                       XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD, RGB_SAD, RGB_M_P,
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_CAPS,                       XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUI, RGB_VAI, RGB_M_B,
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_VAD, RGB_M_R,
								_______, _______, _______, _______,     _______, _______, _______, _______ 
  )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NUM] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_SYS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

// This function allows switching to the 'hidden' layer. DO NOT EDIT!
layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, 1, 2, 3);
}

// Rotate OLED to fit vertical placement. DO NOT EDIT!
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
	
    if (is_keyboard_left()) {
        return OLED_ROTATION_90;
	}
    return OLED_ROTATION_270;
}

// Renders default QMK Logo. DO NOT EDIT!
void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
	// Create OLED content
    oled_write_P(PSTR("\n"), false);
	oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Lotus -58-"), false);
	oled_write_P(PSTR("\n"), false);

    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("-Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("-Num \n"), false);
            break;
        case 2:
            oled_write_P(PSTR("-Func\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("-Sys \n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
	
	// Display autoshift
    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("Caps- lock"), led_usb_state.caps_lock);
	bool autoshift = get_autoshift_state();
	oled_write_P(PSTR("\n"), false);
	oled_write_P(PSTR("Auto-Shift"), autoshift);
	oled_write_P(PSTR("\n"), false);
	
}

bool oled_task_user(void) {
	// Render the OLED
	if (is_keyboard_left()) {
		print_status_narrow();
		//render_logo();
    } else {
		print_status_narrow();
        //render_logo();
    }
	return false;
}