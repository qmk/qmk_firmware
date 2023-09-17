// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE 0 
#define _CAPA1 1
#define _CAPA2 2
#define _CAPA3 3
#define _CAPA4 4
#define _CAPA5 5

layer_state_t layer_state_set_user(layer_state_t state);

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    layer_state_set_user(layer_state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = biton32(state);
    switch (layer) {    
        case _CAPA1:
            rgblight_sethsv_noeeprom(HSV_YELLOW);
            break;

        case _CAPA2:
            rgblight_sethsv_noeeprom(HSV_RED);
            break;

        case _CAPA3:
            rgblight_sethsv_noeeprom(HSV_WHITE);
            break;

        case _CAPA4:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            break;

        case _CAPA5:
            rgblight_sethsv_noeeprom(HSV_CORAL);
            break;

        default:
            rgblight_sethsv_noeeprom(HSV_BLUE); // MI COLOR
            break;
    }
    
    return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x4( /* CAPAS BASE */
        LT(1, KC_7),   KC_8,   KC_9,   KC_SLASH,
        KC_4,   KC_5,   KC_6,   KC_PAST,
        KC_1,   KC_2,   KC_3,   KC_PMNS,
        KC_0,   KC_PDOT, KC_PENT, KC_PPLS
    ),
    [1] = LAYOUT_ortho_4x4( /* CAPAS */
        _______, TG(5),     _______,   _______,
        TG(2),   _______,   _______,   _______,
        TG(3),   _______,   _______,   _______,
        TG(4),   _______,   _______,   _______
    ),
    [2] = LAYOUT_ortho_4x4( /* CAPA2 */
        TG(2),      KC_2,   KC_2,   KC_2,
        KC_2,       KC_2,   KC_2,   KC_2,
        KC_2,       KC_2,   KC_2,   KC_2,
        KC_2,       KC_2,   KC_2,   KC_2
    ),
    [3] = LAYOUT_ortho_4x4( /* CAPA3 */
        TG(3),      KC_3,   KC_3,   KC_3,
        KC_3,       KC_3,   KC_3,   KC_3,
        KC_3,       KC_3,   KC_3,   KC_3,
        KC_3,       KC_3,   KC_3,   KC_3
    ),
    /* MOUSE
     * ,-------------------------------------------------.
     * |           |           | SCROLL UP  |     X      |
     * |-----------+-----------+------------+------------|
     * |  BUTTON 5 |LEFT CLICK |     UP     |RIGHT CLICK |
     * |-----------+-----------+------------+------------|
     * |  BUTTON 4 |   LEFT    |    DOWN    |   RIGHT    |
     * |-----------+-----------+------------+------=-----|
     * |  BUTTON 3 |SCROLL LEFT|SCROLL DOWN |SCROLL RIGHT|
     * `-------------------------------------------------'
     */
    [4] = LAYOUT_ortho_4x4(
        TG(4),   _______, KC_WH_U, _______,
        KC_BTN5, KC_BTN1, KC_MS_U, KC_BTN2,
        KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R,
        KC_BTN3, KC_WH_L, KC_WH_D, KC_WH_R
    ),
     /* NAV
   * ,-----------------------.
   * | INS |PGUP | TAB |PRSCR|
   * |-----+-----+-----+-----|
   * | DEL |PGDN |VOLD |VOLU |
   * |-----+-----+-----+-----|
   * |HOME | UP  | END |     |
   * |-----+-----+-----+-----|
   * |LEFT |DOWN |RIGHT|ENTER|
   * `---------------------- '
   */
  [5] = LAYOUT_ortho_4x4( /* NAV CLUSTER */
    TG(5),  KC_PGUP, KC_TAB,  KC_PSCR,
    KC_DEL,  KC_PGDN, KC_VOLD, KC_VOLU,
    KC_HOME, KC_UP,   KC_END,  _______,
    KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT
  ),

};

