// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "keymap_jis2us.h"
#include "action_pseudo_lut.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum comet46_layers
{
    _QWERTY,
    _RAISE,
    _LOWER,
    _ADJUST,
    _BASE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_RSE RAISE
#define KC_LWR LOWER
#define KC_ADJ ADJUST
#define KC_SPCT CTL_T(KC_SPC)
#define KC_ENSF SFT_T(KC_ENT)
#define KC_CTSF S(KC_LCTL)
#define KC_IMON KC_F13
#define KC_IMOF GUI_T(KC_F14)
#define KC_USC S(KC_RO)
#define KC_PIP S(KC_JYEN)
#define KC_CAD LCA(KC_DEL)
#define KC_RST RESET

#define LONGPRESS_DELAY 150

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_ KC_TRNS 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     ESC , Q  , W  , E  , R  , T  ,                 Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     TAB , A  , S  , D  , F  , G  ,IMOF,      IMON, H  , J  , K  , L  ,FN0 ,BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     CTSF, Z  , X  , C  , V  , B  ,FN0 ,      FN0 , N  , M  ,COMM,DOT ,SLSH,FN0 ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         LALT,LWR ,SPCT,      ENSF,RSE ,ADJ
  //                    +----+----+---/       \---+----+----+
  ),

  [_RAISE] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     LCBR, 1  , 2  , 3  , 4  , 5  ,                 6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,          ,    ,MINS,UNDS,RBRC,BSLS,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,ASTR,      LPRN,    ,    ,    ,    ,    ,JYEN,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_LOWER] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     PLUS,EXLM,LBRC,HASH,DLR ,PERC,                EQL ,CIRC, DQT,ASTR,LPRN,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         , F1 , F2 , F3 , F4 , F5 , F6 ,          ,    ,USC ,COLN,RCBR,PIPE,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         , F7 , F8 , F9 , F10, F11, F12,          ,    ,    ,    ,    ,    ,PIP ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_ADJUST] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                    ,PGUP, UP ,PGDN,    ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,CAD ,          ,HOME,LEFT,DOWN,RGHT, END,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,RST ,          ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                          GRV,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_BASE] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,SCLN,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,LBRC,      RBRC,    ,    ,    ,    ,    ,QUOT,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  )

};


/*
 * user defined action function
 */
enum function_id
{
    PSEUDO_US_FUNCTION,
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{

    switch (id)
    {
    case PSEUDO_US_FUNCTION:
        action_pseudo_lut(record, _BASE, keymap_jis2us);
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
    	case _QWERTY:
    	    set_led_green;
    	    break;
        case _RAISE:
            set_led_blue;
            break;
        case _LOWER:
            set_led_red;
            break;
        case _ADJUST:
            set_led_magenta;
            break;
        default:
            set_led_green;
            break;
    }
};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
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
