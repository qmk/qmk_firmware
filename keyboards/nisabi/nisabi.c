/* Copyright 2024 RaijuInc (@RaijuInc)
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

#include "nisabi.h"

#include "print.h"

void matrix_scan_user(void) {
    #ifdef CONSOLE_ENABLE
    static uint32_t last_print = 0;
    uint32_t current_time = timer_read32();

    if (current_time - last_print > 1000) {  // 1秒ごとに状態を出力
        last_print = current_time;

    // 現在のマスター/スレーブの状態を出力
        if (is_keyboard_master()) {
            uprintf("Master side active\n");
        } else {
            uprintf("Slave side active\n");
        }
    }
    #endif
}

