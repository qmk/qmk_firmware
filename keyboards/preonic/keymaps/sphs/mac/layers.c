#include QMK_KEYBOARD_H
#include "keycodes.c"

#define LAYOUT_preonic_grid_mac(...) LAYOUT_preonic_grid(__VA_ARGS__)

/* Layer 0: BASE (Colemak-DH)
 * ,-----------------------------------------------------------------------------------------------.
 * |   `   |   6   |   3   |   1   |   2   |   7   |   9   |   4   |   0   |   5   |   8   |  Del  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |TAB_LLM|   Q   |   W   |   F   |   P   |   B   |   J   |   L   |   U   |   Y   |   ;   |Opt | \|
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |IME_CMD|   A   |   R   |   S   |   T   |   G   |   M   |   N   |   E   |   I   |   O   |   '   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  |   Z   |   X   |   C   |   D   |   V   |   K   |   H   |   ,   |   .   |   /   |ENT_FNM|
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  | Left  | Right | Lower |BSP_MKM| Ctrl  | Shift |SPC_NVM| Raise | Down  |  Up   | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
#define LAYER_BSM \
KC_GRV,  KC_6,    KC_3,    KC_1,    KC_2,    KC_7,    KC_9,    KC_4,    KC_0,    KC_5,    KC_8,    KC_DEL, \
TAB_LLM, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, BSL_OPT, \
IME_CMD, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
KC_ESC,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, ENT_FNM, \
KC_ESC,  KC_LEFT, KC_RGHT, OSL_NMM, BSP_MKM, KC_LCTL, OSM_SFT, SPC_NVM, OSL_SMM, KC_DOWN, KC_UP,   KC_ENT

/* Layer 1: NUMBER (Lower)
 * ,-----------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |       |       |       |       |       |  Del  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Tab  | KP 6  | KP 3  | KP 1  | KP 2  | KP 7  | KP 9  | KP 4  | KP 0  | KP 5  | KP 8  |  Opt  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Cmd  |   6   |   3   |   1   |   2   |   7   |   9   |   4   |   0   |   5   |   8   | KP =  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  | KP /  | KP *  | KP -  | KP +  |   (   |   )   | KP .  |   ,   |   %   |   ^   |KPEnter|
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  | Left  | Right |SET_NMM| Bksp  | Ctrl  | Shift |SET_BSM|SET_BSM| Down  |  Up   | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
#define LAYER_NMM \
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
KC_TAB,  KC_P6,   KC_P3,   KC_P1,   KC_P2,   KC_P7,   KC_P9,   KC_P4,   KC_P0,   KC_P5,   KC_P8,   KC_LOPT, \
_______, KC_6,    KC_3,    KC_1,    KC_2,    KC_7,    KC_9,    KC_4,    KC_0,    KC_5,    KC_8,    KC_PEQL, \
_______, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_LPRN, KC_RPRN, KC_PDOT, KC_COMM, KC_PERC, KC_CIRC, KC_PENT, \
_______, _______, _______, SET_NMM, KC_BSPC, _______, _______, SET_BSM, SET_BSM, _______, _______, _______

/* Layer 2: SYMBOL (Raise)
 * ,-----------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |       |       |       |       |       |  Del  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Tab  |       |   %   |   [   |   ]   |       |       |       |   `   |   $   |       |  Opt  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Cmd  |   <   |   >   |   (   |   )   |   |   |   ~   |   -   |   +   |   =   |   _   |   "   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  |   ^   |   @   |   {   |   }   |   &   |   !   |   ?   |   :   |   *   |   #   | Enter |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  | Left  | Right |SET_BSM| Bksp  | Ctrl  | Shift |SET_BSM|SET_SMM| Down  |  Up   | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
#define LAYER_SMM \
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
KC_TAB,  XXXXXXX, KC_PERC, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV,  KC_DLR,  XXXXXXX, KC_LOPT, \
KC_LCMD, KC_LT,   KC_GT,   KC_LPRN, KC_RPRN, KC_PIPE, KC_TILD, KC_MINS, KC_PLUS, KC_EQL,  KC_UNDS, KC_DQUO, \
_______, KC_CIRC, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR, KC_EXLM, KC_QUES, KC_COLN, KC_ASTR, KC_HASH, KC_ENT, \
_______, _______, _______, SET_BSM, KC_BSPC, _______, _______, SET_BSM, SET_SMM, _______, _______, _______

/* Layer 3: MOUSE KEYS (Backspace)
 * ,-----------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |       |       |       |       |       |  Del  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Tab  |       |       | MsUp  |       |       |       |MWLeft | MWUp  |MWRight|       |  Opt  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Cmd  |       |MsLeft |MsDown |MsRight|       |       |MsBtn1 |MsBtn3 |MsBtn2 |       |SET_BSM|
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  |       |       |       |       |       |       |MsBtn4 |MWDown |MsBtn5 |       | Enter |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  | Left  | Right |SET_BSM| Bksp  | Ctrl  | Shift | Space |SET_BSM| Down  |  Up   | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
#define LAYER_MKM \
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
KC_TAB,  XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_U, KC_WH_R, XXXXXXX, KC_LOPT, \
KC_LCMD, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, SET_BSM, \
_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN4, KC_WH_D, KC_BTN5, XXXXXXX, KC_ENT, \
_______, _______, _______, SET_BSM, KC_BSPC, _______, _______, KC_SPC,  SET_BSM, _______, _______, _______

/* Layer 4: NAVIGATION + MEDIA (Space)
 * ,-----------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |       |       |       |       |       |  Del  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Tab  |  Ins  | PgUp  |  Up   | PgDn  |  Del  |       |Rewind | Vol+  |Forward|       |  Opt  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Cmd  |MOV_LSM| Left  | Down  | Right |MOV_LEM|       | Play  | Mute  | Stop  |       |SET_BSM|
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  |DEL_LSM|MOV_PWM|DEL_LNM|MOV_NWM|DEL_LEM|       | Home  | Vol-  |  End  |       | Enter |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  | Left  | Right |SET_BSM|DEL_PWM| Ctrl  | Shift |SET_BSM|SET_BSM| Down  |  Up   | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
#define LAYER_NVM \
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
KC_TAB,  KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_DEL,  XXXXXXX, KC_MRWD, KC_VOLU, KC_MFFD, XXXXXXX, KC_LOPT, \
KC_LCMD, MOV_LSM, KC_LEFT, KC_DOWN, KC_RGHT, MOV_LEM, XXXXXXX, KC_MPLY, KC_MUTE, KC_MSTP, XXXXXXX, SET_BSM, \
_______, DEL_LSM, MOV_PWM, DEL_LNM, MOV_NWM, DEL_LEM, XXXXXXX, KC_HOME, KC_VOLD, KC_END,  XXXXXXX, KC_ENT, \
_______, _______, _______, SET_BSM, DEL_PWM, _______, _______, SET_BSM, SET_BSM, _______, _______, _______

/* Layer 5: FUNCTION (Enter)
 * ,-----------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |       |       |       |       |       |  Del  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Tab  | Reset | Debug |EEPRST |       | NLCK  | SLCK  | CAPS  |       | Wake  | Sleep |  Opt  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Cmd  |  F6   |  F3   |  F1   |  F2   |  F7   |  F9   |  F4   |  F10  |  F5   |  F8   |SET_BSM|
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  |LYT_WIN|       |  F11  |  F12  | Brt-  | Brt+  | Calc  | Print | Menu  | Pause | Enter |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  Esc  | Left  | Right |SET_BSM| Bksp  | Ctrl  | Shift |SET_BSM|SET_BSM| Down  |  Up   | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
#define LAYER_FNM \
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
KC_TAB,  RESET,   DEBUG,   EEP_RST, XXXXXXX, KC_NLCK, KC_SLCK, KC_CAPS, XXXXXXX, KC_WAKE, KC_SLEP, KC_LOPT, \
KC_LCMD, KC_F6,   KC_F3,   KC_F1,   KC_F2,   KC_F7,   KC_F9,   KC_F4,   KC_F10,  KC_F5,   KC_F8,   SET_BSM, \
_______, LYT_WIN, XXXXXXX, KC_F11,  KC_F12,  KC_BRID, KC_BRIU, KC_CALC, KC_PSCR, KC_APP,  KC_PAUS, KC_ENT, \
_______, _______, _______, SET_BSM, KC_BSPC, _______, _______, SET_BSM, SET_BSM, _______, _______, _______

/* Layer 6: LAYER LOCKS (Tab)
 * ,-----------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |SET_BSM|       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |SET_FNM|
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |SET_NMM|SET_MKM|       |       |SET_NVM|SET_SMM|       |       |       |
 * `-----------------------------------------------------------------------------------------------'
 */
#define LAYER_LLM \
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
SET_BSM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SET_FNM, \
XXXXXXX, XXXXXXX, XXXXXXX, SET_NMM, SET_MKM, XXXXXXX, XXXXXXX, SET_NVM, SET_SMM, XXXXXXX, XXXXXXX, XXXXXXX
