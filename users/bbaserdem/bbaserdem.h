/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include QMK_KEYBOARD_H
#include "quantum.h"

/* Besides loading libraries and definitions, this file has my layout defs
 * LAYOUTS:
 *  This file has a couple layouts I use; so that the general changes can be
 *  propagated by only editing this file.
 */

// Macros to use, this has base level code so not affected by enabled features
#include "bb-macro.h"
// Audio from onboard speakers
#ifdef AUDIO_ENABLE
  #include "bb-audio.h"
#endif
// Underglow using rgb LEDs
#ifdef RGBLIGHT_ENABLE          
    #include "bb-underglow.h"
#endif
// Keycap backlight using non-rgb LEDs
#ifdef BACKLIGHT_ENABLE         
  #include "bb-backlight.h"
#endif
// Keycap backlight using rgb LEDs
#ifdef RGB_MATRIX_ENABLE
    #include "bb-keylight.h"
#endif
// Rotary encoder
#ifdef ENCODER_ENABLE  
    #include "bb-encoder.h"
#endif
// Oled screen
#ifdef OLED_ENABLE
    #include "bb-oled.h"
#endif

// Function definitions that can be accessed through specific keymaps
// Runs before all initialization
void keyboard_pre_init_keymap(void);
// For code that launches once midway through initialization
void matrix_init_keymap(void);
// For code that launches after initialization is finished.
void keyboard_post_init_keymap(void);
// This code also launches on boot; but used after eeprom is available to write
void eeconfig_init_keymap(void);
// These will be delegated to keymap specific stuff (weak definition)
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
// This code runs on every tick
void matrix_scan_keymap(void);
// This code runs after every layer change
layer_state_t layer_state_set_keymap(layer_state_t state);
// This code runs when the default layer changes
layer_state_t default_layer_state_set_keymap (layer_state_t state);
// This code runs to set LED states
void led_set_keymap(uint8_t usb_led);
// For code that runs on suspend
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
// For code that runs on powerdown
void shutdown_keymap(void);

// Make it so that keymaps can use KEYMAP_SAFE_RANGE for custom keycodes
#if defined(KEYMAP_SAFE_RANGE)
  #define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

// Custom macro keycode ranges
enum userspace_custom_keycodes {
    // Safe stuff
    BB_SAFE = PLACEHOLDER_SAFE_RANGE,
    // Double entry macros
    DBL_ANG,
    DBL_PAR,
    DBL_CBR,
    DBL_BRC,
    // Macro key
    BB_PGPK,
    // Unicode strings
    #ifdef UNICODEMAP_ENABLE
    BB_LENY,
    BB_TABL,
    TR_FLAG,
    #endif
    // Encoder buttons
    #ifdef ENCODER_ENABLE
    BB_ENC0,
    BB_ENC1,
    #endif
    //use for keymap specific codes
    KEYMAP_SAFE_RANGE
};
// Mask these keycodes if required features are not enabled
#ifndef UNICODEMAP_ENABLE
#define BB_LENY KC_NO
#define BB_TABL KC_NO
#define TR_FLAG KC_NO
#endif
#ifndef ENCODER_ENABLE
#define BB_ENC0 KC_NO
#define BB_ENC1 KC_NO
#endif

/// Enumerate of layers
enum userspace_layers {
    _BASE = 0,  // Base layer
    _CHAR,      // Characters layer
    _GAME,      // Game layer
    _MEDI,      // R3: Media layer
    _NAVI,      // R3: Navigation layer
    _SYMB,      // R1: Symbols layer
    _NUMB,      // L1: Numbers layer
    _FUNC,      // L2: Function keys layer
    _MOUS,      // L3: Mouse keys layer
    _MUSI       // Music overlay
};

// Use 7 wide characters for keymaps, to keep things aligned with 4 tabs
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// These defines allow multiple multi-parameter definitions to expand
// for these boards
#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)  LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_5x15_wrapper(...)  LAYOUT_ortho_5x15(__VA_ARGS__)
#define LAYOUT_ortho_3x10_wrapper(...)  LAYOUT_ortho_3x10(__VA_ARGS__)
#define LAYOUT_split_3x6_3_wrapper(...) LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_split_3x5_3_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

