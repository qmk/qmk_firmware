#include QMK_KEYBOARD_H

// Sources and thanks
// OLED taken from u/Nik005566 https://github.com/kalinstanchev/qmk_firmware/tree/master/keyboards/dmqdesign/spin/keymaps/gorbachev
// Layer switching via encoder based on posts by u/SpaceBarRacecar and u/Klathmon
// Photoshop opacity encoder modified from u/AlonTzarfi https://github.com/AlonTzarafi/qmk_firmware_for_alon_keebs/blob/alon-sol2/keyboards/rgbkb/sol/keymaps/alon/keymap.c

enum layers {
    _NUMPAD,	//	This is a standard Numberpad layer
    _RGB,		//	This is the RGB control layer
	_FNUM,		//	This has F keys with modifiers
    _PS,		//	This is the Photoshop layer
	_PSDPAD,	//	This is the arrows - merge into other PS layer if possible
	_D2			//	This is the Destiny 2 layer, for lazy Guardians which doesn't exist yet becasue macros are hard
};

#define HIGHEST_LAYER _D2 // When adding a new layer or chaing their order make sure this is updated



//Photoshop Shortcuts
#define	UNDO	LCTL(KC_Z)
#define	NXTDOC	LCTL(KC_TAB)

// Tap Dance declarations
enum {
    TD_A_I,
	TD_N_G,
	TD_X_C,
	TD_V_D,
	TD_S_E,
	TD_P_K,
	TD_L_Z,
	TD_ENT_BSPACE,
	TD_F1_F10,
	TD_F2_F11,																							
	TD_F3_F12,
	TD_F4_F13,
	TD_F5_F14,
	TD_F6_F15,
	TD_F7_F16,
	TD_F8_F17,
	TD_F9_F18,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_A_I] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_I), // Ref Photohop
	[TD_N_G] = ACTION_TAP_DANCE_DOUBLE(KC_N, KC_G), // Ref Photohop
	[TD_X_C] = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_C), // Ref Photohop
	[TD_V_D] = ACTION_TAP_DANCE_DOUBLE(KC_V, KC_D), // Ref Photohop
	[TD_S_E] = ACTION_TAP_DANCE_DOUBLE(KC_S, KC_E), // Ref Photohop
	[TD_P_K] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_K), // Ref Photohop
	[TD_L_Z] = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_Z), // Ref Photohop
	[TD_ENT_BSPACE] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_BSPACE), // Ref Photohop
	[TD_F1_F10] = ACTION_TAP_DANCE_DOUBLE(KC_F1, KC_F10), // Ref Photohop
	[TD_F2_F11] = ACTION_TAP_DANCE_DOUBLE(KC_F2, KC_F11), // Ref Photohop					
	[TD_F3_F12] = ACTION_TAP_DANCE_DOUBLE(KC_F3, KC_F12), // Ref Photohop
	[TD_F4_F13] = ACTION_TAP_DANCE_DOUBLE(KC_F4, KC_F13), // Ref Photohop
	[TD_F5_F14] = ACTION_TAP_DANCE_DOUBLE(KC_F5, KC_F14), // Ref Photohop
	[TD_F6_F15] = ACTION_TAP_DANCE_DOUBLE(KC_F6, KC_F15), // Ref Photohop
	[TD_F7_F16] = ACTION_TAP_DANCE_DOUBLE(KC_F7, KC_F16), // Ref Photohop
	[TD_F8_F17] = ACTION_TAP_DANCE_DOUBLE(KC_F8, KC_F17), // Ref Photohop
	[TD_F9_F18] = ACTION_TAP_DANCE_DOUBLE(KC_F9, KC_F18), // Ref Photohop
	};



// These are the layer layouts
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// _NUMPAD keymap
// .--------------------------------.
// |		   |		  |			|
// |   Mute	   |   Reset  |  To PS  |
// |		   |		  |			|
// |--------------------------------|
// |		|		|		|		|
// |	7	|	8	|	9	|	0	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |	4	|	5	|	6	|	.	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |	1	|	2	|	3	|   Ent |
// |		|		|		|		|
//  -------------------------------- 
    [_NUMPAD] = LAYOUT(/* Base */
                KC_AUDIO_MUTE, RESET, TO(_PS),
                KC_7, KC_8, KC_9, KC_0,
                KC_4, KC_5, KC_6, KC_DOT,
                KC_1, KC_2, KC_3, KC_ENT
                ),

