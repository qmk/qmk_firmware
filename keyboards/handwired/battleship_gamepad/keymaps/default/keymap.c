#include QMK_KEYBOARD_H
#include "joystick.h"
#include "analog.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_F1, KC_F2, KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, 
		KC_F3, KC_F4, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 
		KC_F5, KC_F6, KC_NO, KC_A, KC_S, KC_D, KC_F, KC_G, 
		KC_F7, KC_F8, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, 
		KC_F9, KC_F10, LT(1, KC_NO), KC_LCTL, KC_LALT, LT(2, KC_NO), LT(1, KC_NO), KC_SPC),

	[1] = LAYOUT(
		RESET, DEBUG, KC_TILD, KC_6, KC_7, KC_8, KC_9, KC_0, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_IN(F5, 1023, 512, 0),
    [1] = JOYSTICK_AXIS_IN(F4, 0, 512, 1023)
};

// joystick button code (thumbstick pressed)
void keyboard_pre_init_user(void) {
	setPinInputHigh(F6);
}