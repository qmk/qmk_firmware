/* Copyright 2017 Fred Sundvik
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

#ifndef TESTS_TEST_COMMON_TEST_MATRIX_H_
#define TESTS_TEST_COMMON_TEST_MATRIX_H_

#ifdef __cplusplus
extern "C" {
#endif

void press_key(uint8_t col, uint8_t row);
void release_key(uint8_t col, uint8_t row);
void clear_all_keys(void);

#ifdef __cplusplus
}
#endif

#endif /* TESTS_TEST_COMMON_TEST_MATRIX_H_ */
