#include QMK_KEYBOARD_H

// Sources and thanks
// OLED taken from u/Nik005566 https://github.com/kalinstanchev/qmk_firmware/tree/master/keyboards/dmqdesign/spin/keymaps/gorbachev
// Layer switching via encoder based on posts by u/SpaceBarRacecar and u/Klathmon
// Photoshop opacity encoder modified from u/AlonTzarfi https://github.com/AlonTzarafi/qmk_firmware_for_alon_keebs/blob/alon-sol2/keyboards/rgbkb/sol/keymaps/alon/keymap.c

enum layers {
    _NUMPAD,	//	This is a standard Numberpad layer
    _RGB,		//	This is the RGB control layer
    _PS,		//	This is the Photoshop layer
	_PSBRUSH,	//	This is alternate Nuumberpad for Photoshop ease of use
	_D2			//	This is the Destiny 2 layer
};

#define HIGHEST_LAYER _D2 // When adding a new layer or chaing their order make sure this is updated



//Photoshop Shortcuts
#define UNDO LCTL(KC_Z)

// Tap Dance declarations
enum {
    TD_X_D,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for X, twice for D - Photoshop switch swatches, and reset swatches shortcuts respectively
    [TD_X_D] = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_D),
};



// These are the layer layouts
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT(/* Base */
                KC_7, KC_8, KC_9, KC_AUDIO_MUTE,
                KC_4, KC_5, KC_6, RESET,
                KC_1, KC_2, KC_3, TO(_PS),
                KC_0, KC_DOT, KC_ENT
                ),

    [_RGB] = LAYOUT(/* Base */
                RGB_HUI,  RGB_SAI, RGB_VAI, KC_TRNS,
                RGB_HUD,  RGB_SAD, RGB_VAD, KC_TRNS,
                RGB_RMOD,    RGB_TOG,   RGB_MOD,   TO(_NUMPAD),
                TO(_NUMPAD), TO(_PS), RESET
                ),

    [_PS] = LAYOUT(/* Base */
                KC_L, KC_G, KC_N, KC_V,
                KC_K, KC_S, TD(TD_X_D), KC_O,
                KC_LSHIFT, KC_Z, KC_M, TO(_NUMPAD),
                KC_LCTL, KC_LALT, KC_SPACE
                ),
				
	[_PSBRUSH] = LAYOUT(/* Base */
                KC_7, KC_8, KC_9, KC_B,
                KC_4, KC_5, KC_6, KC_D,
                KC_1, KC_2, KC_3, TO(_PS),
                KC_0, KC_LSHIFT, TD(TD_X_D)
                ),
				
	[_D2] = LAYOUT(/* Base */
                KC_NO, KC_NO, KC_NO, KC_TRNS,
                KC_NO, KC_NO, KC_NO, KC_TRNS,
                KC_NO, KC_NO, KC_NO, TO(_NUMPAD),
                TO(_NUMPAD), TO(_RGB), RESET
                )

};



// These rows deal with the rotary encoders
uint8_t selected_layer = 0;
// For Photohop Opacity control
uint8_t opacity = 60;
uint8_t opacity_increment = 3;
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
                if (clockwise && !layer_state_is(_PS)) {
                    tap_code(KC_VOLU); //  Volume Up
				} else if (clockwise && layer_state_is(_PS)) {
					tap_code(KC_RBRACKET);
				} else if (!clockwise && !layer_state_is(_PS)) {
					tap_code(KC_VOLD);
                } else if (!clockwise && layer_state_is(_PS)) {
                    tap_code(KC_LBRACKET);
                }
    } else if (index == 1) { /* Second encoder */
        switch (get_highest_layer(layer_state)) {
            case _NUMPAD:
                if (clockwise) {
                    tap_code(KC_MS_WH_DOWN); // Scroll vertical
                } else {
                    tap_code(KC_MS_WH_UP);
                }
                break;
            case _RGB:
                if (clockwise) {
                    tap_code(KC_MS_WH_DOWN);
                } else {
                    tap_code(KC_MS_WH_UP);
                }
                break;
            case _PS:
                if (clockwise) {
                    if (opacity > 100 - opacity_increment) {
                        opacity = 100;
                    } else {
                        opacity += opacity_increment;
                    }
                } else {
                    if (opacity < 0 + opacity_increment) {
                        opacity = 0;
                    } else {
                        opacity -= opacity_increment;
                    }
                }
                
                uint8_t opacity_to_type = opacity;
                if (opacity_to_type == 0) {
                    opacity_to_type = 1;
                }
                
                uint8_t last = opacity_to_type % 10;
                uint8_t first = opacity_to_type / 10 % 10;
                uint8_t digits[2] = {first, last};
                for(int i = 0; i < 2; ++i) {
                    switch (digits[i]) {
                    case 0: tap_code(KC_0); break;
                    case 1: tap_code(KC_1); break;
                    case 2: tap_code(KC_2); break;
                    case 3: tap_code(KC_3); break;
                    case 4: tap_code(KC_4); break;
                    case 5: tap_code(KC_5); break;
                    case 6: tap_code(KC_6); break;
                    case 7: tap_code(KC_7); break;
                    case 8: tap_code(KC_8); break;
                    case 9: tap_code(KC_9); break;
                    }
				}
                break;
        }
    } else if (index == 2) { /* Third encoder */
        if (clockwise && selected_layer == HIGHEST_LAYER) { // Numpad if at top layer
                    selected_layer = _NUMPAD;
		} else if (clockwise) { // Next layer if not at top layer
			selected_layer ++;
		} else if (!clockwise && selected_layer == 0){ // Top layer if on Numpad
                    selected_layer = HIGHEST_LAYER;
		} else if (!clockwise && selected_layer != 0){ // Previous layer if not on Numpad
			selected_layer --;
				}
				layer_clear();
				layer_on(selected_layer);
    }
        }



#ifdef OLED_DRIVER_ENABLE

static const char *ANIMATION_NAMES[] = {
	"unknown",
	"static",
	"rainbow swirl I",
	"rainbow swirl II",
	"rainbow swirl III",
	"rainbow swirl IV",
	"rainbow swirl V",
	"rainbow swirl VI",
};

void rgblight_get_mode_name(uint16_t mode, size_t bufsize, char *buf) {
    snprintf(buf, bufsize, "%-25s", ANIMATION_NAMES[mode]);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef LEFT_HAND
    return OLED_ROTATION_180;
#else
    return OLED_ROTATION_0;
#endif
}

void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            oled_write_P(PSTR("Numpad\n"), false);
            break;
        case _RGB:
            oled_write_P(PSTR("RGB\n"), false);
            break;
        case _PS:
            oled_write_P(PSTR("Photoshop\n"), false);
            break;
        case _PSBRUSH:
            oled_write_P(PSTR("PS Numpad\n"), false);
            break;
        case _D2:
            oled_write_P(PSTR("Destiny 2\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    static char rgb_mode_name[30];
    rgblight_get_mode_name(rgblight_get_mode(), sizeof(rgb_mode_name), rgb_mode_name);

    oled_write_P(PSTR("Mode: "), false);
    oled_write_ln(rgb_mode_name, false);
}
#endif
