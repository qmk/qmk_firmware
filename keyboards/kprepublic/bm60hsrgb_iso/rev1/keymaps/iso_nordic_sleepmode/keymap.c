/* Copyright 2020 jakobst1n
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

#ifdef RGB_MATRIX_ENABLE
#ifdef SLEEPMODE_ENABLE
    /* A bunch of vars to keep track of the rgb states
       before sleepmode is turned on */
    static bool sleepmode_on = false;
    static uint8_t sleepmode_before_mode = -1;
    static uint8_t sleepmode_before_brightness = -1;
    static uint8_t sleepmode_before_anim_speed = -1;
    static uint8_t halfmin_counter = 0;
    static uint16_t idle_timer = 0;
#endif
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ,-----------------------------------------------------------.
     * |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | + | ´ |  BACK |
     * |-----------------------------------------------------------|
     * | TAB | Q | W | E | R | T | Y | U | I | O | P | Å | ¨ | RET |
     * |------------------------------------------------------\    |
     * | CAPS | A | S | D | F | G | H | J | K | L | Ø | Æ | @ |    |
     * |-----------------------------------------------------------|
     * | ^  | < | Z | X | C | V | B | N | M | , | . |  ^/- | U | - |
     * |-----------------------------------------------------------|
     * |ctrl| win| alt|                        |alt| fn| L | D | R |
     * `-----------------------------------------------------------' */
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,       KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,          KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  MT(MOD_RSFT, KC_SLSH),   KC_UP,  KC_SLSH,
        KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC,                              KC_RALT, OSL(1),                KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* ,-----------------------------------------------------------.
     * |GRA| f1| f2| f3| f4| f5| f6| f7| f8| f9|f10|f11|f12|  DEL  |
     * |-----------------------------------------------------------|
     * |     | R | R | R | R | R | R | R | R |   |   |   |   |     |
     * |------------------------------------------------------\    |
     * |      |   |   |   |   |   | H |PGD|PGU| E |   |   |   |    |
     * |-----------------------------------------------------------|
     * |    |   |   |   |   |   |   |   |   |   |   |      |V_D|V_U|
     * |-----------------------------------------------------------|
     * |    |    |    |                            |   |PRE|PLA|NEX|
     * `-----------------------------------------------------------' */
    [1] = LAYOUT(
         KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
         _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,
         _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, _______, _______,
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU,
         _______, _______, _______,                      _______,                         _______, _______, KC_MPRV, KC_MPLY, KC_MNXT
    ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#if defined(RGB_MATRIX_ENABLE) && defined(SLEEPMODE_ENABLE)
        if (record->event.pressed) {
            if (sleepmode_before_mode == -1) { sleepmode_before_mode = rgb_matrix_get_mode(); }
            if (sleepmode_before_brightness == -1) { sleepmode_before_brightness = rgb_matrix_get_val(); }
            if (sleepmode_before_anim_speed == -1) { sleepmode_before_anim_speed = rgb_matrix_get_speed(); }

            if (sleepmode_on == true) {
                // rgb_matrix_enable_noeeprom();
                rgb_matrix_mode_noeeprom(sleepmode_before_mode);
                rgb_matrix_set_speed_noeeprom(sleepmode_before_anim_speed);
                rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), sleepmode_before_brightness);
                sleepmode_on = false;
            }
            idle_timer = timer_read();
            halfmin_counter = 0;
        }
#endif
    return true;
 }

 void matrix_scan_user(void) {
#if defined(RGB_MATRIX_ENABLE) && defined(SLEEPMODE_ENABLE)
        /* idle_timer needs to be set one time */
        if (idle_timer == 0) idle_timer = timer_read();

        if ( !sleepmode_on && timer_elapsed(idle_timer) > 30000) {
            halfmin_counter++;
            idle_timer = timer_read();
        }

        if ( !sleepmode_on && halfmin_counter >= SLEEPMODE_TIMEOUT * 2) {// * 2) {
            layer_clear();
            sleepmode_before_anim_speed = rgb_matrix_get_speed();
            sleepmode_before_brightness = rgb_matrix_get_val();
            sleepmode_before_mode = rgb_matrix_get_mode();
            //rgb_matrix_disable_noeeprom();

            rgb_matrix_mode_noeeprom(SLEEPMODE_RGB_MODE);
            rgb_matrix_set_speed_noeeprom(SLEEPMODE_RGB_ANIMATION_SPEED);
            rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), SLEEPMODE_RGB_VAL);
            sleepmode_on = true;
            halfmin_counter = 0;
        }
#endif
}
