#include QMK_KEYBOARD_H

#define ST_BOLT QK_STENO_BOLT
#define ST_GEM  QK_STENO_GEMINI

enum keyboard_layers {
  _QWERTY,
  _RAISE,
  _LOWER,
  _PLOVER,
  _ADJUST
};

#define ADJ_Z   LT(_ADJUST, KC_Z)
#define RS_BSPC LT(_RAISE, KC_BSPC)
#define LW_SPC LT(_LOWER, KC_SPC)
#define MO_ADJ  MO(_ADJUST)
#define TG_PLV  TG(_PLOVER)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ortho_3x10(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_RSFT,
    ADJ_Z,   KC_X,    KC_C,    KC_V,    RS_BSPC, LW_SPC,  KC_B,    KC_N,    KC_M,    KC_ENT
  ),

  [_RAISE] = LAYOUT_ortho_3x10(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_ESC,  KC_MINS, KC_EQL,  _______, KC_LBRC, KC_RBRC, _______, KC_QUOT, KC_SCLN, _______,
    OS_LCTL, OS_LGUI, OS_LALT, KC_GRV,  _______, KC_TAB,  KC_BSLS, KC_COMM, KC_DOT,  KC_SLSH
  ),

  [_LOWER] = LAYOUT_ortho_3x10(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX,
    KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______,
    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______, OS_LALT, OS_LGUI, OS_LCTL, KC_CAPS
  ),

  [_PLOVER] = LAYOUT_ortho_3x10(
    STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
    STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
    MO_ADJ,  STN_NUM, STN_A,   STN_O,   STN_NUM, STN_E,   STN_U,   STN_NUM, STN_NUM, XXXXXXX
  ),

  [_ADJUST] = LAYOUT_ortho_3x10(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ST_BOLT, ST_GEM,  TG_PLV,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT
  ),

};
