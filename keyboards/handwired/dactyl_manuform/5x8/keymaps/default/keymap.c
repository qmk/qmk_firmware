/* Copyright 2024 Philip Slinkin (s.philya@gmail.com)
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

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("Right -> Left\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("< >\n"), false);
                break;
            case 3:
                oled_write_P(PSTR("leftNumPad\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undef\n"), false);
        }

        uint16_t modifiers = get_mods();
        oled_write_P(PSTR("Mods: "), false);
        if (modifiers & MOD_MASK_SHIFT) oled_write_P(PSTR("SHF "), false);
        if (modifiers & MOD_MASK_CTRL) oled_write_P(PSTR("CTL "), false);
        if (modifiers & MOD_MASK_ALT) oled_write_P(PSTR("ALT "), false);
        if (modifiers & MOD_MASK_GUI) oled_write_P(PSTR("GUI "), false);
        if (host_keyboard_led_state().caps_lock) oled_write_P(PSTR("CAPS "), false);
        oled_write_P(PSTR("\n"), false);
    } else {
        oled_write_P(PSTR("Dactyl\nManuform"), false);
    }
    return false;
}
#endif

enum layers {
    _QWERTY,
    _RIGHT2LEFT,
    _LEFTIRIGHT, 
    _LEFTNUMPAD
};

    /* Base (qwerty)
     *                      ,----------------------------------,          ,----------------------------------,
     * ,--------------------|   2  |   3  |   4  |   5  |   6  |          |   7  |   8  |   9  |   0  |   -  |--------------------,
     * |  Esc |   `  |   1  |------+------+------+------+------|          |------+------+------+------+------|   =  |   \  |  BS  |
     * |------+------+------|   w  |   e  |   r  |   t  |QKBOOT|          |  F8  |   y  |   u  |   i  |   o  |------+------+------|
     * |M_RSTP|  Tab |   q  |------+------+------+------+------|          |------+------+------+------+------|   p  |   [  |   ]  |
     * |------+------+------|   s  |   d  |   f  |   g  | TO(3)|          |  F9  |   h  |   j  |   k  |   l  |------+------+------|
     * |M_REC1| Caps |   a  |------+------+------+------+------'          '------+------+------+------+------|   ;  |   "  |ENTER |
     * |------+------+------|   x  |   c  |   v  |   b  |                        |   n  |   m  |   ,  |   .  |------+------+------|
     * |M_REC2| Shift|   z  |------+------+------+------'                        '------+------+------+------|   /  |Shift | Ctrl |
     * '------+------+------|  Alt | INS  |                                                    | Down |  Up  |------+------+------'
     *        | Ctrl | Wint |------+------+-------------,                        ,-------------+------+------| TT(2)| Right|
     *        '------+------'             | TT(1)|SPACE |                        | SPACE|  BS  |             '------+------'
     *                                    '------+------+------,          ,------+------+------'
     *                                           | ESC  |ENTER |          | HOME | END  |
     *                                           '------+------'          '------+------'
     *                                           |  DEL |  F2  |          | PGUP | PGDN |
     *                                           '------+------'          '------+------'
     */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x8(
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,    KC_6,        KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC,
        DM_RSTP, KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,    QK_BOOT,     KC_F8,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        DM_REC1, KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,    TO(3),       KC_F9,   KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        DM_REC2, KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,                          KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RCTL,
                 KC_LCTL, KC_LGUI, KC_LALT, KC_INS,                                                         KC_DOWN, KC_UP,   TT(2),   KC_RCTL,
                                                    TT(1),  KC_SPC,                        KC_SPC, KC_BSPC,
                                                            KC_ESC, KC_ENT,       KC_HOME, KC_END,
                                                            KC_DEL, KC_F2,        KC_PGUP, KC_PGDN),
                                                            
    /* Base (right to left on hold button)
     *                      ,----------------------------------,          ,----------------------------------,
     * ,--------------------|   -  |   0  |   9  |   8  |   7  |          |  F7  |  F8  |  F9  |  F10 |  F11 |--------------------,
     * |  BS  |   \  |   =  |------+------+------+------+------|          |------+------+------+------+------|  F12 |      |      |
     * |------+------+------|   o  |   i  |   u  |   y  |QKBOOT|          |      |      |      |      |      |------+------+------|
     * |   [  |   ]  |   p  |------+------+------+------+------|          |------+------+------+------+------|      |      |      |
     * |------+------+------|   l  |   k  |   j  |   h  |PRSCRN|          |      |      | Left | Down |  Up  |------+------+------|
     * |M_PLY1|   "  |   ;  |------+------+------+------+------'          '------+------+------+------+------| Right|      |ENTER |
     * |------+------+------|   .  |   ,  |   m  |   n  |                        |  F1  |  F2  |  F3  |  F4  |------+------+------|
     * |M_PLY2|MShift|   /  |------+------+------+------'                        '------+------+------+------|  F5  |  F6  |      |
     * '------+------+------|  DEL |  BS  |                                                    |      |      |------+------+------'
     *        |MCtrl | MAlt |------+------+-------------,                        ,-------------+------+------|      |      |
     *        '------+------'             |      |SPACE |                        | SPACE|  BS  |             '------+------'
     *                                    '------+------+------'          ,------+------+------'
     *                                           | END  |ENTER |          | HOME | END  |
     *                                           '------+------'          '------+------'
     *                                           | PGDN | PGUP |          | PGUP | PGDN |
     *                                           '------+------'          '------+------'
     */
    [_RIGHT2LEFT] = LAYOUT_5x8(
        KC_BSPC, KC_BSLS, KC_EQL,  KC_MINS, KC_0,   KC_9,  KC_8,    KC_7,         KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,
        KC_RBRC, KC_LBRC, KC_P,    KC_O,    KC_I,   KC_U,  KC_Y,    QK_BOOT,      KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        DM_PLY1, KC_QUOT, KC_SCLN, KC_L,    KC_K,   KC_J,  KC_H,    KC_PSCR,      KC_NO,   KC_LEFT, KC_DOWN,KC_UP,   KC_RIGHT,KC_SCLN, KC_NO,   KC_ENT,
        DM_PLY2, OSM(MOD_LSFT), KC_SLSH, KC_DOT, KC_COMM, KC_M, KC_N,                      KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO,
                 OSM(MOD_LCTL), OSM(MOD_LALT), KC_DEL, KC_BSPC,                                             KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                                    KC_NO,   KC_SPC,                       KC_SPC, KC_BSPC,
                                                             KC_ESC, KC_ENT,      KC_HOME, KC_END,
                                                             KC_DEL, KC_F2,       KC_PGUP, KC_PGDN),