// Masks
#define ___1___ _______
#define ___2___ _______,_______
#define ___3___ _______,_______,_______
#define ___4___ _______,_______,_______,_______
#define ___5___ _______,_______,_______,_______,_______
#define ___6___ _______,_______,_______,_______,_______,_______
#define xxx1xxx KC_NO
#define xxx2xxx KC_NO,  KC_NO
#define xxx3xxx KC_NO,  KC_NO,  KC_NO
#define xxx4xxx KC_NO,  KC_NO,  KC_NO,  KC_NO
#define xxx5xxx KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
#define xxx6xxx KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
#define xxx1xxx KC_NO
#define xxx3xxx KC_NO,  KC_NO,  KC_NO
#define xxx5xxx KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
#define xxx6xxx KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO

// Quick macros: in dvorak
#define BB_UNDO    LCTL(KC_SLSH)    // Ctrl + Z
#define BB_REDO    LCTL(KC_T)       // Ctrl + Y
#define BB_YANK    LCTL(KC_I)       // Ctrl + C
#define BB_CUT     LCTL(KC_B)       // Ctrl + X
#define BB_PSTE    LCTL(KC_DOT)     // Ctrl + V

// Audio keys
#ifdef AUDIO_ENABLE
#define MU_REC  KC_LCTL
#define MU_STOP KC_LALT
#define MU_PLAY KC_LGUI
#define MU_FAST KC_UP
#define MU_SLOW KC_DOWN
#define MU_MASK KC_A
#define BB_SND  MU_ON
#ifdef TAP_DANCE_ENABLE
#define MU_TEMP TD(TD_AUDIO_TEMPO)
#else
#define MU_TEMP KC_DOWN
#endif
#else
#define MU_REC  KC_NO
#define MU_STOP KC_NO
#define MU_PLAY KC_NO
#define MU_FAST KC_NO
#define MU_TEMP KC_NO
#define MU_SLOW KC_NO
#define MU_MASK KC_NO
#define BB_SND  KC_MUTE
#endif

// Unicode keys
#ifdef UNICODEMAP_ENABLE
#define TR_ACIR XP(LOW_A_CIRC, UPC_A_CIRC )
#define TR_CCED XP(LOW_C_CEDI, UPC_C_CEDI )
#define TR_GBRE XP(LOW_G_BREV, LOW_G_BREV )
#define TR_ICIR XP(LOW_I_CIRC, LOW_I_CIRC )
#define TR_I_NO XP(LOW_I_DOTL, LOW_I_DOTL )
#define TR_IDOT XP(LOW_I_DOTT, LOW_I_DOTT )
#define TR_ODIA XP(LOW_O_DIAE, LOW_O_DIAE )
#define TR_SCED XP(LOW_S_CEDI, LOW_S_CEDI )
#define TR_UCIR XP(LOW_U_CIRC, LOW_U_CIRC )
#define TR_UDIA XP(LOW_U_DIAE, LOW_U_DIAE )
#define GR_ALP  XP(LOW_ALPHA,  UPC_ALPHA  )
#define GR_BET  XP(LOW_BETA,   UPC_BETA   )
#define GR_GAM  XP(LOW_GAMMA,  UPC_GAMMA  )
#define GR_DEL  XP(LOW_DELTA,  UPC_DELTA  )
#define GR_EPS  XP(LOW_EPSILON,UPC_EPSILON)
#define GR_ZET  XP(LOW_ZETA,   UPC_ZETA   )
#define GR_ETA  XP(LOW_ETA,    UPC_ETA    )
#define GR_THE  XP(LOW_THETA,  UPC_THETA  )
#define GR_IOT  XP(LOW_IOTA,   UPC_IOTA   )
#define GR_KAP  XP(LOW_KAPPA,  UPC_KAPPA  )
#define GR_LAM  XP(LOW_LAMBDA, UPC_LAMBDA )
#define GR_MU   XP(LOW_MU,     UPC_MU     )
#define GR_NU   XP(LOW_NU,     UPC_NU     )
#define GR_XI   XP(LOW_XI,     UPC_XI     )
#define GR_OMI  XP(LOW_OMICRON,UPC_OMICRON)
#define GR_PI   XP(LOW_PI,     UPC_PI     )
#define GR_RHO  XP(LOW_RHO,    UPC_RHO    )
#define GR_SIG  XP(LOW_SIGMA,  UPC_SIGMA  )
#define GR_TAU  XP(LOW_TAU,    UPC_TAU    )
#define GR_UPS  XP(LOW_UPSILON,UPC_UPSILON)
#define GR_PHI  XP(LOW_PHI,    UPC_PHI    )
#define GR_CHI  XP(LOW_CHI,    UPC_CHI    )
#define GR_PSI  XP(LOW_PSI,    UPC_PSI    )
#define GR_OME  XP(LOW_OMEGA,  UPC_OMEGA  )
#define BB_ELLI X(ELLIPSIS)
#define BB_PLNK X(PLANCK_CON)
#define BB_ANGS X(ANGSTROM)
#define BB_BITC X(BITCOIN)
#else
#define TR_ACIR KC_A
#define TR_CCED KC_C
#define TR_GBRE KC_G
#define TR_ICIR KC_I
#define TR_I_NO KC_I
#define TR_IDOT KC_I
#define TR_ODIA KC_O
#define TR_SCED KC_S
#define TR_UCIR KC_U
#define TR_UDIA KC_U
#define GR_ALP  KC_NO
#define GR_BET  KC_NO
#define GR_GAM  KC_NO
#define GR_DEL  KC_NO
#define GR_EPS  KC_NO
#define GR_ZET  KC_NO
#define GR_ETA  KC_NO
#define GR_THE  KC_NO
#define GR_IOT  KC_NO
#define GR_KAP  KC_NO
#define GR_LAM  KC_NO
#define GR_MU   KC_NO
#define GR_NU   KC_NO
#define GR_XI   KC_NO
#define GR_OMI  KC_NO
#define GR_PI   KC_NO
#define GR_RHO  KC_NO
#define GR_SIG  KC_NO
#define GR_TAU  KC_NO
#define GR_UPS  KC_NO
#define GR_PHI  KC_NO
#define GR_CHI  KC_NO
#define GR_PSI  KC_NO
#define GR_OME  KC_NO
#define BB_ELLI KC_NO
#define BB_PLNK KC_NO
#define BB_ANGS KC_NO
#define BB_BITC KC_NO
#endif

