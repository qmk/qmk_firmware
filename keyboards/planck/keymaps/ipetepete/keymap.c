#include QMK_KEYBOARD_H
//#include "muse.h"
#include "version.h"


#define KC_SPFN LT(_SPCFN, KC_SPC) // press for space, hold for function layer (aka spacefn)
#define KC_BKFN LT(_SPCFN, KC_BSPC)
// use tap dancing to set caps lock
#define HYPER RCTL(RALT(RSFT(KC_RGUI)))
#define KC_TABM LT(_MOUS, KC_TAB)
#define SPCRGT LCTL(KC_RGHT)
#define SPCLFT LCTL(KC_LEFT)
#define ENTSFT SFT_T(KC_ENT)
#define CTLESC RCTL_T(KC_ESC) //CTL_T(KC_ESC)
#define VOLUP  S(LALT(KC_VOLU))
#define VOLDN  S(LALT(KC_VOLD))
#define POWER S(LCTL(KC_POWER))
#define FUN MO(_FUNC)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

enum layers {
_QWERTY,
_COLEMAK,
_GAMR,
_GAMEUP,
_LOWER,
_RAISE,
_ADJUST,
_FUNC,
_MOUS,
_SPCFN
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  GAMR,
  GAMEUP,
  BELOW,
  ABOVE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  {KC_TABM, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {CTLESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ENTSFT },
  {FUN, KC_LALT, KC_LGUI, KC_LCTL,    LOWER,  KC_BKFN,  KC_SPFN,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, HYPER}
},
[_GAMR] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {CTLESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ENTSFT },
  {GAMEUP,  KC_LALT, KC_LGUI, KC_LCTL, LOWER,  KC_SPC, KC_SPC,   RAISE,   KC_RGUI, KC_RALT, KC_RCTL,  FUN}
},
[_COLEMAK] = {
  {KC_TABM, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
  {CTLESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ENTSFT },
  {FUN, KC_LALT, KC_LGUI, KC_LCTL, LOWER,   KC_BKFN,  KC_SPFN,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, HYPER}
},
[_GAMEUP] = {
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______, _______, _______, _______},
    {_______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, _______, _______, _______},
    {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, _______, _______, _______},
    {_______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, _______, _______, _______},
},
[_LOWER] = {
  {_______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_BSPC},
  {_______,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
  {_______, _______, KC_LCBR, KC_LBRC, KC_LPRN, KC_PIPE, KC_BSLS, KC_LPRN, KC_LBRC, KC_LCBR, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_RAISE] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_BSPC},
  {KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_ADJUST] = {
  {RESET  , QWERTY, COLEMAK,  GAMR, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______,   _______,  _______,  _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
},

[_FUNC] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11, KC_F12 },
  {KC_F13,  KC_F14,  KC_F15, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
  {_______, KC_LSFT, _______, POWER , KC_MPRV, KC_MPLY, KC_MPLY, KC_MNXT, HYPER , _______, _______, RESET }
},
[_SPCFN] = {
  {KC_TILD, _______, KC_HOME, KC_PGUP, KC_END , KC_LBRC, KC_RBRC, _______, KC_UP  , _______, KC_PGUP, KC_DEL  },
  {KC_GRV,  _______, SPCLFT , KC_PGDN, SPCRGT , KC_LCBR, KC_RCBR, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______ },
  {_______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_TOGG, BL_STEP }
},
/* Mouse layer */
[_MOUS] = {
  {_______, KC_ACL2, KC_ACL1, KC_ACL0,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX },
  {_______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX },
  {XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
  {XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_BTN1, _______, _______, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX }
}
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    switch(keycode){
      // Flip RGB mode on game/qwerty mode
      case QWERTY:
        if(record->event.pressed){
#ifdef BACKLIGHT_BREATHING
            breathing_disable();
#endif
        set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;
     case COLEMAK:
        if(record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
        }
        return false;
        break;
     case GAMR:
        if(record->event.pressed) {
#ifdef BACKLIGHT_BREATHING
          breathing_period_set(3);
          breathing_enable();
#endif
        set_single_persistent_default_layer(_GAMR);
        }
        return false;
        break;
      case LOWER:
        if (record->event.pressed) {
          layer_on(_LOWER);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
          layer_off(_LOWER);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
      case RAISE:
        if (record->event.pressed) {
          layer_on(_RAISE);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
          layer_off(_RAISE);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    }
    return true;
}
