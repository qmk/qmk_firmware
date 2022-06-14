/* Copyright 2021-2022 alin m elena <alinm.elena@gmail.com>
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

#include "config_common.h"

#ifdef ENCODER_ENABLE
#define ENCODERS_PAD_A \
    { A0 }
#define ENCODERS_PAD_B \
    { B8 }
#define ENCODER_RESOLUTIONS \
    { 4 }

#endif

#define SPLIT_LAYER_STATE_ENABLE


#define SPLIT_HAND_PIN B9
#define SERIAL_USART_TX_PIN B6
#define SERIAL_USART_SPEED 921600


/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 5
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0
