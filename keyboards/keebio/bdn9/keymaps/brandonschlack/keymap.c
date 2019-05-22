#include QMK_KEYBOARD_H
#include "brandonschlack.h"

enum bdn9_layers {
    LR_NAV,
    LR_EDIT,
    LR_REVW,
    BD_FUNC
};

enum bdn9_keycodes {
    TG_NAV = KEYMAP_SAFE_RANGE,
    TG_EDIT,
    TG_REVW,
    MC_UNDO,
    MC_REDO
};

#define MC_UNDO LGUI(KC_Z)
#define MC_REDO LSFT(LGUI(KC_Z))

enum bdn9_combos {
    TG_BDN9,
};

const uint16_t PROGMEM func_combo[] = {KC_LEFT, KC_RGHT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [TG_BDN9] = COMBO_ACTION(func_combo),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Layer: Navigation
        | Knob 1: =/-           |      | Knob 2: Page Dn/Up    |
        | Press: Review         | J    | Press: Edit           |
        | Home                  | Up   | End                   |
        | Left                  | Down | Right                 |
     */
    [LR_NAV] = LAYOUT(
        TG_REVW, KC_J,    TG_EDIT,
        KC_HOME, KC_UP,   KC_END,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
        Layer: Edit/Develop
        | Knob 1: ./,           |      | Knob 2: =/-           |
        | Press: Review         | \    | Press: Nav            |
        | X                     | Undo | P                     |
        | Left                  | Redo | Right                 |
     */
    [LR_EDIT] = LAYOUT(
        TG_REVW, KC_BSLS, TG_NAV,
        KC_X,    MC_UNDO, KC_P,
        KC_LEFT, MC_REDO, KC_RGHT
    ),
    /*
        Layer: Review/Rate
        | Knob 1: ]/[           |      | Knob 2: G(Up)/G(Dn)   |
        | Press: Nav            | 7    | Press: Edit           |
        | 0                     | 8    | U                     |
        | Left                  | 9    | Right                 |
     */
    [LR_REVW] = LAYOUT(
        TG_NAV,  KC_7,    TG_EDIT,
        KC_0,    KC_8,    RGB_MOD,
        KC_LEFT, KC_6,    KC_RGHT
    ),
    /*
        Layer: Review/Rate
        | XXX                   | RST  | XXX                   |
        | MAKE                  | XXX  | Flash                 |
        | Review                | Nav  | Edit                  |
     */
    [BD_FUNC] = LAYOUT(
        XXXXXXX, RESET,   XXXXXXX,
        KC_MAKE, XXXXXXX, KC_FLSH,
        TG_REVW, TG_NAV,  TG_EDIT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case LR_NAV:
                if (!clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
            case LR_EDIT:
                if (!clockwise) {
                    tap_code(KC_DOT);
                } else {
                    tap_code(KC_COMM);
                }
                break;
            case LR_REVW:
                if (!clockwise) {
                    tap_code(KC_RBRC);
                } else {
                    tap_code(KC_LBRC);
                }
                break;
        }
    }
    else if (index == 1) {
        switch (biton32(layer_state)) {
            case LR_NAV:
                if (!clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
            case LR_EDIT:
                if (!clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
            case LR_REVW:
                if (!clockwise) {
                    tap_code16(G(KC_UP));
                } else {
                    tap_code16(G(KC_DOWN));
                }
                break;
        }
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_NAV:
            if (!record->event.pressed) {
                tap_code(KC_G);
                layer_move(LR_NAV);
            }
            break;
        case TG_EDIT:
            if (!record->event.pressed) {
                tap_code(KC_D);
                layer_move(LR_EDIT);
            }
            break;
        case TG_REVW:
            if (!record->event.pressed) {
                tap_code(KC_E);
                layer_move(LR_REVW);
            }
            break;
    }
    return true;
}

void process_combo_event(uint8_t combo_index, bool pressed) {
    switch (combo_index) {
        case TG_BDN9:
            if (pressed) {
                layer_move(BD_FUNC);
            }
            break;
    }
}
