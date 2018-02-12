#include "../../core.h"
#include "../../config.h"

#define KEYMAPS const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]

enum layers { _MA, _FN, _FN1, _FN2, _PN };
#define FN_LEFT LT(_FN, KC_LEFT)
#define KC_FN_LEFT FN_LEFT

#define FN2 TT(_FN2)
#define KC_FN2 FN2

#define PN TT(_PN)
#define KC_PN PN

#define SPC_FN LT(_FN, KC_SPC)
#define KC_SPC_FN SPC_FN

#define SPC_FN1 LT(_FN1, KC_SPC)
#define KC_SPC_FN1 SPC_FN1

#define RCTL_GRV MT(MOD_RCTL, KC_GRV)
#define KC_RCTL_GRV RCTL_GRV

#define GUI_TAB GUI_T(KC_TAB)
#define KC_GUI_TAB GUI_TAB

#define RSHFT_QUOT MT(MOD_RSFT, KC_QUOT)
#define KC_RSHFT_QUOT RSHFT_QUOT

#define LSHFT_SLSH MT(MOD_LSFT, KC_SLSH)
#define KC_LSHFT_SLSH LSHFT_SLSH

#define KC_BACKSPACE KC_BSPC

#define _______ KC_TRNS
#define KC________ _______

//  Visual Studio
#define VS_ADD_CLASS LALT(LSFT(KC_C))

enum custom_keycodes {
  _CKC_START = SAFE_RANGE,

  EMAIL,
  CMD,
  UBUNTU,
  VS_PROP,
  PASTEX,

  _CKC_END
};
