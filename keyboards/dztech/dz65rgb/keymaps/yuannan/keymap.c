/* Copyright 2021 Yuannan (https://github.com/yuannan)
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_keycodes {
    AUTOCLICK_TOGGLE = SAFE_RANGE,
	AUTO_BURST,
    RAPID_BURST,
    INC_CLICK_SPEED,
	DEC_CLICK_SPEED,
    DEL_LINE,
    DEL_HOME,
    DEL_END
};

enum my_layers {
    _ALPHA_LAYER,
    _VIM_EDITING_LAYER,
    _MOUSE_LAYER,
    _HYPER_LAYER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_ALPHA_LAYER] = LAYOUT_65_ansi(
		QK_GESC,	KC_1,	KC_2,	KC_3,   KC_4,	KC_5,	KC_6,	KC_7,	KC_8,		KC_9,	KC_0,		KC_MINUS,	KC_EQUAL,		KC_BSPC,	KC_HOME,
		KC_TAB,		KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC_Y,	KC_U,	KC_I,		KC_O,	KC_P,		KC_LBRC,KC_RBRC,	KC_BSLS,	KC_PGUP,
		KC_LCTL,	KC_A,   KC_S,	KC_D,	KC_F,	KC_G,	KC_H,	KC_J,	KC_K,		KC_L,	KC_SCLN,	KC_QUOTE,	        KC_ENTER,	        KC_PGDN,
		KC_LSFT,	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	KC_N,	KC_M,	KC_COMMA,	KC_DOT,	KC_SLASH,           KC_RSFT,          KC_UP,		KC_END,
		KC_CAPS,KC_LGUI,TL_LOWR,				KC_SPACE,                       TL_UPPR,	KC_LALT,    KC_RCTL,        KC_LEFT,	KC_DOWN,	KC_RIGHT
    ),
    [_VIM_EDITING_LAYER] = LAYOUT_65_ansi(
		KC_GRAVE,	    KC_F1,		        KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_DELETE,	KC_INSERT,
		KC_TRNS,	    KC_TRNS,	        KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	DEL_HOME,	KC_HOME,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_SCRL,
		KC_TRNS,	    KC_TRNS,	        KC_TRNS,	KC_TRNS,	KC_TRNS,	DEL_LINE,	KC_LEFT,	KC_DOWN,	KC_UP,		KC_RIGHT,	KC_TRNS,	KC_TRNS,		    KC_MPLY,        KC_PAUSE,
		KC_TRNS,        AUTOCLICK_TOGGLE,   KC_TRNS,	AUTO_BURST,RAPID_BURST,	KC_TRNS,	DEL_END,	KC_END,	    KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_VOLU,	KC_PSCR,
		DEC_CLICK_SPEED,INC_CLICK_SPEED,	KC_TRNS,                                KC_TRNS,						            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_MPRV,    KC_VOLD,	KC_MNXT
    ),
    [_MOUSE_LAYER] = LAYOUT_65_ansi(
		KC_GRAVE,	KC_F1,				KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_TRNS,	KC_TRNS,
		KC_ACL0,	KC_BTN1,			KC_MS_U,	KC_BTN2,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_BTN4,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
		KC_ACL1,	KC_MS_L,			KC_MS_D,	KC_MS_R,	KC_TRNS,	KC_TRNS,	KC_WH_L,	KC_WH_D,	KC_WH_U,	KC_WH_R,	KC_TRNS,			KC_TRNS,		KC_TRNS,	KC_TRNS,
		KC_ACL2,	AUTOCLICK_TOGGLE,	KC_BTN3,	AUTO_BURST,	RAPID_BURST,	KC_TRNS,	KC_TRNS,	KC_BTN5,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS,
		DEC_CLICK_SPEED,INC_CLICK_SPEED,KC_TRNS,								KC_TRNS,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS
    ),
    [_HYPER_LAYER] = LAYOUT_65_ansi(
		DM_RSTP,		DM_REC1,			DM_REC2,			KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
		KC_NO,			DM_PLY1,			DM_PLY2,			KC_NO,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
		KC_NO,			KC_NO,				KC_NO,				KC_NO,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS,
		KC_LSFT,		KC_NO,				KC_NO,				RGB_HUI,	RGB_SAI,	RGB_VAI,	RGB_SPI,	RGB_MOD,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS,
		KC_TRNS,		KC_TRNS,			KC_TRNS,									RGB_TOG,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS
	)
};

#define CLICKSPEEDS 5
const uint16_t clickspeed_sets[CLICKSPEEDS] = {1000, 100, 50, 20, 1};
uint16_t clickspeed_set = CLICKSPEEDS - 1;
deferred_token autoclick_token = INVALID_DEFERRED_TOKEN;
bool rapid = false;

void decrement_click_speed(void){
	clickspeed_set += CLICKSPEEDS - 1;
	clickspeed_set %= CLICKSPEEDS;
}

void increment_click_speed(void){
	clickspeed_set ++;
	clickspeed_set %= CLICKSPEEDS;
}

uint32_t autoclick_callback(uint32_t trigger_time, void *cb_arg){
    tap_code(KC_BTN1);

    return rapid ? 1 : clickspeed_sets[clickspeed_set];
}

void start_autoclicker(void){
    autoclick_token = defer_exec(1, autoclick_callback, NULL);
}

void stop_autoclicker(void){
    cancel_deferred_exec(autoclick_token);
    autoclick_token = INVALID_DEFERRED_TOKEN;
}

// Custom process key to allow for custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record){
    switch (keycode) {
        case AUTOCLICK_TOGGLE:
            if (record->event.pressed) {
                if (autoclick_token == INVALID_DEFERRED_TOKEN){
                    start_autoclicker();
                } else{
                    stop_autoclicker();
                }
            }
            break;
		case AUTO_BURST:
            if (record->event.pressed && (autoclick_token == INVALID_DEFERRED_TOKEN)) {
                start_autoclicker();
            } else if (autoclick_token != INVALID_DEFERRED_TOKEN){
                stop_autoclicker();
			}
            break;
        case RAPID_BURST:
            if (record->event.pressed){
                rapid = true;
                start_autoclicker();
            } else{
                rapid = false;
                stop_autoclicker();
            }
            break;
        case INC_CLICK_SPEED:
            if (record->event.pressed){
				if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
					decrement_click_speed();
				} else{
					increment_click_speed();
				}
			}
            break;
        case DEC_CLICK_SPEED:
            if (record->event.pressed){
				if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
					increment_click_speed();
				} else{
					decrement_click_speed();
				}
			}
            break;
        case DEL_LINE:
            if(record->event.pressed){
                SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)) SS_TAP(X_DELETE));
            }
            break;
        case DEL_HOME:
            if(record->event.pressed){
                SEND_STRING(SS_LSFT(SS_TAP(X_HOME)) SS_TAP(X_DELETE));
            }
            break;
        case DEL_END:
            if(record->event.pressed){
                SEND_STRING(SS_LSFT(SS_TAP(X_END)) SS_TAP(X_DELETE));
            }
            break;
		case RGB_TOG:
			if(record->event.pressed){
				if (!(get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT))){
					if(rgb_matrix_get_val() < 128){
						rgb_matrix_sethsv(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 255);
					} else{
						rgb_matrix_sethsv(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 0);
					}
					return false;
				}
			}
			break;
    }

    return true;
};

RGB get_inverted_RGB(void){
	HSV current_HSV = rgb_matrix_get_hsv();
	current_HSV.h = 255 - current_HSV.h;
	current_HSV.s = 255;
	current_HSV.v = 255;

	return hsv_to_rgb(current_HSV);
}

// Move Caps indicator to the ctrl key where it belongs
bool rgb_matrix_indicators_user(void){
	RGB inverted_RGB = get_inverted_RGB();
    if (host_keyboard_led_state().caps_lock){
        rgb_matrix_set_color(58, inverted_RGB.r, inverted_RGB.g, inverted_RGB.b);
    }
    return false;
}

// show coloured indicator for layers with a keybind
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max){
    uint8_t layer = get_highest_layer(layer_state);
    if (layer > 0) {
		RGB inverted_RGB = get_inverted_RGB();
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index <= led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, inverted_RGB.r, inverted_RGB.g, inverted_RGB.b);
                }
            }
        }
    }
    return false;
}
