/* Copyright 2025 htx-studio (@https://github.com/htx-studio)
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

#include "wait.h"
#include "eeconfig.h"
#include "pointing_device.h"
#include "one_handed_keyboard.h"

#define TRACKBALL_DPI_MIN 1000
#define TRACKBALL_DPI_MAX 8000
#define TRACKBALL_DPI_DEFAULT 3000
#define TRACKBALL_DPI_STEP 1000

user_config_t user_config;

void pointing_device_init_kb(void) {
    wait_ms(10);
    user_config.TrackballDPI = eeconfig_read_user();
    wait_ms(10);
    adns9800_init();
    wait_ms(10);
    pointing_device_set_cpi(user_config.TrackballDPI);
}

void pointing_adns9800_cpi_up(void) {
    user_config.TrackballDPI += TRACKBALL_DPI_STEP;
    if(user_config.TrackballDPI > TRACKBALL_DPI_MAX) {
        user_config.TrackballDPI = TRACKBALL_DPI_MAX;
    }
    eeconfig_update_user(user_config.TrackballDPI);
    pointing_device_set_cpi(user_config.TrackballDPI);
}

void pointing_adns9800_cpi_down(void) {
    user_config.TrackballDPI -= TRACKBALL_DPI_STEP;
    if(user_config.TrackballDPI < TRACKBALL_DPI_MIN) {
        user_config.TrackballDPI = TRACKBALL_DPI_MIN;
    }
    eeconfig_update_user(user_config.TrackballDPI);
    pointing_device_set_cpi(user_config.TrackballDPI);
}

void pointing_adns9800_reset(void) {
    user_config.TrackballDPI = TRACKBALL_DPI_DEFAULT;
    wait_ms(10);
    eeconfig_update_user(user_config.TrackballDPI);
    pointing_device_set_cpi(user_config.TrackballDPI);
}
