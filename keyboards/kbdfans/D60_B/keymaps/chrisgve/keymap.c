#include QMK_KEYBOARD_H
#include "chrisgve.h"

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   0,		1,		2,		3,		4,		5,		6,		7,		8,		9,		10,		11,		12,		13,		14},
  {   15,		NO_LED, 16,		17,		18,		19,		20,		21,		22,		23,		24,		25,		26,		27,		28},
  {   29,		NO_LED, 30,		31,		32,		33,		34,		35,		36,		37,		38,		39,		40,		NO_LED,	41},
  {   NO_LED,   42,		43,		44,		45,		46,		47,		48,		49,		50,		51,		52,		NO_LED, 53,		54},
  {   55,		NO_LED, 56,		57,		NO_LED,	NO_LED,	NO_LED,  58,	NO_LED, NO_LED, NO_LED,	59,		NO_LED, 60,		61}
}, {
  // LED Index to Physical Position
  {  0,  0},   { 16,  0},  { 32, 0 },   { 48, 0 },   { 64, 0},    { 80, 0},    { 96, 0},   { 112, 0},   { 128, 0},   { 144, 0},   { 160, 0},   { 176, 0},  { 192, 0},  { 208, 0},  { 224, 0},
  {  0,  16},              { 32,  16},  { 48, 16},   { 64, 16},   { 80, 16},   { 96, 16},  { 112, 16},  { 128, 16},  { 144, 16},  { 160, 16},  { 176, 16}, { 192, 16}, { 208, 16}, { 224, 16}, 			//,
  {  0,  32},              { 32,  32},  { 48, 32 },  { 64, 32},   { 80, 32},   { 96, 32},  { 112, 32},  { 128, 32},  { 144, 32},  { 160, 32},  { 176, 32}, { 192, 32},             { 224, 32}, //,
			   { 16,  48}, { 32, 48 },  { 48, 48 },  { 64, 48},   { 80, 48},   { 96, 48},  { 112, 48},  { 128, 48},  { 144, 48},  { 160, 48},  { 176, 48},             { 208, 48}, { 224, 48}, //,
  {  0,  64},              { 32,  64},  { 48, 64 },  			  				           { 112, 64},  			  				  		   { 176, 64},  		   { 208, 64}, { 224, 64},
}, {
  // LED Index to Flag
	  4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4,		4,
	  4, 				4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4,
	  4, 				4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		  		4,
				4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 		4, 				4, 		4,
	  4, 				4, 		4, 		 		  		        4, 		  		  		  		4, 		  		4, 		4,
} };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY_MAC]=LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        CPS_CTL, KC_A,    KC_S,    M_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
	    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, 	                 R_SHIFT, ADJUST,
        XXXXXXX, KC_LALT, KC_LGUI,                                     KC_SPC,                                      KC_RGUI, KC_RALT, XXXXXXX
    ),

    [_MAC_NAV_1]=LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, M_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, A_SHIFT, S_SHIFT, _______, M_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______, _______, _______, _______, _______, M_B_WRD, _______, _______, _______, _______, _______,                   _______, _______,
        _______, _______, _______,                                     _______,                                     _______, _______, _______
    ),

    [_MAC_NAV_2]=LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
        _______, _______, _______,                                     _______,                                     _______, _______, _______
    ),

    [_QWERTY_LINUX]=LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        CPS_CTL, KC_A,    KC_S,    L_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
	    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, 	                 R_SHIFT, ADJUST,
        XXXXXXX, KC_LGUI, KC_LALT,                                     KC_SPC,                                      KC_RALT, KC_RGUI, XXXXXXX
    ),

    [_LINUX_NAV_1]=LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, L_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, A_SHIFT, S_SHIFT, _______, L_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______, _______, _______, _______, _______, L_B_WRD, _______, _______, _______, _______, _______,                   _______, _______,
        _______, _______, _______,                                     _______,                                     _______, _______, _______
    ),

    [_LINUX_NAV_2]=LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
        _______, _______, _______,                                     _______,                                     _______, _______, _______
    ),

    [_QWERTY_WIN]=LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        CPS_CTL, KC_A,    KC_S,    W_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
	    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, 	                 R_SHIFT, ADJUST,
        XXXXXXX, KC_LGUI, KC_LALT,                                     KC_SPC,                                      KC_RALT, KC_RGUI, XXXXXXX
    ),

    [_WIN_NAV_1]=LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, W_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, A_SHIFT, S_SHIFT, _______, W_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______, _______, _______, _______, _______, W_B_WRD, _______, _______, _______, _______, _______,                   _______, _______,
        _______, _______, _______,                                     _______,                                     _______, _______, _______
    ),

    [_WIN_NAV_2]=LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
        _______, _______, _______,                                     _______,                                     _______, _______, _______
    ),

    [_ADJUST]=LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,          _______,
        _______, DF_MAC,  DF_LNX,  DF_WIN,  _______, _______, _______, KC_MUTE, _______, _______, _______,                   _______, _______,
        _______, _______, _______,                                     KC_MPLY,                                     _______, _______, _______
    ),

};

