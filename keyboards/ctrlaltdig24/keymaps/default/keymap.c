#include QMK_KEYBOARD_H

#define HORIZONTAL_1 0
#define VERTICAL_1 1

enum custom_keycodes {
    M_NEXT_TAB = SAFE_RANGE,
    M_PREV_TAB,
    M_PASTE_WOF,
    M_COPY,
    M_ZD,
    TD_COMM_HZTL_1,
    TD_7_VTCL_1
};

qk_tap_dance_action_t tap_dance_actions[] = {
    //tap for slash - hold for horizontal layer 1
    [TD_COMM_HZTL_1] = ACTION_TAP_DANCE_LAYER_MOVE(KC_COMM, HORIZONTAL_1),

    //tap for npad7, hold for vertical layer 1
    [TD_7_VTCL_1] = ACTION_TAP_DANCE_LAYER_MOVE(KC_P7, VERTICAL_1),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_NEXT_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_TAB) SS_UP(X_LCTL));
                return false;
                break;
            }
        case M_PREV_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_TAP(X_TAB) SS_UP(X_LSFT) SS_UP(X_LCTL));
                return false;
                break;
            }
        case M_PASTE_WOF:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_TAP(X_V) SS_UP(X_LSFT) SS_UP(X_LCTL));
                return false;
                break;
            }
        case M_COPY:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_C) SS_UP(X_LCTL));
                return false;
                break;
            }
        case M_ZD:
            if (record->event.pressed) {
                SEND_STRING("ZD#" SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_TAP(X_V) SS_UP(X_LSFT) SS_UP(X_LCTL));
                return false;
                break;
            }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [HORIZONTAL_1] = LAYOUT_numpad_4x6(
        TD_7_VTCL_1,  KC_P8,     KC_P9,     KC_PMNS,      KC_PSLS,     KC_BSPC,
        KC_P4,        KC_P5,     KC_P6,     KC_PPLS,      KC_PAST,     KC_DEL,
        KC_P1,        KC_P2,     KC_P3,     KC_PENT,      KC_SPACE,    M_ZD,
        KC_PDOT,      KC_P0,     M_COPY,    M_PASTE_WOF,  M_PREV_TAB,  M_NEXT_TAB
    ),

        [VERTICAL_1] = LAYOUT_numpad_4x6(
        M_ZD,         M_NEXT_TAB,     KC_PPLS,    KC_PMNS,    KC_PAST,   KC_PSLS,
        KC_PENT,      M_PREV_TAB,     KC_P9,      KC_P6,      KC_P3,     KC_PDOT,
        KC_DEL,       M_PASTE_WOF,    KC_P8,      KC_P5,      KC_P2,     KC_P0,
        KC_BSPC,      M_COPY,         KC_P7,      KC_P4,      KC_P1,     TD_COMM_HZTL_1
    ),

};
