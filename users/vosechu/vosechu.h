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
  MOUSE,
  TT1,
  TT2,
  TT3,
  T23X
};
#define BASE DV

enum userspace_custom_keycodes {
  PAWFIVE = SAFE_RANGE,
  MOUKEY,
  MS_BTN1,
  MS_BTN2,
  MS_BTN3
};

// Transparent macro to indicate that this spot is already being pressed
// to activate this layer
#define _LAYER_ KC_TRNS

// == Dual-action keys on most of the modifiers
#define CTL_ESC CTL_T(KC_ESC)
#define CTL_GRV CTL_T(KC_GRV)
#define ALT_TAB ALT_T(KC_TAB)
#define SFT_SPC SFT_T(KC_SPC)

// == Macro keys for commonly used apps
// -- Slack
// Move one conversation up/down
#define SLACKTB LGUI(LSFT(KC_T))
#define SLACKUP LALT(LSFT(KC_UP))
#define SLACKDN LALT(LSFT(KC_DOWN))

// -- 1password
#define PSWD LCTL(KC_BSLS)
#define PSWD_ALT LCTL(LALT(KC_BSLS))

// -- Browser and OS X
// Activate one tab left/right
#define TAB_LFT LGUI(LSFT(KC_LBRC))
#define TAB_RGT LGUI(LSFT(KC_RBRC))
// Go back/forward in history
#define BWSR_BK LGUI(KC_LBRC)
#define BWSR_FW LGUI(KC_RBRC)

// -- Screen management
// Make window fill the left/right side
#define SCR_LFT HYPR(KC_LEFT)
#define SCR_RGT HYPR(KC_RGHT)
// Make window fill the whole monitor
#define SCR_FUL HYPR(KC_F)

// -- Windows variants of browser commanads
// Activate one tab left/right
#define WTABLFT LCTL(LSFT(KC_TAB))
#define WTABRGT LCTL(KC_TAB)
// Go back/forward in history
#define WBWSRBK LALT(KC_LEFT)
#define WBWSRFW LALT(KC_RGHT)

// == Extended alpha layer toggles
// -- Dvorak
// Pressing U opens up the LWR layer (numpad)
#define LWR_U    LT(LWR,  KC_U)
// Pressing H opens up the RSE layer (brackets/parens)
#define RSE_H    LT(RSE,  KC_H)

// -- Qwerty
// Pressing F opens up the LWR layer (numpad)
#define LWR_F    LT(LWR,  KC_F)
// Pressing J opens up the RSE layer (brackets/parens)
#define RSE_J    LT(RSE,  KC_J)

// -- LFT layer (Works on both Qwerty and Dvorak)
// Pressing Back space or Enter opens up the LFT layer (media/navigation)
#define LFT_BK   LT(LFT,  KC_BSPC)
#define LFT_ENT  LT(LFT,  KC_ENT)
