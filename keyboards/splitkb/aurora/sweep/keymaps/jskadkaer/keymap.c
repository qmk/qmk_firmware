#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
      * │  Q  │  W  │  F  │  P  │  G  │       │  J  │  L  │  U  │  Y  │  T  │
      * │ Alt │     │     │     │     │       │     │     │     │     │ Alt │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │  A  │  R  │  S  │  T  │  D  │       │  H  │  N  │  E  │  I  │  O  │
      * │ Sft │     │     │     │     │       │     │     │     │     │ Sft │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │  Z  │  X  │  C  │  V  │  B  │       │  K  │  M  │  ,  │  .  │  /  │
      * │ Ctl │     │     │     │     │       │     │     │     │     │ Ctl │
      * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
      *
      *                     ┌─────┐               ┌─────┐
      *                     │ Tab ├─────┐   ┌─────┤ Ent │
      *                     │Layr3│ Spc │   │ Bsp │     │
      *                     └─────┤Layr1│   │Layr2├─────┘
      *                           └─────┘   └─────┘
      */
	[0] = LAYOUT(                 ALT_T(KC_Q), KC_W, KC_F, KC_P, KC_G,       KC_J, KC_L, KC_U, KC_Y, RALT_T(KC_SCLN),
	                              SFT_T(KC_A), KC_R, KC_S, KC_T, KC_D,       KC_H, KC_N, KC_E, KC_I, SFT_T(KC_O),
	                              CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B,       KC_K, KC_M, KC_COMM, KC_DOT, CTL_T(KC_SLSH),
	                                       LT(4,KC_TAB), LT(2,KC_SPC),       LT(3,KC_BSPC), GUI_T(KC_ENT)),
     /*
      * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
      * │  T  │  Q  │  W  │  E  │  R  │       │  Y  │  U  │  I  │  O  │  P  │
      * │ Alt │     │     │     │     │       │     │     │     │     │ Alt │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │  G  │  A  │  S  │  D  │  F  │       │  H  │  J  │  K  │  L  │  ;  │
      * │ Sft │     │     │     │     │       │     │     │     │     │ Sft │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │  Z  │  X  │  C  │  V  │  B  │       │  N  │  M  │  ,  │  .  │  /  │
      * │ Ctl │     │     │     │     │       │     │     │     │     │ Ctl │
      * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
      *
      *                     ┌─────┐               ┌─────┐
      *                     │ Tab ├─────┐   ┌─────┤ Ent │
      *                     │Layr3│ Spc │   │ Bsp │     │
      *                     └─────┤Layr1│   │Layr2├─────┘
      *                           └─────┘   └─────┘
      */
	[1] = LAYOUT(                 ALT_T(KC_T), KC_Q, KC_W, KC_E, KC_R,       KC_Y, KC_U, KC_I, KC_O, ALT_T(KC_P),
	                              SFT_T(KC_G), KC_A, KC_S, KC_D, KC_F,       KC_H, KC_J, KC_K, KC_L, SFT_T(KC_SCLN),
	                              CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, CTL_T(KC_SLSH),
                                                 LT(4,KC_TAB), KC_SPC,       LT(3,KC_BSPC), GUI_T(KC_ENT)),
     /*
      * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
      * │SW_UP│ MS2 │MS_UP│ MS1 │Vol_+|       │ PGUP| HOME│  UP │ END │ DEL │
      * │ Alt │     │     │     │     │       │     │     │     │     │     │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │SW_DN│MS_LF│MS_DN│MS_RH│Vol_-│       │ GUI │ LEFT│ DOWN│ RGHT│ Spc |
      * │ Sft │     │     │     │     │       │     │     │     │     │     │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │Reset│ERRST│ PRV │ NXT │ PLY │       │ PGDN│     │     │     │ MENU│
      * │ Ctl │     │     │     │     │       │     │     │     │     │     │
      * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
      *
      *                     ┌─────┐               ┌─────┐
      *                     │ Tab ├─────┐   ┌─────┤ Ent │
      *                     │Layr3│     │   │ Bsp │     │
      *                     └─────┤     │   │Layr2├─────┘
      *                           └─────┘   └─────┘
      */

	[2] = LAYOUT(  ALT_T(KC_WH_U), KC_BTN2, KC_MS_U, KC_BTN1, KC_VOLU,       KC_PGUP, KC_HOME, KC_UP, KC_END, KC_DEL,
	               SFT_T(KC_WH_D), KC_MS_L, KC_MS_D, KC_MS_R, KC_VOLD,       KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,
	                CTL_T(QK_BOOT), EE_CLR, KC_MPRV, KC_MNXT, KC_MPLY,       KC_PGDN, KC_NO, KC_NO, KC_NO, KC_APP,
	                                                   KC_TRNS, KC_NO,       KC_TRNS, KC_TRNS),
     /*
      * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
      * │ Esc │  {  │  [  │  (  │  ~  |       │  ^  |  )  │  ]  │  }  │  `  │
      * │ Alt │     │     │     │     │       │     │     │     │     │     │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │  -  │  *  │  =  │  _  │  $  │       │     │     │     │     │ Bsp |
      * │ Sft │     │     │     │     │       │     │     │     │     │     │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │  +  │  |  │  \  │  '  │  #  │       │  %  │  @  │  &  │  ?  │  !  │
      * │ Ctl │     │     │     │     │       │     │     │     │     │     │
      * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
      *
      *                     ┌─────┐               ┌─────┐
      *                     │ Tab ├─────┐   ┌─────┤ Ent │
      *                     │Layr3│ Spc │   │     │     │
      *                     └─────┤Layr1│   │     ├─────┘
      *                           └─────┘   └─────┘
      */
    [3] = LAYOUT(   ALT_T(KC_ESC), KC_LCBR, KC_LBRC, KC_LPRN, KC_TILD,       KC_CIRC, KC_RPRN, KC_RBRC, KC_RCBR, KC_GRV,
                     SFT_T(KC_MINS), KC_ASTR, KC_EQL, KC_UNDS, KC_DLR,       KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC,
                   CTL_T(KC_PLUS), KC_PIPE, KC_BSLS, KC_QUOT, KC_HASH,       KC_PERC, KC_AT, KC_AMPR, KC_QUES, KC_EXLM,
                                                     KC_TRNS, KC_TRNS,       KC_NO, KC_TRNS),
     /*
      * ┌─────┬─────┬─────┬─────┬─────┐       ┌─────┬─────┬─────┬─────┬─────┐
      * │  1  │  2  │  3  │  4  │  5  |       │  6  |  7  │  8  │  9  │  0  │
      * │ Alt │     │     │     │     │       │     │     │     │     │     │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │     │     │DF(1)│DF(0)│ F11 │       │ F12 │     │     │     │ TAB │
      * │ Sft │     │     │     │     │       │     │     │     │     │     │
      * ├─────┼─────┼─────┼─────┼─────┤       ├─────┼─────┼─────┼─────┼─────┤
      * │  F1 │  F2 │  F3 │  F4 │  F5 │       │  F6 │  F7 │  F8 │  F9 │ F10 │
      * │ Ctl │     │     │     │     │       │     │     │     │     │     │
      * └─────┴─────┴─────┴─────┴─────┘       └─────┴─────┴─────┴─────┴─────┘
      *
      *                     ┌─────┐               ┌─────┐
      *                     │     ├─────┐   ┌─────┤ Ent │
      *                     │     │ Spc │   │ Bsp │     │
      *                     └─────┤Layr1│   │Layr2├─────┘
      *                           └─────┘   └─────┘
      */
	[4] = LAYOUT(                 ALT_T(KC_1), KC_2, KC_3, KC_4, KC_5,       KC_6, KC_7, KC_8, KC_9, KC_0,
	                        SFT_T(KC_NO), KC_NO, DF(1), DF(0), KC_F11,       KC_F12, KC_NO, KC_NO, KC_NO, KC_TAB,
	                         CTL_T(KC_F1), KC_F2, KC_F3, KC_F4, KC_F5,       KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
	                                                   KC_NO, KC_TRNS,       KC_TRNS, KC_TRNS),
};

