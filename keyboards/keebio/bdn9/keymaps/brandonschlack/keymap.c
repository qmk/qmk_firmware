#include QMK_KEYBOARD_H
#include "brandonschlack.h"

enum bdn9_layers {
    LR_NAV,
    LR_REVW,
    LR_EDIT,
    BD_FUNC
};

enum bdn9_keycodes {
    TG_NAV = KEYMAP_SAFE_RANGE,
    TG_REVW,
    TG_EDIT,
    MC_UNDO,
    MC_REDO
};

#define MC_UNDO LGUI(KC_Z)
#define MC_REDO LSFT(LGUI(KC_Z))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Layer: Navigation
        | Knob 1: =/-           |      | Knob 2: Page Dn/Up    |
        | Press: Review         | J    | Press: Edit           |
        | Home, Hold: Shift     | Up   | End                   |
        | Left                  | Down | Right                 |
     */
    [LR_NAV] = LAYOUT(
        TG_REVW, KC_J, TG_EDIT,
        LSFT_T(KC_HOME), KC_UP, KC_END,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
        Layer: Review/Rate
        | Knob 1: ]/[           |      | Knob 2: G(Up)/G(Dn)   |
        | Press: Nav            | 7    | Press: Edit           |
        | 0, Hold: Shift        | 8    | U                     |
        | Left                  | 9    | Right                 |
     */
    [LR_REVW] = LAYOUT(
        TG_NAV, KC_7, TG_EDIT,
        LSFT_T(KC_0), KC_8, KC_U,
        KC_LEFT, KC_6, KC_RGHT
    ),
    /*
        Layer: Edit/Develop
        | Knob 1: ./,           |      | Knob 2: =/-           |
        | Press: Review         | \    | Press: Nav            |
        | X, Hold: Shift        | Undo | P                     |
        | Left                  | Redo | Right                 |
     */
    [LR_EDIT] = LAYOUT(
        TG_REVW, KC_BSLS, TG_NAV,
        LSFT_T(KC_X), MC_UNDO, KC_P,
        KC_LEFT, MC_REDO, KC_RGHT
    ),
    /*
        Layer: BDN9
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
            case LR_REVW:
                if (!clockwise) {
                    tap_code(KC_RBRC);
                } else {
                    tap_code(KC_LBRC);
                }
                break;
            case LR_EDIT:
                if (!clockwise) {
                    tap_code(KC_DOT);
                } else {
                    tap_code(KC_COMM);
                }
                break;
        }
    }
    else if (index == 1) {
        switch (biton32(layer_state)) {
            case LR_NAV:
                if (!clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
                break;
            case LR_REVW:
                if (!clockwise) {
                    tap_code16(G(KC_UP));
                } else {
                    tap_code16(G(KC_DOWN));
                }
                break;
            case LR_EDIT:
                if (!clockwise) {
                    tap_code(KC_EQL);
                } else {
                    tap_code(KC_MINS);
                }
                break;
        }
    }
}

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_NAV:
            if (record->event.pressed) {
                if (MODS_SHIFT) {
                    layer_move(BD_FUNC);
                } else {
                    tap_code(KC_G);
                    layer_move(LR_NAV);
                }
            }
            break;
        case TG_REVW:
            if (record->event.pressed) {
                if (MODS_SHIFT) {
                    layer_move(BD_FUNC);
                } else {
                    tap_code(KC_E);
                    layer_move(LR_REVW);
                }
            }
            break;
        case TG_EDIT:
            if (record->event.pressed) {
                if (MODS_SHIFT) {
                    layer_move(BD_FUNC);
                } else {
                    tap_code(KC_D);
                    layer_move(LR_EDIT);
                }
            }
            break;
    }
    return true;
}
