#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _BL 0
#define _FN 1
#define _FN2 2
#define _FN3 3

// enum custom_keycodes {
//   QWERTY = SAFE_RANGE,
//   LOWER,
//   RAISE,
//   FN3,
// };
//Tap Dance Declarations
enum {
  TD_1 = 0,
  TD_2
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_X0 MT(MOD_LCTL, KC_ESC)
#define KC_X1 MO(_FN)
#define KC_X2 TO(_FN)
#define KC_X3 MO(_FN2)
#define KC_X4 MT(MOD_LSFT, KC_ENT)
// #define KC_X5 TD(TD_1)
// #define KC_X6 TD(TD_2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BL] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     ESC , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     TAB , A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOTE,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,ENT ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LGUI,LALT, X2 , X1 , X1 ,     SPC ,SPC ,LEFT,UP  ,DOWN,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_FN] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
      X0 , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,     LBRC,RBRC,MINS,EQL ,PLUS,PIPE,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,BSLS,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_FN2] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     DEL ,MPRV,MNXT,VOLU,PGUP,UNDS,     EQL ,HOME,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     MUTE,MSTP,MPLY,VOLD,PGDN,MINS,     PLUS,END ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,   
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_FN3] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

};

// //Tap Dance Definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//   //Tap once for Esc, twice for Caps Lock
//   [TD_1]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_TAB),
//   [TD_2]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI)
// // Other declarations would go here, separated by commas, if you have them
// };

// void persistent_default_layer_set(uint16_t default_layer) {
//   eeconfig_update_default_layer(default_layer);
//   default_layer_set(default_layer);
// }
//
//
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case QWERTY:
//       if (record->event.pressed) {
//         #ifdef AUDIO_ENABLE
//           PLAY_SONG(tone_qwerty);
//         #endif
//         persistent_default_layer_set(1UL<<_QWERTY);
//       }
//       return false;
//       break;
//     case LOWER:
//       if (record->event.pressed) {
//         layer_on(_LOWER);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       } else {
//         layer_off(_LOWER);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       }
//       return false;
//       break;
//     case RAISE:
//       if (record->event.pressed) {
//         layer_on(_RAISE);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       } else {
//         layer_off(_RAISE);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       }
//       return false;
//       break;
//     case ADJUST:
//       if (record->event.pressed) {
//         layer_on(_ADJUST);
//       } else {
//         layer_off(_ADJUST);
//       }
//       return false;
//       break;
//   }
//   return true;
// }
