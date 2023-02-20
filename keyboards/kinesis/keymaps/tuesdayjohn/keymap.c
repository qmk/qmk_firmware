#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum kinesis_layers {
  _COLEMAK,   // Colemak (default layer)
  _QWERTY,    // QWERTY
  _GAMING,    // Gaming/vanilla toggle layer (limited dual-role keys and layer access)
  _NUMBERS,   // Numbers & Symbols
  _NUMBERS2,  // Numbers & Symbols 2 (identical as _NUMBERS; basically used for tri-layer access to _ADJUST)
  _FUNCTION,  // Function
  _FUNCTION2, // Function 2 (identical as _FUNCTION; used to allow for easier use of space and backspace while using function layer arrows)
  _NUMPAD,    // Numpad
  _ADJUST,    // Adjust layer (accessed via tri-layer feature)
  _ADJUST2    // Second Adjust layer (accessed outside of tri-layer feature)
};

enum kinesis_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  GAMING
};

//Tap Dance Declarations
enum {
  ADJ = 0,
  LBCB,
  RBCB,
  EQPL,
  PLEQ,
  MNUN,
  SLAS,
  GVTL,
  PPEQ,
  PMUN,
  PSPA
};

void dance_LAYER_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
     layer_on(_ADJUST2);
     set_oneshot_layer(_ADJUST2, ONESHOT_START);
  }
}
void dance_LAYER_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
     layer_off(_ADJUST2);
     clear_oneshot_layer_state(ONESHOT_PRESSED);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
[ADJ]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_LAYER_finished, dance_LAYER_reset),  //  Double-tap to activate Adjust layer via oneshot layer
[LBCB] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),  // Left bracket on a single-tap, left brace on a double-tap
[RBCB] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),  // Right bracket on a single-tap, right brace on a double-tap
[EQPL] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_PLUS),   // Plus sign on a single-tap, equal sign on a double-tap
[PLEQ] = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_EQL),   // Equal sign on a single-tap, plus sign on a double-tap
[MNUN] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),  // Minus sign on a single-tap, underscore on a double-tap
[SLAS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_ASTR),  // Slash in a single-tap, asterisk in a double-tap
[GVTL] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),   // Grave on a single-tap, tilde on a double-tap
[PPEQ] = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_EQL),   // Numpad plus sign on a single-tap, equal sign on a double-tap
[PMUN] = ACTION_TAP_DANCE_DOUBLE(KC_PMNS, KC_UNDS),  // Numpad minus sign on a single-tap, underscore on a double-tap
[PSPA] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_PAST)   // Numpad slash on a single-tap, numpad asterisk on a double-tap
};

//Aliases for longer keycodes
#define NUMPAD  TG(_NUMPAD)
#define ADJUST  MO(_ADJUST2)
#define SPCFN   LT(_FUNCTION, KC_SPC)
#define BSPCFN  LT(_FUNCTION2, KC_BSPC)
#define ENTNS   LT(_NUMBERS, KC_ENT)
#define DELNS   LT(_NUMBERS2, KC_DEL)
#define CTLESC  CTL_T(KC_ESC)
#define ALTAPP  ALT_T(KC_APP)
#define CTL_A   LCTL(KC_A)
#define CTL_C   LCTL(KC_C)
#define CTL_V   LCTL(KC_V)
#define CTL_X   LCTL(KC_X)
#define CTL_Z   LCTL(KC_Z)
#define CTL_Y   LCTL(KC_Y)
#define CA_TAB  LCA(KC_TAB)
#define HYPER   ALL_T(KC_NO)
#define TD_ADJ  TD(ADJ)
#define TD_LBCB TD(LBCB)
#define TD_RBCB TD(RBCB)
#define TD_EQPL TD(EQPL)
#define TD_PLEQ TD(PLEQ)
#define TD_MNUN TD(MNUN)
#define TD_SLAS TD(SLAS)
#define TD_GVTL TD(GVTL)
#define TD_PPEQ TD(PPEQ)
#define TD_PMUN TD(PMUN)
#define TD_PSPA TD(PSPA)
#define NKROTG  MAGIC_TOGGLE_NKRO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
Colemak
(Default layer; keys separated by "/" tap for first, hold for second; uses Space Cadet Shifts)
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|  ESC |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |                                     |  F9  |  F10 |  F11 |  F12 |PrtScr|ScrLck| Pause|Numpad|Adjust|
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|    =    |    1   |    2   |    3   |    4   |    5   |                                                     |    6   |    7   |    8   |    9   |    0   |    -    |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|   Tab   |    Q   |    W   |    F   |    P   |    G   |                                                     |    J   |    L   |    U   |    Y   |    ;   |    \    |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
| ESC/Ctrl|    A   |    R   |    S   |    T   |    D   |                                                     |    H   |    N   |    E   |    I   |    O   |    '    |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
| SC Shift|    Z   |    X   |    C   |    V   |    B   |                                                     |    K   |    M   |    ,   |    .   |    /   | SC Shift|
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |   Ins  |    `   |    [   |    ]   |                                                                       |  Left  |  Down  |   Up   |  Right |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   | ESC/Ctl|  Hyper |                 |  RAlt  |  RCtl  |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |  Space |  Enter | App/Alt|                 |  RGUI  | Delete |  Bspc  |
	                                          |    /   |    /   |--------|                 |--------|    /   |    /   |
	                                          |   Fn   | Number |  Bspc  |                 |  Enter | Number2|   Fn2  |
	                                          `--------------------------'                 `--------------------------'
