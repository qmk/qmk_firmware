#include QMK_KEYBOARD_H

#define HO_A MT(MOD_LCTL, KC_A)
#define HO_S MT(MOD_LSFT, KC_S)
#define HO_D MT(MOD_LALT, KC_D)
#define HO_F MT(MOD_LGUI, KC_F)
#define HO_J MT(MOD_RGUI, KC_J)
#define HO_K MT(MOD_RALT, KC_K)
#define HO_L MT(MOD_RSFT, KC_L)
#define HO_SCLN MT(MOD_RCTL, KC_SCLN)

enum layer_number {
    _BASE = 0,
    _NAV,
    _NUM,
    _SYM,
    _MED,
    _FUN,
    _MOU,
};

#define TH_NAV LT(_NAV, KC_TAB)
#define TH_NUM LT(_NUM, KC_BSPC)
#define TH_SYM LT(_SYM, KC_ENT)
#define TH_MED LT(_MED, KC_ESC)
#define TH_FUN LT(_FUN, KC_DEL)
#define TH_MOU LT(_MOU, KC_SPC)

enum combos {
    QW_ESC,
    COMBO_LENGTH,
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[] = {
    [QW_ESC] = COMBO(qw_combo, KC_ESC),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * BASE
   */
  [_BASE] = LAYOUT_split_3x6_3(
  _______, KC_Q, KC_W, KC_E  , KC_R  , KC_T  ,     KC_Y  , KC_U  , KC_I   , KC_O  , KC_P   , _______,
  _______, HO_A, HO_S, HO_D  , HO_F  , KC_G  ,     KC_H  , HO_J  , HO_K   , HO_L  , HO_SCLN, _______,
  _______, KC_Z, KC_X, KC_C  , KC_V  , KC_B  ,     KC_N  , KC_M  , KC_COMM, KC_DOT, KC_SLSH, _______,
                       TH_MED, TH_NAV, TH_MOU,     TH_SYM, TH_NUM, TH_FUN
  ),
  /* 
  * NAV
  */
  [_NAV] = LAYOUT_split_3x6_3(
    _______, KC_PAGE_UP  , KC_HOME, KC_UP  , KC_END  , _______,      _______, KC_HOME, _______, KC_END  , KC_PAGE_UP  , _______,
    _______, KC_PAGE_DOWN, KC_LEFT, KC_DOWN, KC_RIGHT, _______,      KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT, KC_PAGE_DOWN, _______,
    _______, _______     , _______, _______, _______ , _______,      _______, _______, _______, _______ , _______     , _______,
                                    _______, _______ , _______,      _______, _______, _______
  ),
  /* 
  * NUM
  */
  [_NUM] = LAYOUT_split_3x6_3(
    _______, KC_LBRC, KC_7   , KC_8   , KC_9   , KC_RBRC,      _______, _______, _______, _______, _______, _______,
    _______, KC_QUOT, KC_4   , KC_5   , KC_6   , KC_EQL ,      _______, _______, _______, _______, _______, _______,
    _______, KC_GRV , KC_1   , KC_2   , KC_3   , KC_BSLS,      _______, _______, _______, _______, _______, _______,
                               KC_DOT , KC_0   , KC_MINS,      _______, _______, _______
  ),
  /* 
  * SYM
  */
  [_SYM] = LAYOUT_split_3x6_3(
    _______, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,      _______, _______, _______, _______, _______, _______,
    _______, KC_DQT , KC_DLR , KC_PERC, KC_CIRC, KC_PLUS,      _______, _______, _______, _______, _______, _______,
    _______, KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_PIPE,      _______, _______, _______, _______, _______, _______,
                               KC_LPRN, KC_RPRN, KC_UNDS,      _______, _______, _______
  ),
  /*
  * MED
  */
  [_MED] =  LAYOUT_split_3x6_3(
    _______, QK_BOOT, _______, _______, _______, _______,      _______, _______          , _______        , _______, _______, _______,
    _______, _______, _______, _______, _______, _______,      KC_MPRV, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_MNXT, _______, _______,
    _______, _______, _______, _______, _______, _______,      _______, _______          , _______        , _______, _______, _______,
                               _______, _______, _______,      KC_MSTP, KC_MPLY          , KC_KB_MUTE     
  ),
  /* 
  * FUN
  */
  [_FUN] = LAYOUT_split_3x6_3(
    _______, KC_F12 , KC_F7  , KC_F8  , KC_F9  , KC_PSCR,      _______, _______, _______, _______, _______, _______,
    _______, KC_F11 , KC_F4  , KC_F5  , KC_F6  , KC_SCRL,      _______, _______, _______, _______, _______, _______,
    _______, KC_F10 , KC_F1  , KC_F2  , KC_F3  , KC_PAUS,      _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,      _______, _______, _______ 
  ),
  /* 
  * MOU
  */
  [_MOU] = LAYOUT_split_3x6_3(
    _______, _______, _______, _______, _______, _______,      _______      , _______      , _______    , _______       , _______, _______,
    _______, _______, _______, _______, _______, _______,      KC_MS_LEFT   , KC_MS_DOWN   , KC_MS_UP   , KC_MS_RIGHT   , _______, _______,
    _______, _______, _______, _______, _______, _______,      KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, _______, _______,
                               _______, _______, _______,      KC_MS_BTN1   , KC_MS_BTN2   , KC_MS_BTN3
  ),
};
