/* Copyright 2021 @Itswaffle/@waffle#6666
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

#define CH_CFG_ST_RESOLUTION 16
#define CH_CFG_ST_FREQUENCY 10000

#if __has_include("platforms/chibios/common/configs/chconf.h")
#    include_next "platforms/chibios/common/configs/chconf.h"
#else
#    include_next "chconf.h"
#endif
