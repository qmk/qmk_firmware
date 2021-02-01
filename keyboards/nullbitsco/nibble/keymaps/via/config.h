/* Copyright 2020 Jay Greco
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
// Custom config starts after VIA's EEPROM usage,
// dynamic keymaps start after this.
// Custom config Usage:
// 1 for enabled encoder modes (1 byte)
// 6 for 3x custom encoder settings, left, right, and press (18 bytes)
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 19