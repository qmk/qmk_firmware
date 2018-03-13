#include "bananasplit.h"
#include "talljoe.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = KM_(
      KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSLS, KC_GRV,
      KC_TAB , _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_LBRC, KC_RBRC, KC_BSPC,
      US_CAPS, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, US_QUOT,          KC_ENT ,
      KC_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________,          KC_RSFT, AD_GRV ,
      _________MODS_L__________,                KC_SPC1, KC_SPC2, KC_SPC3,                      ______________MODS_R______________),
  [_WORKMAN] = KM_(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _________________WORKMAN_L1________________, _________________WORKMAN_R1________________, _______, _______, _______,
      _______, _________________WORKMAN_L2________________, _________________WORKMAN_R2________________, _______,          _______,
      _______, _________________WORKMAN_L3________________, _________________WORKMAN_R3________________,          _______, _______,
      _______, _______, _______,                _______, _______, _______,                      _______, _______, _______, _______),
  [_NORMAN] = KM_(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _________________NORMAN_L1_________________, _________________NORMAN_R1_________________, _______, _______, _______,
      _______, _________________NORMAN_L2_________________, _________________NORMAN_R2_________________, _______,          _______,
      _______, _________________NORMAN_L3_________________, _________________NORMAN_R3_________________,          _______, _______,
      _______, _______, _______,                _______, _______, _______,                      _______, _______, _______, _______),
  [_DVORAK] = KM_(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______,
      _______, _________________DVORAK_L1_________________, _________________DVORAK_R1_________________, KC_SLSH, KC_EQL , _______,
      _______, _________________DVORAK_L2_________________, _________________DVORAK_R2_________________, US_MINS,          _______,
      _______, _________________DVORAK_L3_________________, _________________DVORAK_R3_________________,          _______, _______,
      _______, _______, _______,                _______, _______, _______,                      _______, _______, _______, _______),
  [_COLMAK] = KM_(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, _______, _______, _______,
      _______, _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, _______,          _______,
      _______, _________________COLEMAK_L3________________, _________________COLEMAK_R3________________,          _______, _______,
      _______, _______, _______,                _______, _______, _______,                      _______, _______, _______, _______),
  [_GAME] = KM_(
      KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSLS, KC_GRV,
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSPC,
      MO_NAV , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT, MO_ADJ ,
      KC_LCTL, KC_PTT , KC_PGDN,                KC_SPC , KC_SPC , KC_SPC ,                      KC_RALT, KC_RGUI, KC_RCTL, KC_PTT ),
  [_NAV] = KM_(
      KC_GRV , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_TAB , ________________NAVLAYER_L1________________, ________________NAVLAYER_R1________________, XXXXXXX, XXXXXXX, KC_DEL ,
      US_CAPS, ________________NAVLAYER_L2________________, ________________NAVLAYER_R2________________, XXXXXXX,          TG_ADJ ,
      KC_LSFT, ________________NAVLAYER_L3________________, ________________NAVLAYER_R3________________,          KC_RSFT, XXXXXXX,
      _________MODS_L__________,                NV_SPC1, NV_SPC2, NV_SPC3,                      ______________MODS_R______________),
  // Adjust layer is on the split-shift key; or NAV+Enter (for non-split keyboards)
  [_ADJUST] = KM_(
      MO_RST , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, ________________ADJLAYER_L1________________, ________________ADJLAYER_R1________________, XXXXXXX, XXXXXXX, KC_DEL ,
      XXXXXXX, ________________ADJLAYER_L2________________, ________________ADJLAYER_R2________________, XXXXXXX,          TG_ADJ ,
      TG_NKRO, ________________ADJLAYER_L3________________, ________________ADJLAYER_R3________________,          KC_RSFT, XXXXXXX,
      MO_RST , AG_NORM, AG_SWAP,                XXXXXXX, BL_TOGG, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS),
  // To Reset hit FN + ` + Esc
  [_RESET] = KM_(
      RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
      RESET  , XXXXXXX, XXXXXXX,                XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
};
