// Personal keymap of khitsule

#include QMK_KEYBOARD_H

enum layers {
    ALPH,
    GAME,
    LOWR,
    RAIS,
    ADJS
};

// define any macros here to keep keymap clean and readable

#define KM_DLEFT LGUI(LCTL(KC_LEFT))
#define KM_DRIGHT LGUI(LCTL(KC_RIGHT))
#define TSKMGR LCTL(LSFT(KC_ESC))

#define tap_mod_macro(record, mod, macro) ( ((record)->event.pressed) ? \
     ( ((record)->tap.count <= 0 || (record)->tap.interrupted) ? MACRO(D(mod), END) : MACRO_NONE ) : \
     ( ((record)->tap.count > 0 && !((record)->tap.interrupted)) ? (macro) : MACRO(U(mod), END) ) )



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ALPH] = LAYOUT(
    KC_Q,    KC_W,     KC_E,     KC_R,           KC_T,                                               KC_Y,              KC_U,     KC_I,     KC_O,     KC_P,
    KC_A,    KC_S,     KC_D,     KC_F,           KC_G,                                               KC_H,              KC_J,     KC_K,     KC_L,     KC_SCLN,
    KC_Z,    KC_X,     KC_C,     KC_V,           KC_B,                                               KC_N,              KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,
    KC_ESC,  KC_TRNS,  KC_TRNS,  ALT_T(KC_ENT),  LT(LOWR, KC_TAB),  CTL_T(KC_SPC),  SFT_T(KC_BSPC),  LT(RAIS, KC_DEL),  KC_LGUI,  TO(GAME),  KC_QUOT,  KC_MINUS
  ),
  [GAME] = LAYOUT(
    KC_Q,    KC_W,     KC_E,     KC_R,      KC_T,                        KC_Y,    KC_U,     KC_I,     KC_O,     KC_P,
    KC_A,    KC_S,     KC_D,     KC_F,      KC_G,                           KC_H,    KC_J,     KC_K,     KC_L,     KC_SCLN,
    KC_Z,    KC_X,     KC_C,     KC_V,      KC_B,                                  KC_N,    KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,
    KC_ESC,  KC_TRNS,  KC_ENT,   KC_LALT,   KC_TAB,  KC_LCTL,  KC_LSFT,  KC_DEL,  KC_LGUI,  TO(ALPH),  KC_QUOT,  KC_MINUS
  ),
  [LOWR] = LAYOUT(
    KC_PSCR,   KC_HOME,    KC_UP,         KC_END,   KC_TRNS,                      KC_LPRN,        KC_F7,    KC_F8,    KC_F9,    KC_RPRN,
    KC_VOLU,   KC_LEFT,    KC_DOWN,       KC_RIGHT, KC_PGUP,                      KC_LBRC,        KC_F4,    KC_F5,    KC_F6,    KC_RBRC,
    KC_VOLD,   KC_MPRV,    KC_MPLY,       KC_MNXT,  KC_PGDN,                      LSFT(KC_LBRC),  KC_F1,    KC_F2,    KC_F3,    LSFT(KC_RBRC),
    KM_DLEFT,  KM_DRIGHT,  LALT(KC_TAB),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  MO(ADJS),        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),
  [RAIS] = LAYOUT(
    KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,     KC_PERC,                        KC_TRNS,   KC_7,     KC_8,  KC_9,    KC_TRNS,
    KC_CIRC,  KC_AMPR,  KC_GRV,   KC_TILD,    KC_PIPE,                        KC_PLUS,   KC_4,     KC_5,  KC_6,    KC_ASTR,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_BSLS,                        KC_MINUS,  KC_1,     KC_2,  KC_3,    KC_SLASH,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  MO(ADJS),  KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,  KC_0,  KC_DOT,  KC_EQL
  ),
  [ADJS] = LAYOUT(
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_F6,    KC_F7,     KC_F8,     KC_F9,   KC_F10,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      TSKMGR,   KC_TRNS,   KC_TRNS,   KC_F11,  KC_F12,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,
    RESET,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS
  )
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_MACRO_TAP(1),
  [2] = ACTION_MACRO_TAP(2)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case 1:
      return tap_mod_macro(record, LGUI, MACRO( D(LSFT), T(9), U(LSFT), END));
      break;
    case 2:
      return tap_mod_macro(record, LALT, MACRO( D(LSFT), T(0), U(LSFT), END));
      break;

  }
  return MACRO_NONE;
};
