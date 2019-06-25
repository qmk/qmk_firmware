#include QMK_KEYBOARD_H
#include "brandonschlack.h"

enum bdn9_layers {
    _LR_NAV = KEYMAP_LAYERS,
    _LR_REVIEW,
    _LR_EDIT
};

enum bdn9_keycodes {
    TG_LNAV = KEYMAP_SAFE_RANGE,
    TG_REVW,
    TG_EDIT,
    TG_LGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Layer: Navigation
        | Knob 1: Scroll Up/Dn  |      | Knob 2: Tab Prv/Nxt   |
        | Press: Reopen Tab     | CmTb | Close Tab             |
        | PgDn                  | Up   | PgUp                  |
        | Left                  | Down | Right                 |
     */
    [_NAVI] = LAYOUT(
        REO_TAB, CMD_TAB, CLS_TAB,
        KC_PGDN, KC_UP, DTP_LGT,
        KC_LEFT, KC_DOWN, DTP_MGC
    ),
    /*
        Layer: Reeder
        | Knob 1: j/k           |      | Knob 2: n/p           |
        | Press: H              | S    | R                     |
        | CMD+TAB               | M    | L                     |
        | Cmd+1                 | Cmd+2| Cmd+3                 |
     */
    [_REEDER] = LAYOUT(
        KC_H, KC_S, KC_R,
        CMD_TAB, KC_M, DTP_LGT,
        G(KC_1), G(KC_2), DTP_MGC
    ),
    /*
        Layer: Media
        | Knob 1: Vol +/-       |      | Knob 2: Track Prv/Nxt |
        | Press: Mute           | Plyr | Press: Play/Pause     |
        | J                     | K    | L                     |
        | Left                  | Spce | Right                 |
     */
    [_MEDIA] = LAYOUT(
        KC_MUTE, MC_PLYR, KC_MPLY,
        KC_J, KC_K, DTP_LGT,
        KC_LEFT, KC_SPC, DTP_MGC
    ),
    /*
        Layer: Keypad/Karabiner
        | Knob 1: +/-           |      | Knob 2: =/.           |
        | Press: 1              | 2    | 3                     |
        | 4                     | 5    | 6                     |
        | 7                     | 8    | 9                     |
     */
    [_KEYPAD] = LAYOUT(
        KC_P1, KC_P2, KC_P3,
        KC_P4, KC_P5, DTP_LGT,
        KC_P7, KC_P8, DTP_MGC
    ),
    /*
        Layer: Navigation
        | Knob 1: =/-           |      | Knob 2: Page Dn/Up    |
        | Press: Review         | J    | Press: Edit           |
        | Home, Hold: BD Layer  | Up   | End                   |
        | Left                  | Down | Right                 |
     */
    [_LR_NAV] = LAYOUT(
        TG_REVW, KC_J, TG_EDIT,
        KC_HOME, KC_UP, DTP_LGT,
        KC_LEFT, KC_DOWN, DTP_MGC
    ),
    /*
        Layer: Review/Rate
        | Knob 1: ]/[           |      | Knob 2: G(Up)/G(Dn)   |
        | Press: Nav            | 7    | Press: Edit           |
        | 0                     | 8    | U                     |
        | Left                  | 9    | Right                 |
     */
    [_LR_REVIEW] = LAYOUT(
        TG_LNAV, KC_7, TG_EDIT,
        KC_0, KC_8, DTP_LGT,
        KC_LEFT, KC_6, DTP_MGC
    ),
    /*
        Layer: Edit/Develop
        | Knob 1: ./,           |      | Knob 2: =/-           |
        | Press: Review         | \    | Press: Nav            |
        | X                     | Undo | P                     |
        | Left                  | Redo | Right                 |
     */
    [_LR_EDIT] = LAYOUT(
        TG_REVW, KC_BSLS, TG_LNAV,
        KC_X, MC_UNDO, DTP_LGT,
        KC_LEFT, MC_REDO, DTP_MGC
    ),
    /*
        Layer: Light
        | RGB Toggle            | Nav  | RESET                 |
        | Reeder                | Meda | Keypad                |
        | Review                | LNav | Edit                  |
     */
    [_LIGHT] = LAYOUT(
        RGB_TOG, RGB_VAI, TG_LGHT,
        RGB_RMOD,RGB_VAD, RGB_MOD,
        RGB_M_P, RGB_M_B, XXXXXXX
    ),
    /*
        Layer: Magic
        | MAKE                  | Nav  | RESET                 |
        | Reeder                | Meda | Keypad                |
        | Review                | LNav | Edit                  |
     */
    [_MAGIC] = LAYOUT(
        KC_MAKE, TG_NAVI, TG_LGHT,
        TG_REDR, TG_MEDA, TG_KYPD,
        TG_REVW, TG_LNAV, TG_EDIT
    ),
};