/* LeftIRight (left and right on up and down button)
     *                      ,----------------------------------,          ,----------------------------------,
     * ,--------------------|   2  |   3  |   4  |   5  |   6  |          |   7  |   8  |   9  |   0  |   -  |--------------------,
     * |  Esc |   `  |   1  |------+------+------+------+------|          |------+------+------+------+------|   =  |   \  |  BS  |
     * |------+------+------|   w  |   e  |   r  |   t  |QKBOOT|          |  F8  |   y  |   u  |   i  |   o  |------+------+------|
     * |M_RSTP|  Tab |   q  |------+------+------+------+------|          |------+------+------+------+------|   p  |   [  |   ]  |
     * |------+------+------|   s  |   d  |   f  |   g  | TO(3)|          |  F9  |   h  |   j  |   k  |   l  |------+------+------|
     * |M_REC1| Caps |   a  |------+------+------+------+------'          '------+------+------+------+------|   ;  |   "  |ENTER |
     * |------+------+------|   x  |   c  |   v  |   b  |                        |   n  |   m  |   ,  |   .  |------+------+------|
     * |M_REC2| Shift|   z  |------+------+------+------'                        '------+------+------+------|   /  |Shift | Ctrl |
     * '------+------+------|  Alt | INS  |                                                    | Left | Right|------+------+------'
     *        | Ctrl | Wint |------+------+-------------,                        ,-------------+------+------|      | Right|
     *        '------+------'             | TT(1)|SPACE |                        | SPACE|  BS  |             '------+------'
     *                                    '------+------+------,          ,------+------+------'
     *                                           | ESC  |ENTER |          | HOME | END  |
     *                                           '------+------'          '------+------'
     *                                           |  DEL |  F2  |          | PGUP | PGDN |
     *                                           '------+------'          '------+------'
     */
    [_LEFTIRIGHT] = LAYOUT_5x8(
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,    KC_6,        KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC,
        DM_RSTP, KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,    QK_BOOT,     KC_F8,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        DM_REC1, KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,    TO(3),       KC_F9,   KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        DM_REC2, KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,                          KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RCTL,
                 KC_LCTL, KC_LGUI, KC_LALT, KC_INS,                                                         KC_LEFT, KC_RGHT, KC_NO,   KC_RCTL,
                                                    KC_NO,  KC_SPC,                        KC_SPC, KC_BSPC,
                                                            KC_ESC, KC_ENT,       KC_HOME, KC_END,
                                                            KC_DEL, KC_F2,        KC_PGUP, KC_PGDN),

    /* leftNumPad
     *                      ,----------------------------------,          ,----------------------------------,
     * ,--------------------|  NUM |   /  |   *  |   -  |  BS  |          |  F7  |  F8  |  F9  |  F10 |  F11 |--------------------,
     * |  Esc |   `  |   "  |------+------+------+------+------|          |------+------+------+------+------|  F12 |      |      |
     * |------+------+------|   7  |   8  |   9  |   +  |QKBOOT|          |      |      |      |      |      |------+------+------|
     * |M_RSTP|  Tab |   [  |------+------+------+------+------|          |------+------+------+------+------|      |      |      |
     * |------+------+------|   4  |   5  |   6  |   =  |      |          |      |      | Left | Down |  Up  |------+------+------|
     * |M_REC1| Caps |   .  |------+------+------+------+------'          '------+------+------+------+------| Right|      |ENTER |
     * |------+------+------|   1  |   2  |   3  |   ., |                        |  F1  |  F2  |  F3  |  F4  |------+------+------|
     * |M_REC2| Shift|   ]  |------+------+------+------'                        '------+------+------+------|  F5  |  F6  |      |
     * '------+------+------|   ,  |   0  |                                                    |      |      |------+------+------'
     *        | Ctrl |  Alt |------+------+-------------,                        ,-------------+------+------|      |      |
     *        '------+------'             | TT(1)|SPACE |                        | SPACE|  BS  |             '------+------'
     *                                    '------+------+------,          ,------+------+------'
     *                                           | ESC  |ENTER |          | HOME | END  |
     *                                           '------+------'          '------+------'
     *                                           |  DEL |  F2  |          | PGUP | PGDN |
     *                                           '------+------'          '------+------'
     */
    [_LEFTNUMPAD] = LAYOUT_5x8(
        KC_ESC,  KC_GRV,  KC_QUOT, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, KC_BSPC,     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,
        DM_RSTP, KC_TAB,  KC_LBRC, KC_7,    KC_8,    KC_9,    KC_PPLS, QK_BOOT,     KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        DM_REC1, KC_CAPS, KC_DOT,  KC_4,    KC_5,    KC_6,    KC_PEQL, TO(0),       KC_NO,   KC_LEFT, KC_DOWN,KC_UP,   KC_RIGHT,KC_NO,   KC_NO,   KC_ENT,
        DM_REC2, KC_LSFT, KC_RBRC, KC_1,    KC_2,    KC_3,    KC_SLSH,                       KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO,
                 KC_LCTL, KC_LALT, KC_COMM, KC_0,                                                              KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                                    TT(1),   KC_SPC,                        KC_SPC, KC_BSPC,
                                                             KC_ESC, KC_ENT,       KC_HOME, KC_END,
                                                             KC_DEL, KC_F2,        KC_PGUP, KC_PGDN),
};
