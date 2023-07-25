<<<<<<<< HEAD:keyboards/xiudi/xd75/keymaps/dothtm75/config.h
/* Copyright 2017 Mike Cramer
========
/* Copyright 2020 QMK
>>>>>>>> e0ecc772495b92032d36d918cfdb3c631bbdd078:keyboards/mechlovin/infinity88/rev3/mcuconf.h
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

<<<<<<<< HEAD:keyboards/xiudi/xd75/keymaps/dothtm75/config.h
#define HOLD_ON_OTHER_KEY_PRESS

#define MIDI_ADVANCED
========
#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE

#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 TRUE



>>>>>>>> e0ecc772495b92032d36d918cfdb3c631bbdd078:keyboards/mechlovin/infinity88/rev3/mcuconf.h
