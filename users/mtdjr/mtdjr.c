#include "mtdjr.h"

#ifdef SOLENOID_ENABLE
  #include "solenoid.h"

  void solenoid_buzz_on(void);
  void solenoid_buzz_off(void);
  void solenoid_dwell_minus(void);
  void solenoid_dwell_plus(void);
  void solenoid_toggle(void);
  void solenoid_stop(void);
  void solenoid_fire(void);
  void solenoid_check(void);
  void solenoid_setup(void);
  void matrix_init_user(void);
  void matrix_scan_user(void);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef SOLENOID_ENABLE
    if (record->event.pressed) {
      solenoid_fire();
    }
  #endif
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
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
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_ADJUST);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case SOLENOID_TOG:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_toggle();
        }
      #endif
      break;
    case SOLENOID_DWELL_MINUS:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_dwell_minus();
        }
        #endif
      break;
    case SOLENOID_DWELL_PLUS:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_dwell_plus();
        }
        #endif
      break;
    case SOLENOID_BUZZ_ON:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_buzz_on();
        }
        #endif
      break;
    case SOLENOID_BUZZ_OFF:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_buzz_off();
        }
        #endif
      break;
  }
  return true;
};


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC),
  [TD_ALTLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, LGUI(KC_L)),
  [TD_ENDLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_END, LGUI(KC_L)),
  //[TD_PRNT] = ACTION_TAP_DANCE_DOUBLE(PRINT, PRINT_SEL)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
      switch(id) {
          case 0:
              SEND_STRING("sudo su -\n");
              return false; break;
          case 1:
              SEND_STRING("puppet apply /etc/puppetlabs/code/environments/production/manifests/site.pp\n");
              return false; break;
          case 2:
              SEND_STRING("ps -ef | grep ");
              return false; break;
          case 3: // control + insert
              return MACRO(D(LCTL), T(INS), U(LCTL), END);
              break;
          case 4: // shift + insert
              return MACRO(D(LSFT), T(INS), U(LSFT), END);
              break;
          case 5: // control + alt + delete
              return MACRO(D(LCTL), D(RALT), T(DEL), U(LCTL), U(LALT), END);
              break;
          case 6: // lgui + L
              return MACRO(D(LGUI), T(L), U(LGUI), END);
              break;
      }
  }
  return MACRO_NONE;
};
