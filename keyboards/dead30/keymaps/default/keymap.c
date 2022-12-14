#include QMK_KEYBOARD_H
#include "dead30.h"

#undef TAPPING_TERM
#define TAPPING_TERM 120

//Tap Dance Declarations
enum {
  B_SPACE = 0,
  N_ENTER,
  V_ALT,
  C_LGUI,
  COMM_GRV
};


#define FN1_SPC     LT(1, KC_SPC)
#define FN2_BSPC    LT(2, KC_BSPC)
#define FN3_C       LT(3, KC_C)
#define FN4_V       LT(4, KC_V)
#define FN5_B       LT(5, KC_B)
#define CTL_Z       CTL_T(KC_Z)
#define ALT_X       ALT_T(KC_X)
#define ALT_N       ALGR_T(KC_N)
#define CTL_M       RCTL_T(KC_M)
#define SFT_ENT     RSFT_T(KC_ENT)

#define KC_CUT   LCTL(KC_X)
#define KC_COPY  LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)
#define KC_UNDO  LCTL(KC_Z)
#define KC_REDO  LCTL(KC_Y)
// Home row and modifiers
#define LT2_A    LT(2,KC_A)
#define LSFT_S   LSFT_T(KC_S)
#define LSFT_W   LSFT_T(KC_W)
#define ALT_BSP  LALT_T(KC_BSPC)
#define LT3_D    LT(3,KC_D)
#define LCTL_F   LCTL_T(KC_F)
#define LCTL_R   LCTL_T(KC_R)
#define RCTL_J   RCTL_T(KC_J)
#define LT5_K    LT(5,KC_K)
#define RSFT_L   RSFT_T(KC_L)
#define LSFT_KP  LSFT_T(KC_CAPS)
#define LCTL_SP  LCTL_T(KC_SPC)
#define LT3_SPC  LT(3,KC_SPC)
#define LT3_ENT  LT(3,KC_ENT)
#define LT1_DEL  LT(1,KC_DEL)
#define LT6_GRV  LT(6,KC_GRV)
#define CTL_ENT  LCTL_T(KC_ENT)
#define LGU_ESC  LGUI_T(KC_ESC)
#define ALT_BSP  LALT_T(KC_BSPC)

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Tab, twice for Escape
  [B_SPACE] = ACTION_TAP_DANCE_DOUBLE(KC_B, KC_SPC),
  [N_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_N, KC_ENT),
  [V_ALT]   = ACTION_TAP_DANCE_DOUBLE(KC_V, KC_LALT),
  [C_LGUI]  = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_LGUI),
  [COMM_GRV]= ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_GRAVE)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐                               ┌───┐
     * │ A │                               │ Z │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x10_dead30(
        KC_ESC, XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX,     XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX, KC_BSPC,
        KC_Q,   KC_W,    KC_E,       KC_R,      KC_T,        KC_Y,        KC_U,    KC_I,         KC_O,    KC_P,
        LT2_A,  LSFT_S,  LT3_D,      LCTL_F,    KC_G,        KC_H,        RCTL_J,  LT5_K,        RSFT_L,  KC_SCLN,
        KC_Z,   KC_X,    TD(C_LGUI), TD(V_ALT), TD(B_SPACE), TD(N_ENTER), KC_M,    TD(COMM_GRV), KC_DOT,  KC_SLSH
        //CTL_Z,  ALT_X,   FN3_C,   FN4_V,   FN1_SPC, FN2_BSPC,FN5_B,   ALT_N,   CTL_M,   SFT_ENT
    ),

    [1] = LAYOUT_ortho_4x10_dead30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______
    ),

    [2] = LAYOUT_ortho_4x10_dead30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, KC_GRV,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [3] = LAYOUT_ortho_4x10_dead30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        KC_TAB,  _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, KC_SCLN, KC_QUOT,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [4] = LAYOUT_ortho_4x10_dead30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        KC_TAB,  _______, _______, _______, _______, KC_LABK, KC_RABK, KC_QUES, KC_COLN, KC_DQUO,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),

    [5] = LAYOUT_ortho_4x10_dead30(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_CALC, KC_WHOM, KC_MAIL, KC_MYCM, _______, _______, _______, _______, _______, KC_PSCR,
        _______, _______, _______, _______, _______, _______, _______, _______, BL_DEC,  BL_INC,
        _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______
    )
};
