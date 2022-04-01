/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "keymap_bepo.h"
#include "keymap_french.h"
#include "sendstring_french.h"

// timers for Mod-Tap
uint16_t mu_cced_timer = 0;
uint16_t sft_i_timer = 0;
uint16_t sft_s_timer = 0;

// record key pressed or held for personnal Mod-Tap
bool is_sft_i_pressed = false;
bool is_sft_s_pressed = false;
bool is_sft_i_active = false;
bool is_sft_s_active = false;

// record states of modifiers before using alt-code
uint8_t mod_state;

// for character both on _SHALGR and _ALTGR layers, record is Left Shift was on
bool is_lsft_on = false;

enum planck_layers {
  _BEPO,
  _LOWER,
  _AZ_LOWER,
  _LOWERAG,
  _RAISE,
  _AZ_RAISE,
  _RAISEAG,
  _AZERTY,
  _SHIFT,
  _ALTGR,
  _SHALT,
  _MATHS,
  _TOUCHCURSOR,
  _ADJUST
};

enum planck_keycodes {
  BEPO = SAFE_RANGE,
  AZERTY,
  SHIFT,
  ALTGR,
  ALT_TAB, // super alt/tab macro
  ASFT_I,
  ASFT_S,
  // using alt+code, HX_XXXX enumeration muste be in exact same order
  AL_ECIR, // must be the first in range
  AL_UECR,
  AL_UOE,
  AL_UAE,
  AL_UUGR,
  AL_EACU,
  AL_EGRV,
  AL_AGRV,
  AL_UCCE,
  AL_OE,
  AL_AE,
  AL_UGRV,
  AL_CPRT,
  AL_QUOT,
  AL_TM,
  AL_LDAQ,
  AL_RDAQ,
  AL_R,
  AL_ELP,
  AL_DQUA,
  AL_QUAD,
  AL_P,
  AL_DQUB,
  AL_X,
  AL_EMP,
  AL_PML,
  AL_PMS,
  AL_OOQ,
  AL_OOT,
  AL_TOF,
  AL_QMK,
  AL_CRC, // must be the last in range
  UC_REE,
  UC_LEQL,
  UC_GEQL,
  // custom keycodes
  MVI_CLK, // clear keyboard
  MVI_CXU, // C-x u
  MVI_CCC, // C-c ;
  MU_CCED  // Ç when tapped, Mute when held  
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define MATHS OSL(_MATHS)

// Custom macros
#define TC_SPC     LT(_TOUCHCURSOR, KC_SPC)  // L-ayer T-ap T-ouch C-ursor on Space
#define TC_ENT     LT(_TOUCHCURSOR, KC_ENT)  // L-ayer T-ap T-ouch C-ursor on Enter
#define MVI_CUT  S(KC_DEL)    // cut
#define MVI_CPY  C(KC_INS)    // copy
#define MVI_PST  S(KC_INS)    // paste
#define XCV_CUT  C(FR_X)    // cut
#define XCV_CPY  C(FR_C)    // copy
#define XCV_PST  C(FR_V)    // paste
#define CTL_TAB  C(KC_TAB)
#define CS_TAB   C(S(KC_TAB))
#define MVI_MEN  LSFT(KC_F10)
  
#define SFT_CAPS LSFT_T(KC_CAPS)    // M-od T-ap LShift / Capslock
#define SFT_ENT  RSFT_T(KC_ENT)    // M-od T-ap RShift / Enter

// Left-hand home row mods
#define GUI_A  LGUI_T(BP_A)
#define ALT_U  LALT_T(BP_U)
#define SFT_I  LALT_T(BP_I)
#define CTRL_E LCTL_T(BP_E)

#define AGUI_A  LGUI_T(FR_A)
#define AALT_U  LALT_T(FR_U)
#define ACTRL_E LCTL_T(FR_E)

#define GUI_WHD LGUI_T(KC_WH_D)
#define ALT_MSL LALT_T(KC_MS_L)
#define SFT_MSD LSFT_T(KC_MS_D)
#define CTR_MSR LCTL_T(KC_MS_R)

// Right-hand home row mods
#define CTRL_T LCTL_T(BP_T)
#define ALT_R  LALT_T(BP_R)
#define SFT_S  LALT_T(BP_S)
#define GUI_N  RGUI_T(BP_N)

#define ACTRL_T LCTL_T(FR_T)
#define AALT_R  LALT_T(FR_R)
#define AGUI_N  RGUI_T(FR_N)

// indexes for alt_codes, must be in exact same order as AL_XXXX keycodes
enum windows_alt_codes_entries {
  HX_ECIR=0,
  HX_UECR,
  HX_UOE,
  HX_UAE,
  HX_UUGR,
  HX_EACU,
  HX_EGRV,
  HX_AGRV,
  HX_UCCE,
  HX_OE,
  HX_AE,
  HX_UGRV,
  HX_CPRT,
  HX_QUOT,
  HX_TM,
  HX_LDAQ,
  HX_RDAQ,
  HX_R,
  HX_ELP,
  HX_DQUA,
  HX_QUAD,
  HX_P,
  HX_DQUB,
  HX_X,
  HX_EMP,
  HX_PML,
  HX_PMS,
  HX_OOQ,
  HX_OOT,
  HX_TOF,
  HX_QMK,
  HX_CRC,
};

const uint16_t windows_alt_codes[] = {
  [HX_ECIR] = 0x0234,
  [HX_UECR] = 0x0202,
  [HX_UOE]  = 0x0140,
  [HX_UAE]  = 0x0198,
  [HX_UUGR] = 0x0217,
  [HX_EACU] = 0x0201,
  [HX_EGRV] = 0x0200,
  [HX_AGRV] = 0x0192,
  [HX_UCCE] = 0x0199,
  [HX_OE]   = 0x0156,
  [HX_AE]   = 0x0230,
  [HX_UGRV] = 0x0249,
  [HX_CPRT] = 0x0169,
  [HX_QUOT] = 0x0146,
  [HX_TM]   = 0x0153,
  [HX_LDAQ] = 0x0171,
  [HX_RDAQ] = 0x0187,
  [HX_R]    = 0x0174,
  [HX_ELP]  = 0x0133,
  [HX_DQUA] = 0x0150,
  [HX_QUAD] = 0x0151,
  [HX_P]    = 0x0182,
  [HX_DQUB] = 0x0132,
  [HX_X]    = 0x0215,
  [HX_EMP]  = 0x0216,
  [HX_PML]  = 0x0137,
  [HX_PMS]  = 0x0177,
  [HX_OOQ]  = 0x0188,
  [HX_OOT]  = 0x0189,
  [HX_TOF]  = 0x0190,
  [HX_QMK]  = 0x0191,
  [HX_CRC]  = 0x0136
};

enum unicodes_entries {
  U_REE=0,
  U_LEQL,
  U_GEQL
};

const char unicodes_list[][5] = {
  [U_REE] = "211d",
  [U_LEQL] = "2a7d",
  [U_GEQL] = "2a7e"
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Bépo
 *,-----------------------------------------------------------------------------------------------------------.
 *| W      | B      | É      | P      | O      | È      | ^      | V      | D      | L      | J      | Bksp   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Z      | A      | U      | I      | E      | ,      | C      | T      | S      | R      | N      | M      |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Ê      | À      | Y      | X      | .      | K      | '      | Q      | G      | H      | F      | Ç      |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Ctrl   | Left   | Down   | AltGr  |Lower   | Enter  | Space  | Raise  | AltGr  | Up     |Right   | Ent    |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_BEPO] = LAYOUT_planck_grid(
    BP_W,    BP_B,     BP_EACU, BP_P,    BP_O,   BP_EGRV, BP_DCIR, BP_V,    BP_D,    BP_L,    BP_J,    KC_BSPC,
    BP_Z,    GUI_A,    ALT_U,   SFT_I,   CTRL_E, BP_COMM, BP_C,    CTRL_T,  SFT_S,   ALT_R,   GUI_N,   BP_M,
    BP_ECIR, BP_AGRV,  BP_Y,    BP_X,    BP_DOT, BP_K,    BP_QUOT, BP_Q,    BP_G,    BP_H,    BP_F,    MU_CCED,
    KC_LCTL, KC_LEFT,  KC_DOWN, KC_ALGR, LOWER,  TC_ENT,  TC_SPC,  RAISE,   KC_ALGR, KC_UP,   KC_RGHT, KC_ENT
),

/* Bépo sur Azerty
 *,-----------------------------------------------------------------------------------------------------------.
 *| w      | b      | é      | p      | o      | è      | ^      | v      | d      | l      | j      | Bksp   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| z      | a      | u      | i      | e      | ,      | c      | t      | s      | r      | n      | m      |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| ê      | à      | y      | x      | .      | k      | '      | q      | g      | h      | f      | ç      |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Ctrl   | Left   | Down   | AltGr  |Lower   | Enter  | Space  | Raise  | AltGr  | Up     |Right   | Enter  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_AZERTY] = LAYOUT_planck_grid(
    FR_W,    FR_B,     FR_EACU, FR_P,    FR_O,   FR_EGRV, FR_CIRC, FR_V,    FR_D,    FR_L,    FR_J,    KC_BSPC,
    FR_Z,    AGUI_A,   AALT_U,  ASFT_I,  ACTRL_E, FR_COMM, FR_C,   ACTRL_T, ASFT_S,  AALT_R,  AGUI_N,   FR_M,
    AL_ECIR, FR_AGRV,  FR_Y,    FR_X,    FR_DOT, FR_K,    FR_QUOT, FR_Q,    FR_G,    FR_H,    FR_F,    MU_CCED,
    SHIFT,   KC_LEFT,  KC_DOWN, ALTGR,   LOWER,  TC_ENT,  TC_SPC,  RAISE,   ALTGR,   KC_UP,   KC_RGHT, SHIFT
),

/* Shifted keys
 *,-----------------------------------------------------------------------------------------------------------.
 *| W      | B      | É      | P      | O      | È      | !      | V      | D      | L      | J      | Bksp   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Z      | A      | U      | I      | E      | ;      | C      | T      | S      | R      | N      | M      |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Ê      | À      | Y      | X      | :      | K      | ?      | Q      | G      | H      | F      | Ç      |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Ctrl   | Left   | Down   | AltGr  | Lower  | Enter  | Spce   | Raise  | AltGr  | Up     | Right  | Enter  |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_SHIFT] = LAYOUT_planck_grid(
    _______, _______, AL_EACU, _______, _______, AL_EGRV, FR_EXLM, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, FR_SCLN, _______, _______, _______, _______, _______, _______,
    AL_UECR, AL_AGRV, _______, _______, FR_COLN, _______, FR_QUES, _______, _______, _______, _______, AL_UCCE,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Alt. Gr.
 *,-----------------------------------------------------------------------------------------------------------.
 *|        | |      |        | &      | oe     | `      |        |        | Maths  |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | ae     | ù      | ¨      |        | '      |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| /      | \      | {      | }      | ...    | ~      | ?      |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_ALTGR] = LAYOUT_planck_grid(
    _______, FR_PIPE, _______, FR_AMPR, AL_OE,   FR_GRV,  _______, _______, MATHS,   _______, _______, _______,
    _______, AL_AE,   AL_UGRV, FR_DIAE, FR_EURO, FR_QUOT, _______, _______, _______, _______, _______, _______,
    FR_SLSH, FR_BSLS, FR_LCBR, FR_RCBR, AL_ELP,  FR_TILD, AL_QMK,  _______, FR_MICR, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, FR_UNDS, _______, _______, _______, _______, _______
),

/* Shifted Alt. Gr.
 *,-----------------------------------------------------------------------------------------------------------.
 *|        | _      |        | §      | OE     |        |        |        |        | £      |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | AE     | Ù      |        | ¤      |        | ©      | TM     |        | ®      |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| ^      |        |        |        |        |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_SHALT] = LAYOUT_planck_grid(
    _______, FR_UNDS, _______, FR_SECT, AL_UOE,  _______, _______, _______, _______, FR_PND,  _______, _______,
    _______, AL_UAE,  AL_UUGR, _______, FR_CURR, _______, AL_CPRT, AL_TM,   _______, AL_R,    _______, _______,
    FR_CIRC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Lower
 *,-----------------------------------------------------------------------------------------------------------.
 *| $      | "      | «      | »      | (      | )      | @      | +      | -      |   /    | *      |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Esc    | C-x u  | <      | >      | [      | ]      | PScr   | =      | C-Tab  | A-Tab  | Tab    | Menu   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| CapsL  | A-Tab  | <or=   | >or=   | C-Tab  | Tab    | C-c ;  | %      | Cut    | Copy   |Paste   | Mute   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | Home   | PgDn   |        |        |        |        |        |        | PgUp   | End    |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    BP_DLR,  BP_DQUO, BP_LDAQ, BP_RDAQ, BP_LPRN, BP_RPRN, BP_AT,   BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR, _______,
    KC_ESC,  MVI_CXU, BP_LABK, BP_RABK, BP_LBRC, BP_RBRC, KC_PSCR, BP_EQL,  _______, _______, KC_TAB,  MVI_MEN,
    KC_CAPS, ALT_TAB, BP_LEQL, BP_GEQL, CTL_TAB, _______, MVI_CCC, BP_PERC, MVI_CUT, MVI_CPY, MVI_PST, KC_VOLD,
    _______, KC_HOME, KC_PGDN, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_END,  _______
),

/* Lower
 *,-----------------------------------------------------------------------------------------------------------.
 *| $      | "      | <<     | >>     | (      | )      | @      | +      | -      | /      | *      |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Esc    | C-x u  | <      | >      | [      | ]      | PrtScr | =      | C-Tab  | A-Tab  | Tab    | Menu   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| CapsL  | A-Tab  |        |        | C-Tab  | Tab    | C-c ,  | %      | Cut    | Copy   | Paste  | Vol-   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | Home   | Pg Dn  |        |        |        |        |        |        | Pg Up  | End    |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_AZ_LOWER] = LAYOUT_planck_grid(
    FR_DLR,  FR_DQUO, AL_LDAQ, AL_RDAQ, FR_LPRN, FR_RPRN, FR_AT,   FR_PLUS, FR_MINS, FR_SLSH, FR_ASTR, _______,
    _______, _______, FR_LABK, FR_RABK, FR_LBRC, FR_RBRC, _______, FR_EQL,  _______, _______, _______, _______,
    _______, _______, UC_LEQL, UC_GEQL, _______, _______, _______, FR_PERC, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


/* Lower Alt. Gr.
 *,-----------------------------------------------------------------------------------------------------------.
 *| -      | --     |        |        |        |        | ^      | +/-    |        |        | x      |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        | %o     |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_LOWERAG] = LAYOUT_planck_grid(
    AL_DQUA, AL_QUAD, _______, _______, _______, _______, AL_CRC,  AL_PMS,  _______, _______, AL_X,    _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, AL_PML,  _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise
 *,-----------------------------------------------------------------------------------------------------------.
 *| #      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Esc    | F1     | F2     | F3     | F4     | F5     | F6     | °      | C-Tab  | A-Tab  | Tab    | Menu   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| CapsLck| F7     | F8     | F9     | F10    | F11    | F12    | `      | Cut    | Copy   | Paste  | Mute   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | Mute   | Ins    |        |        |        |        |        |        | PScr   | Del    |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    BP_HASH, BP_1,    BP_2,   BP_3,    BP_4,    BP_5,    BP_6,    BP_7,    BP_8,    BP_9,    BP_0,    _______,
    KC_ESC,  KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,   BP_DEG, CTL_TAB, ALT_TAB, KC_TAB,  MVI_MEN,
    KC_CAPS, KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  BP_GRV,  XCV_CUT, XCV_CPY, XCV_PST, KC_VOLU,
    _______, KC_MUTE, KC_INS, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_DEL,  _______
),

/* Raise
 *,-----------------------------------------------------------------------------------------------------------.
 *| #      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Esc    | F1     | F2     | F3     | F4     | F5     | F6     | °      | C-Tab  | A-Tab  | Tab    | Menu   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| CapsL  | F7     | F8     | F9     | F10    | F11    | F12    | `      | Cut    | Copy   | Paste  | Vol+   |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | Mute   | Insert |        |        |        |        |        |        | PrtScr | Del    |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_AZ_RAISE] = LAYOUT_planck_grid(
    FR_HASH, FR_1,    FR_2,    FR_3,    FR_4,    FR_5,    FR_6,    FR_7,    FR_8,    FR_9,    FR_0,    _______,
    _______, _______, _______, _______, _______, _______, _______, FR_DEG,  _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, FR_GRV,  _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise Alt. Gr.
 *,-----------------------------------------------------------------------------------------------------------.
 *| |P     |        |        |        |        |        |        |        | 1/4    | 1/2    | 3/4    |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_RAISEAG] = LAYOUT_planck_grid(
    AL_P,    AL_DQUB, _______, _______, _______, _______, _______, _______, AL_OOQ,  AL_OOT,  AL_TOF,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Mathematical Layer
 *,-----------------------------------------------------------------------------------------------------------.
 *|        |        |        |        | 0      |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_MATHS] = LAYOUT_planck_grid(
    _______, _______, _______, _______, AL_EMP,  _______, _______, _______, UC_REE,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Touch Cursor
 *,-----------------------------------------------------------------------------------------------------------.
 *| Reset  | KeyClr |        |        |        |        |        | TermOn | TermOff|        |        | Del    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Esc    |        | MusMod | Aud On | Aud Off| AG Norm| AG Swap| Bépo   |        |        |        | Debug  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | Voice- | Voice+ | Mus On | Mus Off| Midi On| MidiOff|        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_TOUCHCURSOR] = LAYOUT_planck_grid(
    KC_TAB,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN1, KC_INS,  KC_HOME, KC_UP,   KC_PGUP, KC_BTN1, KC_ACL2,
    KC_ESC,  GUI_WHD, ALT_MSL, KC_MS_D, CTR_MSR, KC_BTN2, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_BTN2, KC_ACL1,
    KC_CAPS, KC_ACL2, KC_ACL1, KC_ACL0, KC_BTN4, KC_BTN3, KC_BTN5, KC_END,  KC_DOWN, KC_PGDN, KC_BTN3, KC_ACL0,
    _______, _______, _______, _______, _______, KC_SPC,  _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 *,-----------------------------------------------------------------------------------------------------------.
 *| Reset  | KeyClr |        |        |        |        |        | TermOn | TermOff|        |        | Del    |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *| Esc    |        | MusMod | Aud On | Aud Off| AG Norm| AG Swap| Bépo   |        |        |        | Debug  |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        | Voice- | Voice+ | Mus On | Mus Off| Midi On| MidiOff|        |        |        |        |        |
 *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *|        |        |        |        |        |        |        |        |        |        |        |        |
 *`-----------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RESET,   MVI_CLK, _______, _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,
    KC_ESC,  _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, BEPO,    AZERTY,  _______, _______, DEBUG,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

uint16_t hextokeycode(int hex) {
    if (hex == 0x0) {
        return KC_P0;
    } else if (hex < 0xA) {
        return KC_P1 + (hex - 0x1);
    } else {
        return KC_A + (hex - 0xA);
    }
}

void send_alt_code(uint16_t altcode)
{
  mod_state = get_mods(); // save state of mods and delete Shift and Alt
  del_mods(MOD_MASK_SA);
  register_code(KC_LALT);
  for (int i = 12; i >= 0; i -= 4) {
    tap_code(hextokeycode((altcode >> i) & 0xF));
  }
  unregister_code(KC_LALT);
  set_mods(mod_state); // put back the mods state
}

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  if (IS_LAYER_ON_STATE(state, _AZERTY)) {
    if (IS_LAYER_ON_STATE(state, _LOWER))  {
      state |= ((layer_state_t)1 << _AZ_LOWER);
    }
    else {
      state &= ~((layer_state_t)1 << _AZ_LOWER);
    }
    if (IS_LAYER_ON_STATE(state, _RAISE))  {
      state |= ((layer_state_t)1 << _AZ_RAISE);
    }
    else {
      state &= ~((layer_state_t)1 << _AZ_RAISE);
    }
  }
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  state = update_tri_layer_state(state, _SHIFT, _ALTGR, _SHALT);
  state = update_tri_layer_state(state, _LOWER, _ALTGR, _LOWERAG);
  state = update_tri_layer_state(state, _RAISE, _ALTGR, _RAISEAG);
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case BEPO: // base layer, bépo layout using azerty driver on windows
      if (record->event.pressed) {
	set_single_persistent_default_layer(_BEPO);
 	layer_clear();
      }
      return false;
      break;
  case AZERTY: // base layer, bépo layout using azerty driver on windows
      if (record->event.pressed) {
        set_single_persistent_default_layer(_AZERTY);
      }
      return false;
      break;
  /* case AZ_LOWER: // turn on layer _SHIFT with modifier Left Shift held */
  /*     if (record->event.pressed) { */
  /*       layer_on(_LOWER); */
  /*       layer_on(_AZ_LOWER); */
  /*     } */
  /*     else { */
  /*       layer_off(_AZ_LOWER); */
  /*       layer_off(_LOWER); */
  /*     } */
  /*     return false; */
  /*     break; */
  /* case AZ_RAISE: // turn on layer _SHIFT with modifier Left Shift held */
  /*     if (record->event.pressed) { */
  /*       layer_on(_RAISE); */
  /*       layer_on(_AZ_RAISE); */
  /*     } */
  /*     else { */
  /*       layer_off(_AZ_RAISE); */
  /*       layer_off(_RAISE); */
  /*     } */
  /*     return false; */
  /*     break; */
  case SHIFT: // turn on layer _SHIFT with modifier Left Shift held
      if (record->event.pressed) {
	register_code(KC_LSFT);
        layer_on(_SHIFT);
      }
      else {
        layer_off(_SHIFT);
	unregister_code(KC_LSFT);
      }
      return false;
      break;
  case ALTGR: // turn on layer _ALTGR with modifier AltGr held
      if (record->event.pressed) {
	register_code(KC_ALGR);
        layer_on(_ALTGR);
      }
      else {
        layer_off(_ALTGR);
	unregister_code(KC_ALGR);
      }
      return false;
      break;
  case ASFT_I: // personnal Mod-Tap for _SHIFT layer and KC_LSFT on
    if (record->event.pressed) { // key is pressed, set timer
      is_sft_i_pressed = true;
      sft_i_timer = timer_read();
    }
    else { // key is releasd, see if it was tapped (send FR_I)
      // or held (in this case, layer _SHIFT was turned on and Left Shift held)
      is_sft_i_pressed = false;
      if (!is_sft_i_active) {
	tap_code16(FR_I);
      }
      else {
	layer_off(_SHIFT);
	unregister_code(KC_LSFT);
	is_sft_i_active = false;
      }
    }
    break;
  case ASFT_S: // personnal Mod-Tap for _SHIFT layer and KC_LSFT on
    // see SFT_I for details
    if (record->event.pressed) {
      is_sft_s_pressed = true;
      sft_s_timer = timer_read();
    }
    else {
      is_sft_s_pressed = false;
      if (!is_sft_s_active) {
	tap_code16(FR_S);
      }
      else {
	layer_off(_SHIFT);
	unregister_code(KC_LSFT);
	is_sft_s_active = false;
      }
    }
    break;
  case UC_REE...UC_GEQL:
    if (record->event.pressed) { // blackboard R
      mod_state = get_mods(); // save state of mods and delete Shift, Control and Alt
      del_mods(MOD_MASK_CSA);
      SEND_STRING(SS_TAP(X_RCTL)"u");
      send_string(unicodes_list[keycode-UC_REE]);
      SEND_STRING("\n");
      set_mods(mod_state); // put back the mods state
    }
    return false;
    break;
  case AL_ECIR ... AL_CRC: // character rendered using alt-code on windows
    if (record->event.pressed) {
      send_alt_code(windows_alt_codes[keycode-AL_ECIR]);
    }
    return false;
    break;
  case MU_CCED: // personnal Mod-Tap for 2 keycodes: KC_MUTE (held) and FR_CCEDr (tapped)
    if (record->event.pressed) {
      mu_cced_timer = timer_read();
    } else {
      if (timer_elapsed(mu_cced_timer) < TAPPING_TERM) {
	tap_code16(FR_CCED);
      }
      else {
	tap_code(KC_MUTE);
      }
    }
    break;
  case FR_EXLM: // for characters on the _SHIFT layer, remove KC_LSFT modifier while using the keycode
  case FR_SCLN:
  case FR_COLN:
  case FR_QUES:
    if (record->event.pressed) {
      unregister_code(KC_LSFT);
    }
    else {
      register_code(KC_LSFT);	
    }
    break;
  case FR_PIPE: // for characters on the _ALTGR layer, remove KC_ALGR modifier while using the keycode
  case FR_AMPR:
  case FR_GRV:
  case FR_DIAE:
  case FR_EURO:
  case FR_QUOT:
  case FR_SLSH:
  case FR_BSLS:
  case FR_LCBR:
  case FR_RCBR:
  case FR_TILD:
  case FR_MICR:
    if (record->event.pressed) {
      unregister_code(KC_ALGR);	
    }
    else {
      register_code(KC_ALGR);	
    }
    break;
  case FR_UNDS: // this character is on _SHALGR and _ALTGR layers
    if (record->event.pressed) {
      unregister_code(KC_ALGR);
      if (get_mods() & MOD_BIT(KC_LSFT)) {
	is_lsft_on = true;
	unregister_code(KC_LSFT);
      }
    }
    else {      
      register_code(KC_ALGR);
      if (is_lsft_on) {
	is_lsft_on = false;
	register_code(KC_LSFT);
      }
    }
    break;
  case FR_SECT: // for characters on the _SHALGR layer, remove both KC_LSFT and KC_ALGR modifier while using the keycode
  case FR_PND:
  case FR_CURR:
  case FR_CIRC:
    if (record->event.pressed) {
      unregister_code(KC_ALGR);	
      unregister_code(KC_LSFT);	
    }
    else {
      register_code(KC_LSFT);	
      register_code(KC_ALGR);	
    }
    break;
  case MVI_CLK:
    if (record->event.pressed) { // clear all mods and keys currently pressed
      clear_keyboard();
    }
    return false;
    break;
  case MVI_CXU:
    if (record->event.pressed) { // C-x u, undo in Emacs
      register_code(KC_LCTL);
      tap_code(FR_X);
      unregister_code(KC_LCTL);
      tap_code16(FR_U);
    }
    return false;
    break;
  case MVI_CCC:
    if (record->event.pressed) { // C-c ;, comment/uncomment region in Emacs/AucTeX
      register_code(KC_LCTL);
      tap_code(FR_C);
      unregister_code(KC_LCTL);
      tap_code16(FR_SCLN);
    }
    return false;
    break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;


bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_DOWN);
#else
      tap_code(KC_PGDN);
#endif
    } else {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_UP);
#else
      tap_code(KC_PGUP);
#endif
    }
  }
  return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
  if(is_sft_i_pressed && !is_sft_i_active){
    if (timer_elapsed(sft_i_timer) > TAPPING_TERM) {
      is_sft_i_active = true;
      register_code(KC_LSFT);
      layer_on(_SHIFT);
    }
  }
  if(is_sft_s_pressed && !is_sft_s_active){
    if (timer_elapsed(sft_s_timer) > TAPPING_TERM) {
      is_sft_s_active = true;
      register_code(KC_LSFT);
      layer_on(_SHIFT);
    }
  }
#ifdef AUDIO_ENABLE
  if (muse_mode) {
    if (muse_counter == 0) {
      uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
      if (muse_note != last_muse_note) {
	stop_note(compute_freq_for_midi_note(last_muse_note));
	play_note(compute_freq_for_midi_note(muse_note), 0xF);
	last_muse_note = muse_note;
      }
    }
    muse_counter = (muse_counter + 1) % muse_tempo;
  } else {
    if (muse_counter) {
      stop_all_notes();
      muse_counter = 0;
    }
  }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
