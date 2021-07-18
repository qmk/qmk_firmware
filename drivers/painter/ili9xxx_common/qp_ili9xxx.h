/* Copyright 2020 Nick Brassel (@tzarc)
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

#include <qp.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter ILI9xxx configurables
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// The buffer size to use when rendering chunks of data, allows limiting of RAM allocation when rendering images
#ifndef ILI9XXX_PIXDATA_BUFSIZE
#    define ILI9XXX_PIXDATA_BUFSIZE 32
#endif

#if ILI9XXX_PIXDATA_BUFSIZE < 16
#    error ILI9XXX pixel buffer size too small -- ILI9XXX_PIXDATA_BUFSIZE must be >= 16
#endif
