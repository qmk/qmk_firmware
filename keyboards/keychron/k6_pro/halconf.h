/* Copyright 2020 QMK
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

#define HAL_USE_I2C TRUE

<<<<<<< HEAD:keyboards/keychron/k6_pro/halconf.h
#ifdef BLUETOOTH_ENABLE
#    define PAL_USE_CALLBACKS TRUE
#    define HAL_USE_SERIAL TRUE
#endif

=======
>>>>>>> master:keyboards/acheron/apollo/87h/gamma/halconf.h
#include_next <halconf.h>
