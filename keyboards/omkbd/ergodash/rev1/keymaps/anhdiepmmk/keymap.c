#include QMK_KEYBOARD_H


enum layer_names {
    _BASE,
    _NUM,
    _NAV,
    _SYM,
    _MED,
    // _FUN,
    // _MOUSE
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  NUM,
  NAV,
  SYM,
  MED,
};

// home row mod
#define HO_A MT(MOD_LCTL, KC_A)
#define HO_S MT(MOD_LSFT, KC_S)
#define HO_D MT(MOD_LALT, KC_D)
#define HO_F MT(MOD_LCTL, KC_F)
#define HO_J MT(MOD_RGUI, KC_J)
#define HO_K MT(MOD_RALT, KC_K)
#define HO_L MT(MOD_RSFT, KC_L)
#define HO_SCLN MT(MOD_RCTL, KC_SCLN)

// thumb
#define TH_NAV LT(NAV, KC_TAB) 
#define TH_NUM LT(NUM, KC_BSPC) 
#define TH_SYM LT(SYM, KC_ENT) 
#define TH_MED LT(MED, KC_ESC) 

#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 
   * Base
   */
  [_BASE] = LAYOUT(
    _______, _______, _______, _______, _______, _______ ,    _______,                             _______, _______, _______, _______, _______, _______, _______,
    _______, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T    ,    _______,                             _______, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , _______,
    _______, HO_A   , HO_S   , HO_D   , HO_F   , KC_G    ,    _______,                             _______, KC_H   , HO_J   , HO_K   , HO_L   , HO_SCLN, _______,
    _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B    ,    _______,                             _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
    _______, _______, _______, _______,          TH_MED  ,  TH_NAV , KC_SPC,               TH_SYM, TH_NUM , KC_DEL,          _______ , _______, _______, _______
  ),
  /* 
   * Num
   */
  [_NUM] = LAYOUT(
    _______, _______        , _______, _______, _______, _______         , _______,                                _______, _______, _______, _______, _______, _______, _______,
    _______, KC_LEFT_BRACKET, KC_7   , KC_8   , KC_9   , KC_RIGHT_BRACKET, _______,                                _______, _______, _______, _______, _______, _______, _______,
    _______, KC_QUOTE       , KC_4   , KC_5   , KC_6   , KC_EQUAL        , _______,                                _______, _______, _______, _______, _______, _______, _______,
    _______, KC_GRAVE       , KC_1   , KC_2   , KC_3   , KC_BACKSLASH    , _______,                                _______, _______, _______, _______, _______, _______, _______,
    _______, _______        , _______, _______,          KC_DOT          , KC_0   , KC_MINUS,             _______, _______, _______,          _______, _______, _______, _______
  ),
  /* 
   * Nav
   */
  [_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                            _______, _______, KC_HOME, _______, KC_END,  KC_PGUP, _______,
    _______, _______, _______, _______, _______, _______, _______,                            _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          _______, _______, _______,          _______, _______, _______,          _______, _______, _______, _______
  ),
  /* 
   * Sym
   */
  [_SYM] = LAYOUT(
    _______, _______   , _______, _______, _______, _______   , _______,                                _______, _______, _______, _______, _______, _______, _______,
    _______, KC_LCBR   , KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR   , _______,                                _______, _______, _______, _______, _______, _______, _______,
    _______, KC_DQUO   , KC_DLR , KC_PERC, KC_CIRC, KC_PLUS   , _______,                                _______, _______, _______, _______, _______, _______, _______,
    _______, KC_TILD   , KC_EXLM, KC_AT  , KC_HASH, KC_PIPE   , _______,                                _______, _______, _______, _______, _______, _______, _______,
    _______, _______   , _______, _______,          KC_LPRN   , KC_RPRN, KC_UNDS,              _______, _______, _______,          _______, _______, _______, _______
  ),
  /* 
   * Med
   */
  [_MED] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                        _______, _______   , _______          , _______        , _______, _______, _______,
    _______, QK_BOOT, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                        _______, _______   , _______          , _______        , _______, _______, _______,
    _______, _______, BL_TOGG, BL_BRTG, BL_UP  , BL_DOWN,_______,                        _______, KC_MPRV   , KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_MNXT, _______, _______,
    _______, _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI,_______,                        _______, _______   , _______          , _______        , _______, _______, _______,
    _______, _______, _______, _______,          _______,_______,_______,       KC_MSTP, KC_MPLY, KC_KB_MUTE,                    _______        , _______, _______, _______
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
    case BASE:
      if (record->event.pressed) {
         print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_BASE);
      }
      return false;
      break;
    case NUM:
      if (record->event.pressed) {
        layer_on(_NUM);
      } else {
        layer_off(_NUM);
      }
      return false;
      break;
    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
      } else {
        layer_off(_NAV);
      }
      return false;
      break;
    case SYM:
      if (record->event.pressed) {
        layer_on(_SYM);
      } else {
        layer_off(_SYM);
      }
      return false;
      break;
    case MED:
      if (record->event.pressed) {
        layer_on(_MED);
      } else {
        layer_off(_MED);
      }
      return false;
      break;
  }
  return true;
}
