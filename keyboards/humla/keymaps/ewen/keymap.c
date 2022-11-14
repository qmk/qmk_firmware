#include QMK_KEYBOARD_H
#include "keymap_steno.h"

enum layers {
    _QWERTY,
    _RAISE,
    _LOWER,
	_PLOVER
};

enum combo_events {
  COMBO_BSPC,
  COMBO_NUMBAK,
  COMBO_TAB,
  COMBO_ESC,
  COMBO_DEL,
  COMBO_QUES,
  COMBO_ENTER,
  COMBO_LMOUSE,
  COMBO_RMOUSE,
};

#define KC_CTSC RCTL_T(KC_SCLN)
#define LOWER_SPC LT(_LOWER, KC_SPC)
#define RASE_BACK LT(_RAISE, KC_BSPC)
#define SHFT_Z MT(MOD_LSFT, KC_Z)
#define SHIFT_SLASH MT(MOD_RSFT,KC_SLSH)
#define RASE_ENT LT(_RAISE, KC_ENT)
#define CTRL_A MT(MOD_LCTL,KC_A)
#define PREVWINDOW MT(MOD_LCTL, KC_LEFT)
#define NEXTWINDOW MT(MOD_LCTL, KC_RGHT)
#define TG_PLV TG(_PLOVER)
#define ST_GEM QK_STENO_GEMINI


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
     CTRL_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L, KC_CTSC,
     SHFT_Z,    KC_X,    KC_C,     KC_V,    KC_B,            KC_N,    KC_M, KC_COMM,  KC_DOT, SHIFT_SLASH,
                       MT(MOD_LGUI, KC_ESC), MT(MOD_LALT, KC_ENT), LT(_LOWER, KC_SPC),       LT(_RAISE, KC_SPC),     KC_LSFT, MT(MOD_RSFT, KC_TAB)
),
[_RAISE] = LAYOUT(
    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,		KC_6,    KC_7, 	  KC_8,    KC_9,    KC_0,
    KC_MUTE,KC_VOLD,KC_VOLU,KC_COPY,KC_PSTE,   	KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSLS,
    KC_NO,  KC_GRV, KC_F11, KC_F12, TG_PLV,  	KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DQUO,
     		    KC_TRNS,  KC_NO,  KC_NO,        KC_NO,   KC_NO,   KC_NO
),
[_LOWER] = LAYOUT(
       KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,             KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     			KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
       KC_CAPS, KC_LGUI, KC_INS,  KC_DEL,  KC_BSPACE, 			KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_QUOT,
                            _______,  KC_LGUI,  KC_ENT,         KC_BSPC,  KC_SPC, _______
),
[_PLOVER] = LAYOUT(
    STN_N1, STN_N2, STN_N3, STN_N4, STN_N4,              STN_N5, STN_N6, STN_N7, STN_N8, STN_N9,
    STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,      	     STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
    STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,  	         STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
     		   TG_PLV, STN_A , STN_O,                    STN_E,  STN_U,  STN_ST3
)
};

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_bspc[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_numbak[] = {KC_0, KC_9, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_E, KC_W, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_MINS, KC_EQL, COMBO_END};
const uint16_t PROGMEM combo_ques[] = {KC_COMM, KC_M, COMBO_END};
const uint16_t PROGMEM combo_enter[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_lmouse[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM combo_rmouse[] = {KC_H, KC_J, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
  [COMBO_NUMBAK] = COMBO(combo_numbak,KC_BSPC),
  [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
  [COMBO_DEL] = COMBO(combo_del,KC_DEL),
  [COMBO_QUES] = COMBO(combo_ques,KC_QUES),
  [COMBO_ENTER] = COMBO(combo_enter,KC_ENTER),
  [COMBO_LMOUSE] = COMBO(combo_lmouse,KC_BTN1),
  [COMBO_RMOUSE] = COMBO(combo_rmouse,KC_BTN1),
};
#endif

void matrix_init_user() {
  steno_set_mode(STENO_MODE_GEMINI);
}