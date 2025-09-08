// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum my_keycodes {
  FOO = SAFE_RANGE,
  RGB_LYR
};

enum custom_layers {
	 _NEU = 0,
	 _GAMES = 1,
     _LOWER = 2,
     _UPPER = 3,
	 _ADJUST = 4
};

// Combinations used all the time.

#define KC_CAD LCTL(LALT(KC_DEL))
#define KC_CSE LCTL(LSFT(KC_ENT))

// Homerow for Neu

#define CRL_T LCTL_T(KC_T)
#define SFT_N LSFT_T(KC_N)
#define	ALT_S LALT_T(KC_S)
#define	RLT_R RALT_T(KC_R)

#define CRL_A LCTL_T(KC_A)
#define SFT_E LSFT_T(KC_E)
#define	ALT_I LALT_T(KC_I)
#define	RLT_H RALT_T(KC_H)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
/* HANDS DOWN NEU
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                   ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │ ESC  │   1  │   2  │   3  │   4  │   5  │                   │   6  │   7  │   8  │   9  │   0  │  \ | │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   W  │   F  │   M  │   P  │   V  │                   │  : ; │   Q  │  , < │  . > │   Z  │  / ? │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Caps │RLT(R)│ALT(S)│SFT(N)│CRL(T)│   G  │                   │  ' " │CRL(A)│SFT(E)│ALT(I)│RLT(H)│  J   │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐     ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ LCTR │   X  │   C  │   L  │   D  │   B  │ Enter│     │  GUI │  - _ │   U  │   O  │   Y  │   K  │  = + │
 * └──────┴──────┴──────┴────┬─┴────┬─┴────┬─┴────┬─┘     └─┬────┴─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
 *                           │  [ { │ LOWER│ BKPC │         │Space │UPPER │ ] }  │
 *                           └──────┴──────┴──────┘         └──────┴──────┴──────┘
 */
  
  [_NEU] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
     KC_TAB,  KC_W,    KC_F,    KC_M,    KC_P,    KC_V,                           KC_SCLN, KC_Q,    KC_COMM, KC_DOT,  KC_Z,    KC_SLSH,
     KC_CAPS, RLT_R,   ALT_S,   SFT_N,   CRL_T,   KC_G,                           KC_QUOT, CRL_A,   SFT_E,   ALT_I,   RLT_H,   KC_J,
     KC_LCTL, KC_X,    KC_C,    KC_L,    KC_D,    KC_B,   KC_ENT,        KC_RGUI, KC_MINS, KC_U,    KC_O,    KC_Y,    KC_K,    KC_EQL,
                                   KC_LBRC, TL_LOWR, KC_BSPC,                KC_SPC, TL_UPPR, KC_RBRC
  ),
  
/* GAMES - The gaming layer, without homerow or weird stuff.
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                   ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │ ESC  │   1  │   2  │   3  │   4  │   5  │                   │   6  │   7  │   8  │   9  │   0  │ Bspc │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   Q  │   W  │   E  │   R  │   T  │                   │   Y  │   U  │   I  │   O  │   P  │ Enter│
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │LShift│   A  │   S  │   D  │   F  │   G  │                   │   H  │   J  │   K  │   L  │  ' " │  - _ │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐     ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ LCTR │   Z  │   X  │   C  │   V  │   B  │ RGui │     │  \ | │   N  │   M  │  , < │  . > │  : ; │  / ? │
 * └──────┴──────┴──────┴────┬─┴────┬─┴────┬─┴────┬─┘     └─┬────┴─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
 *                           │  [ { │ LOWER│ Space│         │Space │UPPER │ ] }  │
 *                           └──────┴──────┴──────┘         └──────┴──────┴──────┘
 */
  
  [_GAMES] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
     KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_MINS,
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_RGUI,       KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN, KC_SLSH,
                                   KC_LBRC, TL_LOWR, KC_SPC,                 KC_SPC, TL_UPPR, KC_RBRC
  ),

