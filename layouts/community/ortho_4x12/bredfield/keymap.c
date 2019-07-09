#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Keymap layers
enum layer_names {
    _BASE_LAYER,
    _RAISE_LAYER,
    _LOWER_LAYER,
    _NUMPAD_LAYER,
    _NAVIGATION_LAYER,
    _UI_LAYER,
    _KEYBOARD_LAYER,
};

// Layer switches aliases
#define L_LOWER MO(_LOWER_LAYER)
#define L_RAISE MO(_RAISE_LAYER)
#define L_NUMPAD MO(_NUMPAD_LAYER)
#define L_UI MO(_UI_LAYER)
#define L_KEYBD MO(_KEYBOARD_LAYER)
#define SCL_NAV LT(_NAVIGATION_LAYER, KC_SCLN)
#define SFT_MIN MT(MOD_RSFT, KC_MINS)
#define SFT_ENT KC_SFTENT

// GUI chords
#define GUI_1 LGUI(KC_1)
#define GUI_2 LGUI(KC_2)
#define GUI_3 LGUI(KC_3)
#define GUI_4 LGUI(KC_4)
#define GUI_5 LGUI(KC_5)
#define GUI_6 LGUI(KC_6)
#define GUI_7 LGUI(KC_7)
#define GUI_8 LGUI(KC_8)
#define GUI_9 LGUI(KC_9)
#define GUI_0 LGUI(KC_0)
#define GUI_MIN LGUI(KC_MINS)
#define GUI_EQL LGUI(KC_EQL)
#define GUI_LBR LGUI(KC_LBRC)
#define GUI_RBR LGUI(KC_RBRC)
#define GUI_ENT LGUI_T(KC_ENT)
#define GUI_ESC LGUI_T(KC_ESC)
#define GUI_TAB LGUI(KC_TAB) // application toggle
#define GUI_GRV LGUI(KC_GRV) // window toggle
#define GUI_SSF LGUI(LSFT(KC_3)) // Full screen shot
#define GUI_SST LGUI(LSFT(KC_4)) // Targetted screen shot

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------------------------------.
 * |   Tab  |    Q   |    W   |    E   |    R   |    T   |    Y   |    U   |    I   |    O   |    P   |   -    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * | GUI/Esc|    A   |    S   |    D   |    F   |    G   |    H   |    J   |    K   |    L   |  ;/nav |   "    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |  Shift |    Z   |    X   |    C   |    V   |    B   |    N   |    M   |    ,   |    .   |    /   | Sft/ent|
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * | Numpad |  Ctrl  |  Alt   |  GUI   |  Lower |  Bksp  |  Space | Raise  |  Ctrl  |  Alt   |   UI   |  Keybd |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_BASE_LAYER] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    GUI_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SCL_NAV, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT,
    L_NUMPAD,KC_LCTL, KC_LALT, KC_LGUI, L_LOWER, KC_BSPC, KC_SPACE,L_RAISE, KC_RCTRL,KC_RALT, L_UI,    L_KEYBD
),

/* Lower
 * ,-----------------------------------------------------------------------------------------------------------.
 * |   `    |    !   |    @   |    #   |    $   |    %   |    ^   |    &   |    *   |   +    |    =   |    -   |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |    0   |    \   |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |   ,    |    .   |    /   |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |  Del   |        |        |        |        |        |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_LOWER_LAYER] = LAYOUT_ortho_4x12(
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,  _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, _______,
    _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------------------------------.
 * |   ~    |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |    F9  |  F10   |   _    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |    {   |    [   |    (   |   <    |    >   |    )   |    ]   |    }   |        |   |    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |   Del  |        |        |        |        |        |        |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_RAISE_LAYER] = LAYOUT_ortho_4x12(
    KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_7,    KC_F8,   KC_F9,   KC_F10,  KC_UNDS,
    _______, XXXXXXX, KC_LCBR, KC_LBRC, KC_LPRN, KC_LABK, KC_RABK, KC_RPRN, KC_RBRC, KC_RCBR, XXXXXXX, KC_PIPE,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______, _______
),

/* Numpad
 * ,-----------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |   7    |    8   |   9    |   *    |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |   4    |    5   |   6    |   -    |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |   1    |    2   |   3    |   +    |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |   0    |    .   |   /    |        |        |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_NUMPAD_LAYER] = LAYOUT_ortho_4x12(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_ASTR, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_MINS, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_PLUS, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_DOT,  KC_SLSH, _______, _______
),

/* Navigation
 * ,-----------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |  Home  |   Up   |  End   |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |  Left  |  Down  | Right  |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |  Enter |        |        |   Del  |        |        |        |        |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_NAVIGATION_LAYER] = LAYOUT_ortho_4x12(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, KC_ENT,  _______, _______, KC_DEL,  _______, _______, _______, _______
),

/* UI
 * ,--------------------------------------------------------------------------------+--------+-----------------.
 * | GUI Tab|        |        |        |        |        |        |        |        | GUI -  | GUI =  |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * | GUI `  | GUI 1  |  GUI 2 |  GUI 3 |  GUI 4 |  GUI 5 | GUI 6  | GUI 7  |        | GUI [  | GUI ]  |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------------------------+--------|
 * |        |Full SS | Area SS|        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |  Prev  |  Play  | Next   |  Bri - |        |        |  Bri + |  Mute  | Vol -  | Vol +  |        |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_UI_LAYER] = LAYOUT_ortho_4x12(
    GUI_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GUI_MIN, GUI_EQL, XXXXXXX,
    GUI_GRV, GUI_1,   GUI_2,   GUI_3,   GUI_4,   GUI_5,   GUI_6,   GUI_7,   XXXXXXX, GUI_LBR, GUI_RBR, XXXXXXX,
    _______, GUI_SSF, GUI_SST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_MRWD, KC_MPLY, KC_MFFD, KC_VOLD, KC_MUTE, KC_MUTE, KC_VOLU, _______, _______, _______, _______
),

/* Keyboard
 * ,--------------------------------------------------------------------------------+--------+-----------------.
 * |        |        |        |        |        |        |        |        |        |        |        | RESET  |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | DEBUG  |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_KEYBOARD_LAYER] = LAYOUT_ortho_4x12(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______
),
};