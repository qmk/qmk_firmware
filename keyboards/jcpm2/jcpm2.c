/* Copyright 2022 DOIO
 * Copyright 2022 DOIO2022 <https://github.com/DOIO2022>
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
 #include "quantum.h"
 
#ifdef OLED_ENABLE
uint16_t logo_timer = 0;

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    logo_timer = timer_read();
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
    0xFF, 0xFF, 0xFF, 0xFF
    };
    oled_write_P(qmk_logo, false);
}

bool oled_task_kb(void) {
    if (timer_elapsed(logo_timer) < 2000) {
        render_logo();
        return false;
    }
    if (!oled_task_user()) {
        return false;
    }
    // rest of your code
    return true;
}

#endif