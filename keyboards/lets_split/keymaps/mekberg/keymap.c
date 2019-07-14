#include QMK_KEYBOARD_H

/*
Let's Split physical layout
1u == 8chars
* == Homing keys
                             LEFT                                                     RIGHT
   ,-----------------------------------------------------.   ,-----------------------------------------------------.
   |        |        |        |        |        |        |   |        |        |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |   *    |        |   |        |   *    |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |        |        |   |        |        |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |        |        |   |        |        |        |        |        |        |
   `-----------------------------------------------------´   `-----------------------------------------------------'
*/

// Layers
#define _DEFAULT 0
#define _RAISE 1
#define RAISE MO(_RAISE)
#define _LOWER 2
#define LOWER MO(_LOWER)
#define _SPECIAL 3
#define SPECIAL MO(_SPECIAL)

// Modifiers
#define SFTENT KC_SFTENT        // Enter => Shift when held
#define CTLTAB LCTL_T(KC_TAB)   // Tab => Ctrl when held

// ISO keycodes with Swedish layout names
#define SE_PLUS KC_MINS         // +
#define SE_QSTM S(SE_PLUS)      // Question mark
#define SE_TCK KC_EQL           // Fronttick (´)
#define SE_BTCK S(SE_TCK)       // Backtick (`)
#define SE_UML KC_RBRC          // Umlaut (¨)
#define SE_TAK S(SE_UML)        // Caret (^)
#define SE_TILD A(SE_UML)       // Tilde (~)
#define SE_QUT KC_NUHS          // Singlequote (')
#define SE_DQUT S(KC_2)         // Doublequote (")
#define SE_AST S(SE_QUT)        // Asterisk
#define SE_AUML KC_QUOT         // Ä
#define SE_ARNG KC_LBRC         // Å
#define SE_OUML KC_SCLN         // Ö
#define SE_LT KC_NUBS           // <
#define SE_GT S(SE_LT)          // >
#define SE_DASH KC_SLSH         // -
#define SE_USCR S(SE_DASH)      // _
#define SE_AT RALT(KC_2)        // @
#define SE_EXCL S(KC_1)         // !
#define SE_HASH S(KC_3)         // #
#define SE_USD RALT(KC_4)       // $
#define SE_PCNT S(KC_5)         // %
#define SE_AMP S(KC_6)          // &
#define SE_EQLS S(KC_0)         // =

// Apple-specific layout keys
#define AP_SLS S(KC_7)          // /
#define AP_PIPE LALT(KC_7)      // |
#define AP_BSLS A(AP_SLS)       // Backslash
#define AP_LCBR A(AP_LPAR)      // {
#define AP_RCBR A(AP_RPAR)      // }
#define AP_LBR A(KC_8)          // [
#define AP_RBR A(KC_9)          // ]
#define AP_LPAR S(KC_8)         // (
#define AP_RPAR S(KC_9)         // )

// My common shortcuts
#define MY_PREV KC_MRWD         // Media: Previous
#define MY_NEXT KC_MFFD         // Media: Next
#define MY_PLAY KC_MPLY         // Media: Play/Pause
#define MY_VOLU KC__VOLUP       // Media: Volume Up
#define MY_VOLD KC__VOLDOWN     // Media: Volume Down
#define MY_MUTE KC__MUTE        // Media: Mute
#define MY_SLEP G(A(KC_POWER))  // Mac: Sleep
#define MY_LOCK C(A(KC_L))      // Mac: Lock


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
DEFAULT
    Main layout for alphas and modifiers
    Tab => Ctrl when held
    Esc => MOVEMENT layer when held
    Enter => Shift when held
                             LEFT                                                     RIGHT
   ,-----------------------------------------------------.   ,-----------------------------------------------------.
   |   Esc  |   Q    |   W    |   E    |   R    |   T    |   |   Y    |   U    |   I    |   O    |   P    |   Å    |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |Ctrl/Tab|   A    |   S    |   D    |   F   *|   G    |   |   H    |*  J    |   K    |   L    |   Ö    |   Ä    |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |  Shift |   Z    |   X    |   C    |   V    |   B    |   |   N    |   M    |   ,    |   .    |   -    | Enter  |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   | SPECIAL|  Ctrl  |  Alt   |  Cmd   | LOWER  | Space  |   | Backspc| RAISE  |  Left  |  Down  |   Up   | Right  |
   `-----------------------------------------------------´   `-----------------------------------------------------'
