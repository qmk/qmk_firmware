#pragma once

enum crkbd_layers {
  _BASE,
  _GAMING,
  _GAMING2,
  _ACCENTS,
  _LOWER,
  _RAISE,
  _FUN,
  _NAV,
  _MOUSE,
  _ADJUST
};

#define CTRLSC LCTL_T(KC_ESC)
#define QUORCTL RCTL_T(KC_QUOT)
#define MOSCLN LT(_MOUSE,KC_SCLN)
#define ACCENTS LT(_ACCENTS,KC_RALT)
#define FUN LT(_FUN,KC_SPC)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SPCNAV LT(_NAV,KC_SPC)
#define SFTENT MT(MOD_RSFT,KC_ENT)
#define TABLGUI LGUI_T(KC_TAB)
#define BASE DF(_BASE)
#define GAMING DF(_GAMING)
#define GAMING2 MO(_GAMING2)

#define SC_F1 LSFT(LCTL(KC_F1))
#define SC_F2 LSFT(LCTL(KC_F2))
#define SC_F3 LSFT(LCTL(KC_F3))
#define SC_F4 LSFT(LCTL(KC_F4))