// MOD-tap definitions
#define GUI_A   MT(MOD_LGUI, KC_A)
#define ALT_S   MT(MOD_LALT, KC_S)
#define CTRL_D  MT(MOD_LCTL, KC_D)
#define SHIFT_F MT(MOD_LSFT, KC_F)
#define ALTGR_X MT(MOD_RALT, KC_X)
#define GUI_SCL MT(MOD_RGUI, KC_SCLN)
#define ALT_L   MT(MOD_LALT, KC_L)
#define CTRL_K  MT(MOD_LCTL, KC_K)
#define SHIFT_J MT(MOD_LSFT, KC_J)
#define ALTGR_D MT(MOD_RALT, KC_DOT)

// Layer switches
#define MED_DEL LT(_MEDI, KC_DEL )
#define NAV_TAB LT(_NAVI, KC_TAB )
#define SYM_SPC LT(_SYMB, KC_SPC )
#define NUM_ENT LT(_NUMB, KC_ENT )
#define FUN_ESC LT(_FUNC, KC_ESC )
#define MOU_BSP LT(_MOUS, KC_BSPC)

// Layer switches
#define BB_CHAR OSL(_CHAR)
#define BB_GAME TG(_GAME)
#define BB_BIGS TD(TD_BIGSWITCH)

/* Depending on how the layouts change with language; the keys are shown as;
 * ┌────────────────────────────────────────────────┐
 * │AltGr       -none-      Shift       Shift+AltGr │
 * └────────────────────────────────────────────────┘
 * If there is an exclamation mark; it indicates a dead key on this map.
 */

