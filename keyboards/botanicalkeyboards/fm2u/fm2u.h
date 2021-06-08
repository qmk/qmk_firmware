/* Copyright 2020 mechmerlin
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_1u( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_1u25( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_1u5( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_1u75( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_2u( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_2u25( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_2u75( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_3u( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_6u( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_6u25( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_7u( \
    k00 \
) { \
    { k00 } \
}

#define LAYOUT_isoenter( \
    k00 \
) { \
    { k00 } \
}

// Backward compatibility TODO: remove these
#define LAYOUT_100u LAYOUT_1u
#define LAYOUT_125u LAYOUT_1u25
#define LAYOUT_150u LAYOUT_1u5
#define LAYOUT_175u LAYOUT_1u75
#define LAYOUT_200u LAYOUT_2u
#define LAYOUT_225u LAYOUT_2u25
#define LAYOUT_275u LAYOUT_2u75
#define LAYOUT_300u LAYOUT_3u
#define LAYOUT_600u LAYOUT_6u
#define LAYOUT_625u LAYOUT_6u25
#define LAYOUT_700u LAYOUT_7u
#define LAYOUT_iso LAYOUT_isoenter