*/
[_COLEMAK] = LAYOUT_pretty(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS, NUMPAD,  ADJUST,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                                          KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  CTLESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                                                          KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                                          KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,                                                                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
                                                        CTLESC,  HYPER,                     KC_RALT, KC_RCTL,
                                                                 ALTAPP,                    KC_RGUI,
                                               SPCFN,   ENTNS,   KC_BSPC,                   KC_ENT,  DELNS,   BSPCFN
),

/*
QWERTY
(Keys separated by "/" tap for first, hold for second; uses Space Cadet Shifts)
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|  ESC |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |                                     |  F9  |  F10 |  F11 |  F12 |PrtScr|ScrLck| Pause|Numpad|Adjust|
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|    =    |    1   |    2   |    3   |    4   |    5   |                                                     |    6   |    7   |    8   |    9   |    0   |    -    |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|   Tab   |    Q   |    W   |    E   |    R   |    T   |                                                     |    Y   |    U   |    I   |    O   |    P   |    \    |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
| ESC/Ctrl|    A   |    S   |    D   |    F   |    G   |                                                     |    H   |    J   |    K   |    L   |    ;   |    '    |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
| SC Shift|    Z   |    X   |    C   |    V   |    B   |                                                     |    N   |    M   |    ,   |    .   |    /   | SC Shift|
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |   Ins  |    `   |    [   |    ]   |                                                                       |  Left  |  Down  |   Up   |  Right |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   | ESC/Ctl|  Hyper |                 |  RAlt  |  RCtl  |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |  Space |  Enter | App/Alt|                 |  RGUI  | Delete |  Bspc  |
	                                          |    /   |    /   |--------|                 |--------|    /   |    /   |
	                                          |   Fn   | Number |  Bspc  |                 |  Enter | Number2|   Fn2  |
	                                          `--------------------------'                 `--------------------------'
*/
[_QWERTY] = LAYOUT_pretty(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS, NUMPAD,  ADJUST,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  CTLESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,                                                                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
                                                        CTLESC,  HYPER,                     KC_RALT, KC_RCTL,
                                                                 ALTAPP,                    KC_RGUI,
                                               SPCFN,   ENTNS,   KC_BSPC,                   KC_ENT,  DELNS,   BSPCFN
),

