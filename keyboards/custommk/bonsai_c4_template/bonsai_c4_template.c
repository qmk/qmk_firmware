/* Copyright 2022 customMK
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

// Set up SPI slave select pin
void keyboard_post_init_kb(void) {
    #ifdef EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN
        setPinOutput(EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN);
        writePinHigh(EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN);
    #endif
}
