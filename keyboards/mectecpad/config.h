/*
 * config.h
 *
 * Copyright 2025 Iakovos Sachinidhs isachinidhs@gmail.com
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
/* Key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* LED pin definitions */
#define LED_PIN_LAYER1 GP12
#define LED_PIN_LAYER2 GP11
#define LED_PIN_LAYER3 GP10
#define LED_PIN_LAYER4 GP9

/* Pin for the layer change button */
#define LAYER_CHANGE_PIN GP13

/* Debounce time in milliseconds */
#define DEBOUNCE 15
