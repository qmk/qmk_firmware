// Copyright 2026 Arthur Frangyan <https://github.com/ArthurFrangyan>

#include QMK_KEYBOARD_H


enum layers {
  _QWERTY,
  _GEMINI,
  _GAME_R, // qwerty without mod-tap
  _GAME,
  _GAME_2,
  _GAME_N, //numpad left hand
  _BRUSH,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MENU,
  _RREZ,
  _FN
};
bool menu_R = false;
uint8_t _PAD_index = _NUMPAD;
bool isSetOn = false;
#define buffMemory 10
uint16_t SetKey[buffMemory];
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  GEMINI,
  GAME,
  GAME_2,
  GAME_N, //numpad left hand for game
  GAME_R, // qwerty
  BRUSH,
  NUMPAD,
  LOWER,
  RAISE,
  ADJUST,
  LOWER_F,
  RAISE_F,
  MENU,
  MENU_R,
  GAME_X,
  PAD,
  M_F1,
  M_F2,
  M_F3,
  MKC_00,
  SET
};
#define GAME_R MO(_GAME_R)
#define C_BSPC C(KC_BSPC)
#define C_DEL C(KC_DEL)
#define C_DOWN C(KC_DOWN)
#define C_UP C(KC_UP)
#define C_RGHT C(KC_RGHT)
#define C_LEFT C(KC_LEFT)
#define A_DOWN A(KC_DOWN)
#define A_UP A(KC_UP)
#define A_RGHT A(KC_RGHT)
#define A_LEFT A(KC_LEFT)

#define SPC_LOW LT(_LOWER, KC_SPC)
#define ENT_SWP SH_T(KC_ENT)
#define TAB_SET LT(0, KC_TAB)

#define BSPC_LALT LALT_T(KC_BSPC)
#define TAB_ALT LALT_T(KC_TAB)

#define SPC_REZ LT(_RAISE, KC_SPC)
#define SPC_RSFT RSFT_T(KC_SPC)
#define DEL_RSFT RSFT_T(KC_DEL)
#define BSPC_RREZ LT(_RREZ, KC_BSPC)
#define BSPC_REZ LT(_RAISE, KC_BSPC)

#define F_ LSFT_T(KC_F)
#define D_ LCTL_T(KC_D)
#define S_ LALT_T(KC_S)
#define A_ LGUI_T(KC_A)
#define J_ RSFT_T(KC_J)
#define K_ RCTL_T(KC_K)
#define L_ RALT_T(KC_L)
#define SCLN_ RGUI_T(KC_SCLN)

#define ESC_M_ LT(_MENU, KC_ESC)
#define QUOT_ LT(_MENU, KC_QUOT)
#define PENT_M LT(_MENU, KC_PENT)
#define BSPC_M LT(_MENU, KC_BSPC)

#define V_ LT(_FN, KC_V)
#define Z_ LT(_ADJUST, KC_Z)
#define X_ LT(_RAISE, KC_X)
#define C_ LT(_LOWER, KC_C)
#define DOT_ LT(_RAISE, KC_DOT)
#define COMM_ LT(_LOWER, KC_COMM)

#define CngLngD S(KC_LALT) // LALT(KC_LSFT)
#define CngLngU RSFT(KC_LALT) // LALT(KC_RSFT)
#define CngLngG S(KC_LCTL)



#define F__ LT(0, KC_F)
#define D__ LT(0, KC_D)
#define S__ LT(0, KC_S)
#define A__ LT(0, KC_A)
#define J__ LT(0, KC_J)
#define K__ LT(0, KC_K)
#define L__ LT(0, KC_L)
#define SCLN__ LT(0, KC_SCLN)

