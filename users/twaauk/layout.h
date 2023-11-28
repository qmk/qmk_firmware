#ifndef LAYOUT_H
#define LAYOUT_H


#include "virtualkeys.h"

#define LAYER0 LAYER_LAYOUT(											\
		_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
		_______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, _______, \
		_______,  VKC_SA,  VKC_CS,  VKC_AD,  VKC_2F,    KC_G,                      KC_H,  VKC_1J,  VKC_AK,  VKC_CL, VKC_SSP, _______, \
		_______,  VKC_SZ,  VKC_CX,  VKC_AC,  VKC_4V,  VKC_2B, _______, _______,  VKC_1N,  VKC_3M,VKC_ACMM,VKC_CDOT, VKC_SET, _______, \
        _______, _______, _______, _______, _______,  VKC_2B,    KC_G,    KC_T,    KC_Y,    KC_H, _______, _______, _______, _______)

#define LAYER1 LAYER_LAYOUT( \
		_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
		_______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______, \
		_______,  VKC_S6,  VKC_C7,  VKC_A8,    KC_9,    KC_0,                     KC_F6,   KC_F7, VKC_AF8, VKC_CF9,VKC_SF10, _______, \
		_______, VKC_STB,VKC_CPSR, KC_LGUI, KC_BSPC,  KC_DEL, _______, _______, XXXXXXX, XXXXXXX, KC_RALT,VKC_CF11,VKC_SF12, _______, \
        _______, _______, _______, _______, _______,  KC_DEL,    KC_0,    KC_5,   KC_F1,   KC_F6, _______, _______, _______, _______)

#define LAYER2 LAYER_LAYOUT(											\
		_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
		_______,  KC_ESC,   KC_UP, XXXXXXX, XXXXXXX, VKC_CAD,                   KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, _______, \
		_______, VKC_SLF, VKC_CDN, VKC_ART, XXXXXXX, XXXXXXX,                   KC_LEFT, KC_DOWN, VKC_AUP, VKC_CRT, VKC_SGR, _______, \
		_______, KC_LSFT, KC_LCTL, KC_LALT, XXXXXXX, XXXXXXX, _______, _______, KC_COMM,  KC_DOT, VKC_ASL, VKC_CSC, VKC_SQT, _______, \
        _______, _______, _______, _______, _______, _______, XXXXXXX, VKC_CAD, KC_MINS, KC_LEFT, _______, _______, _______, _______)

#define LAYER3 LAYER_LAYOUT( \
		_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
		_______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______, \
		_______,VKC_SCIR,VKC_CAMP,VKC_AAST, KC_LPRN, KC_RPRN,                     KC_F6,   KC_F7, VKC_AF8, VKC_CF9,VKC_SF10, _______, \
		_______, VKC_STB,VKC_CPSR, KC_LGUI, KC_BSPC,  KC_DEL, _______, _______, XXXXXXX, XXXXXXX, KC_RALT,VKC_CF11,VKC_SF12, _______, \
        _______, _______, _______, _______, _______,  KC_DEL, KC_RPRN, KC_PERC,   KC_F1,   KC_F6, _______, _______, _______, _______)

#define LAYER4 LAYER_LAYOUT( \
		_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
		_______,  KC_ESC,   KC_UP, XXXXXXX, XXXXXXX, VKC_CAD,                   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, _______, \
		_______, VKC_SLF, VKC_CDN, VKC_ART, XXXXXXX, XXXXXXX,                   KC_LEFT, KC_DOWN, VKC_AUP, VKC_CRT,VKC_STLD, _______, \
		_______, KC_LSFT, KC_LCTL, KC_LALT, XXXXXXX, XXXXXXX, _______, _______,   KC_LT,   KC_GT,VKC_AQES,VKC_CCLN,VKC_SDQT, _______, \
        _______, _______, _______, _______, _______, _______, XXXXXXX, VKC_CAD, KC_UNDS, KC_LEFT, _______, _______, _______, _______)

#define LAYER5 LAYER_LAYOUT( \
		_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______,                   KC_WH_U, _______, KC_MS_U, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______,                   KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, KC_WH_D, KC_BTN1, KC_BTN2, KC_BTN3, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_U, KC_WH_L, _______, _______, _______, _______)

#define LAYER6 LAYER_LAYOUT( \
		_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
		_______, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS,                 TO(0), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
		_______, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS,                KC_MY_BTN2,KC_MY_BTN1, KC_MY_SCR, KC_MY_BTN3, KC_RSFT,_______, \
		_______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3,KC_KP_DOT,_______, _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_DOT, _______, \
        _______, _______, _______, _______, _______,KC_KP_DOT,KC_KP_PLUS,KC_KP_MINUS,TO(0),KC_MY_BTN2, _______, _______, _______, _______)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYER0,
	LAYER1,
	LAYER2,
	LAYER3,
	LAYER4,
	LAYER5,
	LAYER6
};


#endif
