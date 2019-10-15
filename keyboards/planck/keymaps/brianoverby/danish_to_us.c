/* This is base on SpacebarRacecars work https://github.com/qmk/qmk_firmware/tree/master/users/spacebarracecar */
#include "danish_to_us.h"

// Indicate if shift is physically pressed
bool lshift = false;

// Number of items that are saved in prev_kcs
uint8_t prev_indx = 0;
// Used to save the last 6 actual keycodes activated by frankenkeycodes
uint16_t prev_kcs[6] = {0, 0, 0, 0, 0, 0};

/*
Used to add a keycode to a prev_kcs to remember it.
When full the last code gets discarded and replaced by
the new one.
*/
void add_to_prev(uint16_t kc){
  for (int i=0; i<prev_indx; i++){
    if (kc == prev_kcs[i])
      return;
  }
  if (prev_indx == 6){
    for (int i=5; i>0; i--){
      prev_kcs[i] = prev_kcs[i-1];
    }
    prev_kcs[0] = kc;
  } else {
    prev_kcs[prev_indx] = kc;
    prev_indx++;
  }
}

/*
Unregisters all codes saved in prev_kcs and resets prev_indx.
gets called on multiple occasions mainly when shift is released
and when frankenkeycodes are pressed. Prevents output of
wrong characters when really specific key combinations
that would never occur during normal usage are pressed.
*/
void unreg_prev(void){
  if (prev_indx == 0)
    return;
  for (int i=0; i<prev_indx; i++){
    unregister_code(prev_kcs[i]);
  }
  prev_indx = 0;
}

// Interrupts all timers
void timer_timeout(void){
  timer_timeout_keymap();
}

__attribute__((weak))
void timer_timeout_keymap(void){
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {  
    case LSFT:
      if(record->event.pressed) {
        unregister_code(KC_LSFT);
        register_code(KC_LSFT);
        lshift = true;
      } else {
        unreg_prev();
        unregister_code(KC_LSFT);
        lshift = false;
      }
      return false;
    
    case COMM:
      SHIFT_NO(KC_COMM, lt)
    case DOT:
      SHIFT_NORM(KC_DOT, lt)
    case SLSH:
      SHIFT_ALL(KC_7, plus)
    case SCLN:
      SHIFT_ALL(KC_COMM, KC_DOT)
    case QUOT:
      SHIFT_NORM(quot, KC_2)

    default:
      if(record->event.pressed) {
        timer_timeout();
        if (lshift)
          register_code(KC_LSFT);
        else
          unregister_code(KC_LSFT);
      }
    return process_record_keymap(keycode, record);
  }
}

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
