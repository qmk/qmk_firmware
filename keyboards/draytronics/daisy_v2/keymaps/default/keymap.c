/*Copyright 2024 Blake Drayson / Draytronics

Contact info@draytronics.co.uk

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

This code is inspired by and adapted from the code used in the Printed Pad by Noah Beidelman (@noahbei)

It also references the concept of glitching animations from Aleks (@aleksbrgt)

The pixel graphics used here are from a combination of sources;

1. Layer indicators are created by myself and free to use by anyone.
2. "Revengeday", "Cyber Cafe", "Cortex Implant" logos are used with kind permission of OBEY THE SYSTEM.
   A collective of Fediverse instances and creatives. https://git.cyberwa.re/obey-the-system.
   They are licenced as Non-Commercial and for use by members of the network, with attribution.
3. Key press indicator graphics were commissioned for this project and were designed by the
   amazing https://corteximplant.com/@jadedtwin / https://www.jadedtwin.com/
*/
#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _CODE
};

enum my_keycodes {
  ENCODER_PRESS = QK_USER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * ┌────────────┐
     * │* See Note *│
     * ├────────────┼────────────┬────────────┬─────────────┐
     * │ Code Layer │ Media Next │ Media Prev │ Media Pause │
     * ├────────────┼────────────┼────────────┼─────────────┤
     * │ Prev Desk  │ Miss Ctrl  │ App Window │  Next Desk  │
     * └────────────┴────────────┴────────────┴─────────────┘
     */
    [_BASE] = LAYOUT(
        LT(0, ENCODER_PRESS),
        MO(_CODE), KC_MPRV, KC_MNXT, KC_MPLY,
        C(KC_LEFT), C(KC_UP), C(KC_DOWN), C(KC_RIGHT)
    ),
    /*
     * ┌────────────┐
     * │* See Note *│
     * ├────────────┼────────────┬────────────┬─────────────┐
     * │            │  RGB Mode  │   RBG Hue  │  RGB Toggle │
     * ├────────────┼────────────┼────────────┼─────────────┤
     * │ Scrn Shot  │ Force Quit │   GUI + F  │   DFU Mode  │
     * └────────────┴────────────┴────────────┴─────────────┘
     */
    [_CODE] = LAYOUT(
        LT(0, ENCODER_PRESS),
        _______, RGB_MOD, RGB_HUI, RGB_TOG,
        G(S(KC_5)), G(A(KC_ESC)), G(KC_F), QK_BOOT
    )

    /*
    * See Note *
    * Tapping on the rotary encoder switch will mute or unmute the volume.
    * Pressing and holding will cycle through the OLED modes, they are as follows;
    * 1. Layer indicator
    * 2. Revengeday glitch logo
    * 3. Cyber Cafe glitch logo
    * 4. Cortex Implant glitch logo
    * 5. Key press animation.
    *
    * By default the rotary encoder itself will adjust the volume but it can be adjusted by changing the encoder_update_user function.
    */
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_CODE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LT(0, ENCODER_PRESS):
            if (record->event.pressed) {
                // on tap
                if (record->tap.count) {
                    tap_code(KC_MUTE);
                }
                #ifdef OLED_ENABLE
                // on hold
                else {
                    void oled_display_mode_step(void);
                    oled_display_mode_step();
                    // hidden = false;
                    // current_display_mode = (current_display_mode + 1) % 5;
                    // // When mode changes update EEPROM.
                    // kb_config.oled_mode = current_display_mode;
                    // eeconfig_update_kb(kb_config.raw);
                }
                #endif
            }
            return false;
    }
    return true;
}
