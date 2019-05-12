#include QMK_KEYBOARD_H

#define DYNAMIC_MACRO_SIZE 64
#define DYNAMIC_MACRO_RANGE SAFE_RANGE
#include "dynamic_macro.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_dynamic_macro(keycode, record);
}

enum macro_keycodes {
  KC_M_FIND,
  KC_M_AGAIN,
  KC_M_UNDO,
  KC_M_CUT,
  KC_M_COPY,
  KC_M_PASTE,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    bool use_cmd = true;
    if(keymap_config.swap_lalt_lgui == 1) {
      use_cmd = false;
    }

    switch (id) {
      case KC_M_FIND:
        return use_cmd ? MACRODOWN( D(LGUI), T(F), END ) : MACRODOWN( D(LCTRL), T(F), END );
      case KC_M_AGAIN:
        return use_cmd ? MACRODOWN( D(LGUI), T(G), END ) : MACRODOWN( D(LCTRL), T(G), END );
      case KC_M_UNDO:
        return use_cmd ? MACRODOWN( D(LGUI), T(Z), END ) : MACRODOWN( D(LCTRL), T(Z), END );
      case KC_M_CUT:
        return use_cmd ? MACRODOWN( D(LGUI), T(X), END ) : MACRODOWN( D(LCTRL), T(X), END );
      case KC_M_COPY:
        return use_cmd ? MACRODOWN( D(LGUI), T(C), END ) : MACRODOWN( D(LCTRL), T(C), END );
      case KC_M_PASTE:
        return use_cmd ? MACRODOWN( D(LGUI), T(V), END ) : MACRODOWN( D(LCTRL), T(V), END );
    }

    return MACRO_NONE;
}

/* Keymap */

#define LC_ESC  CTL_T(KC_ESC)
#define LC_END  LCTL_T(KC_END)
#define LC_PGDN LCTL_T(KC_PGDN)

#define LS_HOME LSFT_T(KC_HOME)
#define LS_PGUP LSFT_T(KC_PGUP)

#define RC_RGHT RCTL_T(KC_RGHT)

#define RA_DOWN RALT_T(KC_DOWN)

#define RS_UP   RSFT_T(KC_UP)

#define RG_LEFT RGUI_T(KC_LEFT)

#define RCAG_ENT MT(MOD_RGUI | MOD_RALT | MOD_RCTL, KC_ENT)

#define M_FIND  M(KC_M_FIND)
#define M_AGAIN M(KC_M_AGAIN)
#define M_UNDO  M(KC_M_UNDO)
#define M_CUT   M(KC_M_CUT)
#define M_COPY  M(KC_M_COPY)
#define M_PSTE  M(KC_M_PASTE)

#define M_RECD1 DYN_REC_START1
#define M_STOP1 DYN_REC_STOP
#define M_PLAY1 DYN_MACRO_PLAY1

enum keyboard_layers {
  _BL = 0,
  _FL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_aek_103(
    KC_GRV , KC_1   , KC_2   , KC_3  , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9    , KC_0   , KC_MINS, KC_EQL , KC_BSPC,
    KC_TAB , KC_Q   , KC_W   , KC_E  , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O    , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,
    LC_ESC , KC_A   , KC_S   , KC_D  , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L    , KC_SCLN, KC_QUOT, RCAG_ENT ,
    LS_PGUP, KC_Z   , KC_X   , KC_C  , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT  , KC_SLSH, RS_UP  ,
    LC_PGDN, KC_LALT, KC_LGUI,                       LT(_FL ,KC_SPC)                        , RG_LEFT, RA_DOWN, RC_RGHT
  ),
  [_FL] = LAYOUT_aek_103(
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_DEL ,
    _______, M_RECD1, M_STOP1, M_PLAY1, _______, _______, KC_MPLY, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, _______, RESET  ,
    M_UNDO , M_CUT  , M_COPY , M_PSTE , M_FIND , M_AGAIN, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, _______,
    LS_HOME, AG_SWAP, AG_NORM, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_BSLS, KC_PIPE,
    LC_END , _______, _______,                            _______                           , _______, _______, _______
  )
};
