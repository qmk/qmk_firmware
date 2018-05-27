#include "not_so_minidox.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "action_macro.h"
#include "solenoid.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  SOLENOID_TOG,
  SOLENOID_DWELL_MINUS,
  SOLENOID_DWELL_PLUS,
  SOLENOID_BUZZ_ON,
  SOLENOID_BUZZ_OFF,
  TD_LOCK = 0,
};

#define KC_     KC_TRNS
#define KC_xxxx KC_NO

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST  RESET
#define KC_LOCK TD(TD_LOCK)

#define KC_STOG SOLENOID_TOG
#define KC_SDM  SOLENOID_DWELL_MINUS
#define KC_SDP  SOLENOID_DWELL_PLUS
#define KC_SBON SOLENOID_BUZZ_ON
#define KC_SBOF SOLENOID_BUZZ_OFF

// Macro Declarations
#define KC_ROOT M(0)
#define KC_PPLY M(1)
#define KC_PSEF M(2)
#define KC_XCPY M(3)
#define KC_XINS M(4)
#define KC_CAD  M(5)
#define UM_LOCK M(6)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  // ,----+-----+-----+-----+-----+-----,         ,----+-----+-----+-----+-----+-----,
       TAB,    Q,    W,    E,    R,    T,             Y,    U,    I,    O,    P, BSPC,
  // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
      LCTL,    A,    S,    D,    F,    G,             H,    J,    K,    L, SCLN, QUOT,
  // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
      LSFT,    Z,    X,    C,    V,    B,             N,    M, COMM,  DOT, SLSH,  ENT,
  // |----+-----+-----+-----+-----+-----|-,     ,-|----+-----+-----+-----+-----+-----|
                          LGUI, LOWR,  SPC,       SPC, RASE, LOCK
  //                     `----+-----+-----`     `----+-----+-----`
   ),

  [_LOWER] = LAYOUT(
  // ,----+-----+-----+-----+-----+-----,         ,----+-----+-----+-----+-----+-----,
       ESC,    1,    2,    3,    4,    5,             6,    7,    8,    9,    0,  DEL,
  // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,              ,     ,     , LCBR, RCBR, BSLS,
  // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
          ,     ,     , XCPY, XINS,     ,              ,     ,     ,     ,     ,     ,
  // |----+-----+-----+-----+-----+-----|-,     ,-|----+-----+-----+-----+-----+-----|
                              ,     ,     ,          ,     ,
  //                     `----+-----+-----`     `----+-----+-----`
  ),

  [_RAISE] = LAYOUT(
  // ,----+-----+-----+-----+-----+-----,         ,----+-----+-----+-----+-----+-----,
       GRV, EXLM,   AT, HASH,  DLR, PERC,          CIRC, AMPR, ASTR, LPRN, RPRN,  DEL,
  // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
          ,     ,     ,     , MINS,  EQL,              ,     ,   UP, LBRC, RBRC, PIPE,
  // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,              , LEFT, DOWN, RGHT,     ,     ,
  // |----+-----+-----+-----+-----+-----|-,     ,-|----+-----+-----+-----+-----+-----|
                              ,     ,     ,          ,     ,
  //                     `----+-----+-----`     `----+-----+-----`
   ),
  [_ADJUST] = LAYOUT(
  // ,----+-----+-----+-----+-----+-----,         ,----+-----+-----+-----+-----+-----,
      STOG, xxxx, xxxx, xxxx,  RST, xxxx,          ROOT, PPLY, PSEF, xxxx, xxxx,  CAD,
  // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
      SDM,   SDP, SBOF, SBON, xxxx, xxxx,          xxxx, xxxx, xxxx, xxxx, xxxx, xxxx,
  // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
      xxxx, xxxx, xxxx, xxxx, xxxx, xxxx,          xxxx, xxxx, xxxx, xxxx, xxxx, xxxx,
  // |----+-----+-----+-----+-----+-----|-,     ,-|----+-----+-----+-----+-----+-----|
                          xxxx,     , xxxx,      xxxx,     , xxxx
  //                     `----+-----+-----`     `----+-----+-----`
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    solenoid_fire();
  }
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
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
      if (record->event.pressed) {
        solenoid_toggle();
      }
      break;
    case SOLENOID_DWELL_MINUS:
      if (record->event.pressed) {
        solenoid_dwell_minus();
      }
      break;
    case SOLENOID_DWELL_PLUS:
      if (record->event.pressed) {
        solenoid_dwell_plus();
      }
      break;
    case SOLENOID_BUZZ_ON:
      if (record->event.pressed) {
        solenoid_buzz_on();
      }
      break;
    case SOLENOID_BUZZ_OFF:
      if (record->event.pressed) {
        solenoid_buzz_off();
      }
      break;
  }
  return true;
};

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for RALT, twice to lock pc
  [TD_LOCK] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, UM_LOCK)
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
          case 3:
              return MACRO(D(LCTL), T(INS), U(LCTL), END);
              break;
          case 4:
              return MACRO(D(LSFT), T(INS), U(LSFT), END);
              break;
          case 5:
              return MACRO(D(LCTL), D(RALT), T(DEL), U(LCTL), U(LALT), END);
              break;
          case 6:
              return MACRO(D(LGUI), T(L), U(LGUI), END);
              break;
      }
  }
  return MACRO_NONE;
};
