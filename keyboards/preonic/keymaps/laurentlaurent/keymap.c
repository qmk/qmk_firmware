/* Laurent's Preonic Layout
 */

#include QMK_KEYBOARD_H
#include "muse.h"

// ==== These keys allows usage of the home row as modifiers (when held) ====
// Very bad for gaming

// For _QWERTY_MAC
#define LCT_S LCTL_T(KC_S)
#define LWN_F LGUI_T(KC_F)
#define LWN_Z LGUI_T(KC_Z)
#define LCT_L LCTL_T(KC_S)
#define LWN_J LGUI_T(KC_F)

// For _QWERTY_WIN
#define LWN_S LGUI_T(KC_S)
#define LCT_F LCTL_T(KC_F)
#define LCT_Z LCTL_T(KC_Z)
#define LWN_L LGUI_T(KC_L)
#define LCT_J LCTL_T(KC_J)

// For _QWERTY_MAC and _QWERTY_WIN
#define LAT_D LALT_T(KC_D)
#define LAT_K LALT_T(KC_K)

// ============================================================================

// ==== For All ====
#define LTO_BS TO(_QWERTY_MAC)
#define LLY_SC LT(_NAV, KC_SCLN)
#define LLY_A  LT(_NAV, KC_A)
#define LLY_GR LT(_NUM, KC_GRAVE)
#define LLSWIT MO(_LYSWT)
#define LLY_TB LT(_PUNC, KC_TAB)
#define LLY_BK LT(_PUNC, KC_BSPACE)
#define LLY_BS LT(_PUNC, KC_BSLASH)
#define LLY_ET LT(_EXTRA, KC_ENT)
#define LLY_LW LOWER
#define LLY_RS RAISE

// ==== Audio ====
#ifdef AUDIO_ENABLE
#include "audio.h"
float tone_macro1_record[][2] = SONG(CAPS_LOCK_ON_SOUND);
float tone_macro2_record[][2] = SONG(SCROLL_LOCK_ON_SOUND);
float tone_macro_record_stop[][2] = SONG(SCROLL_LOCK_OFF_SOUND );
#endif

enum preonic_layers {
  _QWERTY_MAC,
  _QWERTY_WIN,
  _GAMING,
  _MUSIC,
  _LOWER,
  _RAISE,
  _ADJUST,
  _PUNC,
  _EXTRA, 
  _NUM,
  _NAV,
  _LYSWT
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  QWWIN,
  //COLEMAK,
  //DVORAK,
  LOWER,
  RAISE,
  BACKLIT,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty for Mac
 * ,-----------------------------------------------------------------------------------.
 * |   =  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LY|TB |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | LY|\ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Hyper| LY|A | CT|S | AT|D | WN|F |   G  |   H  | WN|J | AT|K | CT|L | LY|; |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift| WN|Z |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LY|` | Esc  | Del  |Lower |LY|Bkp|    Space    |LY|ENT|Raise |   [  |   ]  |LY_SW |
 * `-----------------------------------------------------------------------------------'
 * LY|` 	-> To _NUM
 * LY|; 	-> To _NAV
 * LY|A 	-> To _NAV
 * LY|TB 	-> To _PUNC
 * LY|\ 	-> To _PUNC
 * LY|Bkp 	-> To _PUNC
 * LY|ENT 	-> To_EXTRA
 */
[_QWERTY_MAC] = LAYOUT_preonic_grid( \
  KC_EQUAL,	KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS, \
  LLY_TB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    LLY_BS, \
  KC_HYPR,  LLY_A, 	 LCT_S,   LAT_D,   LWN_F,   KC_G,    KC_H,    LWN_J,   LAT_K,   LCT_L,   LLY_SC,  KC_QUOT, \
  KC_LSFT,  LWN_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSPACE, \
  LLY_GR,   KC_ESC,  KC_DEL,  LLY_LW,  LLY_BK,  KC_SPC,  KC_SPC,  LLY_ET,  LLY_RS,  KC_LBRC, KC_RBRC, LLSWIT  \
),

/* Qwerty for Windows
 * ,-----------------------------------------------------------------------------------.
 * |   =  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LY|TB |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | LY|\ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Hyper| LY|A | WN|S | AT|D | CT|F |   G  |   H  | CT|J | AT|K | WN|L | LY|; |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift| CT|Z |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LY|` | Esc  | Del  |Lower |LY|Bk |    Space    |LY|ENT|Raise |   [  |   ]  |LY_SW |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY_WIN] = LAYOUT_preonic_grid( \
  KC_EQUAL,	KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS, \
  LLY_TB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    LLY_BS, \
  KC_HYPR,  LLY_A, 	 LWN_S,   LAT_D,   LCT_F,   KC_G,    KC_H,    LCT_J,   LAT_K,   LWN_L,   LLY_SC,  KC_QUOT, \
  KC_LSFT,  LCT_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSPACE, \
  LLY_GR,   KC_ESC,  KC_DEL,  LLY_LW,  LLY_BK,  KC_SPC,  KC_SPC,  LLY_ET,  LLY_RS,  KC_LBRC, KC_RBRC, LLSWIT  \
),

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | LY|; |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | ESC  |  Alt | Lower| Bksp |    Space    | Enter| Raise|   [  |   ]  |LY_SW |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLASH,  \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    LLY_SC,  KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQUAL,  \
  KC_LCTL, KC_ESC,  KC_LALT, LOWER,   KC_BSPC, KC_SPC,  KC_SPC,  KC_ENT,  RAISE,   KC_LBRC, KC_RBRC, LLSWIT  \
),

