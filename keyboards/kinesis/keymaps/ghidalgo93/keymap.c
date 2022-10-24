#include QMK_KEYBOARD_H

// #define QWERTY 0 // Base qwerty
enum layers {
    _QWERTY = 0,
    _NAV,
    _RSYM,
    _LSYM,
    _NUM,
    _ALWAYS
};

// Left-hand mods
#define GUI_A LGUI_T(KC_A)
#define CTL_S LCTL_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define RSYM_F LT(_RSYM, KC_F)
#define ALT_Z LALT_T(KC_Z)
#define NAV MO(_NAV)

// Right-hand mods
#define LSYM_J LT(_LSYM, KC_J)
#define SFT_K RSFT_T(KC_K)
#define CTL_L LCTL_T(KC_L)
#define GUI_SCLN LGUI_T(KC_SCLN)
#define ALT_SLSH LALT_T(KC_SLSH)
#define ALW_SPC LT(_ALWAYS, KC_SPC)
#define NUM MO(_NUM)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_pretty(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_NO,    QK_BOOT,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                                                                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                                                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     XXXXXXX,
    XXXXXXX,  GUI_A,    CTL_S,    SFT_D,    RSYM_F,   KC_G,                                        				 KC_H,     LSYM_J,   SFT_K,    CTL_L,    GUI_SCLN, XXXXXXX,
    XXXXXXX,  ALT_Z,    KC_X,     KC_C,     KC_V,     KC_B,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   ALT_SLSH, XXXXXXX,
                   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,                                                                      XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                               XXXXXXX,
                                            KC_BSPC,  NAV,      XXXXXXX,                                               XXXXXXX,  NUM,        ALW_SPC
  ),

  [_NAV] = LAYOUT_pretty(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______, 									 _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                     				 _______,  KC_PGDN,  KC_PGUP,  _______,  KC_DEL,   _______, 
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,             					                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, 
    _______, _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, 	      								 _______, KC_END,  KC_HOME, _______, _______, _______, 
                 XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,                                                                      XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                               XXXXXXX,
                                            _______,  _______,  _______,                                               _______,  _______,  _______ 
  ),

  [_RSYM] = LAYOUT_pretty(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______, 									 _______,  _______,  _______,  _______,  _______,  _______,
    _______, _______, _______, _______, _______, _______,                                     					 _______, KC_TILD, KC_SLSH, KC_QUOT, _______, _______, 
    _______, KC_CIRC, KC_ASTR, KC_AMPR, XXXXXXX, _______,                                     					 KC_HASH, KC_MINS, KC_PIPE, KC_DQUO, KC_DLR,  _______,
    _______, _______, _______, _______, _______, _______, 									 _______, KC_UNDS, KC_BSLS, KC_GRV,  _______, _______,
                   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,                                                                      XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                               XXXXXXX,
                                            _______,  _______,  _______,                                               _______,  _______,  _______ 
  ),

  [_LSYM] = LAYOUT_pretty(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______, 									 _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______, 									 _______,  _______,  _______,  _______,  _______,  _______,
    _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AT,                                       					 _______, XXXXXXX, KC_EQL,  KC_PPLS, KC_PERC, _______, 
    _______, _______, KC_EXLM, KC_LBRC, KC_RBRC, _______,  									 _______, _______, _______, _______, _______, _______,  
                   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,                                                                      XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                               XXXXXXX,
                                            _______,  _______,  _______,                                               _______,  _______,  _______ 
  ),

  [_NUM] = LAYOUT_pretty(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______, 									 _______,  _______,  _______,  _______,  _______,  _______, 
    _______,  _______,  _______,  _______,  _______,  _______, 									 _______,  _______,  _______,  _______,  _______,  _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        					 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, 
    _______,  _______,  _______,  _______,  _______,  _______, 									 _______,  _______,  _______,  _______,  _______,  _______,
                   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,                                                                      XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                               XXXXXXX,
                                            _______,  _______,  _______,                                               _______,  XXXXXXX,  _______ 
  ),

  [_ALWAYS] = LAYOUT_pretty(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______, 									 _______,  _______,  _______,  _______,  _______,  _______,
    _______, _______, _______, KC_COLN, KC_ESC,  _______,                                     					 _______, _______, _______, _______, _______, _______,
    _______, _______, KC_PERC, KC_SLSH, KC_ENT,  _______,                                     					 _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_EXLM, _______, 									 _______, _______, _______, _______, _______, _______,
                   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,                                                                      XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                      XXXXXXX,  XXXXXXX,                                               XXXXXXX,  XXXXXXX,
                                                                XXXXXXX,                                               XXXXXXX,
                                            KC_TAB,   _______,  _______,                                               _______,  _______, XXXXXXX
  ),
};
