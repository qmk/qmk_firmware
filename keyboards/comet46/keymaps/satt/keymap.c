// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "keymap_jis2us.h"
#include "action_pseudo_lut.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum comet46_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _PSEUDO_US,
    _PSEUDO_US_LOWER,
    _PSEUDO_US_RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  PSEUDO_US,
};

#define KC_LWR MO(_LOWER)
#define KC_RSE MO(_RAISE)
#define KC_P_LW MO(_PSEUDO_US_LOWER)
#define KC_P_RS MO(_PSEUDO_US_RAISE)
#define KC_QWRT QWERTY
#define KC_P_US PSEUDO_US
#define KC_SPCT CTL_T(KC_SPC)
#define KC_ENSF SFT_T(KC_ENT)
#define KC_SFTA SFT_T(KC_A)
#define KC_CTSF S(KC_LCTL)
#define KC_IMON ALT_T(KC_F13)
#define KC_IMOF GUI_T(KC_F14)
#define KC_SRO S(KC_RO)
#define KC_SYEN S(KC_JYEN)
#define KC_CAD LCA(KC_DEL)
#define KC_RST RESET

#define LONGPRESS_DELAY 150

// Fillers to make layering more clear
#define KC_ KC_TRNS 
#define KC_XXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     ESC , Q  , W  , E  , R  , T  ,                 Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     TAB ,SFTA, S  , D  , F  , G  ,LPRN,      RPRN, H  , J  , K  , L  ,SCLN,BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     CTSF, Z  , X  , C  , V  , B  ,LBRC,      RBRC, N  , M  ,COMM,DOT ,SLSH,QUOT,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         IMOF,LWR ,SPCT,      ENSF,RSE ,IMON
  //                    +----+----+---/       \---+----+----+
  ),

  [_LOWER] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,EXLM, AT ,HASH,DLR ,PERC,                CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         , F1 , F2 , F3 , F4 , F5 , F6 ,      GRV ,BSLS,MINS,EQL ,LBRC,RBRC,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         , F7 , F8 , F9 , F10, F11, F12,      TILD,PIPE,UNDS,PLUS,LCBR,RCBR,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_RAISE] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         , 1  , 2  , 3  , 4  , 5  ,                 6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,      XXXX,LEFT,DOWN, UP ,RGHT,END ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,      HOME,XXXX,XXXX,XXXX,XXXX,XXXX,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_PSEUDO_US] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     ESC , Q  , W  , E  , R  , T  ,                 Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     TAB ,SFTA, S  , D  , F  , G  ,ASTR,      LPRN, H  , J  , K  , L  ,FN0 ,BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     CTSF, Z  , X  , C  , V  , B  ,FN0 ,      FN0 , N  , M  ,COMM,DOT ,SLSH,FN0 ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         IMOF,P_LW,SPCT,      ENSF,P_RS,IMON
  //                    +----+----+---/       \---+----+----+
  ),


  [_PSEUDO_US_LOWER] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,EXLM,LBRC,HASH,DLR ,PERC,                EQL ,CIRC, DQT,ASTR,LPRN,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         , F1 , F2 , F3 , F4 , F5 , F6 ,      LCBR,JYEN,MINS,UNDS,RBRC,BSLS,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         , F7 , F8 , F9 , F10, F11, F12,      PLUS,SYEN,SRO ,COLN,RCBR,PIPE,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_PSEUDO_US_RAISE] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         , 1  , 2  , 3  , 4  , 5  ,                 6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    , GRV,      XXXX,LEFT,DOWN, UP ,RGHT,END ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,      HOME,XXXX,XXXX,XXXX,XXXX,XXXX,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_ADJUST] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,CAD ,      QWRT,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,RST ,      P_US,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  )

};


/*
 * user defined action function
 */
enum function_id {
    PSEUDO_US_FUNCTION,
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id)
    {
    case PSEUDO_US_FUNCTION:
        action_pseudo_lut(record, _QWERTY, keymap_jis2us);
        break;
    }
}

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(PSEUDO_US_FUNCTION),
};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);
    switch (layer) {
      case _LOWER:
          set_led_red;
          break;
      case _RAISE:
          set_led_blue;
          break;
      case _PSEUDO_US_LOWER:
          set_led_yellow;
          break;
      case _PSEUDO_US_RAISE:
          set_led_cyan;
          break;
      case _ADJUST:
          set_led_magenta;
          break;
      default:
          set_led_green;
          break;
    }
};

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _PSEUDO_US:
      return update_tri_layer_state(state, _PSEUDO_US_RAISE, _PSEUDO_US_LOWER, _ADJUST);
      break;
    case _PSEUDO_US_LOWER:
      return update_tri_layer_state(state, _PSEUDO_US_RAISE, _PSEUDO_US_LOWER, _ADJUST);
      break;
    case _PSEUDO_US_RAISE: 
      return update_tri_layer_state(state, _PSEUDO_US_RAISE, _PSEUDO_US_LOWER, _ADJUST);
      break;
    default:
      return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
      break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case PSEUDO_US:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_PSEUDO_US);
      }
      return false;
      break;
  }
  return true;
}
