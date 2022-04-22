#include QMK_KEYBOARD_H
#include "z60.h"

#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

#define SD_LTYPE_01		  0, 223, 252     	// KM_Light_red
#define SD_LTYPE_02		 31, 208, 234    	// KM_Light_yellow
#define SD_LTYPE_03		 97, 231, 230    	// KM_dirty_green
#define SD_LTYPE_04		 32, 191, 236    	// LM_golden_yellow
#define SD_LTYPE_05		255, 246, 238   	// LM_Slight_dark_red
#define SD_LTYPE_06		166, 240, 228   	// LM_Blue
#define SD_LTYPE_07		  0, 183, 238     	// LM_LightOrange
#define SD_LTYPE_08		130, 255, 255  		// LM_Cyan
#define SD_LTYPE_09		 42, 248, 240   	// LM_Yellow
#define SD_LTYPE_10		  0,   0,   0       // NULL
#define SD_LTYPE_11		216, 123, 238   	// LM_Light_pink
#define SD_LTYPE_12		  0,   0, 255       // LM_White
#define SD_LTYPE_13		  6, 240, 224     	// LM_Red_Blood
#define SD_LTYPE_14		 82, 247, 246  	  	// LM_NeonGreen
#define SD_LTYPE_15		178, 231, 238   	// LM_LighterBlue
#define SD_LTYPE_16		 36, 230, 248    	// LM_darker_Yellow
#define SD_LTYPE_17		 31, 255, 255    	// LM_Light_orange
#define SD_LTYPE_18		  0, 242, 205     	// LM_Blooder_Red
#define SD_LTYPE_19		 19, 150, 185    	// LM_LightBrown
#define SD_LTYPE_20		 13, 237, 253    	// LM_Orange
#define SD_LTYPE_21		124,  62, 253    	// LM_skyBlue
#define SD_LTYPE_22		115, 255, 248   	// LM_Toirquise
#define SD_LTYPE_23		195, 255, 251   	// LM_Purple
#define SD_LTYPE_24		178, 183, 238   	// LM_Light_blue_purple

bool aj_timer_active = false;
bool cmb_timer_active = false;

uint16_t cmb_timer1 = 0;
uint16_t aj_timer = 0;

enum custom_keycodes{
	SD_KC_1,
	SD_KC_2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_Z60_VIA(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL, 
		LT(3, KC_TAB),    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, 
		LT(4, KC_CAPS),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_HASH, KC_ENT, 
		KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_UP),    MO(1), 
		KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,  MO(2),   RALT_T(KC_LEFT),  RGUI_T(KC_DOWN),  RCTL_T(KC_RGHT)),

	[1] = LAYOUT_Z60_VIA( 
		RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[2] = LAYOUT_Z60_VIA(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[3] = LAYOUT_Z60_VIA(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[4] = LAYOUT_Z60_VIA(
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	//keyevent_t event = record->event;

	switch (id) {
		case 10:
            if (record -> event.pressed){
                if(!aj_timer_active){
                    aj_timer = timer_read();
                    aj_timer_active = true;
                }else if(aj_timer_active){
                    aj_timer_active = false;
                    aj_timer = 0;
                }
            }else{}
            break;
        case 11:
            if (record -> event.pressed){
            send_string(SS_TAP(X_F5) SS_DELAY(7000) SS_TAP(X_F6) SS_DELAY(2000) SS_TAP(X_F7) SS_DELAY(2000) SS_TAP(X_F8));
            }else{}
            break;
	}
	return MACRO_NONE;
}

void matrix_scan_user(void) { // The very important timer..
    if (aj_timer_active) {
        if (timer_elapsed(aj_timer) > 3000) {
            tap_code(KC_SPC);
            aj_timer = timer_read();
        }
    }
}

extern rgblight_config_t rgblight_config;
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS({103, 1, HSV_WHITE},{104,1,HSV_WHITE});
const rgblight_segment_t PROGMEM my_arnumpad_layer[] = RGBLIGHT_LAYER_SEGMENTS({56, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS({42, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM my_game_layer[] = RGBLIGHT_LAYER_SEGMENTS({28, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM my_macro_layer[] = RGBLIGHT_LAYER_SEGMENTS({ 15, 2, HSV_WHITE});

/*const rgblight_segment_t PROGMEM my_empty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{ 41, 1, HSV_WHITE		}
);*/
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    //my_capslock_layer,
    my_base_layer,			// Default layer
    my_arnumpad_layer,		// Arrow keys & Numpad & Operator keys (both toogle and hold mode to enter this layer)
	my_symbol_layer,		// F1-F12 keys & Symbols (hold mode to enter this layer)
	my_game_layer,			// Self-Defined hotkey layout for A game (toggle mode to enter this layer)
	my_macro_layer			// Self-Defined macro keys layer (hold mode to enter this layer)
	//my_empty_layer			// Preserved layer for customization (Self-Define way to enter this layer)
);
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
	rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    //rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    return state;
}