/* Base layout
 * QWERTY
 *      ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 *  ` ~ │ q Q │ w W │ e E │ r R │ t T │             │ y Y │ u U │ i I │ o O │ p P │ < > 
 *      ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 *  [ { │ a A │ s S │ d D │ f F │ g G │             │ h H │ j J │ k K │ l L │ ; : │ ] } 
 *      ├─Gui─┼─Alt─┼─Ctr─┼─Sft─┼─────┤             ├─────┼─Sft─┼─Ctr─┼─Alt─┼─Gui─┤
 *  \ | │ z Z │ x X │ c C │ v V │ b B │             │ n N │ m M │ , < │ . > │ / ? │ ' " 
 *      └─────┴AltGr┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴AltGr┴─────┘
 *                        │ Del │ Tab │Space│ │Enter│ Esc │BkSpc│
 *                        └─Med─┴─Nav─┴─Sym─┘ └─Num─┴─Fun─┴─Mou─┘
 * DVORAK
 *      ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 *  ` ~ │ ' " │ , < │ . > │ p P │ y Y │             │ f F │ g G │ c C │ r R │ l L │ < > 
 *      ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 *  / ? │ a A │ o O │ e E │ u U │ i I │             │ d D │ h H │ t T │ n N │ s S │ = + 
 *      ├─Gui─┼─Alt─┼─Ctr─┼─Sft─┼─────┤             ├─────┼─Sft─┼─Ctr─┼─Alt─┼─Gui─┤
 *  \ | │ ; : │ q Q │ j J │ k K │ x X │             │ b B │ m M │ w W │ v V │ z Z │ - _ 
 *      └─────┴AltGr┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴AltGr┴─────┘
 *                        │ Del │ Tab │Space│ │Enter│ Esc │BkSpc│
 *                        └─Med─┴─Nav─┴─Sym─┘ └─Num─┴─Fun─┴─Mou─┘
 * TURKISH F
 *      ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 * ¬+ *±│@f F │ g G │ ğ Ğ │¶ı I │ôo OÔ│             │¥d D │®r R │ n N │°h H │£p P │|< >¦
 * !   !├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼────!┤
 * äq Qå│ûu UÛ│îi İÎ│€e E │âa AÂ│ûü ÜÛ│             │₺t T │ k K │µm M │ l L │´y Yá│~w W 
 *     !├─Gui─┼─Alt─┼─Ctr─┼─Sft─┼─────┤             ├─────┼─Sft─┼─Ctr─┼─Alt!┼─Gui─┤    !
 * `x Xà│«j J<│»ö Ö>│“v V │¢c C©│”ç Ç │             │ z Z │§s S │×b B │÷. :ȧ│·, ; │#ş Şǎ
 *      └─────┴AltGr┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴AltGr┴─────┘
 *                        │ Del │ Tab │Space│ │Enter│ Esc │BkSpc│
 *                        └─Med─┴─Nav─┴─Sym─┘ └─Num─┴─Fun─┴─Mou─┘
 * The thing about this layout is that these will fit most boards I have.
 */
#define _BL1_5_ KC_Q,   KC_W,   KC_E,   KC_R,   KC_T
#define _BR1_5_ KC_Y,   KC_U,   KC_I,   KC_O,   KC_P
#define _BL2_5_ GUI_A,  ALT_S,  CTRL_D, SHIFT_F,KC_G
#define _BR2_5_ KC_H,   SHIFT_J,CTRL_K, ALT_L,  GUI_SCL
#define _BL3_5_ KC_Z,   ALTGR_X,KC_C,   KC_V,   KC_B
#define _BR3_5_ KC_N,   KC_M,   KC_COMM,ALTGR_D,KC_SLSH
#define _BL4_3_ MED_DEL,NAV_TAB,SYM_SPC
#define _BR4_3_ NUM_ENT,FUN_ESC,MOU_BSP
// The extra line for the 6th (or 0th) row
#define _BL1_1_ KC_GRV
#define _BR1_1_ KC_NUBS
#define _BL2_1_ KC_LBRC
#define _BR2_1_ KC_RBRC
#define _BL3_1_ KC_BSLS
#define _BR3_1_ KC_QUOT

/* Extra characters layer
 * This is accessed using unicode; so IBus compatible apps only.
 * ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 * │TrFlg│Lenny│Table│  π  │  υ  │             │  φ  │  γ  │  χ  │  ρ  │  λ  │
 * ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 * │  α  │  ο  │  ε  │  ψ  │  ι  │             │  δ  │  η  │  τ  │  ν  │  σ  │
 * ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 * │  ₿  │  θ  │  ℏ  │  κ  │  ξ  │             │  β  │  μ  │  ω  │  Å  │  ζ  │
 * └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
 *                   │ Shf │ ... │ GPG │ │     │     │ Shf │
 *                   └─────┴─────┴─────┘ └─────┴─────┴─────┘
 *
 */
