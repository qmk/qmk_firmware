#pragma once

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  CP_PSTE,
  ALT_TAB,
  CTLS,
  MAKE,
  UNIT,
  UNIT2,
  UNIT3,
  UNIT4
};

#define SFA SFT_T(KC_A)
#define SFCLN RSFT_T(KC_SCLN)
#define CTLSLH RCTL_T(KC_SLSH)
#define SFEXM MT(MOD_LSFT, KC_F23)
#define SFPRN MT(MOD_RSFT, KC_F24)
#define CTLESC CTL_T(KC_ESC)
#define CTLTZ CTL_T(KC_Z)
#define CTLNXT RCTL_T(KC_MNXT)
#define GPSCR G(KC_PSCR)
