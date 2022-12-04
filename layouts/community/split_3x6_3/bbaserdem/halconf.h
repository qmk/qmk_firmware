<<<<<<<< HEAD:keyboards/hfdkb/ac001/ac001.h
/* Copyright (C) 2022 jonylee@hfd
========
/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
>>>>>>>> f271c985ce (Revert "Merge branch 'hex6c-rev2' of https://github.com/mechlovin/qmk_firmware into hex6c-rev2"):layouts/community/split_3x6_3/bbaserdem/halconf.h
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

<<<<<<<< HEAD:keyboards/hfdkb/ac001/ac001.h
#include "quantum.h"

#define LAYOUT( \
	K000, K001, K002,  K003, K004  \
) { \
	{ K000, K001, K002,  K003, K004 } \
}
// clang-format on
========
#ifdef KEYBOARD_crkbd_rev1
    // #define HAL_USE_DAC TRUE
#   define HAL_USE_PWM TRUE
#   define HAL_USE_SERIAL TRUE
#   include_next <halconf.h>
#endif
>>>>>>>> f271c985ce (Revert "Merge branch 'hex6c-rev2' of https://github.com/mechlovin/qmk_firmware into hex6c-rev2"):layouts/community/split_3x6_3/bbaserdem/halconf.h
