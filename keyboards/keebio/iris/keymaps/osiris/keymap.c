#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layer_names {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE
};

#define KC_ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST  RESET
#define KC_BL_S BL_STEP

// left shift as a left key too - makes perfect sense
#define KC_LESF LSFT_T(KC_LEFT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GESC, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LESF, Z  , X  , C  , V  , B  ,LBRC,     RBRC, N  , M  ,COMM,DOT ,SLSH,RGHT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,LOWR,ENT ,         SPC ,RASE,RALT
  //                  `----+----+----'        `----+----+----'
  ),

    [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GESC, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LESF, Z  , X  , C  , V  , B  ,LBRC,     RBRC, K  , M  ,COMM,DOT ,SLSH,RGHT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,LOWR,ENT ,         SPC ,RASE,RALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV ,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,BTN1,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,               MS_L,MS_D,MS_U,MS_R,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    , UP ,    ,         ,DOWN,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,   
  //                  `----+----+----'        `----+----+----'

),
  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,VOLU,    ,    ,LBRC,               RBRC,UNDS,PLUS,    ,    ,MUTE,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,MPLY,VOLD,MNXT,    ,LPRN,               RPRN,MINS,EQL ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                          ,-------+-------+-------+-------+-------+-------.
     _______,_______,_______,_______,_______, QWERTY,                           COLEMAK,_______,_______,_______,_______,_______,
  //|-------+-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------+-------|
     _______,RGB_TOG,RGB_MOD,RGB_HUI,RGB_SAI,RGB_VAI,                           _______,_______,_______,_______,_______,_______,
  //|-------+-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------+-------|
     RESET  ,DEBUG  ,_______,RGB_HUD,RGB_SAD,RGB_VAD,                           _______,_______,_______,_______,_______,_______,
  //|-------+-------+-------+-------+-------+-------+-------.        ,-------|-------+-------+-------+-------+-------+-------|
     BL_STEP,_______,_______,_______,_______,_______,_______,         _______,_______,_______,_______,_______,_______,_______,
  //`--------+-------+-------+----+--+-------+-------+-------/        \-------+-------+-------+---+---+-------+-------+-------'
                                    _______,_______,_______,             _______,_______,_______
  //                               `-------+-------+-------'            `-------+-------+-------'
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
  }
  return true;
}
