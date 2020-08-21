#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum iris_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD
};

// Tap Dance Declarations
enum {
    TD_LALT_LGUI = 0,
    TD_RALT_RGUI
};

#define KC_ KC_TRNS

#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)
#define KC_NUM TG(_NUMPAD)
#define KC_RST RESET
#define KC_DBUG DEBUG
#define KC_BL_S BL_STEP
#define KC_RTOG RGB_TOG
#define KC_RMD RGB_MOD
#define KC_RRMD RGB_RMOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

#define KC_LAG TD(TD_LALT_LGUI)
#define KC_RAG TD(TD_RALT_RGUI)
#define KC_RSEN MT(MOD_RSFT, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,ENT ,     ENT , N  , M  ,COMM,DOT ,SLSH,RSEN,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LAG ,LOWR,SPC ,         SPC ,RASE,RAG
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CAPS,    ,HOME, UP ,END ,PGUP,               LEFT,DOWN, UP ,RGHT,INS ,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,TILD,LEFT,DOWN,RGHT,PGDN,                   ,UNDS,PLUS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,MPLY,MPRV,MNXT,VOLD,VOLU,    ,         ,HOME,PGDN,PGUP,END ,APP ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CAPS,    ,BTN1,MS_U,BTN2,WH_U,               LEFT,DOWN, UP ,RGHT,INS ,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,GRV ,MS_L,MS_D,MS_R,WH_D,                   ,MINS,EQL ,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,MPLY,MPRV,MNXT,VOLD,VOLU,    ,         ,HOME,PGDN,PGUP,END ,APP ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,RMD ,RHUI,RSAI,RVAI,RTOG,                   ,PSCR,SLCK,PAUS,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,RRMD,RHUD,RSAD,RVAD,BL_S,               LEFT,DOWN, UP ,RGHT,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,DBUG,    ,    ,    ,RST ,NUM ,     NUM ,HOME,PGDN,PGUP,END ,APP ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,               NLCK, P7 , P8 , P9 ,PSLS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   , P4 , P5 , P6 ,PAST,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   , P1 , P2 , P3 ,PPLS,ENT ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    , P0 , P0 ,PDOT,PMNS,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  )

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for L-Alt, twice for L-GUI
    [TD_LALT_LGUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
    // Tap once for R-Alt, twice for R-GUI
    [TD_RALT_RGUI] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_RGUI)
};
