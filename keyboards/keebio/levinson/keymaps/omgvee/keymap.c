#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _FN3 5
#define _FN4 6
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  FN3,
  FN4,
  ADJUST,
};

#define KC_ KC_TRNS

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_X0 MT(MOD_LCTL, KC_ESC)
#define KC_SCAP SFT_T(KC_CAPS)
#define KC_LOW LOWER
#define KC_RAIS RAISE
#define KC_X3 LT(_FN3, KC_GRV)
#define KC_SENT MT(MOD_LSFT, KC_ENT)
#define KC_X5 BL_STEP
#define KC_CTB CTL_T(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     GESC, Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     SCAP, A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      CTB, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,SENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X3 ,LCTL,LALT,LGUI,LOW ,ENT ,      SPC,RAIS,RALT,    ,    ,    
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     SCAP, NO ,HOME,PGDN,PGUP, END,     LEFT,DOWN, UP ,RGHT, INS, DEL,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     CTB , F1 , F2 , F3 , F4 , F5 ,      F6,  F7 , F8 , F9 , F10, F11,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X3 ,LCTL,LALT,LGUI, LOW, ENT,      SPC,RAIS,RALT,    ,    , F12
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB, EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN, DEL,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     SCAP,    ,    ,    ,    ,    ,     MINS, EQL,    ,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      CTB,    ,    ,    ,    ,    ,     UNDS,PLUS,VOLD,VOLU,MUTE,SENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X3 ,LCTL,LALT,LGUI, LOW, ENT,      SPC,RAIS,RALT,    ,    , NO
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     GESC, Q  , W  , F  , P  , G  ,      J  , L  , U  , Y  ,SCLN,MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     SCAP, A  , R  , S  , T  , D  ,      H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      CTB, Z  , X  , C  , V  , B  ,      K  , M  ,COMM,DOT ,SLSH,SENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X3 ,LCTL,LALT,LGUI, LOW, ENT,      SPC,RAIS,RALT,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_DVORAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.  
     TAB ,QUOT,COMM,DOT , P  , Y  ,      F  , G  , C  , R  , L  ,MINS, 
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X0 , A  , O  , E  , U  , I  ,      D  , H  , T  , N  , S  ,SLSH,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT,SCLN, Q  , J  , K  , X  ,      B  , M  , W  , V  , Z  ,SENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X3 ,LCTL,LALT,LGUI, LOW, ENT,      SPC,RAIS,RALT,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_FN3] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,     MS_L,MS_D,MS_U,MS_R,WH_L,WH_R,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,     BTN1,WH_D,WH_U,BTN2,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|Sat Up|Sat Dn|Val Up|Val Dn|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT( \
      RESET,  QWERTY, COLEMAK,  DVORAK, _______, EEP_RST,   KC_MNXT, KC_MPRV, KC_MFFD, KC_MRWD,  DVORAK, KC_EJCT, \
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_PGUP, KC_HOME,   KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   CK_UP, CK_DOWN, \
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_PGDN,  KC_END,   KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, \
    BL_TOGG,  BL_INC,  BL_DEC, BL_BRTG, _______, _______,    CK_RST, _______, CK_TOGG,  MU_MOD,  MU_TOG,  AU_TOG \
  )


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
         set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
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
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
