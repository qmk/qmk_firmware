#include "quantum.h"

#define KC_ KC_TRNS
#define KC_XXX KC_NO

#define KC_CESC CTRLESC

#define KC__FN1 MO(_FN1)
#define KC__FN2 MO(_FN2)
#define KC__CFG MO(_CFG)
#define KC_FNUM MO(_NUM)
#define KC__TGN TG(_NUM)
#define KC__TGM TG(_GAME)

#define KC_SFN1 SPCFN1
#define KC_BFN2 BKSFN2
#define KC_EFN2 LT(_FN2, KC_ENTER)
#define KC_ALBS LALT_T(KC_BSPC)

#define KC__RST RESET
#define KC_MISS MISCTRL
#define KC__VUP KC__VOLUP
#define KC__VDN KC__VOLDOWN

#define KC_ENTS LSFT(KC_ENTER)

#define KC__WN LCMD(KC_GRV)
#define KC__STP LCMD(KC_UP)
#define KC__SBT LCMD(KC_DOWN)
#define KC__BCK LCMD(KC_LBRC)
#define KC__FWD LCMD(KC_RBRC)
#define KC__TAN LCMD(KC_RCBR)
#define KC__TAP LCMD(KC_LCBR)

#define KC__WL LALT(KC_LEFT)
#define KC__WR LALT(KC_RIGHT)

#ifdef RGBLIGHT_ENABLE
#    define KC_RVAD RGB_VAD
#    define KC_RVAI RGB_VAI
#    define KC_RTOG RGB_TOG
#    define KC_RMOD RGB_MOD
#    define KC_RHUI RGB_HUI
#    define KC_RHUD RGB_HUD
#    define KC_RSAI RGB_SAI
#    define KC_RSAD RGB_SAD
#else
#    define KC_RVAD KC_NO
#    define KC_RVAI KC_NO
#    define KC_RTOG KC_NO
#    define KC_RMOD KC_NO
#    define KC_RHUI KC_NO
#    define KC_RHUD KC_NO
#    define KC_RSAI KC_NO
#    define KC_RSAD KC_NO
#endif
