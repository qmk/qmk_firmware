/* Copyright 2018-2020 Nick Brassel (@tzarc)
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

/* Address for jumping to bootloader on STM32 chips. */
/* It is chip dependent, the correct number can be looked up here (page 175):
 * http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
 * This also requires a patch to chibios:
 *  <tmk_dir>/tmk_core/tool/chibios/ch-bootloader-jump.patch
 */
#define STM32_BOOTLOADER_ADDRESS 0x1FFF0000