/* Music Layer (Switch to this layer if want to use music mode)
 * ,-----------------------------------------------------------------------------------.
 * | Esc  | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | ALT  | CMD  |      | XXXX |             | XXXX |      | XXXX | XXXX |LY_SW |
 * `-----------------------------------------------------------------------------------'
 */
[_MUSIC] = LAYOUT_preonic_grid( \
    KC_ESC ,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    KC_LCTL,  KC_LALT,  KC_LGUI,  _______,  XXXXXXX,  _______,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  LLSWIT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  | Home |  Up  | End  | PGUP | XXXX | XXXX | XXXX | PrSc | Home | PGUP | XXXX |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Left | Down | Right|PGDWN | XXXX | XXXX | XXXX | Pause| End  |PGDWN | F12  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | Prev | Play | Next | INS  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL |  Alt |  CMD | !!!! |      |             |      |      | Vol- | Vol+ |LY_SW |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, \
  KC_TAB,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_HOME, KC_PGUP,  XXXXXXX, \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS, KC_END,  KC_PGDN,  KC_F12, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT,  KC_INS, \
  KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU,  LLSWIT\
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   &  |   *  |   {  |   }  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL |  Alt |  CMD |      |      |             |      | !!!! |      |      |LY_SW |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_TAB,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, KC_DEL,  \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, DYN_REC_START1, DYN_REC_START2, DYN_REC_STOP, \
  KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______, _______, _______, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, LLSWIT  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|QWmac |QWwin |QWmac |QWin  |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |LY_SW |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  KC_TAB,  RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
 /*_______, _______, MU_MOD,  AU_ON,   AU_OFF,  QWERTY,  QWWIN,	 QWERTY,  COLEMAK, DVORAK,  _______, _______, \ Remove this if adding Colemak and Dvorak*/
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  QWERTY,  QWWIN,	 QWERTY,  QWWIN, _______,  _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LLSWIT  \
),

/* Punctuation Layer
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | !!!! |  |   |  &   |  {   |   }  |  -   |  -   |  {   |   }  |  &   |  |   | !!!! |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  "   |  /   |  *   |  (   |   )  |  +   |  +   |  (   |   )  |  *   |  /   | F12  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  \   |  %   |  [   |   ]  |  =   |  =   |  [   |   ]  |  %   |  \   | INS  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX |  _   |  ^   | XXXX | !!!! |             |  ENT | XXXX |  ^   |  _   |LY_SW |
 * `-----------------------------------------------------------------------------------'
 */
[_PUNC] = LAYOUT_preonic_grid( \
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11, \
    _______,  KC_PIPE,  KC_AMPR,  KC_LCBR,  KC_RCBR,  KC_MINS,  KC_MINS,  KC_LCBR,  KC_RCBR,  KC_AMPR,  KC_PIPE,  _______, \
    KC_DQUO,  KC_SLSH,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PLUS,  KC_PLUS,  KC_LPRN,  KC_RPRN,  KC_ASTR,  KC_SLSH,  KC_F12, \
    _______,  KC_BSLS,  KC_PERC,  KC_LBRC,  KC_RBRC,  KC_EQL,   KC_EQL,   KC_LBRC,  KC_RBRC,  KC_PERC,  KC_BSLS,  KC_INS, \
    XXXXXXX,  KC_UNDS,  KC_CIRC,  XXXXXXX,  _______,  _______,  _______,  KC_ENT,   XXXXXXX,  KC_CIRC,  KC_UNDS,  LLSWIT  \
),

/* Extra Layer
 * ,-----------------------------------------------------------------------------------.
 * |  ESC |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL |  ALT |  CMD |      |      |             |      |      |      |      |LY_SW |
 * `-----------------------------------------------------------------------------------'
 */
[_EXTRA] = LAYOUT_preonic_grid( \
    KC_ESC ,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, \
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, \
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, \
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  DYN_REC_START1, DYN_REC_START2, DYN_REC_STOP, \
    KC_LCTL,  KC_LALT,  KC_LGUI,  _______,  _______,  _______,  _______,  _______,  _______,  DYN_MACRO_PLAY1, DYN_MACRO_PLAY2,  LLSWIT \
),

