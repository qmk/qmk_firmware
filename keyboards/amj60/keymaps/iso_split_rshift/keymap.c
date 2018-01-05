
#include "amj60.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DEF 0
#define _SPC 1
#define _TAB 2
#define _SFX 3

// dual-role shortcuts
#define TABDUAL   LT(_TAB, KC_TAB)
#define CAPSDUAL  CTL_T(KC_ESC)
#define SPACEDUAL LT(_SPC, KC_SPACE)
#define ENTERDUAL CTL_T(KC_ENT)
// arrow cluster duality bottom right corner
#define ARRLEFT  ALT_T(KC_LEFT)
#define ARRDOWN  GUI_T(KC_DOWN)
#define ARRUP    SFT_T(KC_UP)
#define ARRRIGHT CTL_T(KC_RIGHT)
// german brackets
#define GER_CUR_L RALT(KC_7)    // [
#define GER_CUR_R RALT(KC_0)    // ]
#define GER_PAR_L LSFT(KC_8)    // (
#define GER_PAR_R LSFT(KC_9)    // )
#define GER_ANG_L KC_NUBS       // <
#define GER_ANG_R LSFT(KC_NUBS) // >
#define GER_BRC_L RALT(KC_8)    // [
#define GER_BRC_R RALT(KC_9)    // ]

// increase readability 
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _DEF: Default Layer
     * ,-----------------------------------------------------------.
     * |Grv|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   \ | Tab is Fn1
     * |-----------------------------------------------------------|
     * |Ctrl   | A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Return |
     * |-----------------------------------------------------------|
     * |Sft | < |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn2| RShift is UP
     * |-----------------------------------------------------------|
     * |Ctrl|Win |Alt |      Space/Fn0         |Alt |Win |Menu|RCtl| Gui Menu, RCtrl is 
     * `-----------------------------------------------------------'   LEFT DWN RIGHT
     */
    [_DEF] = KEYMAP_ISO_SPLITRSHIFT(
        KC_GRV,   KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,   \
        TABDUAL,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,   \
        CAPSDUAL, KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,  ENTERDUAL, \
        KC_LSFT,  KC_NUBS, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, ARRUP,    TG(_SFX),  \
        KC_LCTL,  KC_LGUI, KC_LALT,             SPACEDUAL,                       KC_RALT, ARRLEFT, ARRDOWN,  ARRRIGHT),

    /* Keymap 1: F-and-vim Layer, modified with Space (by holding space)
     * ,-----------------------------------------------------------.
     * |PrSc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete|
     * |-----------------------------------------------------------|
     * |    |Paus| Up| [ | ] |   |   |   | ( | ) |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |Lft|Dwn|Rgt|   |   |Left|Down|Right|Up|  |   | PLAY |
     * |-----------------------------------------------------------|
     * |    |   |   |   | < | > |   |M0 |   |   |   |   | Vol+ |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |Alt |Prev|Vol-|Next|
     * `-----------------------------------------------------------'
     */
    [_SPC] = KEYMAP_ISO_SPLITRSHIFT(
        KC_PSCR, KC_F1,   KC_F2,   KC_F3,     KC_F4,     KC_F5,     KC_F6,    KC_F7,     KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
        _______, KC_PAUS, KC_UP,   GER_BRC_L, GER_BRC_R, _______,   _______,  GER_PAR_L, GER_PAR_R, _______, _______, _______, _______, _______, \
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,  _______,   _______,   KC_LEFT,  KC_DOWN,   KC_UP,     KC_RGHT, _______, _______, _______, KC_MPLY, \
        _______, _______, _______, _______,   GER_ANG_L, GER_ANG_R, KC_SPACE, M(0),      _______,   _______, _______, _______, KC_VOLU, _______, \
        _______, _______, _______,                                  _______,                                 _______, KC_MPRV, KC_VOLD, KC_MNXT),

    /* Keymap 2: Tab Layer w/ vim pageup, modified with Tab (by holding tab)
     * ,-----------------------------------------------------------.
     * |WAKE|   |   |   |   |   |   |   |   |   |   |   |   |Insert|  TAB+GRC = WAKE
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |   | { | } |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |Pos1|PgDn|PgUp|End|  |   |Retrn |
     * |-----------------------------------------------------------|
     * |    |   |   |   |   |   |   |AF2|   |   |   |   | PgUp |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |Alt |Pos1|PgDn|End |
     * `-----------------------------------------------------------'
     */
    [_TAB] = KEYMAP_ISO_SPLITRSHIFT(
        KC_WAKE, _______, _______, _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______, KC_INS,  \
        _______, _______, _______, _______, _______, _______, _______, GER_CUR_L, GER_CUR_R, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN,    KC_PGUP,  KC_END,  _______, _______, _______, KC_ENT,  \
        _______, _______, _______, _______, _______, _______, _______, M(1),       _______,  _______, _______, _______, KC_PGUP, _______, \
        _______, _______, _______,                            _______,                                _______, KC_HOME, KC_PGDN, KC_END),

    /* Keymap 3: Split right shift Numpad toggle Layer (by tapping the split rshift key)
     * ,-----------------------------------------------------------.
     * |RSET|  |   |   |   |   |   |  7|  8|  9|   |   |   |Backsp |
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   | 4 | 5 | 6 |   |   |   |   \ |
     * |-----------------------------------------------------------|
     * |      | L | L |   |   |   |   | 1 | 2 | 3 |   |   | Return |
     * |-----------------------------------------------------------|
     * |    |   | L | L | L | L | L | L |   | 0 |   |  /|  Up  |   | All "L"s represent
     * |-----------------------------------------------------------| LED controlling
     * |Ctrl|Win |Alt |                        |Alt |Left|Down|Right|
     * `-----------------------------------------------------------'
     */
    [_SFX] = KEYMAP_ISO_SPLITRSHIFT(
        RESET,   _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9, _______, _______, _______, KC_BSPC, \
        _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6, _______, _______, _______, KC_BSLS, \
        _______, F(2),    F(3),    _______, _______, _______, _______, KC_1,    KC_2,    KC_3, _______, _______, XXXXXXX, KC_ENT,  \
        _______, F(4),    F(5),    F(6),    F(7),    F(8),    F(9),    _______, _______, KC_0, _______, KC_SLSH, KC_UP,   _______, \
        _______, _______, _______,                            _______,                         _______, KC_LEFT, KC_DOWN, KC_RGHT),
};

enum function_id {
    LAUNCH,
    RGBLED_TOGGLE,
};

const uint16_t PROGMEM fn_actions[] = {
    [1]  = ACTION_FUNCTION(LAUNCH),
    [10] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ENT),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
        case 0:
            return (record->event.pressed ? 
                    MACRO( D(RALT), T(SPC), U(RALT), END )
                    :MACRO( END ));
            break;
        case 1:
            return (record->event.pressed ? 
                    MACRO( D(LALT), T(F2), U(LALT), END )
                    :MACRO( END ));
            break;
    }
    return MACRO_NONE;
};
