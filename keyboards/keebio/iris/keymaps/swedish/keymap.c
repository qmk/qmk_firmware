#include "iris.h"
#include "keymap_swedish.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _EMPTY 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE
};

#define KC_ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET

#define KC_AA SE_AA
#define KC_AE SE_AE
#define KC_OE SE_OSLH

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  , AA ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSFT, A  , S  , D  , F  , G  ,                H  , J  , K  , L  , OE , AE ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL, Z  , X  , C  , V  , B  ,DEL ,     BSPC, N  , M  ,COMM,DOT ,SLSH,MINS,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,LOWR,SPC ,         ENT ,RASE,LALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     SE_TILD,KC_EXLM,SE_AT  ,KC_HASH,SE_DLR ,KC_PERC,                     SE_CIRC,SE_AMPR,SE_ASTR,SE_SLSH,SE_LPRN,SE_RPRN,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     SE_ACUT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                     KC_TRNS,KC_TRNS,KC_TRNS,SE_PIPE,SE_LCBR,SE_RCBR,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,SE_BSLS,                     KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,SE_LBRC,SE_RBRC,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,SE_LESS,SE_GRTR,
  //`-------+-------+-------+--+----+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                   KC_TRNS,KC_TRNS,KC_TRNS,         KC_TRNS,KC_TRNS,KC_TRNS
  //                              `-------+-------+-------'        `-------+-------+-------'
  ),

  [_RAISE] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     KC_F12 ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,                     KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     SE_GRV ,KC_7   ,KC_8   ,KC_9   ,SE_MINS,SE_ASTR,                     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,SE_PIPE,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_TRNS,KC_4   ,KC_5   ,KC_6   ,SE_PLUS,SE_SLSH,                     KC_HOME,KC_PGDN,KC_PGUP,KC_END ,KC_TRNS,SE_BSLS,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
     KC_TRNS,KC_1   ,KC_2   ,KC_3   ,KC_0   ,SE_EQL ,KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
  //`-------+-------+-------+--+----+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                   KC_TRNS,KC_TRNS,KC_TRNS,         KC_TRNS,KC_TRNS,KC_TRNS
  //                              `-------+-------+-------'        `-------+-------+-------'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
        update_tri_layer(_LOWER, _RAISE, _EMPTY);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _EMPTY);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _EMPTY);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _EMPTY);
      }
      return false;
      break;
  }
  return true;
}
