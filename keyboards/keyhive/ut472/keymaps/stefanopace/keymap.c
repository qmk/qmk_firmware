/* Copyright 2021 Stefano Pace
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

enum layers {
    _QWE,
    _SYM,
    _NUM,
    _NAV,
    _NV2,
    _FN,
};

enum tapdance {
    TD_SINGLE_QUOTE_DOUBLE_QUOTES,
    TD_APP_CAPS_LOCK,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SINGLE_QUOTE_DOUBLE_QUOTES] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TD_APP_CAPS_LOCK]              = ACTION_TAP_DANCE_DOUBLE(KC_APP, KC_CAPS),
};

#define LTFN_ESC LT(_FN, KC_ESC)
#define LTSYM_F LT(_SYM, KC_F)
#define LTSYM_J LT(_SYM, KC_J)
#define TD_QUOT TD(TD_SINGLE_QUOTE_DOUBLE_QUOTES)
#define TD_APP_CAPS TD(TD_APP_CAPS_LOCK)
#define SFT_SLSH RSFT_T(KC_SLSH)

#define UNDO LCTL(KC_Z)
#define REDO LCTL(KC_Y)
#define CUT LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)

#define CUSTOM1 LCA(KC_EQL)
#define CUSTOM2 MEH(KC_PLUS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
       /* Base qwerty Layer
        * 
        * Holding Esc activates the Fn layer
        * Holding F or J activates Symbols layer
        * Holding / acts as Shift
        * Double tap on ' acts as "
        * Double tap on Menu activates CapsLock
        * 
        * Nav and Num layers are togglable with triple tapping on relative keys while holding them will activate layers momentarily.
        * 
        * I personally use Pause to mute/unmute microphone
        * I personally use Menu to act as compose key to input accented letters
        * 
        * ,----------------------------------------------------------------------------.
        * |Esc-Fn|  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  | Bspace  |
        * |----------------------------------------------------------------------------+
        * | Tab   |  A  |  S  |  D  |F-Sym|  G  |  H  |J-Sym|  K  |  L  |  '*  | Enter |
        * |----------------------------------------------------------------------------+
        * | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |/-Shift|Menu*|
        * |----------------------------------------------------------------------------+
        * | Ctrl | Gui | Alt |Pause|(Nav) |   Space   |(Num) |Left |Down | Up   |Right |
        * `----------------------------------------------------------------------------'
        */
    [_QWE] = LAYOUT(
        LTFN_ESC,  KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,    KC_Y,    KC_U,      KC_I,     KC_O,     KC_P,      KC_BSPC,
        KC_TAB,    KC_A,     KC_S,     KC_D,     LTSYM_F,   KC_G,    KC_H,    LTSYM_J,   KC_K,     KC_L,     TD_QUOT,   KC_ENT,
        KC_LSFT,   KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,    KC_N,    KC_M,      KC_COMM,  KC_DOT,   SFT_SLSH,  TD_APP_CAPS,
        KC_LCTL,   KC_LGUI,  KC_LALT,  KC_PAUS,  TT(_NAV),       KC_SPC,      TT(_NUM),  KC_LEFT,  KC_DOWN,  KC_UP,     KC_RGHT
    ),

       /* Symbols Layer (Sym)
        * ,----------------------------------------------------------------------------.
        * |      |  `  |  @  |  #  |  $  |  %  |     |  &  |  *  |  ^  |     |  Del    |
        * |----------------------------------------------------------------------------+
        * |       |  ~  |  {  |  -  |  (  |  +  |  =  |  )  |  |  |  }  |   ;  |       |
        * |----------------------------------------------------------------------------+
        * |        |  !  |  <  |  _  |  [  |     |  :  |  ]  |  \  |  >  |  ?   |      |
        * |----------------------------------------------------------------------------+
        * |      |     |     |     |     |            |      |     |     |      |      |
        * `----------------------------------------------------------------------------'
        */
    [_SYM] = LAYOUT(
        _______,  KC_GRV,   KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  XXXXXXX,  KC_AMPR,  KC_ASTR,  KC_CIRC,  XXXXXXX,  KC_DEL,
        _______,  KC_TILD,  KC_LCBR,  KC_MINS,  KC_LPRN,  KC_PLUS,  KC_EQL,   KC_RPRN,  KC_PIPE,  KC_RCBR,  KC_SCLN,  _______,
        _______,  KC_EXLM,  KC_LT,    KC_UNDS,  KC_LBRC,  XXXXXXX,  KC_COLN,  KC_RBRC,  KC_BSLS,  KC_GT,    KC_QUES,  _______,
        _______,  _______,  _______,  _______,  XXXXXXX,       _______,       XXXXXXX,  _______,  _______,  _______,  _______
    ),

       /* Numbers Layer (Num)
        *
        * Custom2 will act as Ctrl+Shift+Alt+"+" that can be used for example to spawn new terminal instances
        * ,----------------------------------------------------------------------------.
        * |      |     |     |     |     |    |Ctrl-y|     |     |     |     |         |
        * |----------------------------------------------------------------------------+
        * |       |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0   |       |
        * |----------------------------------------------------------------------------+
        * |        |Ctr-z|Ctr-x|Ctr-c|Ctr-v|     |     |     |  ,  |  .  |      |      |
        * |----------------------------------------------------------------------------+
        * |      |     |     |    |Custom2|           |      |     |     |      |      |
        * `----------------------------------------------------------------------------'
        */
    [_NUM] = LAYOUT(
        _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  REDO,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,
        _______,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
        _______,  UNDO,     CUT,      COPY,     PASTE,     XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_COMM,  KC_DOT,   _______,  _______,
        _______,  _______,  _______,  _______,  CUSTOM2,        _______,       _______,  _______,  _______,  _______,  _______
    ),

       /* Navigation Layer (Nav)
        * 
        * This layer is optimized for gui handling and code navigation
        * It makes easier to reach common key combinations as: Ctrl+Shift, Gui+Shift, Ctrl+Alt, Alt+Tab, Ctrl+F, Ctrl+S
        * 
        * Holding (Nav2) replaces arrow keys with Home PgDown PgUp End
        * 
        * 
        * Custom1 will act as Ctrl+Alt+"=" that can be used for example to focus last spawned terminal
        * 
        * ,----------------------------------------------------------------------------.
        * |      |Shift|Shift|Shift|     |     |     |     |     |     |     |         |
        * |----------------------------------------------------------------------------+
        * |(Nav2) |Ctrl | Gui | Alt | Tab |     |Left |Down | Up  |Right|   F  |       |
        * |----------------------------------------------------------------------------+
        * |        |Ctr-z|Ctr-x|Ctr-c|Ctr-v|     |     |     |  L  |     |  A   |  S   |
        * |----------------------------------------------------------------------------+
        * |      |     |     |     |     |            |Custom1|    |     |      |      |
        * `----------------------------------------------------------------------------'
        */
    [_NAV] = LAYOUT(
        _______,   KC_LSFT,  KC_LSFT,  KC_LSFT,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,
        MO(_NV2),  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_TAB,   _______,  KC_LEFT,  KC_DOWN,   KC_UP,    KC_RGHT,  KC_F,     _______,
        _______,   UNDO,     CUT,      COPY,     PASTE,    _______,  _______,  _______,   KC_L,     KC_DOT,   KC_A,     KC_S,
        _______,   _______,  _______,  _______,  _______,       _______,       CUSTOM1,   _______,  _______,  _______,  _______
    ),

       /* Speed Navigation Layer (Nav2)
        * ,----------------------------------------------------------------------------.
        * |      |     |     |     |     |     |     |     |     |     |     |         |
        * |----------------------------------------------------------------------------+
        * |       |     |     |     |     |     |Home |PgUp |PgDown|End |      |       |
        * |----------------------------------------------------------------------------+
        * |        |     |     |     |     |     |     |     |     |     |      |      |
        * |----------------------------------------------------------------------------+
        * |      |     |     |     |     |            |      |     |     |      |Reset |
        * `----------------------------------------------------------------------------'
        */
    [_NV2] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,       _______,       _______,  _______,  _______,  _______,  QK_BOOT
    ),

       /* Fn Layer (Fn)
        * ,----------------------------------------------------------------------------.
        * |      |     |     |     |     |     |     | F1  | F2  | F3  | F10 |         |
        * |----------------------------------------------------------------------------+
        * | Print |     |     |     |     |     |     | F4  | F5  | F6  | F11  |       |
        * |----------------------------------------------------------------------------+
        * |ScrLock |     |     |     |     |     |     | F7  | F8  | F9  | F12  |      |
        * |----------------------------------------------------------------------------+
        * | Ins  |     |     |     |     |            |      |     |     |      |      |
        * `----------------------------------------------------------------------------'
        */
    [_FN] = LAYOUT(
        _______,  RGB_TOG, RGB_RMOD, RGB_MOD, RGB_HUD,  RGB_HUI,  XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F10,  XXXXXXX,
        KC_PSCR,  RGB_SAD, RGB_SAI,  RGB_VAD, RGB_VAI,  RGB_SPD,  RGB_SPI,  KC_F4,    KC_F5,    KC_F6,    KC_F11,  XXXXXXX,
        KC_SCRL,  RGB_M_P, RGB_M_B,  RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K,  KC_F7,    KC_F8,    KC_F9,    KC_F12,  XXXXXXX,
        KC_INS,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX
    ),
};
