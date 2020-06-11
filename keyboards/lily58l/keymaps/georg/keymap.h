#ifndef KEYMAP_USER_H
#define KEYMAP_USER_H

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layers {
	_QWERTY = 0,
	_LOWER,
	_RAISE,
	_ADJUST
};

enum custom_keycodes {
	CUSTOM_SHIFT_QUOT = SAFE_RANGE,
	TOG_DK,  // Toggle dead keys
};

#endif