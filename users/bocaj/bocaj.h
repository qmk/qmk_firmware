#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

/* *** *** *** *** *** *
 * Define layer names  *
 * *** *** *** *** *** */
enum userspace_layers {
  _HWRKMN = 0,
  _SWRKMN,
  _LOWER,
  _ADJUST,
  _NUMS,
  _NMOD,
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
  KC_SWRK,
  KC_HWRK,
  KC_VRSN,
  JJ_COPY,
  JJ_PSTE,
  JJ_ARRW,
  KC_CCCV,
  MC_LOCK,
  KC_DCLR,
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
#define XXXXXXX KC_NO
#define _______ KC_TRNS

void tap(uint16_t keycode);

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
#define KC_D3_1 KC_1
#define KC_D3_2 KC_2
#define KC_D3_3 KC_3
#define KC_D3_4 KC_4
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

#define _______________________SWORKMAN_L1_______________________       KC_Q,     KC_W,           KC_E,           KC_R,           KC_T
#define _______________________SWORKMAN_L2_______________________       KC_A,     SFT_T(KC_S),    GUI_T(KC_D),    ALT_T(KC_F),    KC_G
#define _______________________SWORKMAN_L3_______________________ CTL_T(KC_Z),    KC_X,           KC_C,           KC_V,           KC_B

#define _______________________SWORKMAN_R1_______________________       KC_Y,     KC_U,           KC_I,           KC_O,           KC_P
#define _______________________SWORKMAN_R2_______________________       KC_H,     ALT_T(KC_J),    GUI_T(KC_K),    SFT_T(KC_L),    KC_SCLN
#define _______________________SWORKMAN_R3_______________________       KC_N,     KC_M,           KC_COMM,        KC_DOT,         CTL_T(KC_SLASH)

// Hardware Driven Workman
#define _______________________HWORKMAN_L1_______________________       KC_Q,     KC_D,           KC_R,           KC_W,           KC_B
#define _______________________HWORKMAN_L2_______________________       KC_A,     SFT_T(KC_S),    GUI_T(KC_H),    ALT_T(KC_T),    KC_G
#define _______________________HWORKMAN_L3_______________________ CTL_T(KC_Z),    KC_X,           KC_M,           KC_C,           KC_V

#define _______________________HWORKMAN_R1_______________________       KC_J,     KC_F,           KC_U,           KC_P,           KC_SCLN
#define _______________________HWORKMAN_R2_______________________       KC_Y,     ALT_T(KC_N),    GUI_T(KC_E),    SFT_T(KC_O),    KC_I
#define _______________________HWORKMAN_R3_______________________       KC_K,     KC_L,           KC_COMM,        KC_DOT,         CTL_T(KC_SLASH)

#define ___________________ERGODOX_BOTTOM_LEFT___________________    TT(_DIABLO), KC_NUMS,        TT(_LOWER),     KC_UP,          KC_LEFT
#define ___________________ERGODOX_BOTTOM_RIGHT__________________    KC_RIGHT,    KC_DOWN,        XXXXXXX,        XXXXXXX,        TT(_ADJUST)

#define _______________________NUMBER_LEFT_______________________       KC_1,     KC_2,           KC_3,           KC_4,           KC_5
#define _______________________NUMBER_RIGHT______________________       KC_6,     KC_7,           KC_8,           KC_9,           KC_0

#define _______________________SPECIAL_LEFT______________________       KC_EXLM,  KC_AT,          KC_HASH,        KC_DLR,         KC_PERC
#define _______________________SPECIAL_RIGHT_____________________       KC_CIRC,  KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN

#define _________________________________________________________       KC_TRNS,  KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS
#define XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       KC_NO,    KC_NO,          KC_NO,          KC_NO,          KC_NO

//                                                                    LEFT        |       RIGHT
#define ______________________ERGODOX_THUMBS_____________________ KC_APP,KC_HOME,    KC_PGUP,KC_ESC,           \
                                                                          KC_END,    KC_PGDOWN,                \
                                                      KC_SPACE,KC_BSPACE,JJ_COPY,    JJ_PSTE,KC_TAB,KC_LWEN


#endif // !USERSPACE
