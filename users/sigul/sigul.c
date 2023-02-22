#include "keymap_italian_mac_ansi.h"
#include "sigul.h"

__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case IT_SCCL:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RIGHT_SHIFT)){
          register_code16(IT_COLN);
        } else {
          register_code16(IT_SCLN);
        }
      } else {
        unregister_code16(IT_COLN);
        unregister_code16(IT_SCLN);
      }
      return false;
      break;

    case IT_APDQ:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RIGHT_SHIFT)){
          register_code16(IT_DQUO);
        } else {
          register_code16(IT_QUOT);
        }
      } else {
        unregister_code16(IT_DQUO);
        unregister_code16(IT_QUOT);
        }
      return false;
      break;

    case IT_CMLS:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RIGHT_SHIFT)){
          unregister_code16(KC_LSFT);
          register_code16(IT_LABK);
	  register_code16(KC_LSFT);
        } else {
          register_code16(IT_COMM);
        }
      } else {
        unregister_code16(IT_LABK);
        unregister_code16(IT_COMM);
      }
      return false;
      break;

    case IT_DTMR:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RIGHT_SHIFT)){
          register_code16(IT_RABK);
        } else {
          register_code16(IT_DOT);
        }
      } else {
        unregister_code16(IT_RABK);
        unregister_code16(IT_DOT);
      }
      return false;
      break;

    case IT_SLQS:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RIGHT_SHIFT)){
          register_code16(IT_QUES);
        } else {
          register_code16(IT_SLSH);
        }
      } else {
        unregister_code16(IT_QUES);
        unregister_code16(IT_SLSH);
      }
      return false;
      break;
  }
  return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
};

