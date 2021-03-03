/** @file rgb.c
 *  @brief rgb module.
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
 * @author Mario Corona (mariocc@comunidad.unam.mx) 2021
 *
 */

#include "rgb.h"

/* Setting ADJUST layer RGB back to default */
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3)
{
    if(IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2))
    {
        layer_on(layer3);
    }
    else
    {
        layer_off(layer3);
    }
}
