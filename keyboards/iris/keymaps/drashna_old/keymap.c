
#include QMK_KEYBOARD_H
#include "drashna.h"

#define KC_ALAP ALT_T(KC_APP)
#define KC_OSLG OSM(MOD_LGUI)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_wrapper(
     KC_ESC,  ________________NUMBER_LEFT________________,                       ________________NUMBER_RIGHT_______________, KC_MINS,
     KC_TAB , _________________QWERTY_L1_________________,                       _________________QWERTY_R1_________________, KC_BSLS,
     KC_CCCV, _________________QWERTY_L2_________________,                       _________________QWERTY_R2_________________, KC_QUOT,
     KC_MLSF, _________________QWERTY_L3_________________, KC_ALAP,     KC_OSLG, _________________QWERTY_R3_________________, KC_MRSF,
                             LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),
  [_COLEMAK] = LAYOUT_wrapper(
     KC_ESC , ________________NUMBER_LEFT________________,                       ________________NUMBER_RIGHT_______________, KC_MINS,
     KC_TAB , _________________COLEMAK_L1________________,                       _________________COLEMAK_R1________________, KC_BSLS,
     KC_CCCV, _________________COLEMAK_L2________________,                       _________________COLEMAK_R2________________, KC_QUOT,
     KC_MLSF, _________________COLEMAK_L3________________, KC_ALAP,     KC_OSLG, _________________COLEMAK_R3________________, KC_MRSF,
                             LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),
  [_DVORAK] = LAYOUT_wrapper(
     KC_ESC,  ________________NUMBER_LEFT________________,                       ________________NUMBER_RIGHT_______________, KC_MINS,
     KC_TAB , _________________DVORAK_L1_________________,                       _________________DVORAK_R1_________________, KC_BSLS,
     KC_CCCV, _________________DVORAK_L2_________________,                       _________________DVORAK_R2_________________, KC_QUOT,
     KC_MLSF, _________________DVORAK_L3_________________, KC_ALAP,     KC_OSLG, _________________DVORAK_R3_________________, KC_MRSF,
                             LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),
  [_WORKMAN] = LAYOUT_wrapper(
     KC_ESC,  ________________NUMBER_LEFT________________,                       ________________NUMBER_RIGHT_______________, KC_MINS,
     KC_TAB , _________________WORKMAN_L1________________,                       _________________WORKMAN_R1________________, KC_BSLS,
     KC_CCCV, _________________WORKMAN_L2________________,                       _________________WORKMAN_R2________________, KC_QUOT,
     KC_MLSF, _________________WORKMAN_L3________________, KC_ALAP,     KC_OSLG, _________________WORKMAN_R3________________, KC_MRSF,
                             LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),

  [_MODS] = LAYOUT_wrapper(
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     KC_LSFT, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, KC_RSFT,
                                       _______, _______, _______,         _______, _______, _______
  ),


  [_LOWER] = LAYOUT_wrapper(
     _______, _________________FUNC_LEFT_________________,                       _________________FUNC_RIGHT________________, _______,
     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
     _______, _______, _______, _______, _______, _______,                       _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
     _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
                                       _______, _______, _______,         _______, _______, _______
  ),

  [_RAISE] = LAYOUT_wrapper(
      _______, _________________FUNC_LEFT_________________,                      _________________FUNC_RIGHT________________, _______,
      KC_GRV,  ________________NUMBER_LEFT________________,                      ________________NUMBER_RIGHT_______________, _______,
      _______, _______, _______, _______, _______, _______,                      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
      _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
                                        _______, _______, _______,        _______, _______, _______
   ),

  [_ADJUST] = LAYOUT_wrapper(
      KC_MAKE, _______, _______, _______, _______, _______,                      KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5, KC_RST,
      VRSN,    RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG,                      KC_NUKE, _______, _______, _______, _______, EPRM,
      _______, _______, CK_TOGG, AU_ON,   AU_OFF,  AG_NORM,                      AG_SWAP, QWERTY,  COLEMAK, DVORAK,  WORKMAN, TG(_MODS),
      _______, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD, KC_RGB_T,_______,    _______, MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY,
                                        _______, _______, _______,        _______, _______, _______
   )

};


bool indicator_is_this_led_used(uint8_t index) {
  switch (index) {
#ifdef INDICATOR_LIGHTS
    case SHFT_LED1:
    case SHFT_LED2:
    case CTRL_LED1:
    case CTRL_LED2:
    case GUI_LED1:
    case GUI_LED2:
      return true;
      break;
#endif
    default:
    return false;
  }
}
