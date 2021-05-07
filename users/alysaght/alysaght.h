#pragma once
#include QMK_KEYBOARD_H

enum custom_layers {
  _COLEMAK,
  _QWERTY,
  _FFXIV,
  _MEDIA,
  _NAVR,
  _MOUSE,
  _NSSL,
  _NSL,
  _FUNL,
  _ADJUST
};

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  FFXIV,
  BACKLIT,
  R_ASIGN,
  R_PIPE,
  GITFETC,
  GITPULL,
  GITPUSI,
  GITPUSO,
  GITREBA,
  GITADD,
  GITCOMM,
  GITBRCH,
  GITCOUT,
  GITCOBR,
  GITSTAT,
  GITBDEL
};

// tap-hold modifier keys
// Left Home row
#define HOMQ_A  LSFT_T(KC_A) //QWERTY
#define HOMQ_S  LCTL_T(KC_S) //QWERTY
#define HOMQ_D  LALT_T(KC_D) //QWERTY
#define HOMQ_F  LGUI_T(KC_F) //QWERTY

#define HOMK_A  LSFT_T(KC_A) //COLEMAK
#define HOMK_R  LCTL_T(KC_R) //COLEMAK
#define HOMK_S  LALT_T(KC_S) //COLEMAK
#define HOMK_T  LGUI_T(KC_T) //COLEMAK

// Right Home row
#define HOMQ_J  LGUI_T(KC_J)       //QWERTY
#define HOMQ_K  LALT_T(KC_K)       //QWERTY
#define HOMQ_L  LCTL_T(KC_L)       //QWERTY
#define HOMQ_QUOT  LSFT_T(KC_QUOT) //QWERTY

#define HOMK_N  LGUI_T(KC_N)       //COLEMAK
#define HOMK_E  LALT_T(KC_E)       //COLEMAK
#define HOMK_I  LCTL_T(KC_I)       //COLEMAK
#define HOMK_O  LSFT_T(KC_O)       //COLEMAK

// Left Thumb keys
#define LT_ESC  LT(_MEDIA, KC_ESC)
#define LT_BSPC LT(_NAVR, KC_BSPC)
#define LT_TAB  LT(_MOUSE, KC_TAB)

// Right Thumb keys
#define LT_ENT  LT(_NSSL, KC_ENT)
#define LT_SPC  LT(_NSL, KC_SPC)
#define LT_DEL  LT(_FUNL, KC_DEL)

// useful shortcuts
#define UNDO  LGUI(KC_Z)
#define CUT   LGUI(KC_X)
#define COPY  LGUI(KC_C)
#define PASTE LGUI(KC_V)

#define NX_HOME LCTL(KC_A)
#define NX_END  LCTL(KC_E)
#define NX_WB   LALT(KC_B)
#define NX_WF   LALT(KC_F)

#define SCR_GRB SGUI(C(KC_4))

// LAYOUT wrappers to handle keycode bundles below
#define LAYOUT_custom_wrapper(...)   LAYOUT(__VA_ARGS__)




/* Alpha layer thumb keys
 *
 * |======+======+======+======+======+        +======+======+======+======+======|
 * |  NO  |  NO  |LTEsc |LTBksp|LTTab |        |LTEnt |LTSpc |LTDel |  NO  |  NO  |
 * `----------------------------------'        `----------------------------------'
 */
#define _________________ALPHA_LT__________________        XXXXXXX, XXXXXXX, LT_ESC,  LT_BSPC, LT_TAB
#define _________________ALPHA_RT__________________        LT_ENT,  LT_SPC,  LT_DEL,  XXXXXXX, XXXXXXX

/* Alpha layer number row
 *
 * ,----------------------------------.        ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |        |   6  |   7  |   8  |   9  |   0  |
 * |======+======+======+======+======+        +======+======+======+======+======|
 */

#define _________________ALPHA_LN__________________        KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________ALPHA_RN__________________        KC_6,    KC_7,    KC_8,    KC_9,    KC_0

