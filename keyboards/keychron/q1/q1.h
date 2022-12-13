/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

#include "quantum.h"

#if   defined(KEYBOARD_keychron_q1_ansi_atmega32u4)
#    include "ansi_atmega32u4.h"
#elif defined(KEYBOARD_keychron_q1_ansi_atmega32u4_encoder)
#    include "ansi_atmega32u4_encoder.h"
#elif defined(KEYBOARD_keychron_q1_iso_atmega32u4)
#    include "iso_atmega32u4.h"
#elif defined(KEYBOARD_keychron_q1_iso_atmega32u4_encoder)
#    include "iso_atmega32u4_encoder.h"
#elif defined(KEYBOARD_keychron_q1_ansi_stm32l432)
#    include "ansi_stm32l432.h"
#elif defined(KEYBOARD_keychron_q1_ansi_stm32l432_encoder)
#    include "ansi_stm32l432_encoder.h"
#elif defined(KEYBOARD_keychron_q1_iso_stm32l432)
#    include "iso_stm32l432.h"
#elif defined(KEYBOARD_keychron_q1_iso_stm32l432_encoder)
#    include "iso_stm32l432_encoder.h"
#elif defined(KEYBOARD_keychron_q1_jis_stm32l432)
#    include "jis_stm32l432.h"
#elif defined(KEYBOARD_keychron_q1_jis_stm32l432_encoder)
#    include "jis_stm32l432_encoder.h"
#endif
