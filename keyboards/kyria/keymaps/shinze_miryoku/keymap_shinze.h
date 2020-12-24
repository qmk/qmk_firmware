// https://github.com/manna-harbour/qmk_firmware/blob/miryoku/users/manna-harbour_miryoku/manna-harbour_miryoku.c
// https://github.com/manna-harbour/qmk_firmware/tree/miryoku/users/manna-harbour_miryoku#customisation
// https://raw.githubusercontent.com/manna-harbour/miryoku/master/data/qmk/miryoku-kle-qmk_keycodes.png
// http://www.keyboard-layout-editor.com/#/gists/d7fa820f40c78036fe4fa00c609b8741
// https://github.com/qmk/qmk_firmware/blob/master/keyboards/kyria/keymaps/shinze/keymap.c
#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

/*
 * Base Layer: BÉPO
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RAIS/ESC|   B  |   É  |   P  |   O  |   È  |                              |   ^  |   V  |   D  |   L  |   J  |  | Z   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   W    |   A  |   U  |  I   |   E  |   ,  |                              |   C  |   T  |   S  |   R  |   N  |   M    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   À  |   Y  |   X  |   .  |   K  |  SPC |LShift|  |LShift|LShift|   ’  |   Q  |   G  |   H  |   F  |   Ç    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | CTRL | Alt  | Enter| Space| Esc  |  | Enter| Space| Tab  | Bksp | AltGr|
 *                        |      |      | CMD  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
#define XXX KC_NO                   // Nothink here
#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)

//
// Alpha layer
//

// Row 1
// Left
#define S00 XXX
#define S01 BP_B
#define S02 BP_E_ACUTE
#define S03 BP_P
#define S04 BP_O
#define S05 BP_E_GRAVE
// Right
#define S06 BP_DCRC
#define S07 BP_V
#define S08 BP_D
#define S09 BP_L
#define S10 BP_J
#define S11 BP_Z

// Row 2
// Left
#define S12 BP_W                     // @TODO : See how I can insert FN_T(BP_W) ? Need it ?
#define S13 LCTL_T(BP_A)
#define S14 LALT_T(BP_U)
#define S15 GUI_T(BP_I)
#define S16 LSFT(BP_E)
#define S17 BP_COMMA
// Right
#define S18 BP_C
#define S19 RSFT(BP_T)
#define S20 GUI_T(BP_S)
#define S21 RALT_T(BP_R)
#define S22 RCTL_T(BP_N)
#define S23 BP_M

// Row 3
#define S24 XXX
#define S25 BP_A_GRAVE
#define S26 BP_Y                     // @NOTE : LCTL_T(BP_Y) in Original layout
#define S27 BP_X
#define S28 BP_DOT
#define S29 BP_K
#define S30 XXX                      // Top outer key
#define S31 XXX                      // Top outer key
#define S32 XXX                      // Top outer key
#define S33 XXX                      // Top outer key
#define S34 BP_APOSTROPHE
#define S35 BP_Q
#define S36 BP_G
#define S37 BP_H
#define S38 BP_F
#define S39 BP_CCED

// Row 4
#define B00 XXX
#define B01 LT(MEDR, KC_ESC)
#define B02 LT(NAVR, KC_SPC)
#define B03 LT(MOUR, KC_TAB)
#define B04 XXX
#define B05 XXX
#define B06 LT(NSSL, KC_ENT)
#define B07 LT(NSL, KC_BSPC)
#define B08 LT(FUNL, KC_DEL)
#define B09 XXX
#define B10 XXX
