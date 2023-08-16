#include "taphold.h"

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

  switch(keycode) {

    //Double Taps
    case TR_UNDS:
      key = KC_UNDS; break;
    case TR_SLSH:
      key = KC_SLSH; break;
    case TR_BSLS:
      key = KC_BSLS; break;
    case TR_HASH:
      key = KC_HASH; break;
    
    //Double Taps with Spaces
    case TR_PIPE:
      key = KC_PIPE; break;
    case TR_AMPR:
      key = KC_AMPR; break;
    case TR_EQL:
      key = KC_EQL; break;
      
    //Triple Tap
    case TR_GRV:
      key = KC_GRV; break;      

    //custom
    case TR_EXLM:
      key = KC_EXLM; break;
    case TR_LPRN:
      key = KC_LPRN; break;
    case TR_LBRC:
      key = KC_LBRC; break;
    case TR_LCBR:
      key = KC_LCBR; break;
    case TR_LABK:
      key = KC_LABK; break;
    case TR_QUOT:
      key = KC_QUOT; break;
    case TR_DQUO:
      key = KC_DQUO; break;
    case TR_MINS:
      key = KC_MINS;
      altkey = LSFT(KC_MINS);
      break;
    case TR_COMM:
      key = KC_COMM;
      altkey = LSFT(KC_9);
      break;
    case TR_DOT:
      key = KC_DOT;
      altkey = LSFT(KC_0);
      break;
    case TR_SCLN:
      key = KC_SCLN;
      altkey = LSFT(KC_SCLN);
      break;
  }


  if (record->tap.count && record->event.pressed) {

    tap_code16(key);
    return false;

  } else if (record->tap.count == 0 && record->event.pressed) {

    switch(keycode) {

      //Double Taps
      case TR_UNDS:
      case TR_SLSH:
      case TR_BSLS:
      case TR_HASH:
        isShift ? double_tap(LSFT(key)) : double_tap(key);
        break;

      //Double Taps with Spaces
      case TR_PIPE:
      case TR_AMPR:
      case TR_EQL:
        isShift ? double_tap_space(LSFT(key)) : double_tap_space(key);
        break;

      //Triple Tap
      case TR_GRV:
        isShift ? triple_tap(LSFT(key)) : triple_tap(key);
        break;

      //custom
      case TR_EXLM:
        send_string(" != ");
        break;
      case TR_LPRN:
        double_parens_left(KC_LPRN, KC_RPRN);
        break;
      case TR_LBRC:
        double_parens_left(KC_LBRC, KC_RBRC);
        break;
      case TR_LCBR:
        double_parens_left(KC_LCBR, KC_RCBR);
        break;
      case TR_LABK:
        double_parens_left(KC_LABK, KC_RABK);
        break;
      case TR_QUOT:
      case TR_DQUO:
        isShift ? double_parens_left(LSFT(key), LSFT(key)) : double_parens_left(key, key);
        break;
      //case TR_DQUO:
      //  double_parens_left(key, key);
      //  return false;
      case TR_MINS:
      case TR_COMM:
      case TR_DOT:
      case TR_SCLN:
        tap_code16(altkey);
        break;
    }

    return false;
  }

  return true;  // Continue default handling.
}