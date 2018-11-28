#ifndef NEO2_BASIC_LAYOUT_H
#define NEO2_BASIC_LAYOUT_H

/*
This is the basic layout for NEO2 on a levinson keyboard

It consists of a block of 5x3 for each hand. This allows us
to use these blocks for a variety of keyboards like the planck, preonic and
even splits like the ergodox.

You can see that we use some quirky preprocessor defines to achive what we
desire. In the future I would like to see qmk taking a more generic approach
like the KLL.

The naming convention for these blocks is
  L<LAYER>_<SIDE>_<ROW>

  The LAYER is a number following the neo2 manner starting at 1 for the base
  layer, 2 is shift, 3 is for special chars etc.

  SIDE is, well either the left or right side/half of a keyboard.

  The ROW is starting from the top, numbering beginning at 1.
*/


#include "neo2-common.h"

/*
 *
 *                    LEFT                                  RIGHT
 *    ,----------------------------------.  ,----------------------------------.
 * 01 | x    | v    | l    | c    | w    |  | k    | h    | g    | f    | q    |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 02 | u    | i    | a    | e    | o    |  | s    | n    | r    | t    | d    |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 03 | ü    | ö    | ä    | p    | z    |  | b    | m    | ,    | .    | j    |
 *    `----------------------------------'  `----------------------------------'
 */
#define L01_LEFT_01  KC_X,    KC_V,    KC_L,    KC_C,    KC_W
#define L01_LEFT_02  KC_U,    KC_I,    KC_A,    KC_E,    KC_O
#define L01_LEFT_03  N_UE,     N_OE,    N_AE,    KC_P,    N_Z

#define L01_RIGHT_01 KC_K,    KC_H,    KC_G,    KC_F,    KC_Q
#define L01_RIGHT_02 KC_S,    KC_N,    KC_R,    KC_T,    KC_D
#define L01_RIGHT_03 KC_B,    KC_M,    KC_COMM, KC_DOT,  KC_J


/*
 *
 *                    LEFT                                  RIGHT
 *    ,----------------------------------.  ,----------------------------------.
 * 01 | …    | _    | [    | ]    | ^    |  | !    | <    | >    | =    | &    |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 02 | \    | /    | {    | }    | *    |  | ?    | (    | )    | -    | :    |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 03 | #    | $    | |    | ~    | `    |  | +    | %    | "    | '    | ;    |
 *    `----------------------------------'  `----------------------------------'
 */
#define L03_LEFT_01  N_DOTS,  N_USC,   N_LSQBR, N_RSQBR, N_CIRC
#define L03_LEFT_02  N_BSLS,  N_SLSH,  N_LCUBR, N_MINS, N_COLN
#define L03_LEFT_03  N_HASH,  N_DLR,   N_PIPE,  N_TILD,  N_GRAVE

#define L03_RIGHT_01 N_EXKL,  N_LT,    N_GT,    N_EQ,    N_AMP
#define L03_RIGHT_02 N_QUES,  N_LPARN, N_RPARN, N_MINS,  N_AT
#define L03_RIGHT_03 N_PLUS,  N_PERC,  N_QUOT,  N_SING,  N_SEMI


/*
 *
 *                    LEFT                                  RIGHT
 *    ,----------------------------------.  ,----------------------------------.
 * 01 | PAGEU| BACKS| UP   | DELET| PAGED|  | /    | 7    | 8    | 9    | -    |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 02 | HOME | LEFT | DOWN | RIGHT| END  |  | *    | 4    | 5    | 6    | +    |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 03 | ESC  | TAB  | INSRT| ENTER| UNDO |  | ENTER| 1    | 2    | 3    | ,    |
 *    `----------------------------------'  `----------------------------------'
 */
#define L04_LEFT_01  KC_PGUP,        KC_BSPC, KC_UP,   KC_DEL,   KC_PGDN
#define L04_LEFT_02  KC_HOME,        KC_LEFT, KC_DOWN, KC_RIGHT, KC_END
#define L04_LEFT_03  KC_ESC,         KC_TAB,  KC_INS,  KC_ENTER, N_UNDO

#define L04_RIGHT_01 KC_KP_SLASH,    KC_KP_7, KC_KP_8, KC_KP_9,  KC_KP_MINUS
#define L04_RIGHT_02 KC_KP_ASTERISK, KC_KP_4, KC_KP_5, KC_KP_6,  KC_KP_PLUS
#define L04_RIGHT_03 KC_KP_ENTER,    KC_KP_1, KC_KP_2, KC_KP_3,  KC_KP_DOT

/* Space for greek (L05)/ mathematical (L06) layers
*/

/*
 *
 *                    LEFT                                  RIGHT
 *    ,----------------------------------.  ,----------------------------------.
 * 01 | F1   | F2   | F3   | F4   |      |  | MAIL | MUSIC| FILES| CALC | PASTE|
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 02 | F5   | F6   | F7   | F8   |      |  | PREV |PLAY/P| NEXT | STOP | COPY |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 03 | F9   | F10  | F11  | F12  |      |  | PRINT| SCROL| PAUSE| NUMLK| CUT  |
 *    `----------------------------------'  `----------------------------------'
 */
#define L07_LEFT_01  KC_F1,   KC_F2,   KC_F3,   KC_F4,          _______
#define L07_LEFT_02  KC_F5,   KC_F6,   KC_F7,   KC_F8,          _______
#define L07_LEFT_03  KC_F9,   KC_F10,  KC_F11,  KC_F12,         _______

#define L07_RIGHT_01 KC_MAIL, KC_MSEL, KC_MY_COMPUTER, KC_CALCULATOR, N_PASTE
#define L07_RIGHT_02 KC_MPRV, KC_MPLY, KC_MNXT,        KC_MSTP,       N_COPY
#define L07_RIGHT_03 KC_PSCR, KC_SLCK, KC_PAUS,        KC_NLCK,       N_CUT


/*
 *
 *                    LEFT                                  RIGHT
 *    ,----------------------------------.  ,----------------------------------.
 * 01 | q    | w    | e    | r    | t    |  | z    | u    | i    | o    | p    |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 02 | a    | s    | d    | f    | g    |  | h    | j    | k    | l    | ö    |
 *    |------+------+------+------+------|  |------+------+------+------+------|
 * 03 | y    | x    | c    | v    | b    |  | n    | m    | ,    | .    | -    |
 *    `----------------------------------'  `----------------------------------'
 */
#define L08_LEFT_01  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define L08_LEFT_02  KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define L08_LEFT_03  KC_Y,    KC_X,    KC_C,    KC_V,    N_B

#define L08_RIGHT_01 KC_Z,    KC_U,    KC_I,    KC_O,    KC_P
#define L08_RIGHT_02 KC_H,    KC_J,    KC_K,    KC_L,    N_OE
#define L08_RIGHT_03 KC_N,    KC_M,    KC_COMM, KC_DOT,  N_MINS


#endif
