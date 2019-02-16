#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _HYPER,
};

#define KC_ KC_TRNS

#define KC_ESCC MT(MOD_LCTL, KC_ESC)
#define KC_ENTS MT(MOD_LSFT, KC_ENT)
#define KC_HYPE MO(_HYPER)
#define KC_RST  RESET
// Brightness
#define KC_BRUP KC_PAUS
#define KC_BRDN KC_SLCK
#define KC_BLTG BL_TOGG

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,EQL,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     ESCC, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,SPC,      BSPC, N  , M  ,COMM,DOT ,SLSH,ENTS,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LGUI,SPC,          BSPC,HYPE,ENT
  //                  `----+----+----'        `+---+----+----'
  ), //                                              |
  //                                                 |
  [_HYPER] = LAYOUT_kc( //                           V
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     RST , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 ,LBRC,RBRC,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,PGUP,    ,BRUP,                   ,    , UP ,LCBR,RCBR,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,HOME,PGDN,END ,BRDN,               MINS,LEFT,DOWN,RGHT,    ,PIPE,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,BLTG,     VOLU,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,         VOLD,    ,MUTE
  //                  `----+----+----'        `----+----+----'
  ),
};