/* QWERTY layer
 *
 * ,----------------------------------.        ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |        |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |A-Shft|S-Ctrl|D-Alt |F-GUI |   G  |        |   H  |J-GUI |K-Alt |L-Ctrl|'-Shft|
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |        |   N  |   M  |   ,  |   .  |   /  |
 * |======+======+======+======+======+        +======+======+======+======+======|
 * |  NO  |  NO  |LTEsc |LTBksp|LTTab |        |LTEnt |LTSpc |LTDel |  NO  |  NO  |   // ALPHA_*T
 * `----------------------------------'        `----------------------------------'
 */

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        HOMQ_A,  HOMQ_S,  HOMQ_D,  HOMQ_F,  KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    HOMQ_J,  HOMQ_K,  HOMQ_L,  HOMQ_QUOT
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH



/* Colemak-DH layer
 *
 * ,----------------------------------.        ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |        |   J  |   L  |   U  |   Y  |   '  |
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |A-Shft|R-Ctrl|S-Alt |T-GUI |   G  |        |   M  |N-GUI |E-Alt |I-Ctrl|O-Shft|
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  |   V  |        |   K  |   H  |   ,  |   .  |   /  |
 * |======+======+======+======+======+        +======+======+======+======+======|
 * |  NO  |  NO  |LTEsc |LTBksp|LTTab |        |LTEnt |LTSpc |LTDel |  NO  |  NO  |   // ALPHA_*T
 * `----------------------------------'        `----------------------------------'
 */
#define _________________COLEMAK_L1________________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define _________________COLEMAK_L2________________       HOMK_A,  HOMK_R,  HOMK_S,  HOMK_T,  KC_G
#define _________________COLEMAK_L3________________       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define _________________COLEMAK_R1________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT
#define _________________COLEMAK_R2________________       KC_M,    HOMK_N,  HOMK_E,  HOMK_I,  HOMK_O
#define _________________COLEMAK_R3________________       KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH



/* FFXIV layer
 *
 * ,----------------------------------.        ,----------------------------------.
 * |  Esc |   `  |  Tab |   4  | LT5  |        |   6  |   7  |   8  |   9  |   0  |
 * |======+======+======+======+======+        +======+======+======+======+======|
 * |   Q  |   W  |   E  |   R  |   T  |        |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |        |   H  |   J  |   K  |   L  |   '  |
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |        |   N  |   M  |   ,  |   .  |   /  |
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |  NO  |  NO  | Alt  |Shift | GUI  |        |Enter |Space | Bksp |  NO  |  NO  |
 * `----------------------------------'        `----------------------------------'
 */

#define _________________FFXIV_L0__________________        KC_ESC,  KC_GRV,  KC_TAB,  KC_1,    LT(_ADJUST, KC_2)
#define _________________FFXIV_L1__________________        _________________COLEMAK_L1________________
#define _________________FFXIV_L2__________________        KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define _________________FFXIV_L3__________________        _________________COLEMAK_L3________________
#define _________________FFXIV_LT__________________        XXXXXXX, XXXXXXX, KC_LALT, KC_LSFT, KC_LGUI

#define _________________FFXIV_R0__________________        KC_6,    KC_7,   KC_8,    KC_9,    KC_0
#define _________________FFXIV_R1__________________        _________________COLEMAK_R1________________
#define _________________FFXIV_R2__________________        KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________FFXIV_R3__________________        _________________COLEMAK_R3________________
#define _________________FFXIV_RT__________________        KC_ENT,  KC_SPC, KC_BSPC,  XXXXXXX, XXXXXXX

/* Empty sides for alternate layers
 *
 * ,----------------------------------.        ,----------------------------------.
 * |  NO  |  NO  |  NO  |  NO  |  NO  |        |  NO  |  NO  |  NO  |  NO  |  NO  |
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |Shift | Ctrl | Alt  | GUI  |  NO  |        |  NO  | GUI  | Alt  | Ctrl |Shift |
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |  NO  |  NO  |  NO  |  NO  |  NO  |        |  NO  |  NO  |  NO  |  NO  |  NO  |
 * |------+------+------+------+------+        +------+------+------+------+------|
 * |  NO  |  NO  |  NO  |  NO  |  NO  |        |  NO  |  NO  |  NO  |  NO  |  NO  |
 * `----------------------------------'        `----------------------------------'
 */
#define _________________MOD_L2____________________         KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX
#define _________________MOD_R2____________________         XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT

#define _________________BLANK_5___________________         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

