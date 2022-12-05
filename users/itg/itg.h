#pragma once

#include QMK_KEYBOARD_H
#include "keyrecords/wrappers.h"
#include "keyrecords/process_records.h"

#define _BL 0
#define QWE 1
#define GAM 2
#define OSX 3
#define SYM 4
#define MED 5  // media keys
#define MAX 6

#define ____ KC_TRNS

enum custom_keycodes {
    LK_QWE = SAFE_RANGE,
    LK_OSX,
    VRSN,
    SCREENSHOT,
    KC_SCT1,
    KC_SCT2,
    KC_SCT3,
    KC_SCT4,
    KC_SCT5,
};
