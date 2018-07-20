#include "mtdjr.h"

#ifdef SOLENOID_ENABLE
  #include "solenoid.h"
#endif

#ifndef RGB_MODE
  #define RGB_MODE 16
#endif
#ifndef RGB_HUE
  #define RGB_HUE 285
#endif

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC]     = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC),
  [TD_ALTLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, LGUI(KC_L)),
  [TD_ENDLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_END, LGUI(KC_L)),
  [TD_PRINT]   = ACTION_TAP_DANCE_DOUBLE(LGUI(LSFT(KC_3)), LGUI(LSFT(KC_4))),
};

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
      switch(id) {
          case ROOT:
              SEND_STRING("sudo su -\n");
              return false; break;
          case PPLY:
              SEND_STRING("puppet apply /etc/puppetlabs/code/environments/production/manifests/site.pp\n");
              return false; break;
          case PSEF:
              SEND_STRING("ps -ef | grep ");
              return false; break;
      }
  }
  return MACRO_NONE;
};

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGB_MODE);
    rgblight_sethsv (RGB_HUE, 255, 255);
  #endif
  #ifdef SOLENOID_ENABLE
    solenoid_setup();
  #endif
}

void matrix_scan_user(void) {
  #ifdef SOLENOID_ENABLE
    solenoid_check();
  #endif
}

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

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
  switch (biton32(state)) {
    case _RAISE:
      rgblight_sethsv_noeeprom (240, 255, 255);
      break;
    case _LOWER:
      rgblight_sethsv_noeeprom (0, 255, 255);
      break;
    case _ADJUST:
      rgblight_sethsv_noeeprom (0, 0, 255);
      break;
    default:
      rgblight_sethsv_noeeprom (RGB_HUE, 255, 255);
      break;
    }
  return state;
#endif
}
