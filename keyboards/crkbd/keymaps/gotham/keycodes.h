#pragma once

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes { QWERTY = SAFE_RANGE, LOWER, RAISE, ADJUST, RGBRST };

#define SFT_EQ MT(MOD_LSFT, KC_EQL)
#define SFT_QT MT(MOD_RSFT, KC_QUOT)

#define SFT_A MT(MOD_LSFT, KC_A)
#define CTL_Z MT(MOD_LCTL, KC_Z)

#define SFT_SCLN MT(MOD_RSFT, KC_SCLN)
#define CTL_SLSH MT(MOD_RCTL, KC_SLSH)

#define LOW_SPC LT(_LOWER, KC_SPC)
#define RAI_EQ LT(_RAISE, KC_EQL)
#define RAI_ENT LT(_RAISE, KC_ENT)
#define LOW_BSP LT(_LOWER, KC_BSPC)
#define LOW_DEL LT(_LOWER, KC_DEL)
#define ADJ_GRV LT(_ADJUST, KC_GRV)
#define KC_ANGL LSFT(KC_COMM)
#define KC_ANGR LSFT(KC_DOT)
