// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum my_keycodes {
  FOO = SAFE_RANGE,
  RGB_LYR
};

enum custom_layers {
	 _NEU = 0,
	 _QWERTY = 1,
	 _GAMES = 2,
     _LOWER = 3,
     _UPPER = 4,
	 _ADJUST = 5
};

// Combinations used all the time.

#define KC_CAD LCTL(LALT(KC_DEL))
#define KC_CSE LCTL(LSFT(KC_ENT))

// Homerow for Qwerty

#define CRL_F LCTL_T(KC_F)
#define SFT_D LSFT_T(KC_D)
#define	ALT_S LALT_T(KC_S)

#define CRL_J LCTL_T(KC_J)
#define SFT_K LSFT_T(KC_K)
#define	ALT_L LALT_T(KC_L)

// Homerow for Neu

#define CRL_T LCTL_T(KC_T)
#define SFT_N LSFT_T(KC_N)
#define	ALT_S LALT_T(KC_S)

#define CRL_A LCTL_T(KC_A)
#define SFT_E LSFT_T(KC_E)
#define	ALT_I LALT_T(KC_I)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
/* HANDS DOWN NEU
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                   ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │ ESC  │   1  │   2  │   3  │   4  │   5  │                   │   6  │   7  │   8  │   9  │   0  │ Bspc │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   W  │   F  │   M  │   P  │   V  │                   │  ' " │   Q  │  , < │  . > │   Z  │ Enter│
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │LShift│   R  │ALT(S)│SFT(N)│CRL(T)│   G  │                   │  : ; │CRL(A)│SFT(E)│ALT(I)│   H  │   J  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐     ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ LCTR │   X  │   C  │   L  │   D  │   B  │ RGui │     │  \ | │  - _ │   U  │   O  │   Y  │   K  │  / ? │
 * └──────┴──────┴──────┴────┬─┴────┬─┴────┬─┴────┬─┘     └─┬────┴─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
 *                           │  [ { │ LOWER│ RAlt │         │Space │UPPER │ ] }  │
 *                           └──────┴──────┴──────┘         └──────┴──────┴──────┘
 */
  
  [_NEU] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
     KC_TAB,  KC_W,    KC_F,    KC_M,    KC_P,    KC_V,                           KC_QUOT, KC_Q,    KC_COMM, KC_DOT,  KC_Z,    KC_ENT,
     KC_LSFT, KC_R,    ALT_S,   SFT_N,   CRL_T,   KC_G,                           KC_SCLN, CRL_A,   SFT_E,   ALT_I,   KC_H,    KC_J,
     KC_LCTL, KC_X,    KC_C,    KC_L,    KC_D,    KC_B,   KC_RGUI,       KC_BSLS, KC_MINS, KC_U,    KC_O,    KC_Y,    KC_K,    KC_SLSH,
                                   KC_LBRC, TL_LOWR, KC_RALT,                KC_SPC, TL_UPPR, KC_RBRC
  ),
  
/* QWERTY - This is the reference for the other layers.
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                   ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │ ESC  │   1  │   2  │   3  │   4  │   5  │                   │   6  │   7  │   8  │   9  │   0  │ Bspc │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   Q  │   W  │   E  │   R  │   T  │                   │   Y  │   U  │   I  │   O  │   P  │ Enter│
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │LShift│   A  │ALT(S)│SFT(D)│CRL(F)│   G  │                   │   H  │CRL(J)│SFT(K)│ALT(L)│  ' " │  - _ │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐     ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ LCTR │   Z  │   X  │   C  │   V  │   B  │ RGui │     │  \ | │   N  │   M  │  , < │  . > │  : ; │  / ? │
 * └──────┴──────┴──────┴────┬─┴────┬─┴────┬─┴────┬─┘     └─┬────┴─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
 *                           │  [ { │ LOWER│ RAlt │         │Space │UPPER │ ] }  │
 *                           └──────┴──────┴──────┘         └──────┴──────┴──────┘
 */
  
  [_QWERTY] = LAYOUT(
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
     KC_LSFT, KC_A,    ALT_S,   SFT_D,   CRL_F,   KC_G,                           KC_H,    CRL_J,   SFT_K,   ALT_L,   KC_QUOT, KC_MINS,
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_RGUI,       KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN, KC_SLSH,
                                   KC_LBRC, TL_LOWR, KC_RALT,                KC_SPC, TL_UPPR, KC_RBRC
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
 * │      │      │      │      │      │      │                   │      │      │      │      │      │ PRTS │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                   │      │  MWU │   Up │  MWD │      │  = + │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                   │      │ Left │ Down │ Right│      │ C+S+E│
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐     ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │     │      │      │      │      │      │      │ C+A+D│
 * └──────┴──────┴──────┴────┬─┴────┬─┴────┬─┴────┬─┘     └─┬────┴─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
 *                           │      │      │      │         │ Caps │      │      │
 *                           └──────┴──────┴──────┘         └──────┴──────┴──────┘
 */

  [_LOWER] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, KC_PSCR,
     _______, _______, _______, _______, _______, _______,                            _______, MS_WHLU, KC_UP,   MS_WHLD, _______, KC_EQL,
     _______, _______, _______, _______, _______, _______,                            _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, KC_CSE,
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, KC_CAD,
                                    _______, _______, _______,                    KC_CAPS, _______, _______
  ),

/* UPPER - Upper layer
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                   ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  F1  │  F2  │  F3  │  F4  │  F5  │  F6  │                   │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │  F7  │  F8  │  F9  │  F10 │  F11 │  F12 │                   │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                   │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐     ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │     │      │      │      │      │      │      │      │
 * └──────┴──────┴──────┴────┬─┴────┬─┴────┬─┴────┬─┘     └─┬────┴─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
 *                           │      │      │      │         │      │      │      │
 *                           └──────┴──────┴──────┘         └──────┴──────┴──────┘
 */
  
  [_UPPER] = LAYOUT(
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              _______, _______, _______, _______, _______, _______,
     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                             _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
                                    _______, _______, _______,                   _______, _______, _______
  ),

/* ADJUST - Adjust layer for miscellaneous matter such as EEEPROM and reset
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                   ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │EEPROM│ Boot │                   │ Boot │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                   ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                   │      │QWERTY│      │      │      │      │
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
     _______, _______, _______, _______, _______, _______,                        _______, DF(_QWERTY), _______, _______, _______, _______,
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
				hsv = (hsv_t){0, 255, 255}; // red
                break;
            case _UPPER:
				hsv = (hsv_t){85, 255, 255}; // green
                break;
			case _LOWER:
				hsv = (hsv_t){234, 128, 255}; // pink
                break;
			case _GAMES:
				hsv = (hsv_t){190, 255, 134}; // purple
                break;
			case _QWERTY:
				hsv = (hsv_t){128, 255, 255}; // cyan
                break;
			case _NEU:
				hsv = (hsv_t){21, 255, 255}; // orange
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