*/
[_DEFAULT] = LAYOUT_ortho_4x12(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG,
    CTLTAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    SE_OUML, SE_AUML,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  SE_DASH, SFTENT,
    SPECIAL, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,      KC_BSPC, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/*
RAISE
    This layer focuses on symbols and special characters.

                             LEFT                                                     RIGHT
   ,-----------------------------------------------------.   ,-----------------------------------------------------.
   |        |   !    |   ?    |   {    |   }    |   &    |   |   ^    |   |    |   `    |   ´    |        | Backspc|
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |   #    |   $    |   (    |   )   *|   "    |   |   ~    |*  /    |   \    |   ¨    |        |        |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |   @    |   %    |   [    |   ]    |   '    |   |        |   <    |   >    |        |        |        |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |        |        |   |  Del   |XXXXXXXX|        |        |        |        |
   `-----------------------------------------------------´   `-----------------------------------------------------'
*/
[_RAISE] = LAYOUT_ortho_4x12(
    _______, SE_EXCL, E_QSTM,  AP_LCBR, AP_RCBR, SE_AMP,      SE_TAK,  AP_PIPE, SE_BTCK, SE_TCK,  _______, KC_BSPC,
    _______, SE_HASH, SE_USD,  AP_LPAR, AP_RPAR, SE_DQUT,     SE_TILD, AP_SLS,  AP_BSLS, SE_UML,  _______, _______,
    _______, SE_AT,   SE_PCNT, AP_LBR,  AP_RBR,  SE_QUT,      _______, SE_LT,   SE_GT,   _______, _______, _______,
    _______, _______, _______, _______, _______, _______,     KC_DEL,  _______, _______, _______, _______, _______
),

/*
LOWER
    This layer focuses on numbers and math.
                             LEFT                                                     RIGHT
   ,-----------------------------------------------------.   ,-----------------------------------------------------.
   |        |  F1    |  F2    |  F3    |  F4    |        |   |        |   7    |   8    |   9    |   *    | Backspc|
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |  F5    |  F6    |  F7    |  F8   *|        |   |        |*  4    |   5    |   6    |   -    |        |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |  F9    |  F10   |  F11   |  F12   |        |   |        |   1    |   2    |   3    |   +    |        |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |XXXXXXXX|        |   |  Del   |        |   0    |        |   =    |        |
   `-----------------------------------------------------´   `-----------------------------------------------------'
*/
[_LOWER] = LAYOUT_ortho_4x12(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,     _______, KC_7,    KC_8,    KC_9,    SE_AST,  KC_BSPC,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,     _______, KC_4,    KC_5,    KC_6,    SE_DASH, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,     _______, KC_1,    KC_2,    KC_3,    SE_PLUS, _______,
    _______, _______, _______, _______, _______, _______,     KC_DEL,  _______, KC_0,    _______, SE_EQLS, _______
),

/*
SPECIAL
    This layer focuses on special functions, media controls and movement keys.
                             LEFT                                                     RIGHT
   ,-----------------------------------------------------.   ,-----------------------------------------------------.
   | Reset  |        |        | VolUp  |        |        |   |  Ins   |  Home  |   Up   |  End   |  PgUp  | Backspc|
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |EEPReset|        |  Prev  | VolDn  |  Next *|        |   |        |* Left  |  Down  | Right  |  PgDn  |        |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |        |        |        |  Mute  |        |        |   |  Lock  |        |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   |XXXXXXXX|        |        |        |        |  Play  |   |  Del   |        |        |        |        | Sleep  |
   `-----------------------------------------------------´   `-----------------------------------------------------'
*/
[_SPECIAL] = LAYOUT_ortho_4x12(
    RESET,   _______, _______, MY_VOLU, _______, _______,     KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_BSPC,
    EEP_RST, _______, MY_PREV, MY_VOLD, MY_NEXT, _______,     _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
    _______, _______, _______, MY_MUTE, _______, _______,     MY_LOCK, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, MY_PLAY,     KC_DEL,  _______, _______, _______, _______, MY_SLEP
)

};
