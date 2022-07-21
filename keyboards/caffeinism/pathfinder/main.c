/* Copyright 2021 Caffeinism (@caffeinism)
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
#include "keyboard.h"
#include "quantum.h"

void platform_setup(void);
void protocol_setup(void);
void protocol_init(void);
void protocol_task(void);
void protocol_task(void);

int main(void) {
    platform_setup();
    protocol_setup();
    keyboard_setup();

    protocol_init();

    /* Main loop with timeout */
    uint16_t key_timer = timer_read32();
    while (timer_elapsed32(key_timer) < LOOP_TIMEOUT) {
        protocol_task();
        housekeeping_task();
    }

    reset_keyboard();
    return 0;
}
