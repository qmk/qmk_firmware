#pragma once

enum layers 
{ 
    _BASE, 
    _FN, 
    _VS, 
    _CODE, 
    _TOOLS, 
    _LEFT, 
    _RIGHT 
};

enum custom_keycodes 
{ 
    VS_FRM = SAFE_RANGE, 
    COMM, 
    UNCOMM,
    NEW_SAFE_RANGE, 
};


#define _SAVE       LCTL(KC_S)

#define VSC_FRM     LSFT(LALT(KC_F))
#define VSC_TRM     LCTL(KC_GRV)
#define VSC_COM     LCTL(KC_P)

#define VS_INT      LCTL(KC_J)
#define VS_QW       LSFT(KC_F9)
#define VS_PEEK     LALT(KC_F12)
#define VS_GREF     LCTL(KC_F12)

#define SC_SF12     LSFT(KC_F12)

#define TO_BASE     TO(_BASE)
#define TO_FN       TG(_FN)
#define TO_VS       TG(_VS)
#define TO_CODE     TG(_CODE)

#define L_TOOLS     MO(_TOOLS)

#define L_LFT       MO(_LEFT)
#define L_RGT       MO(_RIGHT)

#define _SCREENSHOT LSFT(LGUI(KC_S))