/*
Numbers/Symbols layer
(Multiple characters: single-tap for first, double-tap for second)
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|   F12   |   F1   |   F2   |   F3   |   F4   |   F5   |                                                     |   F6   |   F7   |   F8   |   F9   |   F10  |   F11   |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |    6   |    7   |    8   |    9   |    0   |                                                     |    ^   |    &   |    *   |    (   |    )   |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |    1   |    2   |    3   |    4   |    5   |                                                     |    !   |    @   |    #   |    $   |    %   |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |    .   |   / *  |   - _  |   + =  |                                                     |   ` ~  |   [ {  |   ] }  |        |        |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |    (   |    )   |   [ {  |   ] }  |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/
[_NUMBERS] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                                                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                          KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,
  _______, _______, KC_DOT,  TD_SLAS, TD_MNUN, TD_PLEQ,                                                       TD_GVTL, TD_LBCB, TD_RBCB, _______, _______, _______,
           KC_LPRN, KC_RPRN, TD_LBCB, TD_RBCB,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),

[_NUMBERS2] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                                                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                          KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,
  _______, _______, KC_DOT,  TD_SLAS, TD_MNUN, TD_PLEQ,                                                       TD_GVTL, TD_LBCB, TD_RBCB, _______, _______, _______,
           KC_LPRN, KC_RPRN, TD_LBCB, TD_RBCB,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),

/*
Function layer
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|   F12   |   F1   |   F2   |   F3   |   F4   |   F5   |                                                     |   F6   |   F7   |   F8   |   F9   |   F10  |   F11   |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |   Up   |        |        |                                                     |        |        |   Up   | Ctrl+Y |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         | Ctrl+A |  Left  |  Down  |  Right | C+A+Tab|                                                     |  PgUp  |  Left  |  Down  |  Right |  Home  |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         | Ctrl+Z | Ctrl+X | Ctrl+C | Ctrl+V |  Bspc  |                                                     |  PgDn  |  Mute  |  Vol-  |  Vol+  |   End  |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |  Prev  |  Play  |  Next  |  Stop  |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/
[_FUNCTION] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, _______, _______, KC_UP,   _______, _______,                                                       _______, _______, KC_UP,   CTL_Y,   _______, _______,
  _______, CTL_A,   KC_LEFT, KC_DOWN, KC_RGHT, CA_TAB,                                                        KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, _______,
  _______, CTL_Z,   CTL_X,   CTL_C,   CTL_V,   KC_BSPC,                                                       KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, KC_END,  _______,
           _______, _______, _______, _______,                                                                         KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),

[_FUNCTION2] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, _______, _______, KC_UP,   _______, _______,                                                       _______, _______, KC_UP,   CTL_Y,   _______, _______,
  _______, CTL_A,   KC_LEFT, KC_DOWN, KC_RGHT, CA_TAB,                                                        KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, _______,
  _______, CTL_Z,   CTL_X,   CTL_C,   CTL_V,   KC_BSPC,                                                       KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, KC_END,  _______,
           _______, _______, _______, _______,                                                                         KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),

/*
Numpad layer
(Left side duplicates layout from the Numbers layer, just with numpad output; right side layout close to PC numpad layout)
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         | NumLock|        |        |        |        |                                                     |   Tab  | NumLock|  KP /  |  KP *  |  KP -  |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |  KP 6  |  KP 7  |  KP 8  |  KP 9  |  KP 0  |                                                     |        |  KP 7  |  KP 8  |  KP 9  |  KP +  |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |  KP 1  |  KP 2  |  KP 3  |  KP 4  |  KP 5  |                                                     |        |  KP 4  |  KP 5  |  KP 6  |   =    |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |  KP .  | KP/KP* |  KP- _ |  KP+ = |                                                     |        |  KP 1  |  KP 2  |  KP 3  | KP Ent |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |    (   |    )   |   [ {  |   ] }  |                                                                       |        |  KP 0  |  KP .  | KP Ent |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/
[_NUMPAD] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, KC_NUM,  _______, _______, _______, _______,                                                       KC_TAB,  KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, _______,
  _______, KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,                                                         _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
  _______, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                                                         _______, KC_P4,   KC_P5,   KC_P6,   KC_EQL,  _______,
  _______, _______, KC_PDOT, TD_PSPA, TD_MNUN, TD_PPEQ,                                                       _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
           KC_LPRN, KC_RPRN, TD_LBCB, TD_RBCB,                                                                         _______, KC_P0,   KC_PDOT, KC_PENT,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),

/*
Gaming
(Toggle gaming layer with limited dual-role keys and layer access; NKRO turned on by default; Ent/NS + Delete/Numbers2 to access Adjust layer)
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|  LCtrl  |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|  Shift  |        |        |        |        |        |                                                     |        |        |        |        |        |  Shift  |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |   ESC  |xxxxxxxx|                 |  RAlt  |  RCtl  |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |  LAlt  |                 |  RGUI  | Delete |  Bspc  |
	                                          |  Space |  Enter |--------|                 |--------|    /   |    /   |
	                                          |        |        |  Bspc  |                 |Enter/NS| Number2|   Fn2  |
	                                          `--------------------------'                 `--------------------------'
*/
[_GAMING] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  KC_LCTL, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  KC_LSFT, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, KC_RSFT,
           _______, _______, _______, _______,                                                                         _______, _______, _______, _______,
                                                        KC_ESC,  XXXXXXX,                   _______, _______,
                                                                 KC_LALT,                   _______,
                                               KC_SPC,  KC_ENT,  _______,                   ENTNS,   _______, _______
),

/*
Adjust layer
(Press and hold Adjust key on the function row or Enter/Number + Delete/Number2 to access; Numpad and NKRO are on toggle)
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         | Colemak| QWERTY |        | Gaming |        |                                                     | Numpad |        |        |        |        |  QK_BOOT  |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |  NKRO  |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/
[_ADJUST] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, COLEMAK, QWERTY,  _______, GAMING,  _______,                                                       NUMPAD,  _______, _______, _______, _______, QK_BOOT,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, NKROTG,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),

[_ADJUST2] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, COLEMAK, QWERTY,  _______, GAMING,  _______,                                                       NUMPAD,  _______, _______, _______, _______, QK_BOOT,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, NKROTG,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUMBERS, _NUMBERS2, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
	case COLEMAK:
      if (record->event.pressed) {
//        persistent_default_layer_set(1UL << _COLEMAK);
        default_layer_set(1UL << _COLEMAK);
        layer_move (_COLEMAK);
        keymap_config.nkro = 0;
	  }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
//        persistent_default_layer_set(1UL << _QWERTY);
        default_layer_set(1UL << _QWERTY);
        layer_move (_QWERTY);
        keymap_config.nkro = 0;
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        layer_invert (_GAMING);
        layer_off (_NUMPAD);
        keymap_config.nkro = 1;
	  }
      return false;
      break;
  }
  return true;
}
