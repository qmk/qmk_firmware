// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

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
#define KC_CTTB CTL_T(KC_TAB)
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
     ESC , Q  , W  , E  , R  , T  ,                 Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     CTTB, A  , S  , D  , F  , G  ,LPRN,      RPRN, H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,LCBR,      RCBR, N  , M  ,COMM,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         LGUI,LWR ,SPC ,      ENT ,RSE ,LALT
  //                    +----+----+---/       \---+----+----+
  ),

  [_RAISE] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         , 1  , 2  , 3  , 4  , 5  ,                 6  , 7  , 8  , 9  , 0  ,DEL ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         , F1 , F2 , F3 , F4 , F5 , F6 ,          ,LEFT,DOWN, UP ,RGHT,END ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         , F7 , F8 , F9 , F10, F11, F12,      HOME,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_LOWER] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,EXLM, AT ,HASH,DLR ,PERC,                CIRC,AMPR,ASTR,LPRN,RPRN,DEL ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,      GRV ,BSLS,MINS,EQL ,LBRC,RBRC,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,      TILD,PIPE,UNDS,PLUS,LCBR,RCBR,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_ADJUST] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,CAD ,          ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,RST ,          ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  )
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