void mod_modKey(uint8_t, uint8_t, bool, bool);
void modKey(uint8_t , uint8_t , bool);
bool pushSetKey(uint16_t);
bool popSetKey(uint16_t);
void normolizeMatrix(uint8_t* row, uint8_t* col);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MENU] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, EC_NORM, EC_SWAP, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, NK_OFF,  NK_ON,   XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, XXXXXXX, XXXXXXX, GEMINI,  LOWER_F, RAISE_F, GAME_R,  XXXXXXX,                                     XXXXXXX, GAME_R,  RAISE_F, LOWER_F, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, _______, PAD,     BRUSH,   NUMPAD,  QWERTY,  GAME,                                                          GAME,    QWERTY,  NUMPAD,  BRUSH,   PAD,     _______, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GAME_2,   XXXXXXX,  _______,               _______,  XXXXXXX,  GAME_2,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_CAPS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                                        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,                                     XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  ESC_M_,     A_,      S_,      D_,      F_,   KC_G,                                                          KC_H,       J_,      K_,      L_,     SCLN_,   QUOT_, KC_BSLS,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_LSFT,    Z_,      X_,      C_,      V_,   KC_B,     KC_MPLY,  MENU,                  MENU_R,   _______,  KC_N,    KC_M,      COMM_,    DOT_, KC_SLSH, KC_RSFT, KC_RCTL,
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_LWIN, KC_LALT, TAB_SET,   SPC_LOW, ENT_SWP, XXXXXXX,               KC_ENT, BSPC_RREZ,SPC_REZ,   DEL_RSFT,KC_RALT, KC_RWIN
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_GEMINI] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_CAPS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                                        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,                                     XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  BSPC_M,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_B,    KC_C,    KC_V,     KC_MPLY,  MENU,                  MENU_R,   _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RCTL,
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_LCTL, KC_LWIN, KC_V,      KC_C,    KC_V,    LOWER,                 RAISE,   KC_N,    KC_M,      KC_N,    KC_RALT, KC_RWIN
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),

  [_RREZ] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, MENU,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  _______,               _______,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,               XXXXXXX, _______, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     _______, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,                                     _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_PSCR, CngLngG, _______, C_LEFT,  C_RGHT,  _______, _______, _______,                                     _______, KC_PERC, KC_7,    KC_8,    KC_9,    KC_PSLS, KC_LBRC, KC_RBRC,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS, CngLngU, KC_PGUP, KC_LEFT, KC_RGHT, KC_UP,   KC_INS,                                                        KC_PMNS, KC_4,    KC_5,    KC_6,    KC_PAST, PENT_M,  _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, CngLngD, KC_PGDN, KC_HOME, KC_END,  KC_DOWN, _______,  _______,  _______,               _______,  _______,  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_PPLS, KC_EQL,  _______,
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_LWIN, KC_LCTL, KC_LALT,   _______, _______, _______,               _______, BSPC_RREZ,_______,  KC_0,    MKC_00,  KC_PDOT
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_NUMPAD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_TAB,  KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PERC, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P0,   KC_PSLS, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, ESC_M_,  KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PMNS,                                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PMNS, KC_PAST, KC_PIPE,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, KC_EQL,  KC_PPLS, KC_P1,   KC_P2,   KC_P3,   KC_PENT,  _______,  MENU,                  MENU_R,   _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PPLS, KC_PEQL, XXXXXXX,
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                XXXXXXX, XXXXXXX, KC_0,      SPC_LOW, _______, _______,               KC_ENT, BSPC_RREZ,SPC_REZ,   KC_PDOT, KC_P0,   KC_PDOT
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,                                     _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_GRV,  KC_PIPE, KC_MINS, KC_PLUS, KC_LPRN, KC_LBRC,                                                       KC_RBRC, KC_RPRN, KC_EQL,  KC_UNDS, KC_BSLS, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_TILD, _______, KC_LCBR, _______,  _______,  _______,               _______,  _______,  _______, KC_RCBR, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                _______, _______, _______,   _______, _______, _______,               _______, _______, _______,   _______, _______, _______
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, XXXXXXX, XXXXXXX, KC_MRWD, KC_MFFD, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, KC_CALC, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,                                                       XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, XXXXXXX,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX, KC_MSTP, KC_MPLY, KC_BRID, KC_BRIU, _______, XXXXXXX,  XXXXXXX,  _______,               _______,  XXXXXXX,  XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, XXXXXXX, 
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                XXXXXXX, XXXXXXX, XXXXXXX,   _______, _______, _______,               _______, _______, _______,   KC_LSFT, XXXXXXX, XXXXXXX
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_GAME] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX, KC_LWIN, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC, KC_CAPS, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        PAD,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  ESC_M_,  KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,                                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_B,    SH_MON,  KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,     _______,  MENU,                  MENU_R,   _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RCTL, 
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_B,    KC_G,    KC_LALT,   KC_SPC,  GAME_N,  KC_ENT,                KC_ENT,  BSPC_REZ, KC_SPC,   DEL_RSFT, XXXXXXX, XXXXXXX
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
 
  [_GAME_2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_DEL,  KC_LWIN, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC, KC_CAPS, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        PAD,     KC_Y,    KC_U,    KC_UP,   KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_G,    ESC_M_,  KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,                                                          KC_H,    KC_LEFT, KC_DOWN, KC_RGHT, KC_SCLN, KC_QUOT, KC_BSLS,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_B,    SH_MON,  KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,     _______,  MENU,                  MENU_R,   _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RCTL, 
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_B,    KC_G,    KC_LALT,   KC_SPC,  GAME_N,  KC_ENT,                _______, _______, KC_SPC,    KC_P0,   KC_PDOT, SH_MON
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_GAME_N] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_T,    _______,                                     _______, _______, _______, _______, _______, _______, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_G,                                                          _______, _______, _______, _______, _______, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_B,     _______,  _______,               _______,  _______,  _______, _______, _______, _______, _______, _______, _______, 
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                _______, _______, _______,   _______, _______, _______,               _______, _______, _______,   _______, _______, _______
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),

  [_BRUSH] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_CAPS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                                        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX,                                     KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  ESC_M_,  KC_A,    KC_S,       D_,      F_,   KC_G,                                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_MPLY,  MENU,                  MENU_R,   _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RCTL,
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_LWIN, SET,     KC_LALT,   KC_SPC,  ENT_SWP, LOWER,                 KC_ENT,  BSPC_RREZ,SPC_REZ,  DEL_RSFT,KC_RALT, KC_RWIN
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, MS_BTN4, MS_BTN5, MS_WHLU, _______,                                                       _______, _______, _______, _______, _______, _______, _______,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, MS_WHLD, _______,  XXXXXXX,  _______,               _______,  XXXXXXX,  _______, _______, _______, _______, _______, _______, _______, 
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                _______, _______, _______,   _______, _______, _______,               _______, _______, _______,   _______, _______, _______
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  ),
  [_GAME_R] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐                                   ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_CAPS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                                        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┤                                   ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,                                        KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┬────────┘                                   └────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC, ESC_M_,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
  //├────────├────────┼────────┼────────┼────────┼────────┼────────┤┌────────┐┌────────┐             ┌────────┐┌────────┐├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_MPLY,  MENU,                  GAME_R,   XXXXXXX,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RCTL,
  //└────────┴────────┴────────┼────────┴────────┴────────┴─┬──────┴┴┬───────┴┼────────┤             ├────────┼┴───────┬┴┴──────┬─┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_LWIN, SET,     KC_LALT,   KC_SPC,  ENT_SWP, LOWER,                 KC_ENT,  BSPC_RREZ,SPC_REZ,  DEL_RSFT,KC_RALT, KC_RWIN
  //                           └────────┴────────┴────────┘ └────────┴────────┴────────┘             └────────┴────────┴────────┘ └────────┴────────┴────────┘
  )
};

