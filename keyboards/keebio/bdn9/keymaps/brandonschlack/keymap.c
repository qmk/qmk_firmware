#include QMK_KEYBOARD_H
#include "brandonschlack.h"

enum bdn9_layers {
    _KEYPAD,
    _MEDIA,
    _LR_NAV,
    _LR_REVIEW,
    _LR_EDIT
};

enum bdn9_keycodes {
    TG_KYPD = KEYMAP_SAFE_RANGE,
    TG_MEDA,
    TG_NAV,
    TG_REVW,
    TG_EDIT,
    MC_UNDO,
    MC_REDO
};

#define MC_UNDO LGUI(KC_Z)
#define MC_REDO LSFT(LGUI(KC_Z))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Layer: Keypad/Karabiner
        | Knob 1: +/-           |      | Knob 2: =/.           |
        | Press: 1              | 2    | 3                     |
        | 4, Hold: BD Layer     | 5    | 6                     |
        | 7                     | 8    | 9                     |
     */
    [_KEYPAD] = LAYOUT(
        KC_P1, KC_P2, KC_P3,
        LT(_MAGIC, KC_P4), KC_P5, KC_P6,
        KC_P7, KC_P8, KC_P9
    ),
    /*
        Layer: Media
        | Knob 1: Vol +/-       |      | Knob 2: Track Prv/Nxt |
        | Press: Mute           | Plyr | Press: Play/Pause     |
        | Home, Hold: BD Layer  | Up   | End                   |
        | Left                  | Down | Right                 |
     */
    [_MEDIA] = LAYOUT(
        KC_MUTE, MC_PLYR, KC_MPLY,
        LT(_MAGIC, KC_HOME), KC_UP, KC_END,
        KC_LEFT, KC_DOWN, KC_RGHT
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
        LT(_MAGIC, KC_HOME), KC_UP, KC_END,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
        Layer: Review/Rate
        | Knob 1: ]/[           |      | Knob 2: G(Up)/G(Dn)   |
        | Press: Nav            | 7    | Press: Edit           |
        | 0, Hold: BD Layer     | 8    | U                     |
        | Left                  | 9    | Right                 |
     */
    [_LR_REVIEW] = LAYOUT(
        TG_NAV, KC_7, TG_EDIT,
        LT(_MAGIC, KC_0), KC_8, KC_U,
        KC_LEFT, KC_6, KC_RGHT
    ),
    /*
        Layer: Edit/Develop
        | Knob 1: ./,           |      | Knob 2: =/-           |
        | Press: Review         | \    | Press: Nav            |
        | X, Hold: BD Layer     | Undo | P                     |
        | Left                  | Redo | Right                 |
     */
    [_LR_EDIT] = LAYOUT(
        TG_REVW, KC_BSLS, TG_NAV,
        LT(_MAGIC, KC_X), MC_UNDO, KC_P,
        KC_LEFT, MC_REDO, KC_RGHT
    ),
    /*
        Layer: Magic
        | FLASH                 | XXX  | MAKE                  |
        | ___                   | Kyp  | Media                 |
        | Review                | Nav  | Edit                  |
     */
    [_MAGIC] = LAYOUT(
        KC_FLSH, XXXXXXX, KC_MAKE,
        _______, TG_KYPD, TG_MEDA,
        TG_REVW, TG_NAV,  TG_EDIT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _KEYPAD:
                if (!clockwise) {
                    tap_code(KC_PPLS);
                } else {
                    tap_code(KC_PMNS);
                }
                break;
            case _MEDIA:
                if (!clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
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
        }
    }
    else if (index == 1) {
        switch (biton32(layer_state)) {
            case _KEYPAD:
                if (!clockwise) {
                    tap_code(KC_PEQL);
                } else {
                    tap_code(KC_PDOT);
                }
                break;
            case _MEDIA:
                if (!clockwise) {
                    tap_code(KC_MFFD);
                } else {
                    tap_code(KC_MRWD);
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
        }
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_KYPD:
            if (record->event.pressed) {
                layer_move(_KEYPAD);
            }
            break;
        case TG_MEDA:
            if (record->event.pressed) {
                layer_move(_MEDIA);
            }
            break;
        case TG_NAV:
            if (record->event.pressed) {
                tap_code(KC_G);
                layer_move(_LR_NAV);
            }
            break;
        case TG_REVW:
            if (record->event.pressed) {
                tap_code(KC_E);
                layer_move(_LR_REVIEW);
            }
            break;
        case TG_EDIT:
            if (record->event.pressed) {
                tap_code(KC_D);
                layer_move(_LR_EDIT);
            }
            break;
    }
    return true;
}
