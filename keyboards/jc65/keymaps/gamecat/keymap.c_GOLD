#include "jc65.h"
#include "version.h"

enum layers {
    _BL,     // Base Layer
    _FL,     // Function Layer
    _CL,     // Control Layer
};

enum jc65_keycodes {
    DYNAMIC_MACRO_RANGE = SAFE_RANGE,
};

#include "dynamic_macro.h"
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define FN_CAPS LT(_FL, KC_CAPS)
#define KC_DMR1 DYN_REC_START1
#define KC_DMR2 DYN_REC_START2
#define KC_DMP1 DYN_MACRO_PLAY1
#define KC_DMP2 DYN_MACRO_PLAY2
#define KC_DMRS DYN_REC_STOP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* _BL: Base Layer, mostly standard 65% layout.
    *  FN_CAPS = CAPS when tapped, Fn_FL when held.
    *  GRAVE_ESC + GUI = `
    *  GRAVE_ESC + SHIFT = ~
    *  .---------------------------------------------------------------.
    *  |GrE|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Ins|
    *  |---------------------------------------------------------------|
    *  |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Del|
    *  |---------------------------------------------------------------|
    *  |FnCaps|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |PgU|
    *  |---------------------------------------------------------------|
    *  |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
    *  |---------------------------------------------------------------|
    *  |Ctrl|Gui |Alt |      Space             |RAlt |Ctrl |Lft|Dwn|Rgt|
    *  *---------------------------------------------------------------*
    */
    [_BL] = KEYMAP(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, KC_INS,
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        FN_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_PGUP,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI,          KC_LALT, KC_SPC,           KC_SPC,           KC_SPC,           KC_RALT, XXXXXXX, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* _FL: Function Layer.
    *  M0 opens Chrome
    *  .---------------------------------------------------------------.
    *  |M0 | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|SLock  |PSc|
    *  |---------------------------------------------------------------|
    *  |Fn_CL|   |   |   |   |   |   |   |   |   |   |   |   |     |Pau|
    *  |---------------------------------------------------------------|
    *  |      |   |   |   |   |   |Lft|Dwn|Up |Rgt|   |   |        |Hme|
    *  |---------------------------------------------------------------|
    *  |        |   |   |   |   |   |   |   |   |   |   |VlMute|VlU|End|
    *  |---------------------------------------------------------------|
    *  |    |    |Menu|                        |     |     |WBk|VlD|WFw|
    *  *---------------------------------------------------------------*
    */
    [_FL] = KEYMAP(
        M(0),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_SLCK, KC_PSCR,
        MO(_CL),          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS,
        _______,          _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_MUTE, KC_VOLU, KC_END,
        _______, _______,          KC_MENU, _______,          _______,          _______,          _______, _______, _______, KC_WBAK, KC_VOLD, KC_WFWD
    ),

    /* _CL: Control Layer.
    *  RGB Underglow and Dynamic Macro controls.
    *  .---------------------------------------------------------------.
    *  |Ver|Tog|Mod|H- |H+ |S- |S+ |V- |V+ |   |   |   |   |       |MP1|
    *  |---------------------------------------------------------------|
    *  |     |   |   |   |   |   |   |   |   |   |   |   |   |     |MR1|
    *  |---------------------------------------------------------------|
    *  |      |   |   |   |   |   |   |   |   |   |   |   |        |MS |
    *  |---------------------------------------------------------------|
    *  |        |   |   |   |   |   |   |   |   |   |   |      |   |MR2|
    *  |---------------------------------------------------------------|
    *  |Rst |    |    |                        |     |     |   |   |MP2|
    *  *---------------------------------------------------------------*
    */
    [_CL] = KEYMAP(
        F(0),    RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, KC_DMP1,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DMR1,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_DMRS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, KC_DMR2,
        RESET,   _______,          _______, _______,          _______,          _______,          _______, _______, _______, _______, _______, KC_DMP2
    ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case 0:
            if (record->event.pressed) {
                return MACRO(I(0), D(LGUI), T(R), U(LGUI), END);
            } 
            else {
                SEND_STRING("chrome.exe https://geekhack.org/index.php?topic=86756.0\n");
                return false;
            }
        break;
    }
    return MACRO_NONE;
};

// Enable Dynamic Macros.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    return true;
}

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(0),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case 0:
            if (record->event.pressed) {
                SEND_STRING ("Keyboard:" QMK_KEYBOARD "    QMK Version:" QMK_VERSION "    Keymap:" QMK_KEYMAP);
            }
        break;
    }
};