/* LOWER - Lower layer
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                   ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                   │  F6  │  F7  │  F8  │  F9  │  F10 │  F12 │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                   │  MWU │ HOME │  Up  │  END │      │Insert│
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                   │  MWD │ Left │ Down │ Right│      │Delete│
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐     ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │     │      │      │      │      │      │ C+S+E│ C+A+D│
 * └──────┴──────┴──────┴────┬─┴────┬─┴────┬─┴────┬─┘     └─┬────┴─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
 *                           │      │      │      │         │      │      │      │
 *                           └──────┴──────┴──────┘         └──────┴──────┴──────┘
 */

  [_LOWER] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                            KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F12,
     _______, _______, _______, _______, _______, _______,                            MS_WHLU, KC_HOME, KC_UP,   KC_END,   _______, KC_INS,
     _______, _______, _______, _______, _______, _______,                            MS_WHLD, KC_LEFT, KC_DOWN, KC_RIGHT, _______, KC_DEL,
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,  KC_CSE,  KC_CAD,
                                    _______, _______, _______,                    _______, _______, _______
  ),

/* UPPER - Upper layer
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                   ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  F11 │  F1  │  F2  │  F3  │  F4  │  F5  │                   │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                   │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │ PGUP │      │      │                   │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐     ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │ PAUSE│ PGDW │ PTSC │      │      │     │      │      │      │      │      │      │      │
 * └──────┴──────┴──────┴────┬─┴────┬─┴────┬─┴────┬─┘     └─┬────┴─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
 *                           │      │      │      │         │      │      │      │
 *                           └──────┴──────┴──────┘         └──────┴──────┴──────┘
 */
  
  [_UPPER] = LAYOUT(
     KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                            _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
     _______, _______, _______, KC_PGUP, _______, _______,                          _______, _______, _______, _______, _______, _______,
     _______, _______, KC_PAUS, KC_PGDN, KC_PSCR, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                    _______, _______, _______,                   _______, _______, _______
  ),

/* ADJUST - Adjust layer for miscellaneous matter such as EEEPROM and reset
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                   ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │EEPROM│ Boot │                   │ Boot │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                   │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │  NEU │      │ GAMES│                   │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐     ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │     │      │      │      │      │      │      │      │
 * └──────┴──────┴──────┴────┬─┴────┬─┴────┬─┴────┬─┘     └─┬────┴─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
 *                           │      │      │      │         │      │      │      │
 *                           └──────┴──────┴──────┘         └──────┴──────┴──────┘
 */
  
  [_ADJUST] = LAYOUT(
     _______, _______, _______, _______, EE_CLR,  QK_BOOT,                            QK_BOOT, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
     _______, _______, _______, DF(_NEU), _______, DF(_GAMES),                        _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
                                    _______, _______, _______,                   _______, _______, _______
  )
  
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) >= 0) {
		
        // Get the active layer
        uint8_t layer = get_highest_layer(layer_state|default_layer_state);

        // Pick a color based on the active layer, using HSV values.
        hsv_t hsv = {190, 255, 134}; // purple
		
        switch(layer) {
            case _ADJUST:
				hsv = (hsv_t){0, 255, 255}; // HSV_RED
                break;
            case _UPPER:
				hsv = (hsv_t){21, 255, 255}; // HSV_ORANGE
                break;
			case _LOWER:
				hsv = (hsv_t){21, 255, 255}; // HSV_ORANGE
                break;
			case _GAMES:
				hsv = (hsv_t){128, 255, 128}; // HSV_TEAL
                break;
			case _NEU:
				hsv = (hsv_t){0,   0, 255}; // HSV_WHITE
                break;
            default:
				break;
        }
		
		if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
		}
		
		rgb_t rgb = hsv_to_rgb(hsv); // Conversion from hsv to rgb.

        // Find all keys
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

				// Set the color of all keys that are not transparent to the color picked above, and the transparent ones as off.
                if (index >= led_min && index < led_max && index != NO_LED) {
					if (keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
						rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b); 
					} else {
					rgb_matrix_set_color(index, RGB_OFF);
					}
				}
            }
        }
        
    }
    return false;
}