/* Number/Symbol layer
* ,----------------------------------.        ,----------------------------------.
* |  7   |  8   |  9   |  0   |  \   |        |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  4   |  5   |  6   |  -   |  =   |        |  NO  | GUI  | Alt  | Ctrl |Shift |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  1   |  2   |  3   |  _   |  +   |        |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |  .   |  :   |  `   |        |  NO  |  NO  |  NO  |  NO  |  NO  |
* `----------------------------------'        `----------------------------------'
*/

#define _________________NSL_L1____________________         KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS
#define _________________NSL_L2____________________         KC_4,    KC_5,    KC_6,    KC_MINS, KC_EQL
#define _________________NSL_L3____________________         KC_1,    KC_2,    KC_3,    KC_UNDS, KC_PLUS
#define _________________NSL_LT____________________         XXXXXXX, XXXXXXX, KC_DOT,  KC_COLN, KC_GRV

#define _________________NSL_R1____________________         _________________BLANK_5___________________
#define _________________NSL_R2____________________         _________________MOD_R2____________________
#define _________________NSL_R3____________________         _________________BLANK_5___________________
#define _________________NSL_RT____________________         XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX

/* Shifted Number/Symbol layer
* ,----------------------------------.        ,----------------------------------.
* |  &   |  *   |  |   |  (   |  )   |        |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  $   |  %   |  ^   |  [   |  ]   |        |  NO  | GUI  | Alt  | Ctrl |Shift |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  !   |  @   |  #   |  {   |  }   |        |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |  .   |  ;   |  ~   |        |  NO  |  NO  |  NO  |  NO  |  NO  |
* `----------------------------------'        `----------------------------------'
*/

#define _________________NSSL_L1___________________         KC_AMPR, KC_ASTR, KC_PIPE, KC_LPRN, KC_RPRN
#define _________________NSSL_L2___________________         KC_DLR,  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC
#define _________________NSSL_L3___________________         KC_EXLM, KC_AT,   KC_HASH, KC_LCBR, KC_RCBR
#define _________________NSSL_LT___________________         XXXXXXX, XXXXXXX, KC_DOT,  KC_SCLN, KC_TILD

#define _________________NSSL_R1___________________         _________________BLANK_5___________________
#define _________________NSSL_R2___________________         _________________MOD_R2____________________
#define _________________NSSL_R3___________________         _________________BLANK_5___________________
#define _________________NSSL_RT___________________         _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

/* Fn layer
* ,----------------------------------.        ,----------------------------------.
* |GITFET|GITPUL|  NO  |GITREB|  NO  |        |  NO  |  F9  | F10  | F11  | F12  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |GITADD|GITSTA|GITCOM|GITPUI|GITPUO|        |  NO  |  F5  |  F6  |  F7  |  F8  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |GITBDE|GITBRC|GITCOU|GITCOB|GITBRC|        |  NO  |  F1  |  F2  |  F3  |  F4  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |ScrGrb| <-\s |%>%\n |        |  NO  |  NO  |      |  NO  |  NO  |
* `----------------------------------'        `----------------------------------'
*/

#define _________________FUNC_L1___________________         GITFETC, GITPULL, XXXXXXX, GITREBA, XXXXXXX
#define _________________FUNC_L2___________________         GITADD,  GITSTAT, GITCOMM, GITPUSO, GITPUSI
#define _________________FUNC_L3___________________         GITBDEL, XXXXXXX, GITCOUT, GITCOBR, GITBRCH
#define _________________FUNC_LT___________________         XXXXXXX, XXXXXXX, SCR_GRB, R_ASIGN, R_PIPE

#define _________________FUNC_R1___________________         XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12
#define _________________FUNC_R2___________________         XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8
#define _________________FUNC_R3___________________         XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4
#define _________________FUNC_RT___________________         XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX

/* Navigation layer
* ,----------------------------------.        ,----------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |        |  NO  |NX_HOM|NX_WB |NX_WF |NX_END|
* |------+------+------+------+------+        +------+------+------+------+------|
* |Shift | Ctrl | Alt  | GUI  |  NO  |        | CAPS | Left | Down |  Up  |Right |
* |------+------+------+------+------+        +------+------+------+------+------|
* | Undo | Cut  | Copy |Paste |Paste |        | Ins  | Home | PgDn | PgUp | End  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |  NO  |      |  NO  |        |Enter |Space |  NO  |  NO  |  NO  |
* `----------------------------------'        `----------------------------------'
*/

