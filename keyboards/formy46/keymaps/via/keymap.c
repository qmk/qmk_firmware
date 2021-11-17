/* Copyright 2021 marby3
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
#include "joystick.h"
#include "analog.h"
#include "pointing_device.h"
#include <stdio.h>

/* layer change */
#define FUNC    MO(_FN)
bool re_function = false;

/* short cut */
#define UNDO    LCTL(KC_Z)
#define REDO    C_S_T(KC_Z)
#define CUT     LCTL(KC_X)
#define COPY    LCTL(KC_C)
#define PASTE   LCTL(KC_V)
#define SAVE    LCTL(KC_S)

enum layer_names {
    _BASE = 0,
    _GAME_MODE,
    _CREATION_MODE,
    _FN
};

enum custom_keycodes {
    JS_MODE = SAFE_RANGE,
    RE_MODE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Mode */
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,                                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,       KC_G,                                                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,     KC_NO,                         KC_GRV,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT,     JS_MODE, KC_SPC,  RE_MODE,     KC_BSPC, KC_ENT,  KC_DEL,      KC_RALT, KC_RGUI, KC_RCTL, FUNC
    ),
    /* Game Mode */
    [_GAME_MODE] = LAYOUT(
        _______, _______, _______, _______, _______,                                                 _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                 _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______,                       _______,     _______, _______, _______, _______, _______,
        _______, _______, _______, _______,     KC_NO,   _______, _______,     _______, _______, _______,     _______, _______, _______, _______
    ),
    /* Creation Mode */
    [_CREATION_MODE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,                                                    _______, _______, _______, _______, _______,
        KC_TAB,  KC_LBRC, KC_RBRC, UNDO,    KC_M,                                                    _______, _______, _______, _______, _______,
        KC_LSFT, KC_B,    KC_P,    REDO,    KC_E,       _______,                        _______,     _______, CUT,     COPY,    PASTE,   SAVE,
        KC_LCTL, _______, KC_X,    KC_LALT,     KC_NO,  _______,  _______,     _______, _______, _______,     _______, _______, _______, _______
    ),
    /* Function Mode */
    [_FN] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        _______, _______, _______, _______, KC_MINS,                                                 KC_EQL,  _______, _______, _______, KC_BSLS,
        _______, _______, _______, _______, KC_LBRC,     _______,                       _______,     KC_RBRC, _______, _______, _______, _______,
        _______, _______, _______, _______,     KC_NO,   _______, _______,     _______, _______, _______,     _______, _______, _______, _______
    )
};


/* joystick config */
#ifdef JOYSTICK_ENABLE
// Change this
char arrow_keys[4] = {KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT}; // up, left, down, right
static int joystickThreshold = 6; // Value to prevent joystick drift
static int joystickResolution = 24; // Decide the movement speed of the joystick
// Don't chnage this
static uint8_t joystickMode = 0;
static uint8_t joystick_modes = 3; // amount of modes
static int actuation = 255; // actuation point for arrows (0-511)
bool arrows[4];

joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL
};

void joystick_task(){
	switch (joystickMode) {
	case 0: // gamepad
		joystick_status.axes[0] = 128 - analogReadPin(F4)/4;
		joystick_status.axes[1] = analogReadPin(F5)/4 - 128;
		joystick_status.status |= JS_UPDATED;
        send_joystick_packet(&joystick_status);
		break;
    case 1: // arrows
        if (!arrows[0] && analogReadPin(F5) - 512 > actuation){
            arrows[0] = true;
            register_code16(arrow_keys[2]);
        }
        else if (arrows[0] &&  analogReadPin(F5) - 512 < actuation){
            arrows[0] = false;
            unregister_code16(arrow_keys[2]);
        }
        if (!arrows[1] && analogReadPin(F5) - 512 < -actuation){
            arrows[1] = true;
            register_code16(arrow_keys[0]);
        }
        else if (arrows[1] && analogReadPin(F5) - 512 > -actuation){
            arrows[1] = false;
            unregister_code16(arrow_keys[0]);
        }
        if (!arrows[2] && analogReadPin(F4) - 512 > actuation){
            arrows[2] = true;
            register_code16(arrow_keys[1]);
        }
        else if (arrows[2] &&  analogReadPin(F4) - 512 < actuation){
            arrows[2] = false;
            unregister_code16(arrow_keys[1]);
        }
        if (!arrows[3] && analogReadPin(F4) - 512 < -actuation){
            arrows[3] = true;
            register_code16(arrow_keys[3]);
        }
        else if (arrows[3] && analogReadPin(F4) - 512 > -actuation){
            arrows[3] = false;
            unregister_code16(arrow_keys[3]);
        }
        break;
    case 2: // mouse
        ;
        report_mouse_t currentReport = pointing_device_get_report();
        currentReport.x = (512 - analogReadPin(F4)) / joystickResolution;
        currentReport.y = (analogReadPin(F5) - 512) / joystickResolution;
        if (currentReport.x < joystickThreshold && currentReport.x > -joystickThreshold){
            currentReport.x = 0;
        }
        if (currentReport.y < joystickThreshold && currentReport.y > -joystickThreshold){
            currentReport.y = 0;
        }
        pointing_device_set_report(currentReport);
        pointing_device_send();
        break;
	}
};
#endif

