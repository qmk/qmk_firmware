#include "spacebarracecar.h"

#ifdef GERMAN_ENABLE
// These indicate if left and right shift are physically pressed
bool lshift = false;
bool rshift = false;

// Interrupt and times for space cadet shift
bool lshiftp = false;
bool rshiftp = false;
uint16_t lshift_timer = 0;
uint16_t rshift_timer = 0;

// Number of items that are saved in prev_kcs
uint8_t prev_indx = 0;
// Used to save the last 6 actual keycodes activated by frankenkeycodes
uint16_t prev_kcs[6] = {0, 0, 0, 0, 0, 0};

// If true the deadkey characters grave and circonflexe are not automatically escaped
bool esct = false;

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
#endif

// Interrupt and times for Nav/Esc
bool navesc = false;
uint16_t navesc_timer = 0;

// If true Gui keys and Space Cadet Shift get disabled
bool game = false;

// Interrupts all timers
void timer_timeout(void){
  #ifdef GERMAN_ENABLE
  lshiftp = false;
  rshiftp = false;
  #endif
  navesc = false;
  timer_timeout_keymap();
}

__attribute__((weak))
void timer_timeout_keymap(void){
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case CU_GAME:
    if(record->event.pressed) {
      timer_timeout();
      game = !game;
    }
    // allows keymap to execute further commands when CU_GAME is pressed, for example enabling a macro layer
    return process_record_keymap(keycode, record) && false;
  case KC_LGUI:
  case KC_RGUI:
    if (record->event.pressed)
      timer_timeout();
    if (game)
      return false;
    else
      return true;
  case CU_NAV:
    if(record->event.pressed) {
      navesc = true;
      navesc_timer = timer_read();
      layer_on(_NAV);
    } else {
      if (timer_elapsed(navesc_timer) < TAPPING_TERM && navesc) {
        register_code(KC_ESC);
        unregister_code(KC_ESC);
      }
      layer_off(_NAV);
    }
    return false;
  case KC_P00:
    if(record->event.pressed) {
      timer_timeout();
      register_code(KC_P0);
      unregister_code(KC_P0);
      register_code(KC_P0);
      unregister_code(KC_P0);
    }
    return false;

  #ifdef RGBLIGHT_ENABLE
  case CU_RGBV:
    if(record->event.pressed) {
      timer_timeout();
      if (rgblight_get_val()+32>255)
        rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), 31);
      else
        rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val()+32);
    }
    return false;
  #endif

  #ifdef GERMAN_ENABLE
  case CU_LSFT:
    if(record->event.pressed) {
      lshiftp = true;
      lshift_timer = timer_read();
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      lshift = true;
    } else {
      if (timer_elapsed(lshift_timer) < TAPPING_TERM && lshiftp && !game) {
        register_code(KC_LSFT);
        register_code(KC_8);
        unregister_code(KC_8);
        unregister_code(KC_LSFT);
      }
      unreg_prev();
      if (!rshift)
        unregister_code(KC_LSFT);
      lshift = false;
    }
    return false;
  case CU_RSFT:
    if(record->event.pressed) {
      rshiftp = true;
      rshift_timer = timer_read();
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      rshift = true;
    } else {
      if (timer_elapsed(rshift_timer) < TAPPING_TERM && rshiftp && !game) {
        register_code(KC_LSFT);
        register_code(KC_9);
        unregister_code(KC_9);
        unregister_code(KC_LSFT);
      }
      unreg_prev();
      if (!lshift)
        unregister_code(KC_LSFT);
      rshift = false;
    }
    return false;
  case CU_ESCT:
    if(record->event.pressed) {
      timer_timeout();
      esct = !esct;
    }
    return false;
  case CU_AE:
    UML(DE_AE)
  case CU_OE:
    UML(DE_OE)
  case CU_UE:
    UML(DE_UE)
  case CU_SS:
    if(record->event.pressed) {
      timer_timeout();
      unregister_code(KC_LSFT);
      register_code(DE_SS);
      unregister_code(DE_SS);
      if (lshift || rshift)
        register_code(KC_LSFT);
      layer_off(_DEADKEY);
    }
    return false;
  case CU_DDQ:
    if(record->event.pressed) {
      timer_timeout();
      register_code(KC_LSFT);
      register_code(KC_2);
      unregister_code(KC_2);
      if (!lshift && !rshift)
        unregister_code(KC_LSFT);
      layer_off(_DEADKEY);
    }
    return false;
  case CU_ED:
    if(record->event.pressed) {
      timer_timeout();
      layer_off(_DEADKEY);
    }
    return false;
  case CU_GRV:
    if(record->event.pressed) {
      timer_timeout();
      if (lshift || rshift){
        unregister_code(KC_LSFT);
        register_code(KC_ALGR);
        unregister_code(DE_PLUS);
        register_code(DE_PLUS);
        unregister_code(DE_PLUS);
        unregister_code(KC_ALGR);
        register_code(KC_LSFT);
      } else {
        register_code(KC_LSFT);
        unregister_code(DE_ACUT);
        register_code(DE_ACUT);
        unregister_code(DE_ACUT);
        unregister_code(KC_LSFT);
        if (!esct) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
        }
      }
    }
    return false;
  case CU_CIRC:
    if(record->event.pressed) {
      timer_timeout();
      unregister_code(KC_LSFT);
      unregister_code(DE_CIRC);
      register_code(DE_CIRC);
      unregister_code(DE_CIRC);
      if (!esct) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
      }
      if (lshift || rshift)
        register_code(KC_LSFT);
    }
    return false;
  case CU_QUOT:
    if(record->event.pressed){
      timer_timeout();
      register_code(KC_LSFT);
      if (lshift || rshift){
        layer_on(_DEADKEY);
      } else {
        unregister_code(DE_HASH);
        register_code(DE_HASH);
        add_to_prev(DE_HASH);
      }
    } else {
      unregister_code(DE_HASH);
      unreg_prev();
      if (lshift || rshift)
        register_code(KC_LSFT);
      else
        unregister_code(KC_LSFT);
    }
    return false;
  case CU_6:
    if(record->event.pressed){
      timer_timeout();
      unregister_code(KC_LSFT);
      if (lshift || rshift){
        unregister_code(DE_CIRC);
        register_code(DE_CIRC);
        unregister_code(DE_CIRC);
        if (!esct) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
        }
        register_code(KC_LSFT);
      } else {
        register_code(DE_6);
      }
    } else {
      unregister_code(DE_6);
    }
    return false;
  case CU_COMM:
    SHIFT_NO(DE_COMM, DE_LESS)
  case CU_DOT:
    SHIFT_NORM(DE_DOT, DE_LESS)
  case CU_SLSH:
    SHIFT_ALL(DE_7, DE_SS)
  case CU_SCLN:
    SHIFT_ALL(DE_COMM, DE_DOT)
  case CU_3:
    SHIFT_NO(DE_3, DE_HASH)
  case CU_7:
    SHIFT_NORM(DE_7, DE_6)
  case CU_8:
    SHIFT_NORM(DE_8, DE_PLUS)
  case CU_9:
    SHIFT_NORM(DE_9, DE_8)
  case CU_0:
    SHIFT_NORM(DE_0, DE_9)
  case CU_EQL:
    SHIFT_SWITCH(DE_0, DE_PLUS)
  case CU_LBRC:
    SHIFT_ALGR(DE_8, DE_7)
  case CU_RBRC:
    SHIFT_ALGR(DE_9, DE_0)
  case CU_BSLS:
    SHIFT_ALGR(DE_SS, DE_LESS)
  case CU_Z:
    CTRL(DE_Z, KC_Z)
  case CU_Y:
    CTRL(DE_Y, KC_Y)
  case KC_LCTL:
  case KC_RCTL:
    if(!record->event.pressed) {
      timer_timeout();
      unregister_code(KC_Z);
      unregister_code(KC_Y);
    }
    return true;
  #endif

  default:
    if(record->event.pressed) {
      timer_timeout();

      #ifdef GERMAN_ENABLE
      if (lshift || rshift)
        register_code(KC_LSFT);
      else
        unregister_code(KC_LSFT);
      #endif

    }
    return process_record_keymap(keycode, record);
  }
}

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
