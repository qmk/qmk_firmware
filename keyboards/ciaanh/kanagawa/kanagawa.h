#pragma once

#include "quantum.h"

#ifdef KEYBOARD_ciaanh_kanagawa_ansi
    #include "ansi.h"
#endif 

#ifdef KEYBOARD_ciaanh_kanagawa_iso
    #include "iso.h"
#endif 

#define ___ KC_NO
#define NA NO_LED

enum layers 
{ 
    _BASE,
    _CODE, 
    _FUNC,
    _TOP
};

enum custom_keycodes 
{ 
    CUSTOMKEY = SAFE_RANGE, 
    NEW_SAFE_RANGE, 
};

#define TO_BASE     TO(_BASE)
#define TO_FUNC     TG(_FUNC)

#define L_CODE      MO(_CODE)

#define _SCRNSHOT LSFT(LGUI(KC_S))