/* rotary encorder config */
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(get_highest_layer(layer_state)){
        case _BASE:
            if (re_function){
                if (clockwise) {
                    layer_move(_GAME_MODE);
                } else {
                    layer_move(_CREATION_MODE);
                }
            } else {
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
            }
            break;
        case _GAME_MODE:
            if (re_function){
                if (clockwise) {
                    layer_move(_CREATION_MODE);
                } else {
                    layer_move(_BASE);
                }
            } else {
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
            }
            break;
        case _CREATION_MODE:
            if (re_function){
                if (clockwise) {
                    layer_move(_BASE);
                } else {
                    layer_move(_GAME_MODE);
                }
            } else {
                if (clockwise) {
                    //Redo
                    tap_code16(C(S(KC_Z)));
                } else {
                    //Undo
                    tap_code16(C(KC_Z));
                }
            }
            break;
        case _FN:
            if (re_function){
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else {
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
            }
            break;
    }
    return false;
};
#endif


/* OLED config */
//This configuration is for a 128x32 display.
#ifdef OLED_ENABLE
void render_logo(void) {
    static const char PROGMEM logo[] = {
	0x8c, 0x86, 0x86, 0x86, 0x86, 0x86, 0x8c, 0x98, 0x8c, 0x86, 0x86, 0x86, 0x86, 0x86, 0x8c, 0x98,
	0x8c, 0x86, 0x86, 0x86, 0x86, 0x86, 0x8c, 0x98, 0x8c, 0x86, 0x86, 0x86, 0x86, 0x86, 0x8c, 0x98,
	0x00, 0x78, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0xf8, 0xc0, 0xf8, 0xf8, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0x00, 0x80, 0xe0, 0xf8, 0xfc, 0x9c, 0x0e, 0x06, 0x06, 0xf6, 0xf6, 0x06, 0x06, 0xf6, 0xf6,
	0x06, 0x06, 0xf6, 0xf6, 0x06, 0x36, 0x76, 0x66, 0x86, 0x06, 0x06, 0xf6, 0xf6, 0x06, 0x86, 0xe6,
	0x66, 0x36, 0x36, 0x36, 0x36, 0x66, 0xe6, 0x86, 0x06, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0x98,
	0x8c, 0x86, 0x86, 0x86, 0x86, 0x86, 0x8c, 0x98, 0x8c, 0x86, 0x86, 0x86, 0x86, 0x86, 0x8c, 0x98,
	0x8c, 0x86, 0x86, 0x86, 0x86, 0x86, 0x8c, 0x98, 0x8c, 0x86, 0x86, 0x86, 0x86, 0x86, 0x8c, 0x98,
	0x01, 0x11, 0x11, 0x6d, 0x11, 0x11, 0x01, 0x01, 0x01, 0x11, 0x11, 0x6d, 0x11, 0x11, 0x01, 0x01,
	0x01, 0x11, 0x11, 0x6d, 0x11, 0x11, 0x01, 0x01, 0x01, 0x11, 0x11, 0x6d, 0x11, 0x11, 0x01, 0x01,
	0x00, 0x00, 0x38, 0x38, 0x38, 0x38, 0x38, 0x1f, 0x0f, 0x00, 0xff, 0xff, 0xe0, 0x78, 0x3e, 0x27,
	0x31, 0x3c, 0x3f, 0x0f, 0x83, 0x8f, 0xbf, 0x3c, 0x38, 0x20, 0x0f, 0x3f, 0x30, 0x30, 0x3f, 0x3f,
	0x30, 0xb0, 0x3f, 0x8f, 0x00, 0x0e, 0x1f, 0xbf, 0xb1, 0xb1, 0x30, 0x3f, 0x3f, 0x80, 0x87, 0x9f,
	0x98, 0xb0, 0xb0, 0xb0, 0xb0, 0x98, 0x9f, 0x87, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01,
	0x01, 0x11, 0x11, 0x6d, 0x11, 0x11, 0x01, 0x01, 0x01, 0x11, 0x11, 0x6d, 0x11, 0x11, 0x01, 0x01,
	0x01, 0x11, 0x11, 0x6d, 0x11, 0x11, 0x01, 0x01, 0x01, 0x11, 0x11, 0x6d, 0x11, 0x11, 0x01, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x00, 0x0a, 0x0a, 0x0a, 0x15, 0x15, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00,
	0x02, 0x07, 0x03, 0x02, 0x00, 0x1c, 0x13, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x0f, 0x0f, 0x0f,
	0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0x20, 0x70, 0x78, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
	0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
	0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
	0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x3e, 0x3f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    oled_write_raw_P(logo, sizeof(logo));
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()){
    return OLED_ROTATION_270;
    }
    return rotation;  // flips the display 180 degrees if offhand
}

