/* Copyright 2019 sekigon-gonnoc
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


#define BMP_FORCE_SAFE_MODE true

#define USER_DEFINED_MSCMD { "lpme", usrcmd_lpme_test, "Test LPME-IO"}

#ifndef __ASSEMBLER__
#include "mscmd.h"
MSCMD_USER_RESULT usrcmd_lpme_test(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);
#endif


// place overrides here
