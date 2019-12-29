#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include "tominabox1.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Base layer mod tap
#define KC_A_CT  LCTL_T(KC_A)
#define KC_Z_SF  LSFT_T(KC_Z)
#define KC_C_AL  LALT_T(KC_C)
#define KC_K_GU  LGUI_T(KC_K)
#define KC_ENSF  LSFT_T(KC_ENT)

// Layer tap
#define KC_ENLO  LT(_LOWER, KC_ENT)
#define KC_SPRA  LT(_RAISE, KC_SPC)
#define KC_FDOT  LT(_FKEY, KC_DOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
  TD(TD_Q_ESC),     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,  KC_QUOT, //Y+QUOTE = KC_BSPC
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
  LCTL_T(KC_A),     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I, TD(TD_O_BSLS),
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
  LSFT_T(KC_Z),     KC_X,  KC_C_AL,     KC_V,     KC_B,  KC_K_GU, LT(_LOWER,KC_M),  KC_COMM,  KC_FDOT, TD(TD_QUES_ENT),
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               KC_LALT,  KC_SPRA
  //                                        `---------|---------'
  ),

  [_RAISE] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
          KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0, //0 + 9 = KC_BSPC
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,   KC_EQL,  KC_MINS,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_DEL ,  KC_BSLS,  KC_LCBR,  KC_LBRC,  KC_LPRN,  KC_UNDS,  KC_RPRN,  KC_RBRC,  KC_RCBR,  KC_DOT ,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               KC_TRNS,  KC_TRNS
  //                                        `---------|---------'
  ),

  [_LOWER] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
        KC_ESC,   RGBRST,  AG_NORM,  AG_SWAP,  XXXXXXX,  KC_PGDN,    KC_UP,  KC_PGUP,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_RGHT,   KC_END,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  KC_MINS,    KC_RO,  KC_COMM,   KC_DOT,  KC_SLSH,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               KC_TRNS,  KC_TRNS
  //                                        `---------|---------'
  ),

  [_FKEY] = LAYOUT(
  //,---------------------------------------------------------------------------------------------------.
         KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_GRV,  KC_TILD,  KC_HASH,   KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,   KC_EQL,  KC_MINS,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_DEL ,  KC_BSLS,  KC_LCBR,  KC_LBRC,  KC_LPRN,  KC_UNDS,  KC_RPRN,  KC_RBRC,  KC_RCBR, KC_TRNS ,
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               KC_TRNS,  KC_TRNS
  //                                        `---------|---------'
  )

};

int RGB_current_mode;
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    case KC_LSFT && KC_DOT:
        tap_code16(KC_QUES);
    default:
      result = true;
      break;
  }

  return result;
}

void keyboard_post_init_keymap(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}