#define _________________NAV_L1____________________         _________________BLANK_5___________________
#define _________________NAV_L2____________________         _________________MOD_L2____________________
#define _________________NAV_L3____________________         UNDO,    CUT,     COPY,    PASTE,   PASTE
#define _________________NAV_LT____________________         XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX

#define _________________NAV_R1____________________         XXXXXXX, NX_HOME, NX_WB,   NX_WF,   NX_END
#define _________________NAV_R2____________________         KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
#define _________________NAV_R3____________________         KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END
#define _________________NAV_RT____________________         KC_ENT,  KC_SPC,  KC_DEL,  XXXXXXX, XXXXXXX

/* Mouse layer
* ,----------------------------------.        ,----------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |        |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |Shift | Ctrl | Alt  | GUI  |  NO  |        |  NO  | MS_L | MS_D | MS_U | MS_R |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |        |  NO  | WH_L | WH_D | WH_U | WH_R |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |ADJUST|  NO  |      |        | BTN1 | BTN2 | BTN3 |  NO  |  NO  |
* `----------------------------------'        `----------------------------------'
*/

#define _________________MOUSE_L1__________________         _________________BLANK_5___________________
#define _________________MOUSE_L2__________________         _________________MOD_L2____________________
#define _________________MOUSE_L3__________________         _________________BLANK_5___________________
#define _________________MOUSE_LT__________________         XXXXXXX, XXXXXXX, MO(_ADJUST), XXXXXXX, _______

#define _________________MOUSE_R1__________________         _________________BLANK_5___________________
#define _________________MOUSE_R2__________________         XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
#define _________________MOUSE_R3__________________         XXXXXXX, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R
#define _________________MOUSE_RT__________________         KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX, XXXXXXX

/* Media layer
* ,----------------------------------.        ,----------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |        |RGBTOG|RGBMOD|RGBHUI|RGBSAI|RGBVAI|
* |------+------+------+------+------+        +------+------+------+------+------|
* |Shift | Ctrl | Alt  | GUI  |  NO  |        |  NO  | Prev |VolUp |VolDn | Next |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |        |  ??  |  NO  |RGBHUD|RGBSAD|RGBVAD|
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |      |  NO  |ADJUST|        | Stop | Play | Mute |  NO  |  NO  |
* `----------------------------------'        `----------------------------------'
*/

#define _________________MEDIA_L1__________________         _________________BLANK_5___________________
#define _________________MEDIA_L2__________________         _________________MOD_L2____________________
#define _________________MEDIA_L3__________________         _________________BLANK_5___________________
#define _________________MEDIA_LT__________________         XXXXXXX, XXXXXXX, _______, XXXXXXX, MO(_ADJUST)

#define _________________MEDIA_R1__________________         RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI
#define _________________MEDIA_R2__________________         XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
#define _________________MEDIA_R3__________________         BL_TOGG,  BL_INC,  BL_DEC, BL_BRTG, XXXXXXX
#define _________________MEDIA_RT__________________         KC_MSTP, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX

/* Adjust (_MOUSE + _MEDIA)
* ,----------------------------------.        ,----------------------------------.
* |Reset |Debug |  NO  |  NO  |  NO  |        |TERMON|TERMOF|  NO  |  NO  |  NO  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |        |  NO  |QWERTY|  NO  |  NO  |  NO  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |        |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+        +------+------+------+------+------|
* |  NO  |  NO  |      |  NO  |      |        |  NO  |  NO  |  NO  |  NO  |  NO  |
* `----------------------------------'        `----------------------------------'
*/

#define _________________DRAGO_L1__________________         RESET,   DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX
#define _________________DRAGO_L2__________________         _________________BLANK_5___________________
#define _________________DRAGO_L3__________________         _________________BLANK_5___________________
#define _________________DRAGO_LT__________________         XXXXXXX, XXXXXXX, _______, XXXXXXX, _______

#define _________________DRAGO_R1__________________         TERM_ON, TERM_OFF, XXXXXXX, XXXXXXX, XXXXXXX
#define _________________DRAGO_R2__________________         XXXXXXX, QWERTY,   XXXXXXX, COLEMAK, XXXXXXX
#define _________________DRAGO_R3__________________         _________________BLANK_5___________________
#define _________________DRAGO_RT__________________         _________________BLANK_5___________________
