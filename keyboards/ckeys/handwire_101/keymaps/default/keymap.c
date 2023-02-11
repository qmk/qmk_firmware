/* Copyright 2019 Branden Byers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
    _BASE,          // base layer
    _LAYERS,        // layer of all layers
    _MUSIC,         // music mode
    _MUSIC_4_LIFE,  // music mode until unplugged
    _MOUSE,         // mousekeys
    _TERMINAL,      // terminal
    _ADMIN          // admin duties
};

enum custom_keycodes {
    TERM_ABOUT = SAFE_RANGE,
    TERM_PRINT,
    TERM_FLUSH,
    TERM_HELP,
    CKEYS_ABOUT,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE (numpad)
     * ,-----------------------.
     * |  7  |  8  |  9  |  /  | <-- Hold for LAYERS
     * |-----+-----+-----+-----|
     * |  4  |  5  |  6  |  *  |
     * |-----+-----+-----+-----|
     * |  1  |  2  |  3  |  -  |
     * |-----+-----+-----+-----|
     * |  0  |  .  |  =  |  +  |
     * `-----------------------'
     */
    [_BASE] = LAYOUT_ortho_4x4(
        KC_P7,   KC_P8,   KC_P9,   LT(_LAYERS, KC_PSLS),
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PEQL, KC_PPLS
    ),
    /* LAYERS
     * ,---------------------------.
     * |  MUSIC  |     |     |  X  |
     * |---------+-----+-----+-----|
     * |  MOUSE  |     |     |     |
     * |---------+-----+-----+-----|
     * |TERMINAL |     |     |     |
     * |---------+-----+-----+-----|
     * |  ADMIN  |     |     |     |
     * `---------------------------'
     */
    [_LAYERS] = LAYOUT_ortho_4x4(
          TG(_MUSIC),    _______, _______, _______,
          TG(_MOUSE),    _______, _______, _______,
          TG(_TERMINAL), _______, _______, _______,
          TG(_ADMIN),    _______, _______, _______
    ),
    /* MUSIC
     * ,-----------------------.
     * |  X  |     |     |  X  |
     * |-----+-----+-----+-----|
     * |     |     |     |4EVER|
     * |-----+-----+-----+-----|
     * | OFF |     |     |     |
     * |-----+-----+-----+-----|
     * |  ON |     |     |MODES|
     * `-----------------------'
     */
    // TODO: Make this music layer the one to jump to other music layers (different octaves)
    [_MUSIC] = LAYOUT_ortho_4x4(
        _______,  _______, _______, _______,
        _______,  _______, _______, TG(_MUSIC_4_LIFE),
        MU_OFF,   _______, _______, _______,
        MU_ON,    _______, _______, MU_NEXT
    ),
    /* MUSIC_4_LIFE
     * ,-----------------------.
     * |  ♫  |  ♫  |  ♫  |  ♫  |
     * |-----+-----+-----+-----|
     * |  ♫  |  ♫  |  ♫  |  ♫  |
     * |-----+-----+-----+-----|
     * |  ♫  |  ♫  |  ♫  |  ♫  |
     * |-----+-----+-----+-----|
     * |  ♫  |  ♫  |  ♫  |  ♫  |
     * `-----------------------'
     */
    [_MUSIC_4_LIFE] = LAYOUT_ortho_4x4(
        KC_M,    KC_M,    KC_M,    KC_M,
        KC_M,    KC_M,    KC_M,    KC_M,
        KC_M,    KC_M,    KC_M,    KC_M,
        KC_M,    KC_M,    KC_M,    KC_M
    ),
    /* MOUSE
     * ,-------------------------------------------------.
     * |  BUTTON 5 |           | SCROLL UP  |     X      |
     * |-----------+-----------+------------+------------|
     * |     X     |LEFT CLICK |     UP     |RIGHT CLICK |
     * |-----------+-----------+------------+------------|
     * |  BUTTON 4 |   LEFT    |    DOWN    |   RIGHT    |
     * |-----------+-----------+------------+------=-----|
     * |  BUTTON 3 |SCROLL LEFT|SCROLL DOWN |SCROLL RIGHT|
     * `-------------------------------------------------'
     */
    [_MOUSE] = LAYOUT_ortho_4x4(
        KC_BTN5, _______, KC_WH_U, _______,
        _______, KC_BTN1, KC_MS_U, KC_BTN2,
        KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R,
        KC_BTN3, KC_WH_L, KC_WH_D, KC_WH_R
    ),
    /* TERMINAL
     * ,---------------------------------------.
     * |            |ABOUT|          |    X    |
     * |------------+-----+----------+---------|
     * |TERMINAL OFF|PRINT|          |         |
     * |------------+-----+----------+---------|
     * |     X      |FLUSH|          |         |
     * |------------+-----+----------+---------|
     * |TERMINAL ON |HELP |          |         |
     * `--------=======------------------------'
     */
    [_TERMINAL] = LAYOUT_ortho_4x4(
        _______, TERM_ABOUT, _______, _______,
        _______, TERM_PRINT, _______, _______,
        _______, TERM_FLUSH, _______, _______,
        _______, TERM_HELP , _______, _______
    ),
    /* ADMIN
     * ,-----------------------------------------.
     * |   QK_BOOT    |     |           |    X     |
     * |------------+-----+-----------+----------|
     * |ABOUT CKEYS |     |           |          |
     * |------------+-----+-----------+----------|
     * |            |     |CLICKY UP  |CLICKY OFF|
     * |------------+-----+-----------+----------|
     * |     X      |     |CLICKY DOWN|CLICKY ON |
     * `-----------------------------------------'
     */
    [_ADMIN] = LAYOUT_ortho_4x4(
        QK_BOOT,       _______, _______, _______,
        CKEYS_ABOUT, _______, _______, _______,
        _______,     _______, _______, CK_OFF,
        _______,     _______, _______, CK_ON
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TERM_ABOUT:
            if (record->event.pressed) {
                // when keycode TERM_ABOUT is pressed
                SEND_STRING("about\n");
            }
            break;
        case TERM_PRINT:
            if (record->event.pressed) {
                SEND_STRING("print\n");
            }
            break;
        case TERM_FLUSH:
            if (record->event.pressed) {
                SEND_STRING("flush\n");
            }
            break;
        case TERM_HELP:
            if (record->event.pressed) {
                SEND_STRING("help\n");
            }
            break;
        case CKEYS_ABOUT:
            if (record->event.pressed) {
                SEND_STRING("https://cKeys.org\nMaking people smile one keyboard at a time.\ncKeys is a volunteer-run 501(c)(3) nonprofit organization.\n");
            }
            break;
    }
    return true;
};
