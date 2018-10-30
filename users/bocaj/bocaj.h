#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

/* *** *** *** *** *** *
 * Define layer names  *
 * *** *** *** *** *** */
enum userspace_layers {
  _OSXWRKMN = 0,
  _WINWRKMN,
  _OSXQWERTY,
  _WINQWERTY,
  _CLICKY,
  _LOWER,
  _ADJUST,
  _NUMS,
  _DIABLO
};

#define EECONFIG_USERSPACE (uint8_t *)19
typedef union {
  uint8_t raw;
} userspace_config_t;

/* *** *** *** *** *** *** *
 *  Define Custom Keycodes *
 * *** *** *** *** *** *** */
enum userspace_custom_keycodes {
  KC_EPRM = SAFE_RANGE, // can always be here
  KC_MWRK,
  KC_WWRK,
  KC_MQWR,
  KC_WQWR,
  KC_VRSN,
  JJ_COPY,
  JJ_PSTE,
  JJ_ARRW,
  KC_CCCV,
  MC_LOCK,
  KC_DCLR,
  KC_MAKE,
  NEW_SAFE_RANGE  //use "NEWPLACEHOLDER for keymap specific codes
};

// Space Cadet Hyper/Meh and [/]
#define HYP_LBK ALL_T(KC_LBRACKET)
#define MEH_RBK MEH_T(KC_RBRACKET)

// Layout beauti-/simpli-fication
#define KC_LWEN LT(_LOWER, KC_ENTER)
#define KC_ADJS TT(_ADJUST)
#define KC_NUMS TT(_NUMS)
#define LM_SHFT LM(_NMOD, MOD_LSFT)
#define KC_GAME TT(_DIABLO)
#define KC_CLIK TT(_CLICKY)
#define XXXXXXX KC_NO
#define _______ KC_TRNS

void tap(uint16_t keycode);

/*
define modifiers here, since MOD_* doesn't seem to work for these
 */
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK  (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))

/* *** *** *** *** *** *** *
 * Diablo 3 Macro Handling *
 * *** *** *** *** *** *** */

// If Tap Dancing is enabled, we manage that here.
// If it is not, then we define the KC_D3_# codes gracefully
#ifdef TAP_DANCE_ENABLE
enum {
  TD_D3_1 = 0,
  TD_D3_2,
  TD_D3_3,
  TD_D3_4,
};

#define KC_D3_1 TD(TD_D3_1)
#define KC_D3_2 TD(TD_D3_2)
#define KC_D3_3 TD(TD_D3_3)
#define KC_D3_4 TD(TD_D3_4)
#else // !TAP_DANCE_ENABLE
#define KC_D3_1 KC_A
#define KC_D3_2 KC_S
#define KC_D3_3 KC_D
#define KC_D3_4 KC_F
#endif // TAP_DANCE_ENABLE

// Wrapper for handling of keymap 'blocks'
// not 100% sure what this first part does. Credit to Drashna
#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif

#define LAYOUT_ergodox_pretty_wrapper(...) LAYOUT_ergodox_pretty(__VA_ARGS__)
/* Pretty Layout
.---------------------------------------------.         .---------------------------------------------.
|   1   |  2  |  3  |  4  |  5  |  6  |   7   |         !   8   |  9  |  10 |  11 |  12 |  13 |   14  |
!-------+-----+-----+-----+-----+-------------!         !-------+-----+-----+-----+-----+-----+-------!
|   15  |  16 |  17 |  18 |  19 |  20 |   21  |         !   22  |  23 |  24 |  25 |  26 |  27 |   28  |
!-------+-----+-----+-----x-----x-----!       !         !       !-----x-----x-----+-----+-----+-------!
|   29  |  30 |  31 |  32 |  33 |  34 |-------!         !-------!  35 |  36 |  37 |  38 |  39 |   40  |
!-------+-----+-----+-----x-----x-----!       !         !       !-----x-----x-----+-----+-----+-------!
|   41  |  42 |  43 |  44 |  45 |  46 |   47  |         !   48  |  49 |  50 |  51 |  52 |  53 |   54  |
'-------+-----+-----+-----+-----+-------------'         '-------------+-----+-----+-----+-----+-------'
 |  55  |  56 |  57 |  58 |  59 | .---------------. .---------------. !  60 |  61 |  62 |  63 |   64 |
 '------------------------------' |   65  |   66  | !   67  |   68  | '------------------------------'
                          .-------+-------+-------! !-------+-------+-------.
                          !       !       |   69  | !   70  |       !       !
                          !       !       !-------! !-------!       !       !
                          |   71  |   72  |   73  | !   74  |   75  |   76  |
                          '-----------------------' '-----------------------'
*/

#define _______________________QWERTY_L1_________________________       KC_Q,     KC_W,           KC_E,           KC_R,           KC_T
#define _______________________QWERTY_L2_________________________       KC_A,     KC_S,           KC_D,           KC_F,           KC_G
#define _______________________QWERTY_L3_________________________       KC_Z,     KC_X,           KC_C,           KC_V,           KC_B

#define _______________________QWERTY_R1_________________________       KC_Y,     KC_U,           KC_I,           KC_O,           KC_P
#define _______________________QWERTY_R2_________________________       KC_H,     KC_J,           KC_K,           KC_L,           KC_SCLN
#define _______________________QWERTY_R3_________________________       KC_N,     KC_M,           KC_COMM,        KC_DOT,         KC_SLASH

// Hardware Driven Workman
#define _______________________WORKMAN_L1________________________       KC_Q,     KC_D,           KC_R,           KC_W,           KC_B
#define _______________________WORKMAN_L2________________________       KC_A,     KC_S,           KC_H,           KC_T,           KC_G
#define _______________________WORKMAN_L3________________________       KC_Z,     KC_X,           KC_M,           KC_C,           KC_V

#define _______________________WORKMAN_R1________________________       KC_J,     KC_F,           KC_U,           KC_P,           KC_SCLN
#define _______________________WORKMAN_R2________________________       KC_Y,     KC_N,           KC_E,           KC_O,           KC_I
#define _______________________WORKMAN_R3________________________       KC_K,     KC_L,           KC_COMM,        KC_DOT,         KC_SLASH

#define ___________________ERGODOX_BOTTOM_LEFT___________________       KC_CLIK,  KC_NUMS,        TT(_LOWER),     KC_UP,          KC_LEFT
#define ___________________ERGODOX_BOTTOM_RIGHT__________________       KC_RIGHT, KC_DOWN,        XXXXXXX,        KC_GAME,        KC_ADJS

#define _______________________NUMBER_LEFT_______________________       KC_1,     KC_2,           KC_3,           KC_4,           KC_5
#define _______________________NUMBER_RIGHT______________________       KC_6,     KC_7,           KC_8,           KC_9,           KC_0

#define _______________________SPECIAL_LEFT______________________       KC_EXLM,  KC_AT,          KC_HASH,        KC_DLR,         KC_PERC
#define _______________________SPECIAL_RIGHT_____________________       KC_CIRC,  KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN

#define _________________________________________________________       KC_TRNS,  KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS
#define XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       KC_NO,    KC_NO,          KC_NO,          KC_NO,          KC_NO

//                                                                                LEFT        |       RIGHT
#define ______________________ERGODOX_THUMBS_____________________             KC_APP,KC_HOME,    KC_PGUP,KC_ESC,           \
                                                                                     KC_WWRK,    KC_WQWR,                \
                                                                  KC_SPACE,KC_BSPACE,KC_MWRK,    KC_MQWR,KC_TAB,KC_LWEN

#endif // !USERSPACE
