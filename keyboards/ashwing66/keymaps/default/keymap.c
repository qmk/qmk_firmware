// Copyright 2023 James GzowskiMO(_LAYERB)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layer {
    _LAYERA,
    _LAYERB,
    _LAYERC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYERA] = LAYOUT_5x16(
        KC_ESC ,KC_1   ,KC_2    ,KC_3       ,KC_4    ,KC_5	  			 	 	   ,KC_6       ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_GRV  ,
        KC_TAB ,KC_Q   ,KC_W    ,KC_E       ,KC_R    ,KC_T				 	           ,KC_Y       ,KC_U  	,KC_I    ,KC_O    ,KC_P    ,KC_MINS ,
        KC_LCTL,KC_A   ,KC_S    ,KC_D       ,KC_F    ,KC_G                                                 ,KC_H       ,KC_J   	,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
        KC_LSFT,KC_Z   ,KC_X    ,KC_C       ,KC_V    ,KC_B    ,KC_LBRC          ,KC_MUTE          ,KC_RBRC ,KC_N       ,KC_M 	,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
        KC_LBRC,KC_PSCR,KC_CAPS ,MO(_LAYERB),KC_LGUI ,KC_LALT ,KC_SPC  ,KC_PGDN  	 ,KC_PGUP ,KC_ENT  ,KC_BSPC ,MO(_LAYERC),KC_INS  ,KC_DEL  ,KC_BSLS ,KC_RBRC
),
    [_LAYERB] = LAYOUT_5x16(
        KC_ESC ,RM_TOGG,RM_PREV ,RM_NEXT    ,RM_VALD ,RM_VALU                                              ,RM_SPDD    ,RM_SPDU ,RM_HUED ,RM_HUEU ,RM_SATD ,RM_SATU ,
        KC_TAB ,KC_Q   ,KC_W    ,KC_E       ,KC_R    ,KC_T                                                 ,KC_Y       ,KC_BTN1 ,KC_MS_U ,KC_BTN2 ,KC_P    ,KC_EQL  ,
        KC_LCTL,KC_A   ,KC_S    ,KC_D       ,KC_F    ,KC_G                                                 ,KC_H       ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_SCLN ,KC_QUOT ,
        KC_LSFT,KC_Z   ,KC_X    ,KC_C       ,KC_V    ,KC_B    ,KC_LBRC          ,KC_MUTE          ,KC_RBRC ,KC_N       ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
        KC_LBRC,KC_PSCR,KC_CAPS ,_______    ,KC_LGUI ,KC_LALT ,KC_SPC  ,KC_END          ,KC_HOME  ,KC_ENT  ,KC_BSPC    ,_______ ,KC_INS  ,KC_DEL  ,KC_BSLS ,KC_RBRC
),
    [_LAYERC] = LAYOUT_5x16(
        KC_ESC ,KC_F1  ,KC_F2   ,KC_F3      ,KC_F4   ,KC_F5                                                ,KC_F6      ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_GRV  ,
        KC_TAB ,KC_Q   ,KC_W    ,KC_E       ,KC_R    ,KC_T                                                 ,KC_Y       ,KC_U    ,KC_UP   ,KC_O    ,KC_P    ,KC_EQL  ,
        KC_LCTL,KC_A   ,KC_S    ,KC_D       ,KC_F    ,KC_G                                                 ,KC_H       ,KC_LEFT ,KC_DOWN ,KC_RIGHT,KC_SCLN ,KC_QUOT ,
        KC_LSFT,KC_Z   ,KC_X    ,KC_C       ,KC_V    ,KC_B    ,KC_LBRC          ,KC_MUTE          ,KC_RBRC ,KC_N       ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
        KC_F11 ,KC_PSCR,KC_CAPS ,_______    ,KC_LGUI ,KC_LALT ,KC_SPC  ,KC_END          ,KC_HOME  ,KC_ENT  ,KC_BSPC    ,_______ ,KC_INS  ,KC_DEL  ,KC_BSLS ,KC_F12
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAYERA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LAYERB] =  { ENCODER_CCW_CW(RM_HUED, RM_HUEU)},
    [_LAYERC] =  { ENCODER_CCW_CW(RM_VALD, RM_VALU)}
};
#endif
