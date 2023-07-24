#include "t4corun.h"


//this is used to send simple keycodes so the above doesn't have to be huge
bool process_tap_hold_key(keyrecord_t* record, uint16_t hold_keycode) {

  if ( record->tap.count == 0 ) {
    if ( record->event.pressed ) {
      tap_code16(hold_keycode);
    }
    return false;
  }
  
  return true;  // Continue default handling.
}

//here we can have the holds be more complex, like sending "" when you hold "
bool process_tap_hold_key_custom(uint16_t input_code, bool isTap, bool isHold) {

  switch(input_code) {
    
    case TR_QT:
      //' or '', " or ""
      if ( isTap ) {
        tap_code16( KC_QUOT );  
      } else if ( isHold ) { 
        tap_code16( KC_QUOT );
        tap_code16( KC_QUOT );
      }
      return false;

  }
  return true;  // Continue default handling.
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool isTap = ( record->tap.count && record->event.pressed );
  bool isKeyPress = ( record->event.pressed ); //also considered a hold

#if defined(KEYLOG_ENABLE)
  if ( isKeyPress ) {
    add_keylog(keycode);
  }
#endif //KEYLOG_ENABLE


  switch (keycode) {
    case QWERTY:
      if ( isKeyPress ) {  
          default_layer_set(1UL<<_QWERTY);
      }
      return false;

    case CLMAKDH:
      if ( isKeyPress ) {
          default_layer_set(1UL<<_COLEMAK_DH);
      }
      return false;

    case GAMING:
      if ( isKeyPress ) {  
          default_layer_set(1UL<<_GAMING);
      }
      return false;

    //https://docs.qmk.fm/#/mod_tap?id=changing-both-tap-and-hold
    //https://getreuer.info/posts/keyboards/triggers/index.html#tap-vs.-long-press
    //Doing this may eliminate home row mods forever
    case TR_QT:
      return process_tap_hold_key_custom(keycode, isTap, isKeyPress);

    case TR_COMM:
      return process_tap_hold_key(record, LSFT(KC_9));

    case TR_DOT:
      return process_tap_hold_key(record, LSFT(KC_0));


  }
  return true;
}

