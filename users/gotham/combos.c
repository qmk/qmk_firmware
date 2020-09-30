#include "combos.h"

const uint16_t PROGMEM grv_combo[]  = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM esc_combo[]  = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM tab_combo[]  = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM gui_combo[]  = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM undo_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM redo_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM bsls_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM quot_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM eql_combo[]  = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM mins_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM unds_combo[] = {KC_COMM, KC_DOT, COMBO_END};

/*
,-----------------------------.      ,-----------------------------.
|   Grv  |  Esc   |     |     |      |     |     |   Eql  |  Bsls  |
|-----+-----+-----+-----+-----|      |-----------------------------|
|     |  Tab   |   GUI  |     |      |     |  Quot  |  Mins  |     |
|-----+-----+-----+-----+-----+      |-----------------------------|
|     |  Undo  |  Redo  |     |      |     |     |   Unds    |     |
`-----+-----+-----+-----+-----'      `-----------------------------'
              .-----------------.  .-----------------.
              |     |     |     |  |     |     |     |
              '-----------------'  '-----------------'
*/

combo_t key_combos[COMBO_COUNT] = {
    // clang-format off
    [CMB_GRV]   = COMBO(grv_combo, KC_GRV),
    [CMB_ESC]   = COMBO(esc_combo, KC_ESC),
    [CMB_TAB]   = COMBO(tab_combo, KC_TAB),
    [CMB_GUI]   = COMBO(gui_combo, KC_LGUI),
    [CMB_UNDO]  = COMBO_ACTION(undo_combo),
    [CMB_REDO]  = COMBO_ACTION(redo_combo),
    [CMB_BSLS]  = COMBO(bsls_combo, KC_BSLS),
    [CMB_QUOT]  = COMBO(quot_combo, KC_QUOT),
    [CMB_EQL]   = COMBO(eql_combo, KC_EQL),
    [CMB_MINS]  = COMBO(mins_combo, KC_MINS),
    [CMB_UNDS]  = COMBO(unds_combo, KC_UNDS),
    // clang-format on
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case CMB_UNDO:
            if (pressed) {
                tap_code16(LCTL(KC_Z));
            }
            break;
        case CMB_REDO:
            if (pressed) {
                tap_code16(LCTL(KC_Y));
            }
            break;
    }
}

/* Template
,-----------------------------.      ,-----------------------------.
|     |     |     |     |     |      |     |     |     |     |     |
|-----+-----+-----+-----+-----|      |-----------------------------|
|     |     |     |     |     |      |     |     |     |     |     |
|-----+-----+-----+-----+-----+      |-----------------------------|
|     |     |     |     |     |      |     |     |     |     |     |
`-----+-----+-----+-----+-----'      `-----------------------------'
              .-----------------.  .-----------------.
              |     |     |     |  |     |     |     |
              '-----------------'  '-----------------'
*/
