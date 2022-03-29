#include QMK_KEYBOARD_H

#define SPC_FN(LY) LT(LY, KC_SPC)

enum LAYERS {
  GAMING, // Simpler control scheme for games (e.g. space is just space)
  BASE, // All the bells and whistles for coding.
  FN, // Function keys (e.g. screen brightness, media keys)
  MS, // Mouse buttons and movements.
  KBD_CTRLS, // Controls for the keyboard itself (e.g. brightness, colours)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [GAMING] = LAYOUT_all(
      KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_NO,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      MO(MS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, DF(BASE),
      KC_LCTL, KC_LGUI, KC_LALT,                             KC_SPC,                      KC_RALT, MO(KBD_CTRLS), KC_RCTL
    ),
  [BASE] = LAYOUT_all(
      KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_NO,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      MO(MS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, DF(GAMING),
      KC_LCTL, KC_LGUI, KC_LALT,                             SPC_FN(FN),                      KC_RALT, MO(KBD_CTRLS), KC_RCTL
    ),
  [FN] = LAYOUT_all(
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_NO,
      KC_TRNS, KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_PGUP, KC_TRNS,
      KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_WWW_HOME, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS
    ),
  [MS] = LAYOUT_all(
      KC_GRV, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2,                             KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS
    ),
  [KBD_CTRLS] = LAYOUT_all(
      KC_GRV, EF_DEC, EF_INC, H1_DEC, H1_INC, H2_DEC, H2_INC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BR_DEC, BR_INC, KC_TRNS, KC_NO,
      KC_TRNS, KC_TRNS, KC_TRNS, S1_DEC, S1_INC, S2_DEC, S2_INC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ES_DEC, ES_INC, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS
    ),
};