/* Numeric Pad
 * ,-----------------------------------------------------------------------------------.
 * |  ESC | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | NMLK | NUM/ | NUM* | NUM- | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Home |  Up  | End  | PGUP | XXXX | XXXX | NUM7 | NUM8 | NUM9 | NUM+ | XXXX |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | XXXX | Left | Down | Right| PGDWN| XXXX | XXXX | NUM4 | NUM5 | NUM6 | NUM+ | XXXX |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | CTRL |  ALT | CMD  | XXXX | XXXX | XXXX | NUM1 | NUM2 | NUM3 | NENT | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | !!!! | XXXX | XXXX | XXXX |      |             | NUM0 | NUM0 | NUM. | NENT | QMAC |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_preonic_grid( \
    KC_ESC ,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_NLCK,  KC_PSLS,  KC_PAST,  KC_PMNS,  XXXXXXX, \
    _______,  KC_HOME,  KC_UP,    KC_END,   KC_PGUP,  XXXXXXX,  XXXXXXX,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  XXXXXXX, \
    XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,  XXXXXXX,  XXXXXXX,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  XXXXXXX, \
    _______,  KC_LCTL,  KC_LALT,  KC_LGUI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_P1,    KC_P2,    KC_P3,    KC_PENT,  KC_BSPC, \
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  _______,  KC_P0,   KC_P0,    KC_PDOT,  KC_PENT,  LTO_BS  \
),
/* NAV
 * ,-----------------------------------------------------------------------------------.
 * |  ESC |      |      | MOB3 |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   A  | MOB2 | MOUP | MOB1 | MOSU | PGUP | Home |  Up  | End  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | !!!! | MOLF | MODN | MORT | MOSD | PGDN | Left | Down | Right| !!!! |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | MOSL | MOSR | MOB5 | MOB4 |      | MOA2 | MOA0 |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | ALT  | CMD  |      |      |             |      |      |      |      | QMAC |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_preonic_grid( \
  KC_ESC,  _______,  _______,  KC_BTN3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, \
 _______,  KC_A,     KC_BTN2,  KC_MS_U,  KC_BTN1,  KC_WH_U,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   _______,  _______,  \
 _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_D,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______, \
 _______,  _______,  KC_WH_L,  KC_WH_L,  KC_BTN5,  KC_BTN4,  _______,  _______,  KC_ACL2,  KC_ACL0,  _______,  _______, \
 KC_LCTL,  KC_LALT,  KC_LGUI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  LTO_BS  \
),

/* Layer Switcher
 * ,-----------------------------------------------------------------------------------.
 * | Esc  | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Brite | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CTRL | XXXX | XXXX | XXXX | XXXX | GAME | XXXX | XXXX | XXXX | XXXX | NAV  | XXXX |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | XXXX | XXXX | XXXX | XXXX | QMAC | XXXX | MUSC | XXXX | XXXX | XXXX | XXXX |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NUM  | ALT  | CMD  |      | XXXX |             | XXXX |      | XXXX | XXXX | !!!! |
 * `-----------------------------------------------------------------------------------'
 */
[_LYSWT] = LAYOUT_preonic_grid( \
    KC_ESC ,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  	XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    BACKLIT,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  	XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    KC_LCTL,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(_GAMING), XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  TO(_NAV), XXXXXXX, \
    _______,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  LTO_BS,   	XXXXXXX, TO(_MUSIC), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    TO(_NUM),  KC_LALT,  KC_LGUI,  _______,  XXXXXXX,  _______,  	_______,  XXXXXXX,   _______,  XXXXXXX,  XXXXXXX,  _______  \
) //, //Don't forget to add the comma if going to add more layers here
};

static uint16_t key_timer;
static uint16_t timer_thresh = 200;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	// For dynamic macros
	if (!process_record_dynamic_macro(keycode, record)) {
		// Play sound on Macro stop
		#ifdef AUDIO_ENABLE
		switch(keycode) {
		    case DYN_REC_STOP:
			  if (record->event.pressed) {
				PLAY_SONG(tone_macro_record_stop);
			  }
			  return false;
			  break;
		}
		#endif
        return false;
    }
	
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY_MAC);
          }
          return false;
          break;
		case QWWIN:
		  if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY_WIN);
          }
          return false;
          break;
		// Reinstate these cases if COLEMAK, DVORAK are included in the layouts
        /*case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
		  */
        case LOWER:
          if (record->event.pressed) {
			key_timer = timer_read();
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
			  // Backspace on tap
			  if(timer_elapsed(key_timer) < timer_thresh) {
				  tap_code(KC_BSPC);
			  }
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            PORTE &= ~(1<<6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            PORTE |= (1<<6);
            #endif
          }
          return false;
          break;
		#ifdef AUDIO_ENABLE
		// Play sound on Macro record start
			case DYN_REC_START1:
			  if (record->event.pressed) {
				  
					PLAY_SONG(tone_macro1_record);
			  }
			  return false;
			  break;
			case DYN_REC_START2:
			  if (record->event.pressed) {
					PLAY_SONG(tone_macro2_record);
				  
			  }
			  return false;
			  break;
	    #endif
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
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
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
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
