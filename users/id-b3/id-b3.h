#pragma once

#include "quantum.h"
#include "process_records.h"
#ifdef OLED_DRIVER_ENABLE
#    include "oled_stuff.h"
#endif
#ifdef TRACKBALL_ENABLE
	#include "pimoroni_trackball.h"
#endif
//#define DICE_ROLLER_ENABLE

/*

    Character Frequency: SPC e t a o i n s r h l d c u m f g p y w ENT b , . v k - " _ ' x ) ( ; 0  j 1 q = 2 : z / * ! ? $ 3 5 > { } 4 9 [ ] 8 6 7 \ + | & < % @ # ^ ` ~

    Punctuation Frequency: , . - " _ ' ) ( ; = : / * ! ? $ > { } [ ] \ + | & < % @ # ^ ` ~

*/

/* Define layer names */
enum userspace_layers {
    _COLEMAK = 0,
	_QWERTY,
	_GAMING,
//	_WARHAMMER,
    _SHORTCUT,
    _SYMNUM,
	_NAVIGATION,
	#ifdef DICE_ROLLER_ENABLE
	_RPG,
	#endif

};

#define CADEL LALT(LCTL(KC_DELETE))
#define TRML LALT(LCTL(KC_T))
#define TSKMN LCTL(LSFT(KC_ESCAPE))
#define CLSTAB LCTL(LSFT(KC_T))
#define SNAP LGUI(LSFT(KC_S))
#define SNAPL LGUI(LSFT(KC_LEFT))
#define SNAPR LGUI(LSFT(KC_RGHT))

#define _____________________COLEMAK_L1_____________________ KC_ESC,        KC_Q, KC_W, KC_F, KC_P, KC_G
#define _____________________COLEMAK_L2_____________________ KC_DEL,        KC_A, KC_R, KC_S, KC_T, KC_D
#define _____________________COLEMAK_L3_____________________ KC_LALT, CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B

#define _____________________COLEMAK_R1_____________________ KC_J, KC_L, KC_U   , KC_Y  , KC_SCLN        , KC_NONUS_BSLASH
#define _____________________COLEMAK_R2_____________________ KC_H, KC_N, KC_E   , KC_I  , KC_O           , CMD_T(KC_QUOTE)
#define _____________________COLEMAK_R3_____________________ KC_K, KC_M, KC_COMM, KC_DOT, CTL_T(KC_SLASH), OSL(_SHORTCUT)

#define _____________________THUMBS_LF1_____________________ TO(_GAMING), KC_LEFT, MT(MOD_LSFT, KC_SPC), LT(_SYMNUM, KC_ENT), KC_UP
#define _____________________THUMBS_LF2_____________________ OSM(MOD_LSFT), KC_DOWN

#define _____________________THUMBS_RG1_____________________ KC_LEFT, TD(TD_TABC), KC_BSPC, KC_RIGHT, TO(_QWERTY)
#define _____________________THUMBS_RG2_____________________ OSL(_NAVIGATION), C(KC_BSPC)

#define _____________________SHORTCT_L1_____________________ CADEL,_______,C(KC_W),C(KC_F),SNAPL,SNAPR
#define _____________________SHORTCT_L2_____________________ TRML, _______, _______, SNAP, CLSTAB, _______
#define _____________________SHORTCT_L3_____________________ TSKMN, _______, _______, _______, LALT(LCTL(KC_V)),_______
#define _____________________SHRT_TH_L1_____________________ G(KC_TAB), G(C(KC_LEFT)), G(C(KC_RIGHT)), RGB_TOG, RGB_M_P
#define _____________________SHRT_TH_L2_____________________ _______,_______

#define _____________________SHORTCT_R1_____________________ KC_MYCM, _______, _______, _______, _______,   RESET
#define _____________________SHORTCT_R2_____________________ _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______
#define _____________________SHORTCT_R3_____________________ _______, _______, _______, _______, G(KC_DOT), _______
#define _____________________SHRT_TH_R1_____________________ RGB_HUD, RGB_HUI, RGB_MOD, RGB_RMOD, KC_MUTE
#define _____________________SHRT_TH_R2_____________________ RGB_VAD, RGB_VAI

#define _____________________SYMNUM_LF1_____________________ A(KC_F4),_______, _______, S(KC_2), KC_LPRN, KC_RPRN
#define _____________________SYMNUM_LF2_____________________ _______,  KC_NUHS, KC_EQL, KC_MINS, TD(TD_EXLM), TD(TD_PCAS)
#define _____________________SYMNUM_LF3_____________________ RESET, _______, _______, _______, KC_LBRC, KC_RBRC

