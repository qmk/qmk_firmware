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
bool process_tap_hold_key_custom(keyrecord_t* record, uint16_t keycode) {

  //tap is record->tap.count && record->event.pressed
  //hold is record->event.pressed

  bool isShift = ( (get_mods() & MOD_BIT(KC_LSFT)) || (get_oneshot_mods() & MOD_BIT(KC_LSFT)) );

  switch(keycode) {

    //- or --
    case TR_BSLS:
      if ( record->tap.count && record->event.pressed ) {
        tap_code16( KC_BSLS );  
      } else if ( record->event.pressed ) {
        isShift ? tap_code16( LSFT( KC_BSLS ) ) : tap_code16( KC_BSLS );
        isShift ? tap_code16( LSFT( KC_BSLS ) ) : tap_code16( KC_BSLS ); 
      }
      return false;

    //` or ```
    case TR_GRV:
      if ( record->tap.count && record->event.pressed ) {
        tap_code16( KC_GRV );  
      } else if ( record->event.pressed ) {
        isShift ? tap_code16( LSFT( KC_GRV ) ) : tap_code16( KC_GRV );
        isShift ? tap_code16( LSFT( KC_GRV ) ) : tap_code16( KC_GRV ); 
        isShift ? tap_code16( LSFT( KC_GRV ) ) : tap_code16( KC_GRV );
      }
      return false;

    //- or --
    case TR_MINS:
      if ( record->tap.count && record->event.pressed ) {
        tap_code16( KC_MINS );  
      } else if ( record->event.pressed ) {
        isShift ? tap_code16( LSFT( KC_MINS ) ) : tap_code16( KC_MINS );
        isShift ? tap_code16( LSFT( KC_MINS ) ) : tap_code16( KC_MINS ); 
      }
      return false;

    //' or ''
    case TR_QUOT:
      if ( record->tap.count && record->event.pressed ) {
        //if tapped, then we do not need the ternary operator
        tap_code16( KC_QUOT );  
      } else if ( record->event.pressed ) { 
        //if held, then we need to do this or one shot mods won't cover the second keypress
        isShift ? tap_code16( LSFT( KC_QUOT ) ) : tap_code16( KC_QUOT );
        isShift ? tap_code16( LSFT( KC_QUOT ) ) : tap_code16( KC_QUOT );
      }
      return false;

    // / or //
    case TR_SLSH:
      if ( record->tap.count && record->event.pressed ) {
        tap_code16( KC_SLSH );  
      } else if ( record->event.pressed ) {
        isShift ? tap_code16( LSFT( KC_SLSH ) ) : tap_code16( KC_SLSH );
        isShift ? tap_code16( LSFT( KC_SLSH ) ) : tap_code16( KC_SLSH ); 
      }
      return false;
  }
  return true;  // Continue default handling.
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

    case QWERTY:
      if ( record->event.pressed ) {  
          default_layer_set(1UL<<_QWERTY);
      }
      return false;

    case CLMAKDH:
      if ( record->event.pressed ) {
          default_layer_set(1UL<<_COLEMAK_DH);
      }
      return false;

    case GAMING:
      if ( record->event.pressed ) {  
          default_layer_set(1UL<<_GAMING);
      }
      return false;

    //https://docs.qmk.fm/#/mod_tap?id=changing-both-tap-and-hold
    //https://getreuer.info/posts/keyboards/triggers/index.html#tap-vs.-long-press
#if defined(TAPHOLD_ENABLE)
    case TR_BSLS:
      return process_tap_hold_key_custom(record, keycode);

    case TR_COMM:
      return process_tap_hold_key(record, LSFT(KC_9));

    case TR_DOT:
      return process_tap_hold_key(record, LSFT(KC_0));

    case TR_EQL:
      return process_tap_hold_key(record, LSFT(KC_EQL));

    case TR_GRV:
      return process_tap_hold_key_custom(record, keycode);

    case TR_MINS:
      return process_tap_hold_key_custom(record, keycode);

    case TR_QUOT:
      return process_tap_hold_key_custom(record, keycode);

    case TR_LBRC:
      return process_tap_hold_key(record, LSFT(KC_LBRC));

    case TR_RBRC:
      return process_tap_hold_key(record, LSFT(TR_RBRC));

    case TR_SCLN:
      return process_tap_hold_key(record, LSFT(KC_SCLN));

    case TR_SLSH:
      return process_tap_hold_key_custom(record, keycode);

#endif //TAPHOLD_ENABLE

  }
  return true;
}

