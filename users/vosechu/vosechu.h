#pragma once

#include "quantum.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
enum userspace_custom_layers {
  DV = 0,
  QW,
  GAM1,
  RSE,
  LWR,
  LFT,
  MOUSE
};

enum userspace_custom_keycodes {
  PAWFIVE = SAFE_RANGE,
  MOUKEY,
  MS_BTN1,
  MS_BTN2,
  MS_BTN3
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define _LAYER_ KC_TRNS
#define XXXXXXX KC_NO

// Adding macros to make the keymaps below much easier to read.
#define CTLESC CTL_T(KC_ESC)
#define CTLGRV CTL_T(KC_GRV)
#define ALTTAB ALT_T(KC_TAB)
#define SFTSPC SFT_T(KC_SPC)

// Macro keys for some apps
#define SLACKUP LALT(LSFT(KC_UP))
#define SLACKDN LALT(LSFT(KC_DOWN))
#define TABLEFT LGUI(LSFT(KC_LBRC))
#define TABRIGT LGUI(LSFT(KC_RBRC))
#define HISTBAK LGUI(KC_LBRC)
#define HISTFWD LGUI(KC_RBRC)
#define SCRLEFT HYPR(KC_LEFT)
#define SCRRIGT HYPR(KC_RGHT)
#define SCRFULL HYPR(KC_F)

// Extended alpha key layers for Dvorak
#define LWR_U    LT(LWR,  KC_U)
#define RSE_H    LT(RSE,  KC_H)
#define LWR_F    LT(LWR,  KC_F)
#define RSE_J    LT(RSE,  KC_J)
#define LFT_BK   LT(LFT,  KC_BSPC)
#define LFT_ENT  LT(LFT,  KC_ENT)
