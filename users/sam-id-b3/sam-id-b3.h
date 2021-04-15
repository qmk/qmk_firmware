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
    _QWERTY = 0,
	_GAMING,
    _SHORTCUT,
    _SYMNUM,
	_NAVIGATION,
	_COLEMAK,
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

#define _____________________THUMBS_LF1_____________________ RGB_TOG, KC_LEFT, KC_BSPC, TD(TD_TABC), OSL(_SYMNUM)
#define _____________________THUMBS_LF2_____________________ C(KC_BSPC), OSL(_NAVIGATION)

#define _____________________THUMBS_RG1_____________________ KC_UP, LT(_SYMNUM, KC_ENT), MT(MOD_LSFT, KC_SPC), KC_RIGHT, TO(_GAMING)
#define _____________________THUMBS_RG2_____________________ KC_DOWN, OSM(MOD_LSFT)

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

#define _____________________SYMNUM_LF1_____________________ KC_LPRN, KC_RPRN, S(KC_2),_______, _______, A(KC_F4)
#define _____________________SYMNUM_LF2_____________________ TD(TD_PCAS), TD(TD_EXLM), KC_MINS, KC_EQL,  KC_NUHS, _______ 
#define _____________________SYMNUM_LF3_____________________ KC_LBRC, KC_RBRC ,_______, _______, _______, RESET 

#define _____________________SYMNUM_RT1_____________________ RESET, _______, KC_7, KC_8, KC_9, TD(TD_ASDI)
#define _____________________SYMNUM_RT2_____________________ _______, _______, KC_4, KC_5, KC_6, TD(TD_PLMN)
#define _____________________SYMNUM_RT3_____________________ _______,  KC_DOT, KC_1, KC_2, KC_3, _______

#define _____________________GAMING_LF1_____________________ KC_ESC, KC_O,    KC_I,    KC_U,    KC_Y,    KC_T
#define _____________________GAMING_LF2_____________________ KC_SCLN, KC_L,  KC_K,    KC_J,    KC_H,    KC_G
#define _____________________GAMING_LF3_____________________ A(KC_TAB), KC_DOT,KC_COMM,    KC_M,    KC_N,    KC_B
#define _____________________GAME_TMB_L_____________________ A(KC_TAB),  KC_F9, KC_F5,  KC_4,  KC_5
#define _____________________GAME_TM_L2_____________________ KC_6, KC_7

#define _____________________GAMING_RT1_____________________ KC_R,    KC_E,    KC_W,    KC_Q,    KC_I,    KC_1
#define _____________________GAMING_RT2_____________________ KC_F,    KC_A,    KC_S,    KC_D,    KC_LSFT, KC_2
#define _____________________GAMING_RT3_____________________ KC_V,    KC_C,    KC_X, KC_Z,  KC_LCTRL, KC_3
#define _____________________GAME_TMB_R_____________________ KC_TAB,  KC_ENT,  KC_SPC,  KC_M, TO(_QWERTY)
#define _____________________GAME_TM_R2_____________________ KC_0,  KC_LALT

#define _____________________QWERTY_L1______________________ KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T
#define _____________________QWERTY_L2______________________ KC_DEL, KC_A, KC_S, KC_D, KC_F, KC_G
#define _____________________QWERTY_L3______________________ KC_LALT, CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B

#define _____________________QWERTY_R1______________________ KC_Y, KC_U, KC_I, KC_O, KC_P, KC_NONUS_BSLASH
#define _____________________QWERTY_R2______________________ KC_H, KC_J, KC_K, KC_L, KC_SCLN, CMD_T(KC_QUOTE)
#define _____________________QWERTY_R3______________________ KC_N, KC_M, KC_COMM, KC_DOT, CTL_T(KC_SLASH), OSL(_SHORTCUT)

#define _____________________NAVIGT_L1______________________ _______, KC_HOME,   KC_UP,  KC_END, KC_PGUP, _______
#define _____________________NAVIGT_L2______________________ _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______
#define _____________________NAVIGT_L3______________________ _______, C(KC_MINS), C(KC_EQL), _______, _______, _______

#define _____________________NAVIGT_R1______________________ KC_CAPS, _______, KC_F7,   KC_F8,   KC_F9,  KC_F10
#define _____________________NAVIGT_R2______________________ KC_SLCK, _______, KC_F4,   KC_F5,   KC_F6,  KC_F11
#define _____________________NAVIGT_R3______________________ KC_NLCK, _______, KC_F1,   KC_F2,   KC_F3,  KC_F12

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)