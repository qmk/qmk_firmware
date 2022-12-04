/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bbaserdem.h"

<<<<<<<< HEAD:keyboards/bastardkb/skeletyl/v2/splinky_3/config.h
/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { GP26, GP5, GP4, GP9 }
#define MATRIX_COL_PINS \
    { GP28, GP21, GP6, GP7, GP8 }

/* Handedness. */
#define MASTER_RIGHT

// To use the handedness pin, resistors need to be installed on the adapter PCB.
// If so, uncomment the following code, and undefine MASTER_RIGHT above.
// #define SPLIT_HAND_PIN GP15
// #define SPLIT_HAND_PIN_LOW_IS_LEFT  // High -> right, Low -> left.

/* RGB settings. */
#define RGB_DI_PIN GP0

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
========
// Hook to encoder stuff
bool encoder_update_user(uint8_t index, bool clockwise);
// Complicated code for what the encoder keys do when pressed
bool process_record_encoder(uint16_t keycode, keyrecord_t *record);
// Clear the encoder settings
void reset_encoder_state(void);
// This is so that encoder state is synched between two halves
void housekeeping_task_encoder(void);
// This is purely for oled; should it want to use it
void encoder_state_string(uint8_t index, uint8_t layer, char* buffer);
>>>>>>>> f271c985ce (Revert "Merge branch 'hex6c-rev2' of https://github.com/mechlovin/qmk_firmware into hex6c-rev2"):users/bbaserdem/bb-encoder.h
