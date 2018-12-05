/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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
#include "qwiic.h"

void qwiic_init(void) {
  #ifdef QWIIC_JOYSTIIC_ENABLE
    joystiic_init();
  #endif
  #ifdef QWIIC_MICRO_OLED_ENABLE
    micro_oled_init();
  #endif
}

void qwiic_task(void) {
  #ifdef QWIIC_JOYSTIIC_ENABLE
    joystiic_task();
  #endif
}
