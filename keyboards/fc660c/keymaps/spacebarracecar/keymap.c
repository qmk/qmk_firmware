#include QMK_KEYBOARD_H
#include "spacebarracecar.h"

enum layers {
  _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
        KC_ESC, DE_1,   DE_2,   CU_3,   DE_4,   DE_5,   CU_6,   CU_7,   CU_8,   CU_9,   CU_0,   DE_MINS,CU_EQL, KC_BSPC,     KC_INS,
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   CU_Z,   KC_U,   KC_I,   KC_O,   KC_P,   CU_LBRC,CU_RBRC,CU_BSLS,     KC_DEL,
        CU_NAV, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   CU_SCLN,CU_QUOT,     KC_ENT,
        CU_LSFT,CU_Y,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   CU_COMM,CU_DOT, CU_SLSH,CU_RSFT,     KC_UP,
        KC_LCTL,KC_LGUI,KC_LALT,          KC_SPC,                       KC_RALT,KC_RGUI,KC_RCTL,     KC_LEFT,KC_DOWN,KC_RGHT
    ),

  [_DEADKEY] = LAYOUT(
        CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  _______,     CU_ED,
        _______,CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_UE,  CU_ED,  CU_OE,  CU_ED,  CU_ED,  CU_ED,  CU_ED,       CU_ED,
        _______,CU_AE,  CU_SS,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_DDQ,      CU_DDQ ,
        _______,CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  CU_ED,  _______,     _______,
        _______,_______,_______,                CU_DDQ,                 _______,_______,_______,     _______,_______,_______
    ),

  [_NAV] = LAYOUT(
        CU_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_DEL,      CU_GAME,
        _______,KC_PGDN,KC_UP,  KC_PGUP,KC_HOME,XXXXXXX,XXXXXXX,XXXXXXX,GUIU,   XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,     CU_ESCT,
        _______,KC_LEFT,KC_DOWN,KC_RGHT,KC_END, XXXXXXX,XXXXXXX,GUIL,   GUID,   GUIR,   XXXXXXX,XXXXXXX,     KC_ENT,
        _______,KC_MPRV,KC_MPLY,KC_MNXT,KC_VOLD,KC_VOLU,KC_MUTE,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,     KC_PGUP,
        RESET,  _______,_______,                _______,                _______,_______,_______,     KC_HOME,KC_PGDN,KC_END
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_userspace(keycode, record);
}
