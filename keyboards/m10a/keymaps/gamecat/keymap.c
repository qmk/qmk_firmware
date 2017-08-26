// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "m10a.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "version.h"

extern keymap_config_t keymap_config;

enum layers {
  _L0,
  _L1,
  _L2,
  _L3,
  _L4,
  _L5,
  _L6,
  _L7,
  _L8,
  _L9
};

enum m10a_keycodes {
    DYNAMIC_MACRO_RANGE = SAFE_RANGE,
};

#include "dynamic_macro.h"
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define FN_ZERO LT(_L9, KC_0)
#define KC_DMR1 DYN_REC_START1
#define KC_DMR2 DYN_REC_START2
#define KC_DMP1 DYN_MACRO_PLAY1
#define KC_DMP2 DYN_MACRO_PLAY2
#define KC_DMRS DYN_REC_STOP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* .-----------.  .-----------.  .-----------.  .-----------.  .-----------.
    *  |  7|  8|  9|  |VLU|Ver|WFD|  |VLU|NXT|FFD|  |   |   |   |  |   |   |   |
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |  4|  5|  6|  |MUT|C-W|CHR|  |MUT|STP|PLY|  |   |   |   |  |   |   |   |
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |  1|  2|  3|  |VLD|CMP|WBK|  |VLD|PRV|RWD|  |   |   |   |  |   |   |   |
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |L0 |FN_L9 0|  |L1 |       |  |L2 |       |  |L3 |       |  |L4 |       |
    *  *-----------*  *-----------*  *-----------*  *-----------*  *-----------*
    *  .-----------.  .-----------.  .-----------.  .-----------.  .-----------.
    *  |   |   |   |  |   |   |   |  |MP1|   |MP2|  |_L6|_L7|_L9|  |   |   |   |
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |   |   |   |  |   |   |   |  |   |MRS|   |  |_L3|_L4|_L5|  |   |   |   |
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |   |   |   |  |   |   |   |  |MR1|   |MR2|  |_L0|_L1|_L2|  |_L8|_L8|_L8|
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |L5 |       |  |L6 |       |  |L7 |       |  |L8 |       |  |L9 |       |
    *  *-----------*  *-----------*  *-----------*  *-----------*  *-----------*
    */
    [_L0] = {{KC_7,    KC_8,    KC_9   }, {KC_4,    KC_5,    KC_6   }, {KC_1,    KC_2,    KC_3   }, {XXXXXXX, XXXXXXX, FN_ZERO}},
    [_L1] = {{KC_VOLU, F(0),    KC_WFWD}, {KC_MUTE, M(1),    M(0)   }, {KC_VOLD, KC_MYCM, KC_WBAK}, {XXXXXXX, XXXXXXX, MO(_L8)}},
    [_L2] = {{KC_VOLU, KC_MNXT, KC_MFFD}, {KC_MUTE, KC_MSTP, KC_MPLY}, {KC_VOLD, KC_MPRV, KC_MRWD}, {XXXXXXX, XXXXXXX, MO(_L8)}},
    [_L3] = {{_______, _______, _______}, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L8)}},
    [_L4] = {{_______, _______, _______}, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L8)}},
    [_L5] = {{_______, _______, _______}, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L8)}},
    [_L6] = {{_______, _______, _______}, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L8)}},
    [_L7] = {{KC_DMP1, _______, KC_DMP2}, {_______, KC_DMRS, _______}, {KC_DMR1, _______, KC_DMR2}, {XXXXXXX, XXXXXXX, MO(_L8)}},
    [_L8] = {{TO(_L6), TO(_L7), TO(_L9)}, {TO(_L3), TO(_L4), TO(_L5)}, {TO(_L0), TO(_L1), TO(_L2)}, {XXXXXXX, XXXXXXX, _______}},
    [_L9] = {{_______, _______, _______}, {_______, _______, _______}, {TO(_L8), TO(_L8), TO(_L8)}, {XXXXXXX, XXXXXXX, _______}},
};

void matrix_init_user(void) {
  #ifdef BACKLIGHT_ENABLE
    backlight_level(0);
  #endif
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case 0:
            if (record->event.pressed) {
                return MACRO(I(10), D(LGUI), T(R), U(LGUI), END);
            } 
            else {
                SEND_STRING("chrome.exe\n");
                return false;
            }
        break;
        case 1:
            if (record->event.pressed) {
                return MACRO(I(10), D(LCTL), T(W), U(LCTL), END);
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
                SEND_STRING ("Keyboard:" QMK_KEYBOARD " -- QMK Version:" QMK_VERSION " -- Keymap:" QMK_KEYMAP);
            }
        break;
    }
};
