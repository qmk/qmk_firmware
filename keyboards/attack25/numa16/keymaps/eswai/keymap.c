#include QMK_KEYBOARD_H
#include "pro_micro.h"

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    extern RGB_CONFIG_t RGB_CONFIG;
    RGB_CONFIG_t RGB_current_config;
    bool RGB_momentary_on;
#endif

bool MAC_mode = true;
bool NumLock_Mode = true;

enum layer_number {
    _NUM = 0,
    _CUR,
    _BRC,
    _RGB,
};

enum custom_keycodes {
    RGB_MODR = SAFE_RANGE,
    RGBRST,
    P00,
    WINMAC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_NUM] = LAYOUT_ortho_4x4(
	KC_PEQL, KC_P7  , KC_P8  , KC_P9,
	KC_PDOT, KC_P4  , KC_P5  , KC_P6,
	KC_P0  , KC_P1  , KC_P2  , KC_P3,
	LT(_CUR,KC_PMNS), LT(_BRC,KC_PPLS) , LT(_CUR,KC_PAST) , LT(_RGB,KC_PSLS)),

[_CUR]= LAYOUT_ortho_4x4(
	KC_PENT, KC_BSPC  , KC_UP    , KC_DEL,
	KC_PCMM, KC_LEFT  , KC_DOWN  , KC_RGHT,
	XXXXXXX, XXXXXXX  , XXXXXXX  , XXXXXXX,
	_______, XXXXXXX  , XXXXXXX , XXXXXXX),

[_BRC]= LAYOUT_ortho_4x4(
	KC_LBRC, KC_LPRN  , KC_LT   , KC_DQT,
	KC_RBRC, KC_RPRN  , KC_GT   , KC_QUOT,
	XXXXXXX, XXXXXXX  , XXXXXXX , XXXXXXX,
	_______, XXXXXXX  , XXXXXXX , XXXXXXX),

[_RGB] = LAYOUT_ortho_4x4(
	RGB_TOG, RGB_MOD,  RGB_HUI, RGB_VAI,
  RGBRST , RGB_MODR, RGB_HUD, RGB_VAD,
	RGB_SAI, XXXXXXX,  XXXXXXX, XXXXXXX,
	RGB_SAD, XXXXXXX,  XXXXXXX, _______),

};

void matrix_init_user(void) {
    #if defined(RGBLIGHT_ENABLE)
	    rgblight_init();
        RGB_current_config = RGB_CONFIG;
    #elif defined(RGB_MATRIX_ENABLE)
        RGB_current_config = RGB_CONFIG;
    #endif
    TX_RX_LED_INIT; //Turn LEDs off by default
    RXLED0;
    TXLED0;

}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	    case RGB_MOD:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_mode_noeeprom(RGB_current_config.mode);
		        rgblight_step();
		        RGB_current_config.mode = RGB_CONFIG.mode;
	        }
            return false;
        #else
            return true;
        #endif
	    break;

	    case RGB_MODR:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_mode_noeeprom(RGB_current_config.mode);
		        rgblight_step_reverse();
		        RGB_current_config.mode = RGB_CONFIG.mode;
	        }
            return false;
        #else
            return true;
        #endif
	    break;

	    case RGBRST:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                #ifdef RGBLIGHT_ENABLE
                    eeconfig_update_rgblight_default();
                #else
                    eeconfig_update_rgb_matrix_default();
                #endif
                rgblight_enable();
                RGB_current_config = RGB_CONFIG;
	        }
        #endif
	    return false;
	    break;

	    case RGB_HUI:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
	            rgblight_increase_hue();
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.hue = RGB_CONFIG.hue;
                #else
                    RGB_current_config.hsv.h = RGB_CONFIG.hsv.h;
                #endif
	        }
        return false;
        #else
            return true;
        #endif
	    break;

	    case RGB_HUD:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        	if (record->event.pressed) {
		        rgblight_decrease_hue();
                #ifdef RGBLIGHT_ENABLE
                    RGB_current_config.hue = RGB_CONFIG.hue;
                #else
                    RGB_current_config.hsv.h = RGB_CONFIG.hsv.h;
                #endif
	        }
            return false;
        #else
	        return true;
        #endif
	    break;

	    case RGB_SAI:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
		        rgblight_increase_sat();
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.sat = RGB_CONFIG.sat;
                #else
                    RGB_current_config.hsv.s = RGB_CONFIG.hsv.s;
                #endif
	        }
            return false;
        #else
            return true;
        #endif
    	break;

	    case RGB_SAD:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_decrease_sat();
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.sat = RGB_CONFIG.sat;
                #else
                    RGB_current_config.hsv.s = RGB_CONFIG.hsv.s;
                #endif
	        }
            return false;
        #else
            return true;
        #endif
	    break;

	    case RGB_VAI:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_increase_val();
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.val = RGB_CONFIG.val;
                #else
                    RGB_current_config.hsv.v = RGB_CONFIG.hsv.v;
                #endif
	        }
            return false;
        #else
            return true;
        #endif
    	break;

	    case RGB_VAD:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_decrease_val();
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.val = RGB_CONFIG.val;
                #else
                    RGB_current_config.hsv.v = RGB_CONFIG.hsv.v;
                #endif
	        }
            return false;
        #else
            return true;
        #endif
	    break;

    case RGB_MODE_PLAIN:
    case RGB_MODE_BREATHE:
    case RGB_MODE_RAINBOW:
    case RGB_MODE_SWIRL:
    case RGB_MODE_SNAKE:
    case RGB_MODE_KNIGHT:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
	        } else {
			  RGB_current_config.mode = RGB_CONFIG.mode;
		    }
        #endif
	    return true;
	    break;

	default:
	  break;
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
	if (!g_suspend_state && rgb_matrix_config.enable) {
	    switch (biton32(layer_state)) {
	        case _FN:
		        RGB_momentary_on = true;
                #ifdef RGBLED_BOTH
		            rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                #else
                    rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_NONE);
                #endif
                break;

            case _NUMOFF:
                #ifdef RGBLED_BOTH
                    rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                #else
                    rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_NONE);
                #endif
                break;

	        case _RGB:
                break;

            default:
                RGB_momentary_on = false;
                break;
	    }
	}
    uint8_t usb_led = host_keyboard_leds();
    if (!RGB_momentary_on && rgb_matrix_config.enable && !MAC_mode) {
        NumLock_Mode = usb_led & (1 << USB_LED_NUM_LOCK);
	    if (NumLock_Mode) {
            rgb_matrix_sethsv_noeeprom(RGB_current_config.hsv.h, RGB_current_config.hsv.s, RGB_current_config.hsv.v);
            rgblight_mode_noeeprom(RGB_current_config.mode);
	    } else {
            #ifdef RGBLED_BOTH
                rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
            #else
                rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_NONE);
            #endif
	        }
	    }
}
#elif defined(RGBLIGHT_ENABLE)
    uint32_t layer_state_set_user(uint32_t state) {
	    switch (biton32(state)) {


            default:
		        rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
	            rgblight_mode_noeeprom(RGB_current_config.mode);
	            RGB_momentary_on = false;
                break;
	    }
	    return state;
    }

    void led_set_user(uint8_t usb_led) {
         if (!RGB_momentary_on && !MAC_mode){
	        if (usb_led & (1 << USB_LED_NUM_LOCK)) {
                rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
			    rgblight_mode_noeeprom(RGB_current_config.mode);
	        } else {
		        rgblight_sethsv_noeeprom_azure();
                rgblight_mode_noeeprom(1);
	        }
	    }
    }
#endif