void render_layer_state(void) {
    oled_write_P(PSTR("Mode:\n"), false);
    switch(get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("L0\n"), true);
            oled_write_P(PSTR("L1\n"), false);
            oled_write_P(PSTR("L2\n"), false);
            oled_write_P(PSTR("Fn\n"), false);
            break;
        case _GAME_MODE:
            oled_write_P(PSTR("L0\n"), false);
            oled_write_P(PSTR("L1\n"), true);
            oled_write_P(PSTR("L2\n"), false);
            oled_write_P(PSTR("Fn\n"), false);
            break;
        case _CREATION_MODE:
            oled_write_P(PSTR("L0\n"), false);
            oled_write_P(PSTR("L1\n"), false);
            oled_write_P(PSTR("L2\n"), true);
            oled_write_P(PSTR("Fn\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("L0\n"), false);
            oled_write_P(PSTR("L1\n"), false);
            oled_write_P(PSTR("L2\n"), false);
            oled_write_P(PSTR("Fn\n"), true);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined\n"), false);
    }
    #ifdef RGB_MATRIX_ENABLE
        oled_write_ln_P(PSTR(""), false);
        oled_write_ln_P(PSTR("LED:"), false);
        oled_write_ln_P(PSTR(""), false);
        static char rgbMode[6] = {0};
        snprintf(rgbMode, sizeof(rgbMode), "M:%-3d", rgblight_get_mode());
        oled_write(rgbMode, false);
        static char rgbHue[6] = {0};
        snprintf(rgbHue, sizeof(rgbHue), "H:%-3d", rgblight_get_hue());
        oled_write(rgbHue, false);
        static char rgbSat[6] = {0};
        snprintf(rgbSat, sizeof(rgbSat), "S:%-3d", rgblight_get_sat());
        oled_write(rgbSat, false);
        static char rgbVal[6] = {0};
        snprintf(rgbVal, sizeof(rgbVal), "V:%-3d", rgblight_get_val());
        oled_write(rgbVal, false);
    #endif
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
        render_logo();
        oled_scroll_right();  // Turns on scrolling
    }
}
#endif


/* keycord */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
    case JS_MODE:
        if (record->event.pressed) {
            joystickMode++;
            if (joystickMode == joystick_modes){
                joystickMode = 0;
            }
        }
        return false; // Skip all further processing of this key
    case RE_MODE:
        if (record->event.pressed) {
            re_function = !re_function;
    }
        return true; // Skip all further processing of this key
    default:
        return true; // Process all other keycodes normally
    }
}