// RGB configuration and setup light layer for caps on

enum generic_layer_t {
    _DEF_L,
    _NAV1_L,
    _NAV2_L,
    _ADJ_L,
    _NUM_L,
};

bool caps_lock = false;  // Indicator if caps lock is on
bool def_layer = true;   // Indicates if the board is on a default layer
uint8_t cur_layer = _DEF_L;   // Current layer

void reset_rgb(void) {
    rgb_matrix_disable_noeeprom();
}

void set_rgb(uint8_t red, uint8_t green, uint8_t blue) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_set_color_all(red, green, blue);
}

void keyboard_post_init_user() {
    reset_rgb();
}

void set_nav_1_rgb(void) {
    set_rgb(RGB_NAV1_R, RGB_NAV1_G, RGB_NAV1_B);
}

void set_nav_2_rgb(void) {
    set_rgb(RGB_NAV2_R, RGB_NAV2_G, RGB_NAV2_B);
}

void set_caps_rgb(void) {
    set_rgb(RGB_CAPS_R, RGB_CAPS_G, RGB_CAPS_B); // Warm white
}

void set_adj_rgb(void) {
    set_rgb(RGB_ADJ_R, RGB_ADJ_G, RGB_ADJ_B);
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (caps_lock) {
        set_caps_rgb();
    } else {
        reset_rgb();
    }
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(state)) {
        case _MAC_NAV_1:
        case _LINUX_NAV_1:
        case _WIN_NAV_1:
            cur_layer = _NAV1_L;
            def_layer = false;
            set_nav_1_rgb();
            break;
        case _MAC_NAV_2:
        case _LINUX_NAV_2:
        case _WIN_NAV_2:
            cur_layer = _NAV2_L;
            def_layer = false;
            set_nav_2_rgb();
            break;
        case _ADJUST:
            cur_layer = _ADJ_L;
            def_layer = false;
            set_adj_rgb();
            break;
        default:
            cur_layer = _DEF_L;
            def_layer = true;
            if (caps_lock) {
                set_caps_rgb();
            } else {
                reset_rgb();
            }
    }
    return state;
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        set_caps_rgb();
        caps_lock = true;
    } else {
        if (def_layer) {
            reset_rgb();
        }
        caps_lock = false;
    }
}

void rgb_matrix_indicators_user(void) {
    if (caps_lock) {
        set_caps_rgb();
    } else {
        switch(cur_layer) {
            case _DEF_L:
                reset_rgb();
                break;
            case _NAV1_L:
                set_nav_1_rgb();
                break;
            case _NAV2_L:
                set_nav_2_rgb();
                break;
            case _ADJ_L:
                set_adj_rgb();
                break;
            default:
                break;
        }
    }
}

