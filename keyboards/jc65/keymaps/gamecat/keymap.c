#include "jc65.h"
#define _BL 0    // Base Layer
#define _FL 1    // Function Layer
#define _CL 2    // Control Layer
#define _______ KC_TRNS
#define FN_CAPS LT(_FL, KC_CAPS)

enum jc65_keycodes {
  DYNAMIC_MACRO_RANGE = SAFE_RANGE,
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    *  _BL: Base layer, mostly standard 65% layout.
    *  GRAVE_ESC information:
    *      GUI + GRAVE_ESC results in: `
    *      SHIFT + GRAVE_ESC results in: ~
    *      GRAVE_ESC requires "#define GRAVE_ESC_CTRL_OVERRIDE" in config.h to
    *      avoid breaking CTRL+SHIFT+ESC shortcut to Windows task manager.
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
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______, KC_BSPC, KC_INS,
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        FN_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_PGUP,
        KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI,          KC_LALT, KC_SPC,           KC_SPC,           KC_SPC,           KC_RALT, _______, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
    *  _FL: Function layer.
    *  Fn0 *should* open Chrome
    *  .---------------------------------------------------------------.
    *  |Fn0| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|SLock  |PSc|
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
        F(0),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_SLCK, KC_PSCR,
        MO(_CL),          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS,
        _______,          _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_MUTE, KC_VOLU, KC_END,
        _______, _______,          KC_MENU, _______,          _______,          _______,          _______, _______, _______, KC_WBAK, KC_VOLD, KC_WFWD
    ),

    /*
    *  _CL: Control layer.
    *  RGB ungerglow and Dynamic Macro controls.
    *  .---------------------------------------------------------------.
    *  |   |Tog|Mod|H- |H+ |S- |S+ |V- |V+ |   |   |   |   |       |MP1|
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
        _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, DYN_MACRO_PLAY1,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DYN_REC_START1,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          DYN_REC_STOP,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, DYN_REC_START2,
        RESET,   _______,          _______, _______,          _______,          _______,          _______, _______, _______, _______, _______, DYN_MACRO_PLAY2
    ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
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
                MACRO(D(LGUI), T(R), U(LGUI), END);
                SEND_STRING("chrome.exe");
                MACRO(T(ENT), END);
                MACRO(D(LCTL), T(L), U(LCTL), END);
                SEND_STRING("https://geekhack.org/index.php?topic=86756.0");
                MACRO(T(ENT), END);
                MACRO(D(LCTL), T(T), U(LCTL), END);
                SEND_STRING("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
                MACRO(T(ENT), END);
            }
        break;
    }
};