#define _CL1_5_ TR_FLAG,BB_LENY,BB_TABL,GR_PI,  GR_UPS
#define _CR1_5_ GR_PHI, GR_GAM, GR_CHI, GR_RHO, GR_LAM
#define _CL2_5_ GR_ALP, GR_OMI, GR_EPS, GR_PSI, GR_IOT
#define _CR2_5_ GR_DEL, GR_ETA, GR_TAU, GR_NU,  GR_SIG
#define _CL3_5_ BB_BITC,GR_THE, BB_PLNK,GR_KAP, GR_XI
#define _CR3_5_ GR_BET, GR_MU,  GR_OME, BB_ANGS,GR_ZET
#define _CL4_3_ KC_RSFT,BB_ELLI,BB_PGPK
#define _CR4_3_ XXXXXXX,XXXXXXX,KC_LSFT

/* Game layer
 * This layer turns off the tap-hold keys for the left half.
 *      ┌─────┬─────┬─────┬─────┬─────┐
 *      │  Q  │  W  │  E  │  R  │  T  │
 *      ├─────┼─────┼─────┼─────┼─────┤
 *  Tab │  A  │  S  │  D  │  F  │  G  │
 *      ├─────┼─────┼─────┼─────┼─────┤
 * Shift│  Z  │  X  │  C  │  V  │  B  │
 *      └─────┴─────┴─────┼─────┼─────┼─────┐
 *                        │Space│Enter│ Esc │
 *                        └─────┴─────┴─────┘
 */
#define _GA1_5_ KC_Q,   KC_W,   KC_E,   KC_R,   KC_T
#define _GA1_1_ _______
#define _GA2_5_ KC_A,   KC_S,   KC_D,   KC_F,   KC_G
#define _GA2_1_ KC_TAB
#define _GA3_5_ KC_Z,   KC_X,   KC_C,   KC_V,   KC_B
#define _GA3_1_ KC_LSFT
#define _GA4_3_ KC_SPC, KC_ENT, KC_ESC

/* Media layer
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │ Tog │ Mod │ Hue │ Sat │ Bri │ RGB light control
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Media│Prev.│MuTog│MuStp│Next │ Media control
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Sink │Vol -│ Mut │Eject│Vol +│ Volume control
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │     │Veloc│Music│                   Feature control on keyboard
 * └─────┴─────┴─────┘
 */
#define _ME1_5_ RGB_TOG,RGB_MOD,RGB_HUI,RGB_SAI,RGB_VAI
#define _ME2_5_ KC_MSEL,KC_MPRV,KC_MPLY,KC_MSTP,KC_MNXT
#define _ME3_5_ KC_F13, KC_VOLD,KC_MUTE,KC_EJCT,KC_VOLU
#define _ME4_3_ XXXXXXX,VLK_TOG,MU_TOG

/* Navigation layer
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │Redo │Paste│Yank │ Cut │PrScr│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Undo │  <  │  v  │  ^  │  >  │
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │ Ins │Home │PgDwn│PgUp │ End │
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │Enter│ Esc │BkSpc│
 * └─────┴─────┴─────┘
 */
#define _NA1_5_ BB_REDO,BB_PSTE,BB_YANK,BB_CUT, KC_PSCR
#define _NA2_5_ BB_UNDO,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT
#define _NA3_5_ KC_INS, KC_HOME,KC_PGDN,KC_PGUP,KC_END
#define _NA4_3_ KC_ENT, KC_ESC, KC_BSPC

/* Symbols layer
 *  This layer has the central columns shifted for convenience
 * QWERTY
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │ ` ~ │  -  │  =  │ ] } │Char.│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │ [ { │  (  │  )  │ ' " │CapsL│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │ \ | │  _  │  +  │  <  │  >  │
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │Enter│ Esc │BkSpc│
 * └─────┴─────┴─────┘
 * DVORAK
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │ ` ~ │  [  │  ]  │ = + │Char.│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │ / ? │  (  │  )  │ - _ │CapsL│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │ \ | │  {  │  }  │  <  │  >  │
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │Enter│ Esc │BkSpc│
 * └─────┴─────┴─────┘
 * Turkish F
 * (AltGr is right on the central column, red. keys on main layer are omitted)
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │¬+ *±│ / \ │ - | │     │Char.│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │     │ ) ± │ = ° │     │CapsL│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │     │ ? ¿ │ _   │ < | │ > ¦ │
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │Enter│ Esc │BkSpc│
 * └─────┴─────┴─────┘
 */
