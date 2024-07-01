// Copyright 2023 James Gzowski
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layer {
    _LAYERA,
    _LAYERB,
    _LAYERC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYERA] = LAYOUT_5x16(
        KC_ESC , KC_1  		,KC_2   ,KC_3   , KC_4  , KC_5  ,  			 	 	 KC_6   , KC_7    	, KC_8    , KC_9   , KC_0    , KC_GRV ,
        KC_TAB , KC_Q  		,KC_W   ,KC_F   , KC_P  , KC_G  , 			 		 KC_J   , KC_L  	, KC_U    , KC_Y   , KC_SCLN ,KC_MINUS,
        KC_LCTL, KC_A  		,KC_R   ,KC_S   , KC_T  , KC_D  ,  		 			 KC_H   , KC_N    	, KC_E    , KC_I   , KC_O    ,KC_QUOT ,
        KC_LSFT, KC_Z  		,KC_X   ,KC_C   , KC_V  , KC_B  , KC_LBRC,       KC_MUTE,	KC_RBRC, KC_K   , KC_M    	, KC_COMM , KC_DOT , KC_SLSH , KC_RSFT,
        KC_BSLS  , MO(_LAYERB) 	,KC_LGUI,KC_LALT,KC_SPC , KC_LALT, KC_SPC , KC_PGDN, 	KC_PGUP, KC_ENT , KC_BSPC, MO(_LAYERC)   , KC_INS  , KC_DEL , KC_DEL  , KC_SLSH
),
    [_LAYERB] = LAYOUT_5x16(
        KC_ESC , KC_1           ,KC_2   ,KC_3   , KC_4  , KC_5  ,                                        KC_6   , KC_7          , KC_8    , KC_9   , KC_0    , KC_GRV ,
        KC_TAB , KC_Q           ,KC_W   ,KC_F   , KC_P  , KC_G  ,                                        KC_J   , KC_L          , KC_U    , KC_Y   , KC_SCLN ,KC_MINUS,
        KC_LCTL, KC_A           ,KC_R   ,KC_S   , KC_T  , KC_D  ,                                        KC_H   , KC_N          , KC_E    , KC_I   , KC_O    ,KC_QUOT ,
        KC_LSFT, KC_Z           ,KC_X   ,KC_C   , KC_V  , KC_B  , KC_LBRC,       KC_MUTE,       KC_RBRC, KC_K   , KC_M          , KC_COMM , KC_DOT , KC_SLSH , KC_RSFT,
        KC_BSLS  , MO(_LAYERB)  ,KC_LGUI,KC_LALT,KC_SPC , KC_LALT, KC_SPC , KC_PGDN,    KC_PGUP, KC_ENT , KC_BSPC, MO(_LAYERC)   , KC_INS  , KC_DEL , KC_DEL  , KC_SLSH
),
    [_LAYERC] = LAYOUT_5x16(
        KC_ESC , KC_1           ,KC_2   ,KC_3   , KC_4  , KC_5  ,                                        KC_6   , KC_7          , KC_8    , KC_9   , KC_0    , KC_GRV ,
        KC_TAB , KC_Q           ,KC_W   ,KC_F   , KC_P  , KC_G  ,                                        KC_J   , KC_L          , KC_U    , KC_Y   , KC_SCLN ,KC_MINUS,
        KC_LCTL, KC_A           ,KC_R   ,KC_S   , KC_T  , KC_D  ,                                        KC_H   , KC_N          , KC_E    , KC_I   , KC_O    ,KC_QUOT ,
        KC_LSFT, KC_Z           ,KC_X   ,KC_C   , KC_V  , KC_B  , KC_LBRC,       KC_MUTE,       KC_RBRC, KC_K   , KC_M          , KC_COMM , KC_DOT , KC_SLSH , KC_RSFT,
        KC_BSLS  , MO(_LAYERB)  ,KC_LGUI,KC_LALT,KC_SPC , KC_LALT, KC_SPC , KC_PGDN,    KC_PGUP, KC_ENT , KC_BSPC, MO(_LAYERC)   , KC_INS  , KC_DEL , KC_DEL  , KC_SLSH
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAYERA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LAYERB] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_LAYERC] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
};
#endif
