/*
 *
 * This is the c header for rgb module
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
 *
 * MCrown: mariocc@comunidad.unam.mx 2021
 *
 */

#ifndef MCROWN_RGB_H_LIB
#define MCROWN_RGB_H_LIB

#include "mcrown.h"
extern int RGB_current_mode;

/* Setting ADJUST layer RGB back to default */
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3);


#endif /* End oF MCROWN_RGB_H_LIB */
