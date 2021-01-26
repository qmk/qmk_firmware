// This is the default layout shipped with the Keyboardio atreus

#include QMK_KEYBOARD_H

enum {
  QWERTY,
  RAISE,
  LOWER
};

#define LW_ LOWER
#define RS_ RAISE

#define MOD_A    MT(MOD_LCTL, KC_A)
#define MOD_S    MT(MOD_LALT, KC_S)
#define MOD_D    MT(MOD_LGUI, KC_D)
#define MOD_F    MT(MOD_LSFT, KC_F)

#define MOD_J    MT(MOD_RSFT, KC_J)
#define MOD_K    MT(MOD_RGUI, KC_K)
#define MOD_L    MT(MOD_LALT, KC_L)
#define MOD_SCLN MT(MOD_RCTL, KC_SCLN)

#define L_SPC    LT(RS_, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWERTY] = LAYOUT_stacked
  (
      // left hand...
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      MOD_A,   MOD_S,   MOD_D,   MOD_F,   KC_G,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GRAVE,
      KC_ESC,  KC_TAB,  KC_LEFT, KC_RGHT, MO(LW_), KC_BSPC,
      // right hand...
               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
               KC_H,    MOD_J,   MOD_K,   MOD_L,   MOD_SCLN,
      KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
      KC_ENT,  L_SPC,   KC_UP,   KC_DOWN, KC_QUOT, KC_BSLS
  ),


  [RAISE] = LAYOUT_stacked
  (
      // left hand...
      KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,
      KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
      KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
      KC_MENU,KC_CAPS,  KC_LT,   KC_GT,   KC_DEL,  KC_TRNS,
      // right hand...
               KC_MINS, KC_KP_7, KC_KP_8, KC_KP_9, KC_ASTR,
               KC_DOT,  KC_KP_4, KC_KP_5, KC_KP_6, KC_PLUS,
      KC_TRNS, KC_AMPR, KC_KP_1, KC_KP_2, KC_KP_3, KC_BSLS,
      KC_TRNS, KC_UNDS, KC_TRNS, KC_TRNS, KC_KP_0, KC_EQL
  ),

  [LOWER] = LAYOUT_stacked
  (
      // left hand...
      KC_INS,  KC_HOME, ___,     KC_END,  KC_PGUP,
      KC_DEL,  ___,     ___,     ___,     KC_PGDN,
      ___,     ___,     ___,     ___,     ___,     ___,
      ___,     ___, KC__VOLDOWN,KC__VOLUP,___,     ___,
      // right hand...
               KC_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
               KC_DOWN, KC_F4,   KC_F5,   KC_F6,   KC_F11,
      ___,     ___,     KC_F1,   KC_F2,   KC_F3,   KC_F12,
      ___,     ___,     ___,     KC_PSCR, KC_SLCK, KC_MPLY
   ),

};
