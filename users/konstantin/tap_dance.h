/* Copyright 2019-2021 Konstantin Đorđević <vomindoraan@gmail.com>
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

#include "quantum.h"

#define DST_A_R TD(TD_DST_A_R)

#define RAL_RGU TD(TD_RAL_RGU)
#define RCT_RSF TD(TD_RCT_RSF)
#define RSF_RCT TD(TD_RSF_RCT)

#ifdef LAYER_FN
    #define LSFT_FN TD(TD_LSFT_FN)
    #define RCTL_FN TD(TD_RCTL_FN)
    #define FN_RCTL TD(TD_FN_RCTL)
#endif

enum tap_dance {
    TD_DST_A_R,

    TD_RAL_RGU,
    TD_RCT_RSF,
    TD_RSF_RCT,

#ifdef LAYER_FN
    TD_LSFT_FN,
    TD_RCTL_FN,
    TD_FN_RCTL,
#endif
};
