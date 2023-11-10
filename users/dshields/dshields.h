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
#define MT_A    LGUI_T(KC_A)
#define MT_S    LALT_T(KC_S)
#define MT_D    LSFT_T(KC_D)
#define MT_F    LCTL_T(KC_F)
#define MT_J    RCTL_T(KC_J)
#define MT_K    RSFT_T(KC_K)
#define MT_L    RALT_T(KC_L)
#define MT_SCLN RGUI_T(KC_SCLN)

// layer-tap keys
#if defined KEYBOARD_planck_light \
    || defined KEYBOARD_planck_rev3 \
    || defined KEYBOARD_planck_rev6 \
    || defined KEYBOARD_keyboardio_atreus
    #define LT_G    LT(LWR, KC_G)
    #define LT_H    LT(RSE, KC_H)
#elif defined KEYBOARD_keyboardio_model01
    #define LT_G    LT(FUN, KC_G)
    #define LT_H    LT(FUN, KC_H)
#else
    #define LT_G    KC_G
    #define LT_H    KC_H
#endif

// LED/RGB controls
#if defined KEYBOARD_planck_light
    #define LGT_TOG RGB_TOG
    #define LGT_MOD RGB_MOD
    #define LGT_BRT _______
    #define LGT_INC RGB_HUI
    #define LGT_DEC RGB_HUD
#elif defined KEYBOARD_planck_rev3
    #define LGT_TOG BL_TOGG
    #define LGT_MOD BL_STEP
    #define LGT_BRT BL_BRTG
    #define LGT_INC BL_UP
    #define LGT_DEC BL_DOWN
#else
    #define LGT_TOG _______
    #define LGT_MOD _______
    #define LGT_BRT _______
    #define LGT_INC _______
    #define LGT_DEC _______
#endif

enum layers   { DEF, LWR, RSE, FUN };
