/* Copyright 2022~2024 @ lokher (https://www.keychron.com)
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

#pragma once

#define FACTORY_RESET_CHECK process_record_factory_test
#define FACTORY_RESET_TASK factory_test_task

void factory_test_init(void);

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
bool factory_test_indicator(void);
#endif

bool factory_reset_indicating(void);
void factory_test_task(void);
void factory_test_rx(uint8_t *data, uint8_t length);

bool process_record_factory_test(uint16_t keycode, keyrecord_t *record);

