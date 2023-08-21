// Copyright 2023 Persama (@Persama)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// layer Mac
[0] = LAYOUT(
	KC_ESC, 	KC_BRID,  	KC_BRIU,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DNT,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 				KC_DEL,
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_PGUP,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC, 	KC_BSLS,	KC_PGDN,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 			KC_ENT,		KC_HOME,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,	KC_UP,
	KC_LCTL,	KC_LALT,	KC_LGUI,										KC_SPC, 							KC_RGUI,	MO(1),   	KC_RCTL,	KC_LEFT,	KC_DOWN,    KC_RGHT),
// layer Mac Fn
[1] = LAYOUT(
	_______, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 				KC_INS,
	_______, 	_______,   	_______,    _______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,
	RGB_TOG, 	_______,   	_______,    _______,  	_______,   	_______,   	_______,   	_______,   	_______,   	SYS_WIN,  	SYS_MAC,   	DEV_RESET,	_______, 	_______,	_______,
	_______,	RGB_VAI,  	RGB_VAD,  	RGB_MOD,   	RGB_HUI, 	RGB_SPI, 	RGB_SPD,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,	KC_END,
	_______,				SIDE_VAI,  	SIDE_VAD,  	SIDE_MOD,  	SIDE_HUI,	SIDE_SPI, 	SIDE_SPD, 	_______,   	_______,	_______,	_______,				_______,	_______,
	_______,	_______,	_______,										_______, 							_______,	_______,   	_______,	_______,	_______,    _______),
// layer win
[2] = LAYOUT(
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 				KC_DEL,
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_PGUP,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC, 	KC_BSLS,	KC_PGDN,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 			KC_ENT,		KC_HOME,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,	KC_UP,	
	KC_LCTL,	KC_LGUI,	KC_LALT,										KC_SPC, 							KC_RALT,	MO(3),   	KC_RCTL,	KC_LEFT,	KC_DOWN,    KC_RGHT),
// layer win Fn
[3] = LAYOUT(
	_______, 	KC_BRID,   	KC_BRIU,    _______,  	_______,   	_______,   	_______,   	KC_MPRV,   	KC_MPLY,   	KC_MNXT,  	KC_MUTE, 	KC_VOLD, 	KC_VOLU,				KC_INS,	
	_______, 	_______,   	_______,    _______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,
	RGB_TOG, 	_______,   	_______,    _______,  	_______,   	_______,   	_______,   	_______,   	_______,   	SYS_WIN,  	SYS_MAC,   	DEV_RESET,	_______, 	_______,	_______,
	_______,	RGB_VAI,  	RGB_VAD,  	RGB_MOD,   	RGB_HUI, 	RGB_SPI, 	RGB_SPD,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,	KC_END,
	_______,				SIDE_VAI,  	SIDE_VAD,  	SIDE_MOD,  	SIDE_HUI,	SIDE_SPI, 	SIDE_SPD, 	_______,   	_______,	_______,	_______,				_______,	_______,
	_______,	_______,	_______,										_______, 							_______,	MO(3),   	_______,	_______,	_______,    _______),
};

// LED Matrix
led_config_t g_led_config = { {
  // Key Matrix to LED Index
 	//C0        C1          2           3          4           5           6           7           8           9           10          11          12           13                      14           15          16
    {0,         1,          2,          3,         4,          5,          6,          7,          8,          9,          10,         11,         12,          NO_LED,                 NO_LED,      NO_LED,     NO_LED},
    {28,        27,         26,         25,        24,         23,         22,         21,         20,         19,         18,         17,         16,          15,                     13,          NO_LED,     43},
    {29,        30,         31,         32,        33,         34,         35,         36,         37,         38,         39,         40,         41,          42,                     14,          NO_LED,     44},
    {57,        56,         55,         54,        53,         52,         51,         50,         49,         48,         47,         46,         NO_LED,      45,                     NO_LED,      NO_LED,     NO_LED},
    {58,        NO_LED,     59,         60,        61,         62,         63,         64,         65,         66,         67,         68,         NO_LED,      69,                     70,          NO_LED,     NO_LED},
    {80,        79,         78,         NO_LED,    NO_LED,     NO_LED,     77,         NO_LED,     NO_LED,     76,         75,         NO_LED,     74,          73,                     72,          71,         NO_LED},
}, {
  // LED Index to Physical Position
    //0         1           2           3            4            5            6           7            8           9             10           11           12                      13          14
    {15*0,0},   {15*2,0},   {15*3,0},   {15*4,0},    {15*5,0},    {15*7,0},    {15*8,0},   {15*9,0},    {15*10,0},   {15*11,0},   {15*12,0},   {15*13,0},   {15*14,0},             {15*16,0}, {15*16,10},
    //15        16          17          18           19           20           21          22           23          24            25           26           27          28
    {15*14,10}, {15*12,10}, {15*11,10}, {15*10,10},  {15*9,10},  {15*8,10},   {15*7,10},  {15*6,10},   {15*5,10},  {15*4,10},    {15*3,10},   {15*2,10},   {15*1,10},  {15*0,10},
    //29        30          31          32              33          34          35          36          37          38              39          40          41          42          43          44
    {15*0,20},  {15*2,20},  {15*3,20},  {15*4,20},   {15*5,20},   {15*6,20},   {15*7,20},  {15*8,20},   {15*9,20},  {15*10,20},   {15*11,20},  {15*12,20},  {15*13,30}, {15*14,30}, {15*16,20}, {15*16,30},
    //45        46          47              48          49          50          51          52          53              54          55          56          57
    {15*14,30}, {15*12,30}, {15*11,30},  {15*10,30},  {15*9,30},   {15*8,30},  {15*7,30},   {15*6,30},  {15*5,30},    {15*4,30},   {15*3,30},   {15*2,30},  {15*0,30},
    //58        59          60              61          62          63          64          65          66              67          68          69          70
    {15*0,40},  {15*2,40},  {15*3,40},   {15*4,40},   {15*5,40},   {15*6,40},  {15*7,40},   {15*8,40},  {15*9,40},    {15*10,40},  {15*11,40}, {15*13,40},   {15*15,40},
    //71        72          73          74          75              76          77              78          79          80
    {15*15,50}, {15*14,50}, {15*13,50}, {15*11,50}, {15*10,50},   {15*9,50},    {15*6,50},    {15*2,50},    {15*1,50},   {15*0,50},
}, {
  // LED Index to Flag
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04
} };