bool isSetKey(uint16_t);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(keycode == TAB_SET)
  {
    if(record->event.pressed)
    {
      if (!record->tap.count) {
        isSetOn = true;
      }
    }
    else
    {
      if (!record->tap.count) {
        isSetOn = false;
      }
    }
    return true;
  }
  else if(keycode == SET)
  {
    if(record->event.pressed)
    {
      isSetOn = true;
    }
    else
    {
      isSetOn = false;
    }
    return true;
  }
  if((isSetOn && record->event.pressed) || isSetKey(keycode))
  {
    uint8_t modIndex;
    uint8_t keyIndex = keycode;

    bool isKeyPressed = true;
    bool isKeyComplicated = true;

    uint8_t col = record->event.key.col;
    uint8_t row = record->event.key.row;
    normolizeMatrix(&row, &col);

    switch (keycode)
    {
      case F_:
        keyIndex = KC_F;
        break;
      case D_:
        keyIndex = KC_D;
        break;
      case S_:
        keyIndex = KC_S;
        break;
      case A_:
        keyIndex = KC_A;
        break;
      case C_:
        keyIndex = KC_C;
        break;
      case X_:
        keyIndex = KC_X;
        break;
      case V_:
        keyIndex = KC_V;
        break;

      case J_:
        keyIndex = KC_J;
        break;
      case K_:
        keyIndex = KC_K;
        break;
      case L_:
        keyIndex = KC_L;
        break;
      case SCLN_:
        keyIndex = KC_SCLN;
        break;
      case COMM_:
        keyIndex = KC_COMM;
        break;
      case DOT_:
        keyIndex = KC_DOT;
        break;
      case ESC_M_:
        keyIndex = (uint8_t)KC_ESC;
        break;
      default:
        isKeyComplicated = false;
        break;
    }
    if(row < 4)
    {
      switch (col)
      {
        case 0:
        case 1:
        case 2:
          modIndex = KC_LWIN;
          break;
        case 3:
          modIndex = KC_LALT;
          break;
        case 4:
          modIndex = KC_LCTL;
          break;
        case 5:
        case 6:
          modIndex = KC_LSFT;
          break;
        default:
          isKeyPressed = false;
          break;
      }
    }
    else if(row > 4 && row < 9)
    {
      switch (col)
      {
        case 0:
        case 1:
        case 2:
          modIndex = KC_RWIN;
          break;
        case 3:
          modIndex = KC_RALT;
          break;
        case 4:
          modIndex = KC_RCTL;
          break;
        case 5:
        case 6:
          modIndex = KC_RSFT;
          break;
        default:
          isKeyPressed = false;
          break;
      }
    }
    else
    {
      isKeyPressed = false;
    }
    if(isKeyPressed)
    {
      bool success;
      if(record->event.pressed)
      {
        success = pushSetKey(keycode);
      }
      else
      {
        success = popSetKey(keycode);
      }
      if(success)
      {
        if((row == 2 || row == 7) && col > 1 && col < 6 && isKeyComplicated)
        {
          // modKey(modIndex, keyIndex, record->event.pressed);
          mod_modKey(modIndex, keyIndex, record->event.pressed, record->tap.count);
        }
        else
        {
          modKey(modIndex, keyIndex, record->event.pressed);
        }
        return false;
      }
    }
  }
  switch (keycode) {
    case MKC_00:
      if (record->event.pressed) {
        tap_code(KC_0);
        tap_code(KC_0);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        _PAD_index = _NUMPAD;
        set_single_persistent_default_layer(_QWERTY);
        layer_clear();
      }
      return false;
    case GEMINI:
      if (record->event.pressed) {
        // set_single_persistent_default_layer(_GEMINI);

        layer_move(_GEMINI);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        // layer_off(_SWP_HND);
      }
      return false;
    case SPC_LOW:
    case C_:
    case COMM_:
      if(record->event.pressed)
      {
        if (!record->tap.count) {
          layer_on(_LOWER);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
          layer_off(_LOWER);
        }
      }
      else
      {
        if (!record->tap.count) {
          layer_off(_LOWER);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
          layer_off(_LOWER);
        }
      }
      return true;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case SPC_REZ:
    case BSPC_REZ:
    case X_:
    case DOT_:
      if(record->event.pressed)
      {
        if (!record->tap.count) {
          layer_on(_RAISE);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
          layer_off(_RAISE);
        }
      }
      else
      {
        if (!record->tap.count) {
          layer_on(_RAISE);
          update_tri_layer(_LOWER, _RAISE, _ADJUST);
          layer_off(_RAISE);
        }
      }
      return true;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
    case MENU:
      if (record->event.pressed) {
        layer_on(_MENU);
      }
      else{
        layer_off(_MENU);
      }
      return false;
   case MENU_R:
      if (record->event.pressed) {
        layer_on(_MENU);
        menu_R = true;
      }
      else{
        layer_off(_MENU);
        menu_R = false;
      }
      return false;
    case GAME:
      if (record->event.pressed) {
        _PAD_index = _GAME;
        layer_move(_GAME);
      }
      return false;
    case GAME_2:
      if (record->event.pressed) {
        _PAD_index = _GAME_2;
        layer_move(_GAME_2);
      }
      return false;
    case GAME_N:
      if (record->event.pressed) {
        layer_on(_GAME_N);
      } else {
        layer_off(_GAME_N);
      }
      return false;
    case GAME_R:
      if (record->event.pressed) {
        layer_move(_GAME_R);
      }
      return false;
    case NUMPAD:
      if (record->event.pressed) {
        layer_move(_NUMPAD);
      }
      return false;
    case BRUSH:
      if (record->event.pressed) {
        layer_move(_BRUSH);
      }
      return false;
    case LOWER_F:
      if (record->event.pressed) {
        layer_move(_LOWER);
      }
      return false;
    case RAISE_F:
      if (record->event.pressed) {
        layer_move(_RAISE);
      }
      return false;
    case PAD:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_PAD_index))
          layer_off(_PAD_index);
        else
          layer_on(_PAD_index);
      }
      return false;
  }
    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(MS_WHLL, MS_WHLR)  },
    [_MENU] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_BRID, KC_BRIU)  },
    [_LOWER] = { ENCODER_CCW_CW(KC_DOWN, KC_UP),  ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)  },
    [_RAISE] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU),  ENCODER_CCW_CW(_______, _______)  },
    [_ADJUST] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [_GEMINI] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [_GAME_R] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [_GAME] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [_GAME_2] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [_GAME_N] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [_BRUSH] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [_NUMPAD] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [_RREZ] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [_FN] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
};
#endif

