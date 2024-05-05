#pragma once

#include QMK_KEYBOARD_H
#include "features/achordion.h"
#include "features/compose.h"

enum userspace_layers {
    LCMK = 0,
    LSYM,
    LNUM,
    LFUN,
    LMOV,
    LGME,
#ifdef MOUSEKEY_ENABLE
    LMSE,
#endif
};

// rename some keys here to allow for the difference in keymap between US and GB
#define MY_PIPE LSFT(KC_NUBS)
#define MY_TILD KC_PIPE
#define MY_AT KC_DQUO
#define MY_DQUO LSFT(KC_2)
#define MY_GBP KC_HASH      // just shift-3
#define ALT_TAB ALT_T(KC_TAB)

// one shot mod and layer keys to make the map shorter
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_SFT OSM(MOD_LSFT)

#define SFT_BSP SFT_T(KC_BSPC)
#define CTL_SPC CTL_T(KC_SPC)

#define CTL_W CTL_T(KC_W)
#define CTL_Y CTL_T(KC_Y)
#define SFT_Z SFT_T(KC_Z)
#define SFT_SLS SFT_T(KC_SLSH)
#define MOV_SPC LT(LMOV, KC_SPC)
// keycodes to allow mod tap on ctrl+? and ctrl+@ - cannot use CTL_T(KC_QUES) as this is shifted
#define CTL_QUES LT(0, KC_1)
#define CTL_AT LT(0, KC_2)


enum custom_keycodes {
    MY_COMP = SAFE_RANGE,
};


