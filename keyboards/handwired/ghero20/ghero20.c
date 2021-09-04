/* Copyright 2021 bryan065
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

#include "ghero20.h"

static uint16_t dynamic_loop_timer;
static uint16_t star_timer;

bool mpu_connected  = false;
bool star_power     = false;

const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {1, 1, 1};

void keyboard_pre_init_kb(void) {
    // Call the keyboard pre init code.
}

void keyboard_post_init_kb(void) {
    // Init i2c
    i2c_init();
    if (i2c_start(MPU9250_ADDR,I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {                 // Start i2c communications, if return status_success, flag connected is true (default false)
        i2c_stop();
    } else {
        mpu_connected = true;
        initMPU9250();
    }

    // Init GHero button colors
    init_GH_color();
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
}
void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    // Limit update rate of mpu polling and only poll if connected, User has to reset keyboard to reconnect to mpu
    if ((timer_elapsed(dynamic_loop_timer) > MPU_POLLRATE) && (mpu_connected == true)) {
        dynamic_loop_timer = timer_read();

        // Poll for status, run code or flag disconnected
        if (i2c_start(MPU9250_ADDR,I2C_TIMEOUT) == I2C_STATUS_SUCCESS) {
            update_accel_gyro();
            update_star_power(&star_power);

            //uprintf("Star Power (angle, speed):\n");
            //uprintf("%d, ",getAccScaled(x,100));
            //uprintf("%d\n\n",getGyroScaled(z,10));

        } else {
            i2c_stop();
            mpu_connected = false;
        }
    }

    // Timer for party RGB duration, reset to default button colors afterwards
    if ((timer_elapsed(star_timer) > 5000) && (star_power)) {
        star_power = false;
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        init_GH_color();
    }

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
        case KC_1:
            if (record->event.pressed) {
                set_GH_green(true);
            }
            else {
                set_GH_green(false);
            }
            return true;
        case KC_2:
            if (record->event.pressed) {
                set_GH_red(true);
            }
            else {
                set_GH_red(false);
            }
            return true;
        case KC_3:
            if (record->event.pressed) {
                set_GH_yellow(true);
            }
            else {
                set_GH_yellow(false);
            }
            return true;
        case KC_4:
            if (record->event.pressed) {
                set_GH_blue(true);
            }
            else {
                set_GH_blue(false);
            }
            return true;
        case KC_5:
            if (record->event.pressed) {
                set_GH_orange(true);
            }
            else {
                set_GH_orange(false);
            }
            return true;
        case RGB_TOG:
            if (record->event.pressed) {
                if (rgblight_is_enabled()) {
                    return true;
                }
                else {
                    rgblight_enable();
                    init_GH_color();
                    return false;
                }
            }
        default:
            return true;
    }
}

// Initialize and reset to GH button colors
void init_GH_color(void) {
    rgblight_setrgb_at(255, 255, 255, 0);   // Strum RGB
    rgblight_setrgb_at(255, 255, 255, 1);   // Strum RGB

    set_GH_green(false);
    set_GH_red(false);
    set_GH_yellow(false);
    set_GH_blue(false);
    set_GH_orange(false);
}

/*  Functions to light up the pressed button
*   True = bright
*   false = dim
*/
void set_GH_green(bool set) {
    if (set != true) {
        int color = 255*.5;
        rgblight_setrgb_at(0, color, 0, 6);
    }
    else {
        rgblight_setrgb_at(0, 255, 0, 6);
    }
}

void set_GH_red(bool set) {
    if (set != true) {
        int color = 255*.5;
        rgblight_setrgb_at(color, 0, 0, 5);
    }
    else {
        rgblight_setrgb_at(255, 0, 0, 5);
    }
}

void set_GH_yellow(bool set) {
    if (set != true) {
        int color = 255*.5;
        rgblight_setrgb_at(color, color, 0, 4);
    }
    else {
        rgblight_setrgb_at(255, 255, 0, 4);
    }
}

void set_GH_blue(bool set) {
    if (set != true) {
        int color = 255*.5;
        rgblight_setrgb_at(0, 0, color, 3);
    }
    else {
        rgblight_setrgb_at(0, 0, 255, 3);
    }
}

void set_GH_orange(bool set) {
    if (set != true) {
        int color = 255*.5;
        int color2 = 80*.5;
        rgblight_setrgb_at(color, color2, 0, 2);
    }
    else {
        rgblight_setrgb_at(255, 80, 0, 2);
    }
}

/*  Call in matrix loop to update and track MPU data for star power
*   Star power keycode is set here
*/
void update_star_power(bool* star) {
    int16_t a, g;

    a = getAccScaled(x,100);
    g = getGyroScaled(z,10);

    #ifndef STAR_LEFT_HAND
        if (a >= MPU_ANGLE_SENS && g <= -MPU_SPEED_SENS) {
            tap_code(KC_M);  //STAR POWER KEYCODE

            *star = true;
            rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);     // Party RGB's when start power activated
            star_timer = timer_read();                      // Start timer for party RGB
        }
    #else
        if (a >= MPU_ANGLE_SENS && g >= MPU_SPEED_SENS) {
            tap_code(KC_M);  //STAR POWER KEYCODE

            *star = true;
            rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);     // Party RGB's when start power activated
            star_timer = timer_read();                      // Start timer for party RGB
        }
    #endif


}