void mod_modKey(uint8_t mod, uint8_t key, bool isPressed, bool isTapped)
{
  if(isPressed)
  {
    if (isTapped) {
      register_code(mod);
      register_code(key);
    }
    else
    {
      register_code(mod);
    }
  }
  else
  {
    if (isTapped) {
      unregister_code(mod);
      unregister_code(key);
    }
    else
    {
      unregister_code(mod);
    }
  }
}

void modKey(uint8_t mod, uint8_t key, bool isPressed)
{
  if(isPressed)
  {
    register_code(mod);
    register_code(key);
  }
  else
  {
    unregister_code(mod);
    unregister_code(key);
  }
}

void normolizeMatrix(uint8_t* row, uint8_t* col)
{
  if(*row == 4 && *col == 7)
  {
    *row = 3;
    *col = 8;
  }
  else if(*row == 9 && *col == 6)
  {
    *col = 8;
  }
  else if(*row == 4)
  {
    if(*col == 0 || *col == 1)
      *col += 1;
    *col += 2;
  }
  else if(*row == 9)
  {
    *col+=3;
  }

}
bool pushSetKey(uint16_t value)
{
  for (int i = 0; i < buffMemory; ++i)
  {
    if(SetKey[i] == 0)
    {
      SetKey[i] = value;
      return true;
    }
  }
  return false;
}

bool popSetKey(uint16_t value)
{
  for (int i = 0; i < buffMemory; ++i)
  {
    if(SetKey[i] == value)
    {
      SetKey[i] = 0;
      return true;
    }
  }
  return false;
}

bool isSetKey(uint16_t value)
{
  for (int i = 0; i < buffMemory; ++i)
  {
    if(SetKey[i] == value)
    {
      return true;
    }
  }
  return false;
}