#define _SY1_5_ KC_GRV,KC_MINS,KC_EQL, KC_RBRC,BB_CHAR
#define _SY2_5_ KC_LBRC,KC_LPRN,KC_RPRN,KC_QUOT,KC_CAPS
#define _SY3_5_ KC_BSLS,KC_UNDS,KC_PLUS,KC_NUBS,LSFT(KC_NUBS)
#define _SY4_3_ KC_ENT, KC_ESC, KC_BSPC

/* Numbers layer
 *  This layer contains numbers and the associated symbols.
 * QWERTY
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │     │ 7 & │ 8 * │ 9 ( │ 0 ) │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │     │ 4 $ │ 5 % │ 6 ^ │ ' " │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ [ { │ 1 ! │ 2 @ │ 3 # │ ] } │
 * └─────┴─────┴─────┼─────┼─────┼─────┐
 *                   │ Del │ Tab │Space│
 *                   └─────┴─────┴─────┘
 * DVORAK
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │  ,  │ 7 & │ 8 * │ 9 ( │ 0 ) │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │  .  │ 4 $ │ 5 % │ 6 ^ │ - _ │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ / ? │ 1 ! │ 2 @ │ 3 # │ = + │
 * └─────┴─────┴─────┼─────┼─────┼─────┐
 *                   │ Del │ Tab │Space│
 *                   └─────┴─────┴─────┘
 * Turkish F
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │     │{7 ' │[8 ( │]9 )±│}0 =°│
 * ├─────┼─────┼─────┼─────┼─────┤
 * │     │¼4 $ │½5 %⅜│¾6 & │     │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │     │¹1 !¡│²2 " │#3 ^³│     │
 * └─────┴─────┴─────┼─────┼─────┼─────┐
 *                   │ Del │ Tab │Space│
 *                   └─────┴─────┴─────┘
 */
#define _NU1_5_ KC_W,   KC_7,   KC_8,   KC_9,   KC_0
#define _NU2_5_ KC_E,   KC_4,   KC_5,   KC_6,   KC_QUOT
#define _NU3_5_ KC_LBRC,KC_1,   KC_2,   KC_3,   KC_RBRC
#define _NU4_3_ KC_DEL, KC_TAB, KC_SPC

/* Function layer
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │ F01 │ F02 │ F03 │ F04 │RESET│
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ F05 │ F06 │ F07 │ F08 │EEPRM│
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ F09 │ F10 │ F11 │ F12 │GameL│
 * └─────┴─────┴─────┼─────┼─────┼─────┐
 *                   │ Del │ Tab │Space│
 *                   └─────┴─────┴─────┘
 */
#define _FU1_5_ KC_F1,  KC_F2,  KC_F3,  KC_F4,  RESET
#define _FU2_5_ KC_F5,  KC_F6,  KC_F7,  KC_F8,  EEP_RST
#define _FU3_5_ KC_F9,  KC_F10, KC_F11, KC_F12, BB_GAME
#define _FU4_3_ KC_DEL, KC_TAB, KC_SPC

/* Mouse layer
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │Slow │Right│ Mid │ Lft │Fast │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ |<| │ |v| │ |^| │ |>| │ Bt4 │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ <<< │ vvv │ ^^^ │ >>> │ Bt5 │
 * └─────┴─────┴─────┼─────┼─────┼─────┐
 *                   │ Del │ Tab │Space│
 *                   └─────┴─────┴─────┘
 */
#define _MO1_5_ KC_ACL0,KC_BTN1,KC_BTN2,KC_BTN3,KC_ACL2
#define _MO2_5_ KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,KC_BTN4
#define _MO3_5_ KC_WH_L,KC_WH_D,KC_WH_U,KC_WH_R,KC_BTN5
#define _MO4_3_ KC_DEL, KC_TAB, KC_SPC

/* Music layer
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │   │   │   │   │   │   │   │   │   │   │   │   │
 * └───┴───┴───┼───┼───┼───┼───┼───┼───┼───┴───┴───┘
 *             │Rec│Stp│Ply│Tmp│Mod│Off│
 *             └───┴───┴───┴───┴───┴───┘
 */
#define _MUL_3_ MU_REC, MU_STOP,MU_PLAY
#define _MUR_3_ MU_TEMP,MU_MOD, MU_TOG
#define _MU_01_ MU_MASK
#define _MU_02_ MU_MASK,MU_MASK
#define _MU_03_ MU_MASK,MU_MASK,MU_MASK
#define _MU_06_ MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK
#define _MU_08_ MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK
#define _MU_10_ MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK
#define _MU_12_ MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK
