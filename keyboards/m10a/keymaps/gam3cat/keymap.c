#include "m10a.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "version.h"

extern keymap_config_t keymap_config;

enum layers {
    _L0 = 0,
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

static uint8_t current_layer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* .-----------.  .-----------.  .-----------.  .-----------.  .-----------.
    *  |  7|  8|  9|  |  +|  -|  *|  |  ^|  &|  !|  |VLU|Ver|WFD|  |VLU|NXT|FFD|
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |  4|  5|  6|  |  /|  %|  ,|  |  D|  E|  F|  |MUT|C-W|CHR|  |MUT|STP|PLY|
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |  1|  2|  3|  |  .|  =|Ent|  |  A|  B|  C|  |VLD|CMP|WBK|  |VLD|PRV|RWD|
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |L0 |  _L9/0|  |L1 |  _L9  |  |L2 |  _L9  |  |L3 |  _L9  |  |L4 |  _L9  |
    *  *-----------*  *-----------*  *-----------*  *-----------*  *-----------*
    *  .-----------.  .-----------.  .-----------.  .-----------.  .-----------.
    *  |   |   |   |  |   |   |   |  |MP1|   |MP2|  |   |   |RST|  |_L6|_L7|_L8|
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |   |   |   |  |   |   |   |  |   |MRS|   |  |   |   |   |  |_L3|_L4|_L5|
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |   |   |   |  |   |   |   |  |MR1|   |MR2|  |   |   |   |  |_L0|_L1|_L2|
    *  |-----------|  |-----------|  |-----------|  |-----------|  |-----------|
    *  |L5 |  _L9  |  |L6 |  _L9  |  |L7 |  _L9  |  |L8 |  _L9  |  |L9 |       |
    *  *-----------*  *-----------*  *-----------*  *-----------*  *-----------*
    */
    [_L0] = {{KC_7,    KC_8,    KC_9   }, {KC_4,    KC_5,    KC_6   }, {KC_1,    KC_2,    KC_3   }, {XXXXXXX, XXXXXXX, FN_ZERO}},
    [_L1] = {{KC_PPLS, KC_PMNS, KC_PAST}, {KC_PSLS, KC_PERC, KC_COMM}, {KC_PDOT, KC_EQL,  KC_PENT}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L2] = {{KC_CIRC, KC_AMPR, KC_EXLM}, {S(KC_D), S(KC_E), S(KC_F)}, {S(KC_A), S(KC_B), S(KC_C)}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L3] = {{KC_VOLU, F(0),    KC_WFWD}, {KC_MUTE, M(1),    M(0)   }, {KC_VOLD, KC_MYCM, KC_WBAK}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L4] = {{KC_VOLU, KC_MNXT, KC_MFFD}, {KC_MUTE, KC_MSTP, KC_MPLY}, {KC_VOLD, KC_MPRV, KC_MRWD}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L5] = {{_______, _______, _______}, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L6] = {{_______, _______, _______}, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L7] = {{KC_DMP1, _______, KC_DMP2}, {_______, KC_DMRS, _______}, {KC_DMR1, _______, KC_DMR2}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L8] = {{_______, _______, RESET  }, {_______, _______, _______}, {_______, _______, _______}, {XXXXXXX, XXXXXXX, MO(_L9)}},
    [_L9] = {{DF(_L6), DF(_L7), DF(_L8)}, {DF(_L3), DF(_L4), DF(_L5)}, {DF(_L0), DF(_L1), DF(_L2)}, {XXXXXXX, XXXXXXX, _______}},
};

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

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(0),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case 0:
            if (record->event.pressed) {
                SEND_STRING ("[Keyboard: " QMK_KEYBOARD "]  --  [QMK Version: " QMK_VERSION "]  --  [Keymap: " QMK_KEYMAP "]");
            }
        break;
    }
}

void matrix_init_user(void) {
  #ifdef BACKLIGHT_ENABLE
    backlight_level(0);
  #endif
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    if (current_layer == layer) {
    }
    else {
        current_layer = layer;
        switch (layer) {
            case 0:
                backlight_level(0);
                break;
            case 1:
                backlight_level(1);
                break;
            case 2:
                backlight_level(2);
                break;
            case 3:
                backlight_level(3);
                break;
            case 4:
                backlight_level(4);
                break;
            case 5:
                backlight_level(5);
                break;
            case 6:
                backlight_level(6);
                break;
            case 7:
                backlight_level(6);
                break;
            case 8:
                backlight_level(6);
                break;
            case 9:
                backlight_level(0);
                break;
            default:
                backlight_level(0);
                break;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Enable Dynamic Macros.
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    return true;
}
