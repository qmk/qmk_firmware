// <name>.h file for user or keymap specific settings (such as the enum for layer or keycodes)
#pragma once
#include QMK_KEYBOARD_H
#include "version.h"

#include "wrappers.h"
#define XXX  KC_NO
#define U_NA KC_NO // Present but not available for use.
#define U_NU KC_NO // Available but not used.

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

enum layers { _BASE, _GAMING, _SYM, _NUM, _NAV,  _MEDIA, _FUN, _MOUSE  };

enum custom_keycodes {
    VRSN = SAFE_RANGE,
    U_BASE,
    U_GAMING,
    NEW_SAFE_RANGE  //use "NEW_SAFE_RANGE" for keymap specific codes
};

// Tap Dance declarations
enum {
    TD_BOOT,
    TD_EECLEAR,
    TD_BASE,
    TD_GAMING
};

enum unicode_names {
    AE_L,
    AE_U,
    OE_L,
    OE_U,
    AA_L,
    AA_U,
    IRONY,
    SNEK
};

#define KC_AE XP(AE_L,AE_U)
#define KC_OE XP(OE_L,OE_U)
#define KC_AA XP(AA_L,AA_U)

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods
#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)

// Left-hand home row mods sym

// Right-hand home row mods sym


#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)