
// Default ECO Layout
// KLE here : http://www.keyboard-layout-editor.com/#/gists/0733eca6b4cb88ff9d7de746803f4039

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _FN3 3

enum eco_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS

#define KC_RST RESET
#define KC_DBUG DEBUG
#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)
#define KC_ENTS MT(MOD_LSFT, KC_ENT)
#define KC_ESCC MT(MOD_LCTL, KC_ESC)
#define KC_GRVF LT(_FN3, KC_GRV)
#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,LPRN,RPRN, Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     ESCC, A  , S  , D  , F  , G  ,LBRC,RBRC, H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,LCBR,RCBR, N  , M  ,COMM,DOT ,SLSH,ENTS,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     GRVF,LCTL,LALT,LGUI,LOWR,SPC ,SPC ,BSPC,BSPC,RASE,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----+----+----+----+----+----+----+----+----'
  ),


  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----+----+----+----+----.
         , 1  , 2  , 3  , 4  , 5  ,LPRN,RPRN, 6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     DEL ,CAPP,LEFT,RGHT, UP ,LBRC,LBRC,RBRC,RBRC, P4 , P5 , P6 ,PLUS,PIPE,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,CPYP,    ,    ,DOWN,LCBR,LCBR,RCBR,RCBR, P1 , P2 , P3 ,MINS,    ,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,DEL ,DEL ,    , P0 ,PDOT,    ,
  //`----+----+----+----+----+----+----+----+----+----+----+----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----+----+----+----+----.
         ,EXLM, AT ,HASH,DLR ,PERC,    ,    ,CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     DEL ,MPRV,MNXT,VOLU,PGUP,UNDS,    ,    ,EQL ,HOME,    ,    ,    ,BSLS,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     MUTE,MSTP,MPLY,VOLD,PGDN,MINS,    ,    ,PLUS,END ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----+----+----+----+----+----+----+----'
  ),

  [_FN3] = LAYOUT_kc(
  //,----+----+----+----+----+----+----+----+----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,    ,    , F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     RTOG,RMOD,RHUI,RSAI,RVAI,    ,    ,    ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
     RST ,DBUG,RHUD,RSAD,RVAD,    ,    ,    ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----+----+----+----+----+----+----+----'
  ),

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
  }
  return true;
}

