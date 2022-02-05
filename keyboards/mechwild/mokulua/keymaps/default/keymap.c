// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define FN1_SPC     LT(1, KC_SPC)
#define FN2_SPC     LT(2, KC_SPC)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
	_FN2,
	_FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    /* L00, L01, L02, L03, L04, L05, L06,             R00, R01, R02, R03, R04, R05, R06, */
    /* L10, L11, L12, L13, L14, L15, L16,             R10, R11, R12, R13, R14, R15, R16, */
    /* L20, L21, L22, L23, L24, L25, L26,             R20, R21, R22, R23, R24, R25, R26, */
    /* L30, L31, L32, L33, L34, L35, L36, L37,   R30, R31, R32, R33, R34, R35, R36, R37, */
    /* L40, L41, L42, L43,    L44, L45,   L46,   R40,   R41, R42,    R43, R44, R45, R46  */
    
    [_BASE] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                         KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC, _______,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC, KC_BSLS,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,                         KC_SCLN, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
        KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,    KC_MUTE, KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(2),      FN1_SPC, FN2_SPC,       RGB_RMOD,   RGB_MOD,    FN2_SPC, FN1_SPC,       MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN1] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_DEL,  _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, KC_LBRC, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, KC_SCLN,
        _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,     _______, _______,      _______,    _______,      _______, _______,     _______, _______, _______, _______
    ),
    [_FN2] = LAYOUT(                                                                                   
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,     _______, _______,      _______,    _______,      _______, _______,     _______, _______, _______, _______
    ),
    [_FN3] = LAYOUT(                                                                                   
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, RGB_MOD,    _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,     _______, _______,      _______,    _______,      _______, _______,     _______, _______, _______, _______
    )
};

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
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _FN1:
            oled_write_ln_P(PSTR("FN 1"), false);
            break;
        case _FN2:
            oled_write_ln_P(PSTR("FN 2"), false);
            break;
        case _FN3:
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

