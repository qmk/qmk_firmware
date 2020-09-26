#include "kb.h"
#include QMK_KEYBOARD_H

//General Definitions
#define LOCKSCREEN LCTL(LSFT(KC_POWER)) // Screen Lock shortcut for OSX

// Figma Componenets
#define CREATECOMPONENT LALT(LGUI(KC_K))
#define SHOWCOMPONENT LALT(LKC_KP_2)
#define TEAMLIB LALT(LGUI(KC_O))
#define DETACH LALT(LGUI(KC_B))

// Figma Shortcuts
#define FIGLAYERS LALT(LKC_KP_1)
#define SENDBACK LGUI(KC_LBRACKET)
#define BRINGFORW LGUI(KC_RBRACKET)
#define GRID LCTRL(KC_G)
#define TEXTLEFT LALT(LGUI(KC_L))
#define TEXTRIGHT LALT(LGUI(KC_R))
#define TEXTCENTER LALT(LGUI(KC_T))
#define RUNLASTPLUG LALT(LALT(KC_P))
#define COPYSTYLE KC_LGUI(KC_LALT(KC_C))
#define PASTESTYLE KC_LGUI(KC_LALT(KC_V))
#define AUTOLAYOUT KC_LSHIFT(KC_A)
#define RMLAYOUT KC_LGUI(KC_LSHIFT(KC_A))

enum oktiboard_layers {
  _FIGMA = 0,
  _LAB,
};

enum custom_keycodes {
    M_AUTOLAY = SAFE_RANGE,
    M_COPYSTYLES,
};

bool is_copied = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M_AUTOLAY:
        if(!is_copied) {
            SEND_STRING(AUTOLAYOUT);
            is_copied = true;
        } else {
            SEND_STRING(RMLAYOUT);
            is_copied = false;
        }
        break;

    case M_COPYSTYLES:
        if(!is_copied) {
            SEND_STRING(COPYSTYLE);
            is_copied = true;
        } else {
            SEND_STRING(PASTESTYLE);
            is_copied = false;
        }
        break;
    }
    return true;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _FIGMA:
        rgblight_setrgb (148,0,211);
        break;
    case _LAB:
        rgblight_setrgb (255,218,185);
        break;
    }
  return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Figma
 * ,---------------------------.
 * |  CC  |  SC  |  TL  |  DI  |
 * |------+------+------+------|
 * |  LYR |  BF  |  SB  | SHG  |
 * |------+------+------+------|
 * | PLG  | TAL  | TAC  | TAR  |
 * |------+------+------+------|
 * | AUL  |      |  CPS | CHNG |
 * `---------------------------'
 */


[_FIGMA] = LAYOUT(
		CREATECOMPONENT, SHOWCOMPONENT, TEAMLIB, DETACH,
		FIGLAYERS, BRINGFORW, SENDBACK, GRID,
		RUNLASTPLUG, TEXTLEFT, TEXTCENTER, TEXTRIGHT,
		{M_AUTOLAY}, _______ , {M_COPYSTYLES}, TO(_LAB)
),

/* Lab
 * ,---------------------------.
 * | FGM  |      |      | RESET|
 * |------+------+------+------|
 * |      |AU_ON |AU_OFF|      |
 * |------+------+------+------|
 * |      |      |      |      |
 * |------+------+------+------|
 * | LCK  |      |      | CHNG |
 * `---------------------------'
 */

[_LAB] = LAYOUT(
		_______, _______, _______, _______,
		_______, AU_ON, AU_OFF, _______,
		_______, _______, _______, _______,
		LOCKSCREEN, _______, _______, TO(_FIGMA)
	),
};




void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
