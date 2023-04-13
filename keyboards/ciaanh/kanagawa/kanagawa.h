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
    _FUNC, 
    _CODE
};

enum custom_keycodes 
{ 
    CUSTOMKEY = SAFE_RANGE, 
    NEW_SAFE_RANGE, 
};

#define TO_BASE     TO(_BASE)
#define TO_CODE     TG(_CODE)

#define L_FNC      MO(_FUNC)

#define _SCRNSHOT LSFT(LGUI(KC_S))