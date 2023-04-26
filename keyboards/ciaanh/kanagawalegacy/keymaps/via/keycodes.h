#pragma once

enum layers 
{ 
    _BASE,
    _LOWER, 
    _UPPER,
    _CODE
};

enum custom_keycodes 
{ 
    ENCODER = SAFE_RANGE, 
    NEW_SAFE_RANGE, 
};

#define TO_BASE     TO(_BASE)
#define TO_CODE     TG(_CODE)

#define L_UP       MO(_UPPER)
#define L_DWN      MO(_LOWER)

#define _SCRNSHOT LSFT(LGUI(KC_S))
