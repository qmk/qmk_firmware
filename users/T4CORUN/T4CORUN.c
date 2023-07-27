#include "t4corun.h"


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUMBER, _NAVIGATION, _SYMBOL);
}

void double_tap(uint16_t keycode) {
  tap_code16(keycode);
  tap_code16(keycode);
}

void double_tap_space(uint16_t keycode) {
  tap_code16(KC_SPC);
  double_tap(keycode);
  tap_code16(KC_SPC);
}

void double_parens_left(uint16_t left, uint16_t right) {
  tap_code16(left);
  tap_code16(right);
  tap_code16(KC_LEFT);
}

void triple_tap(uint16_t keycode) {
  tap_code16(keycode);
  tap_code16(keycode);
  tap_code16(keycode);
}

//here we can have the holds be more complex, like sending "" when you hold "
bool process_tap_hold_key(keyrecord_t* record, uint16_t keycode) {

  //tap is record->tap.count && record->event.pressed
  //hold is record->event.pressed

  bool isShift = ( (get_mods() & MOD_BIT(KC_LSFT)) || (get_oneshot_mods() & MOD_BIT(KC_LSFT)) );
  uint16_t key = KC_NO;
  uint16_t altkey = KC_NO;


/*
  switch(keycode) {



    //Double Taps

    case TR_UNDS:
      key = KC_UNDS;
      
      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
      }
      return false;

    case TR_LABK:
      key = KC_LABK;
      
      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
      }
      return false;

    case TR_RABK:
      key = KC_RABK;
      
      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
      }
      return false;

    case TR_SLSH:
      key = KC_SLSH;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
      }
      return false;

    case TR_BSLS:
      key = KC_BSLS;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
      }
      return false;

    case TR_HASH:
      key = KC_HASH;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
      }
      return false;

    case TR_MINS:
      key = KC_MINS;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
      }
      return false;




    //Double Taps with Spaces
    case TR_PIPE:
      key = KC_PIPE;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap_space(LSFT(key)) : double_tap_space(key);
      }
      return false;

    case TR_AMPR:
      key = KC_AMPR;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap_space(LSFT(key)) : double_tap_space(key);
      }
      return false;

    case TR_EQL:
      key = KC_EQL;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_tap_space(LSFT(key)) : double_tap_space(key);
      }
      return false;




    //Triple Tap
    
    case TR_GRV:
      key = KC_GRV;
      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? triple_tap( LSFT( key ) ) : triple_tap( key );
      }
      return false;




    //custom

    case TR_EXLM:
      key = KC_EXLM;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );
      } else if (record->event.pressed) {
        send_string(" != ");
      }
      return false;

    case TR_LPRN:
      key = KC_LPRN;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );
      } else if (record->event.pressed) {
        double_parens_left(KC_LPRN, KC_RPRN);
      }
      return false;

    case TR_LBRC:
      key = KC_LBRC;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );
      } else if (record->event.pressed) {
        double_parens_left(KC_LBRC, KC_RBRC);
      }
      return false;

    case TR_LCBR:
      key = KC_LCBR;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );
      } else if (record->event.pressed) {
        double_parens_left(KC_LCBR, KC_RCBR);
      }
      return false;

    case TR_QUOT:
      key = KC_QUOT;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        isShift ? double_parens_left(LSFT(key), LSFT(key)) : double_parens_left(key, key);
      }
      return false;

    case TR_DQUO:
      key = KC_DQUO;

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        double_parens_left(key, key);
      }
      return false;

    case TR_COMM:
      key = KC_COMM;
      altkey = LSFT(KC_9);

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        tap_code16(altkey);
      }
      return false;

    case TR_DOT:
      key = KC_DOT;
      altkey = LSFT(KC_0);

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        tap_code16(altkey);
      }
      return false;

    case TR_SCLN:
      key = KC_SCLN;
      altkey = LSFT(KC_SCLN);

      if ( record->tap.count && record->event.pressed ) {
        tap_code16( key );  
      } else if (record->event.pressed) {
        tap_code16(altkey);
      }
      return false;
  }

*/

  switch(keycode) {



    //Double Taps

    case TR_UNDS:
      key = KC_UNDS;
      
      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
        return false;
      }
      break;
      
    case TR_LABK:
      key = KC_LABK;
      
      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
        return false;
      }
      break;     

    case TR_RABK:
      key = KC_RABK;
      
      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
        return false;
      }
      break;      

    case TR_SLSH:
      key = KC_SLSH;

      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
        return false;
      }
      break;      

    case TR_BSLS:
      key = KC_BSLS;

      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
        return false;
      }
      break;      

    case TR_HASH:
      key = KC_HASH;

      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
        return false;
      }
      break;      

    case TR_MINS:
      key = KC_MINS;

      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap(LSFT(key)) : double_tap(key);
        return false;
      }
      break;     




    //Double Taps with Spaces
    
    case TR_PIPE:
      key = KC_PIPE;

      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap_space(LSFT(key)) : double_tap_space(key);
        return false;
      }
      break;      

    case TR_AMPR:
      key = KC_AMPR;

      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap_space(LSFT(key)) : double_tap_space(key);
        return false;
      }
      break;
      
    case TR_EQL:
      key = KC_EQL;

      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_tap_space(LSFT(key)) : double_tap_space(key);
        return false;
      }
      break;
      




    //Triple Tap
    
    case TR_GRV:
      key = KC_GRV;
      
      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? triple_tap(LSFT(key)) : triple_tap(key);
        return false;
      }
      break;      




    //custom

    case TR_EXLM:
      key = KC_EXLM;

      if (record->tap.count == 0 && record->event.pressed) {
        send_string(" != ");
        return false;
      }
      break;

    case TR_LPRN:
      key = KC_LPRN;

      if (record->tap.count == 0 && record->event.pressed) {
        double_parens_left(KC_LPRN, KC_RPRN);
        return false;
      }
      break;
      

    case TR_LBRC:
      key = KC_LBRC;

      if (record->tap.count == 0 && record->event.pressed) {
        double_parens_left(KC_LBRC, KC_RBRC);
        return false;
      }
      break;
      

    case TR_LCBR:
      key = KC_LCBR;

      if (record->tap.count == 0 && record->event.pressed) {
        double_parens_left(KC_LCBR, KC_RCBR);
        return false;
      }
      break;
      

    case TR_QUOT:
      key = KC_QUOT;

      if (record->tap.count == 0 && record->event.pressed) {
        isShift ? double_parens_left(LSFT(key), LSFT(key)) : double_parens_left(key, key);
        return false;
      }
      break;
      

    case TR_DQUO:
      key = KC_DQUO;

      if (record->tap.count == 0 && record->event.pressed) { 
        double_parens_left(key, key);
        return false;
      }
      break;

    case TR_COMM:
      key = KC_COMM;
      altkey = LSFT(KC_9);

      if (record->tap.count == 0 && record->event.pressed) {
        tap_code16(altkey);
        return false;
      }
      break;

    case TR_DOT:
      key = KC_DOT;
      altkey = LSFT(KC_0);

      if (record->tap.count == 0 && record->event.pressed) {
        tap_code16(altkey);
        return false;
      }
      break;
      

    case TR_SCLN:
      key = KC_SCLN;
      altkey = LSFT(KC_SCLN);

      if (record->tap.count == 0 && record->event.pressed) {
        tap_code16(altkey);
        return false;
      }
      break;

  }

  if (record->tap.count && record->event.pressed) {
    tap_code16(key);
    return false;
  }

  return true;  // Continue default handling.
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

    case QWERTY:
      if (record->event.pressed) {  
          default_layer_set(1UL<<_QWERTY);
      }
      return false;

    case CLMAKDH:
      if (record->event.pressed) {
          default_layer_set(1UL<<_COLEMAK_DH);
      }
      return false;

    case GAMING:
      if (record->event.pressed) {  
          default_layer_set(1UL<<_GAMING);
      }
      return false;

    //https://docs.qmk.fm/#/mod_tap?id=changing-both-tasp-and-hold
    //https://getreuer.info/posts/keyboards/triggers/index.html#tap-vs.-long-press
    //https://www.jonashietala.se/series/t-34/ he focuses on a keymap for programming/VIM
    case TR_UNDS:
    case TR_LABK:
    case TR_RABK:
    case TR_SLSH:
    case TR_BSLS:
    case TR_HASH:
    case TR_MINS:
    case TR_PIPE:
    case TR_AMPR:
    case TR_EQL:
    case TR_GRV:
    case TR_EXLM:
    case TR_LPRN:
    case TR_LCBR:
    case TR_LBRC:
    case TR_QUOT:
    case TR_DQUO:
    case TR_COMM:
    case TR_DOT:
    case TR_SCLN:
      return process_tap_hold_key(record, keycode);
  }
  return true;
}

