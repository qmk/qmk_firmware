/* Copyright 2021 Paul Cotter (@gr1mr3aver)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ST77XX configurables
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// The buffer size to use when rendering chunks of data, allows limiting of RAM allocation when rendering images
#ifndef ST77XX_PIXDATA_BUFSIZE
#    define ST77XX_PIXDATA_BUFSIZE 512
#endif

// Check for minimum buffer size
#if ST77XX_PIXDATA_BUFSIZE < 16
#    error ST77XX pixel buffer size too small -- ST77XX_PIXDATA_BUFSIZE must be >= 16
#endif
