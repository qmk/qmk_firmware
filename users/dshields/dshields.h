#pragma once

// one-shot layer keys
#define OSL_RSE OSL(RSE)
#define OSL_LWR OSL(LWR)
#define OSL_FUN OSL(FUN)

// one-shot modifier keys
#define OSMLCTL OSM(MOD_LCTL)
#define OSMRCTL OSM(MOD_RCTL)
#define OSMLALT OSM(MOD_LALT)
#define OSMRALT OSM(MOD_RALT)
#define OSMLSFT OSM(MOD_LSFT)
#define OSMRSFT OSM(MOD_RSFT)

// mod-tap keys
#define MT_SPC  SFT_T(KC_SPC)
#define MT_BSPC SFT_T(KC_BSPC)
#define MT_ESC  LGUI_T(KC_ESC)

// LED/RGB controls
#ifdef KEYBOARD_planck_light
    #define LGT_TOG RGB_TOG
    #define LGT_MOD RGB_MOD
    #define LGT_BRT _______
    #define LGT_INC RGB_HUI
    #define LGT_DEC RGB_HUD
#endif
#ifdef KEYBOARD_planck_rev3
    #define LGT_TOG BL_TOGG
    #define LGT_MOD BL_STEP
    #define LGT_BRT BL_BRTG
    #define LGT_INC BL_INC
    #define LGT_DEC BL_DEC
#endif
#ifdef KEYBOARD_planck_rev6
    #define LGT_TOG _______
    #define LGT_MOD _______
    #define LGT_BRT _______
    #define LGT_INC _______
    #define LGT_DEC _______
#endif

enum layers   { DEF, LWR, RSE, FUN };
