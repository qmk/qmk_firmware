/* Vault 45 Default */
#include QMK_KEYBOARD_H
enum layers{
  BASE,
  NUM,
  SYM,
  META
};

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, KC_F5,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOTE,          LT(SYM, KC_ENT),
    RCTL_T(S(KC_9)),        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          S(KC_0),
         LALT(KC_TAB), LALT(KC_TAB),      MO(1), SFT_T(KC_BSPC), KC_SPACE,  KC_SPACE,  MO(2),            KC_LGUI, G(KC_TAB)
  ),

  [NUM] = LAYOUT(
    KC_TRNS,    KC_PGUP,    KC_HOME,    KC_UP,    KC_END,    KC_WBAK,    KC_PSLS,    KC_7,    KC_8,    KC_9,    KC_PMNS,    KC_DEL,    RESET,
    KC_TRNS,    KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_WFWD,    KC_PAST,    KC_4,    KC_5,    KC_6,    KC_PPLS,             KC_TRNS,
    KC_LBRC,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_0,    KC_1,    KC_2,    KC_3,    KC_PDOT,             KC_RBRC,
        KC_PSCR,     KC_TRNS,            KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,  S(KC_RCTRL),        RALT(KC_F4), RALT(KC_F4)
  ),
  
  [SYM] = LAYOUT(
    RGB_TOG,      S(KC_GRV),    KC_GRV,    KC_BSLS,    S(KC_BSLS),    KC_TRNS,    KC_TRNS,    S(KC_MINS),    KC_EQL,    KC_TRNS,    C(KC_W),    C(KC_T),   KC_TRNS,
    KC_TRNS,    S(KC_1),    S(KC_2),    S(KC_3),    S(KC_4),    S(KC_5),    S(KC_6),    S(KC_7),    S(KC_8),    KC_SCLN,    S(KC_SCLN),          KC_TRNS,
    S(KC_LBRC),    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,             S(KC_RBRC),
          KC_TRNS,    KC_TRNS,           KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS, KC_CAPSLOCK,        KC_NUMLOCK,    KC_TRNS
  ),

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP); 
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN); 
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}

enum combos {
  KL_SLSH,
  JK_MINUS
};

const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [KL_SLSH] = COMBO(kl_combo, S(KC_SLSH)),
  [JK_MINUS] = COMBO(jk_combo, KC_MINUS)
};