// _RGB keymap
// .--------------------------------.
// |		   |		  |			|
// |   	 	   |   		  |		    |
// |		   |		  |			|
// |--------------------------------|
// |		|		|		|		|
// |  +Hue	|  +Sat	|+Bright|Nxt RGB|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |  -Hue	|  -Sat	|-Bright|Prv RGB|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// | Numpad	|   PS	| Reset	|Tog RGB|
// |		|		|		|		|
//  -------------------------------- 

    [_RGB] = LAYOUT(/* Base */
				KC_TRNS, KC_TRNS, KC_TRNS,
				RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,
				RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD,
				TO(_NUMPAD), TO(_PS), RESET, RGB_TOG
                ),
				
// _FNUM keymap
// .------------------------------------.
// |		   |		   |	 		|
// |   	 	   |   	   	   |		    |
// |		   |		   |			|
// |------------------------------------|
// |		|		 |		  |			|
// | F1 F10	| F2 F11 | F3 F12 | F4 F13	|
// |		|		 |		  |			|
// |--------+--------+--------+---------|
// |		|		 |		  |			|
// |  SHFT	| F6 F15 | F7 F16 | F8 F17	|
// |		|		 |		  |			|
// |--------+--------+--------+---------|
// |		|		 |		  |			|
// |  CTRL	|	ALT  | F8 F17 | F9 F18	|
// |		|		 |		  |			|
//  ------------------------------------

[_FNUM] = LAYOUT(/* Base */
				KC_TRNS, KC_TRNS, KC_TRNS,
				TD(TD_F1_F10), TD(TD_F2_F11), TD(TD_F3_F12), TD(TD_F4_F13),
				KC_LSHIFT, TD(TD_F5_F14), TD(TD_F6_F15), TD(TD_F7_F16),
				KC_LCTL, KC_LALT, TD(TD_F8_F17), TD(TD_F9_F18)
                ),    

// _PS keymap
// .--------------------------------.
// |		   |		  |			|
// |   	 	   | Next Doc |	Numpad  |
// |		   |		  |			|
// |--------------------------------|
// |		|		|		|		|
// |   A I	|  N G	|  X C	|  V D	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |  SHFT	|  S E	|  P K	|  L Z	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |  CTRL	|  ALT	|  SPC	|  ENT	|
// |		|		|		|		|
//  -------------------------------- 
    [_PS] = LAYOUT(/* Base */
				KC_TRNS, NXTDOC, TO(_NUMPAD),
				TD(TD_A_I), TD(TD_N_G), TD(TD_X_C), TD(TD_V_D),
				KC_LSHIFT, TD(TD_S_E), TD(TD_P_K), TD(TD_L_Z),
				KC_LCTL, KC_LALT, KC_SPACE, TD(TD_ENT_BSPACE)
                ),
				
// _PSDPAD keymap
// .------------------------------------.
// |		   |		   |	 		|
// |   	 	   |   	   	   |		    |
// |		   |		   |			|
// |------------------------------------|
// |		|		 |		  |			|
// | 		| 		 | 		  | 		|
// |		|		 |		  |			|
// |--------+--------+--------+---------|
// |		|		 |		  |			|
// |  		| 	UP	 | 		  | 		|
// |		|		 |		  |			|
// |--------+--------+--------+---------|
// |		|		 |		  |			|
// |  LEFT	|	DOWN | RIGHT  | 		|
// |		|		 |		  |			|
//  ------------------------------------
	[_PSDPAD] = LAYOUT(/* Base */
                KC_NO, KC_NO, KC_NO,
				KC_NO, KC_NO, KC_NO, KC_NO,
				KC_NO, KC_UP, KC_NO, KC_NO,
				KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO
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
        case _FNUM:
            oled_write_P(PSTR("F NUMBERS\n"), false);
            break;
        case _PS:
            oled_write_P(PSTR("Photoshop\n"), false);
            break;
        case _PSDPAD:
            oled_write_P(PSTR("Arrows\n"), false);
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