/**
 * Encoder
 */
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _NAVI:
                if (!clockwise) {
                    tap_code(MC_WH_D);
                } else {
                    tap_code(MC_WH_U);
                }
                break;
            case _REEDER:
                if (!clockwise) {
                    tap_code(KC_J);
                } else {
                    tap_code(KC_K);
                }
                break;
            case _MEDIA:
                if (!clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case _KEYPAD:
                if (!clockwise) {
                    tap_code(KC_PPLS);
                } else {
                    tap_code(KC_PMNS);
                }
                break;
            case _LR_NAV:
                if (!clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
            case _LR_REVIEW:
                if (!clockwise) {
                    tap_code(KC_RBRC);
                } else {
                    tap_code(KC_LBRC);
                }
                break;
            case _LR_EDIT:
                if (!clockwise) {
                    tap_code(KC_DOT);
                } else {
                    tap_code(KC_COMM);
                }
                break;
            case _LIGHT:
                if (!clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
        }
    }
    else if (index == 1) {
        switch (biton32(layer_state)) {
            case _NAVI:
                if (!clockwise) {
                    tap_code16(NXT_TAB);
                } else {
                    tap_code16(PRV_TAB);
                }
                break;
            case _REEDER:
                if (!clockwise) {
                    tap_code(KC_N);
                } else {
                    tap_code(KC_P);
                }
                break;
            case _MEDIA:
                if (!clockwise) {
                    tap_code(KC_MFFD);
                } else {
                    tap_code(KC_MRWD);
                }
                break;
            case _KEYPAD:
                if (!clockwise) {
                    tap_code(KC_PEQL);
                } else {
                    tap_code(KC_PDOT);
                }
                break;
            case _LR_NAV:
                if (!clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
                break;
            case _LR_REVIEW:
                if (!clockwise) {
                    tap_code16(G(KC_UP));
                } else {
                    tap_code16(G(KC_DOWN));
                }
                break;
            case _LR_EDIT:
                if (!clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
            case _LIGHT:
                if (!clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
                break;
        }
    }
}

/**
 * Keycodes
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_LNAV:
            if (!record->event.pressed) {
                tap_code(KC_G);
                layer_move(_LR_NAV);
            }
            break;
        case TG_REVW:
            if (!record->event.pressed) {
                tap_code(KC_E);
                layer_move(_LR_REVIEW);
            }
            break;
        case TG_EDIT:
            if (!record->event.pressed) {
                tap_code(KC_D);
                layer_move(_LR_EDIT);
            }
            break;
        case TG_LGHT:
            if (!record->event.pressed) {
                layer_invert(_LIGHT);
            }
            break;
    }
    return true;
}

/**
 * Layer Switch
 */
layer_state_t layer_state_set_keymap (layer_state_t state) {
    switch (biton32(state)) {
        case _LR_NAV:
            rgb_layer_helper(HSV_TEAL);
            break;
        case _LR_REVIEW:
            rgb_layer_helper(HSV_CYAN);
            break;
        case _LR_EDIT:
            rgb_layer_helper(HSV_AZURE);
            break;
    }
    return state;
}

/**
 * Tap Dances
 */
void process_tap_dance_keycode (bool reset, uint8_t toggle_layer) {
    uint16_t keycode = 0;
    switch (toggle_layer) {
        case _LIGHT:
            switch (biton32(layer_state)) {
                case _NAVI:
                    keycode = KC_PGUP;
                case _REEDER:
                case _MEDIA:
                    keycode = KC_L;
                    break;
                case _KEYPAD:
                    keycode = KC_P6;
                    break;
                case _LR_NAV:
                    keycode = KC_END;
                case _LR_REVIEW:
                    keycode = KC_U;
                case _LR_EDIT:
                    keycode = KC_P;
                    break;
            }
            break;
        case _MAGIC:
            switch (biton32(layer_state)) {
                case _NAVI:
                case _MEDIA:
                case _LR_NAV:
                case _LR_REVIEW:
                case _LR_EDIT:
                    keycode = KC_RGHT;
                    break;
                case _REEDER:
                    keycode = G(KC_3);
                    break;
                case _KEYPAD:
                    keycode = KC_P9;
                    break;
            }
            break;
    }
    if (!reset) {
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
    }
}
