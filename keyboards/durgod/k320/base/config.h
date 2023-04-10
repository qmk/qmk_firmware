/* Copyright 2021 kuenhlee, Don Kjer, Tyler Tidman
 * Copyright 2021 Simon Arlott
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


#define WAIT_US_TIMER           GPTD3

// Dynamic EEPROM
// Something sensible or else VIA may crash
// Users may enable more if they wish
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  4095

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

/* LED indicator pins */
#define LED_WIN_LOCK_PIN    A9
#define LED_MR_LOCK_PIN     A10

/* Original hardware "reset" button on pin D2 */
#define HARDWARE_RESET_PIN  D2
