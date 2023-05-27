#include QMK_KEYBOARD_H

// home row mod
#define HO_A MT(MOD_LCTL, KC_A)
#define HO_S MT(MOD_LSFT, KC_S)
#define HO_D MT(MOD_LALT, KC_D)
#define HO_F MT(MOD_LGUI, KC_F)
#define HO_J MT(MOD_RGUI, KC_J)
#define HO_K MT(MOD_RALT, KC_K)
#define HO_L MT(MOD_RSFT, KC_L)
#define HO_SCLN MT(MOD_RCTL, KC_SCLN)

// thumb
#define TH_NAV LT(NAV, KC_TAB) 
#define TH_NUM LT(NUM, KC_BSPC) 
#define TH_SYM LT(SYM, KC_ENT) 
#define TH_MED LT(MED, KC_ESC) 
#define TH_FUN LT(FUN, KC_DEL) 
#define TH_MOU LT(MOU, KC_SPC) 

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
  _BASE,
  _NAV,
  _NUM,
  _SYM,
  _MED,
  _FUN,
  _MOU,
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  NAV,
  NUM,
  SYM,
  MED,
  FUN,
  MOU,
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * BASE
 */
[_BASE] = LAYOUT_split_3x5_3(
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  HO_A,    HO_S,    HO_D,    HO_F,    KC_G,         KC_H,    HO_J,    HO_K,    HO_L,    HO_SCLN,
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                    TH_MED,  TH_NAV,  TH_MOU,       TH_SYM,  TH_NUM,  TH_FUN
),

/* 
 * NAV
 */
[_NAV] = LAYOUT(
  KC_PAGE_UP  , KC_HOME, KC_UP  , KC_END  , _______,      _______, KC_HOME, _______, KC_END  , KC_PAGE_UP  ,
  KC_PAGE_DOWN, KC_LEFT, KC_DOWN, KC_RIGHT, _______,      KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT, KC_PAGE_DOWN,
  _______     , _______, _______, _______ , _______,      _______, _______, _______, _______ , _______     ,
                    _______, _______ , _______,      _______, _______, _______
),
/* 
 * NUM
 */
[_NUM] = LAYOUT_split_3x5_3(
  KC_LBRC, KC_7   , KC_8   , KC_9   , KC_RBRC,      _______, _______, _______, _______, _______,
  KC_QUOT, KC_4   , KC_5   , KC_6   , KC_EQL ,      _______, _______, _______, _______, _______,
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_BSLS,      _______, _______, _______, _______, _______,
                    KC_DOT , KC_0   , KC_MINS,      _______, _______, _______
),
/* 
 * SYM
 */
[_SYM] = LAYOUT_split_3x5_3(
  KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,      _______, _______, _______, _______, _______,
  KC_DQT , KC_DLR , KC_PERC, KC_CIRC, KC_PLUS,      _______, _______, _______, _______, _______,
  KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_PIPE,      _______, _______, _______, _______, _______,
                    KC_LPRN, KC_RPRN, KC_UNDS,      _______, _______, _______
),
/*
 * MED
 */
[_MED] =  LAYOUT_split_3x5_3(
  _______, _______, _______, _______, _______,      _______, _______          , _______        , _______, _______,
  _______, _______, _______, _______, _______,      KC_MPRV, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_MNXT, _______,
  _______, _______, _______, _______, _______,      _______, _______          , _______        , _______, _______,
                    _______, _______, _______,      _______, _______          , _______
),
/* 
 * FUN
 */
[_FUN] = LAYOUT_split_3x5_3(
  KC_F12 , KC_F7  , KC_F8  , KC_F9  , KC_PSCR,      _______, _______, _______, _______, _______,
  KC_F11 , KC_F4  , KC_F5  , KC_F6  , KC_SCRL,      _______, _______, _______, _______, _______,
  KC_F10 , KC_F1  , KC_F2  , KC_F3  , KC_PAUS,      _______, _______, _______, _______, _______,
                    _______, _______, _______,      _______, _______, _______ 
),
/* 
 * MOU
 */
[_MOU] = LAYOUT_split_3x5_3(
  _______, _______, _______, _______, _______,      _______      , _______      , _______    , _______       , _______,
  _______, _______, _______, _______, _______,      KC_MS_LEFT   , KC_MS_DOWN   , KC_MS_UP   , KC_MS_RIGHT   , _______,
  _______, _______, _______, _______, _______,      KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, _______, 
                    _______, _______, _______,      KC_MS_BTN1   , KC_MS_BTN2   , KC_MS_BTN3
),
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_BASE);
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
    case NUM:
      if (record->event.pressed) {
        layer_on(_NUM);
      } else {
        layer_off(_NUM);
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
    case FUN:
      if (record->event.pressed) {
        layer_on(_FUN);
      } else {
        layer_off(_FUN);
      }
      return false;
      break;
    case MOU:
      if (record->event.pressed) {
        layer_on(_MOU);
      } else {
        layer_off(_MOU);
      }
      return false;
      break;
  }
  return true;
}
