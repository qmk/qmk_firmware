#include "t4corun.h"


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUMBER, _NAVIGATION, _SYMBOL);
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
