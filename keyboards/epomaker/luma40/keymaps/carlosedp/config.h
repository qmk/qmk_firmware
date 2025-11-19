/* Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
 * Copyright 2021 QMK <https://github.com/qmk/qmk_firmware>
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

// Custom configuration
// LUMA40 mode indicator LED indices - using keys that should be visible
#define LED_BLE_1_INDEX (13) // 'A' key position
#define LED_BLE_2_INDEX (14) // 'S' key position
#define LED_BLE_3_INDEX (15) // 'D' key position
#define LED_2P4G_INDEX (16)  // 'F' key position
#define LED_USB_INDEX (17)   // 'G' key position
#undef DEBOUNCE
#define DEBOUNCE 10

#define TAPPING_TERM 140

// Set TYPING HEATMAP as default RGB matrix effect
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP
