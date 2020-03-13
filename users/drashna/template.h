#pragma once

#include QMK_KEYBOARD_H
#include "version.h"
#include "eeprom.h"

// Define layer names
#define BASE 0

enum custom_keycodes {
    VRSN = SAFE_RANGE,  // can always be here
    KC_MAKE,
    KC_RESET,
    NEWPLACEHOLDER  // use "NEWPLACEHOLDER for keymap specific codes
};
