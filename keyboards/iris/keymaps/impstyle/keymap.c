// based on lewisridden layout

#include QMK_KEYBOARD_H


extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MOUSE 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MOUSE,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_TGLW TG(_LOWER)
#define KC_TGRS TG(_RAISE)
#define KC_MOUS MOUSE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // QUERTY LAYER
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
  //  ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  // TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,MINS ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  // LSFT, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  // LCTL, Z  , X  , C  , V  , B  ,PLUS ,     MOUS , N  , M  ,COMM,DOT ,SLSH,BSLASH,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
  //                   LGUI,RASE,SPC ,         ENT ,LOWR,LALT
  //                  `----+----+----'        `----+----+----'

  [_QWERTY] = LAYOUT(
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                    KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
     KC_TAB , KC_Q  , KC_W  ,KC_E  , KC_R  , KC_T  ,                     KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS ,
     KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                    KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_PLUS,     KC_MOUS , KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                                  KC_LGUI,KC_RASE,KC_SPC ,         KC_ENT ,KC_LOWR,KC_LALT
  ),
  
  // LOWER Layer
   //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
  // TILD,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  //     ,    ,PGUP,    ,    ,LBRC,               RBRC, P7 , P8 , P9 ,PLUS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  //     ,HOME,PGDN,END,     ,LPRN,               RPRN, P4 , P5 , P6 ,MINS,PIPE,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  //     ,    ,    ,    ,    ,    ,    ,         ,    , P1 , P2 , P3 ,EQL ,UNDS ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
  //                       ,    ,DEL ,        BSPC ,    , P0
  //                  `----+----+----'        `----+----+----' 

  [_LOWER] = LAYOUT(
     KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,               KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_BSPC,
    _______,_______,KC_PGUP,_______,_______,KC_LBRC,               KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,KC_PLUS,_______,
        _______ ,KC_HOME,KC_PGDN,KC_END,_______,KC_LPRN,               KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
    _______,_______,_______,_______,_______,_______,_______,        _______ ,_______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS ,
                          _______ ,_______,KC_PSCR ,        KC_DEL ,_______, KC_P0
),
  // RAISE LAYER
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
  // F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  //     ,    , UP ,    ,    ,LBRC,               RBRC,    ,NLCK,INS ,SLCK,MUTE,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  //     ,LEFT,DOWN,RGHT,    ,LPRN,               RPRN,MPRV,MPLY,MNXT,    ,VOLU,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  //     ,    ,    ,    ,    ,    ,    ,      PLUS ,    ,    ,    ,    ,    ,VOLD,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
  //                       ,    ,    ,          EQL,    ,
  //                  `----+----+----'        `----+----+----'

  [_RAISE] = LAYOUT(
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
        _______ ,_______, KC_UP ,_______,_______,KC_LBRC,               KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_MUTE,
        _______ ,KC_LEFT,KC_DOWN,KC_RGHT,_______,KC_LPRN,               KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
        _______,_______,_______,_______,_______,_______,_______,        KC_PLUS,_______,_______,_______,_______,_______,KC_VOLD,
                                     _______ ,_______,_______,            KC_EQL,_______,_______
  ),

  [_MOUSE] = LAYOUT(
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
        _______ ,_______, KC_MS_UP ,_______,_______,_______,               KC_MS_WH_UP,_______,_______,_______ ,_______,_______,
        _______ ,KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,_______,_______,               KC_MS_WH_DOWN,KC_MS_BTN1,KC_MS_BTN2,KC_MS_BTN3,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,KC_MS_ACCEL0,KC_MS_ACCEL2,_______,
                                     _______ ,_______,_______,            _______,_______,_______
  ),

};



#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _MOUSE);
      }
      return false;
      break;
  }
  return true;
};