#define _____________________SYMNUM_RT1_____________________ TD(TD_ASDI),KC_7,KC_8,KC_9,_______,_______
#define _____________________SYMNUM_RT2_____________________ TD(TD_PLMN),KC_4,KC_5,KC_6,KC_0,_______
#define _____________________SYMNUM_RT3_____________________ _______,KC_1,KC_2,KC_3,KC_DOT,_______

#define _____________________GAMING_LF1_____________________ KC_ESC,    KC_I,    KC_Q,    KC_W,    KC_E,    KC_R
#define _____________________GAMING_LF2_____________________ KC_LCTRL, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F
#define _____________________GAMING_LF3_____________________ KC_GRV, CTL_T(KC_C),KC_Z,    KC_X,    KC_C,    KC_V
#define _____________________GAME_TMB_L_____________________ TO(_COLEMAK),  OSL(_NAVIGATION), KC_SPC,  KC_LALT,  KC_ENT
#define _____________________GAME_TM_L2_____________________ KC_TAB, KC_0

//#define _____________________GAMING_RT1_____________________ KC_T,    KC_7,    KC_8,    KC_9,    KC_O,    KC_P
//#define _____________________GAMING_RT2_____________________ KC_G,    KC_4,    KC_5,    KC_6,    KC_0, KC_SCLN
//#define _____________________GAMING_RT3_____________________ KC_B,    KC_1,    KC_2,    KC_3,  KC_DOT, KC_SLASH
#define _____________________GAMING_RT1_____________________ KC_T,    TD(TD_7),    TD(TD_8),    TD(TD_9),    KC_O,    KC_P
#define _____________________GAMING_RT2_____________________ KC_G,    TD(TD_4),    TD(TD_5),    TD(TD_6),    TD(TD_0), KC_SCLN
#define _____________________GAMING_RT3_____________________ KC_B,    TD(TD_1),    TD(TD_2),    TD(TD_3),  KC_DOT, KC_SLASH
#define _____________________GAME_TMB_R_____________________ KC_F5,  KC_F8,  KC_F18,  KC_F17,  TO(_COLEMAK)//TO(_WARHAMMER)
#define _____________________GAME_TM_R2_____________________ KC_F10,  KC_F12

//#define _____________________WARHAMMER_LF1_____________________ KC_ESC,    KC_P,    KC_Q,    KC_W,    KC_E,    KC_R
//#define _____________________WARHAMMER_LF2_____________________ KC_T, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F
//#define _____________________WARHAMMER_LF3_____________________ KC_J, KC_Z, KC_X,    KC_C,    KC_V,    KC_B
//#define _____________________WARHAMMER_TMB_L_____________________ C(KC_A),  KC_BSPC, KC_SPC,  KC_LALT,  KC_ENT
//#define _____________________WARHAMMER_TM_L2_____________________ KC_LCTRL, OSL(_NAVIGATION)

//#define _____________________WARHAMMER_RT1_____________________ KC_T,    TD(TD_7),    TD(TD_8),    TD(TD_9),    KC_O,    KC_P
//#define _____________________WARHAMMER_RT2_____________________ KC_G,    TD(TD_4),    TD(TD_5),    TD(TD_6),    TD(TD_0), KC_SCLN
//#define _____________________WARHAMMER_RT3_____________________ KC_B,    TD(TD_1),    TD(TD_2),    TD(TD_3),  KC_DOT, KC_SLASH
//#define _____________________WARHAMMER_TMB_R_____________________ KC_KP_5,  KC_KP_2,  KC_TAB,  KC_F17,  TO(_GAMING)
//#define _____________________WARHAMMER_TM_R2_____________________ KC_F10,  KC_F12

#define _____________________QWERTY_L1______________________ KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T
#define _____________________QWERTY_L2______________________ KC_DEL, KC_A, KC_S, KC_D, KC_F, KC_G
#define _____________________QWERTY_L3______________________ KC_LALT, CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B

#define _____________________QWERTY_R1______________________ KC_Y, KC_U, KC_I, KC_O, KC_P, KC_NONUS_BSLASH
#define _____________________QWERTY_R2______________________ KC_H, KC_J, KC_K, KC_L, KC_SCLN, CMD_T(KC_QUOTE)
#define _____________________QWERTY_R3______________________ KC_N, KC_M, KC_COMM, KC_DOT, CTL_T(KC_SLASH), OSL(_SHORTCUT)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)