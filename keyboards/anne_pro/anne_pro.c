/* Copyright 2019 Michiel Visser
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

#include "anne_pro.h"
#include "anne_pro_lighting.h"
#include "anne_pro_bluetooth.h"
#include "ch.h"
#include "hal.h"

#ifdef NKRO_ENABLE
static bool nkro_enabled_last = false;
#endif
static host_driver_t *host_driver_last;

/* Process the Anne Pro custom keycodes */
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    /* Update the key status for the reactive effects */
    anne_pro_lighting_update_dynamic(record);

    switch (keycode) {
    case APL_RGB:
        /* Toggle the RGB enabled/disabled */
        if (record->event.pressed) {
            anne_pro_lighting_toggle();
        }
        return false;
    case APL_RAT:
        /* Change the animation rate */
        if (record->event.pressed) {
            anne_pro_lighting_rate_next();
        }
        return false;
    case APL_BRT:
        /* Change the brightness */
        if (record->event.pressed) {
            anne_pro_lighting_brightness_next();
        }
        return false;
    case APL_MOD:
        /* Change the lighting mode */
        if (record->event.pressed) {
            anne_pro_lighting_mode_next();
        }
        return false;
    case APB_TOG:
        /* Toggle the output driver between USB and Bluetooth */
        if (record->event.pressed) {
            if (host_get_driver() != &anne_pro_bluetooth_driver) {
                clear_keyboard();
                host_driver_last = host_get_driver();
#ifdef NKRO_ENABLE
                nkro_enabled_last = keymap_config.nkro;
                keymap_config.nkro = false;
#endif
                host_set_driver(&anne_pro_bluetooth_driver);
                anne_pro_bluetooth_on();
                anne_pro_bluetooth_broadcast();
            } else {
                clear_keyboard();
#ifdef NKRO_ENABLE
                keymap_config.nkro = nkro_enabled_last;
#endif
                host_set_driver(host_driver_last);
                anne_pro_bluetooth_off();
            }
        }
        return false;
    default:
        /* Handle other keycodes normally */
        return process_record_user(keycode, record);
    }
}

/* Initialize custom keyboard features */
void keyboard_pre_init_kb(void) {
    /* Initialize the ligthing controller */
    anne_pro_lighting_init();
    /* Initialize the bluetooth controller */
    anne_pro_bluetooth_init();

    keyboard_pre_init_user();
}

/* Turn on the lighting when init is finished */
void keyboard_post_init_kb(void) {
    /* Turn on the lighting */
    anne_pro_lighting_on();
    /* Set the theme to rainbow */
    anne_pro_lighting_mode(APL_MODE_RAINBOW);
    /* Set the effect rate to average and the brightness to average */
    anne_pro_lighting_rate_brightness(128, 5);

    keyboard_post_init_user();
}

/* Start transmissions when the flag is set */
void matrix_scan_kb(void) {
    /* Run some update code for the lighting */
    anne_pro_lighting_update();
    /* Run some update code for the bluetooth */
    anne_pro_bluetooth_update();

    /* Run matrix_scan_user code */
    matrix_scan_user();
}
