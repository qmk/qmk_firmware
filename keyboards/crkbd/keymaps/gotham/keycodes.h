#pragma once

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST
};


#define KC________ KC_TRNS
#define KC____X___ KC_NO
#define KC_RESET RESET

#define KC_SFEQ MT(MOD_LSFT, KC_EQL)
#define KC_SFQT MT(MOD_RSFT, KC_QUOT)

#define KC_SFTA MT(MOD_LSFT, KC_A)
#define KC_CTLZ MT(MOD_LCTL, KC_Z)

#define KC_SFTSCLN MT(MOD_RSFT, KC_SCLN)
#define KC_CTLSLSH MT(MOD_RCTL, KC_SLSH)


#define KC_LWSP LT(_LOWER, KC_SPC)
#define KC_RSEQ LT(_RAISE, KC_EQL)
#define KC_RSENT LT(_RAISE, KC_ENT)
#define KC_LWBSP LT(_LOWER, KC_BSPC)
#define KC_LWDEL LT(_LOWER, KC_DEL)
#define KC_ADGRV LT(_ADJUST, KC_GRV)
#define KC_ANGL LSFT(KC_COMM)
#define KC_ANGR LSFT(KC_DOT)

#define KC_CK_RST CK_RST
#define KC_CK_DOWN CK_DOWN
#define KC_CK_UP CK_UP
#define KC_CK_TOGG CK_TOGG

#define KC_RGB_TOG RGB_TOG
#define KC_RGB_HUI RGB_HUI
#define KC_RGB_HUD RGB_HUD
#define KC_RGB_SAI RGB_SAI
#define KC_RGB_SAD RGB_SAD
#define KC_RGB_VAI RGB_VAI
#define KC_RGB_VAD RGB_VAD
#define KC_RGB_SPI RGB_SPI
#define KC_RGB_SPD RGB_SPD
#define KC_RGB_MOD RGB_MOD
#define KC_RGBRST RGBRST

#define KC_MU_TOG MU_TOG
#define KC_MU_MOD MU_MOD

#define KC_AU_TOG AU_TOG
