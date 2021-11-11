/* Copyright 2021 Cutie Club
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

#include "key_matrix_definitions.h"

#define LAYOUT_60_all( \
    ESC, ALPHAS_R0, SPLIT_BACKSPACE,                   \
    TAB, ALPHAS_R1_ANSI,                               \
    CAPS, ALPHAS_R2, ISO_ENTER,                        \
    SPLIT_LSHIFT, ALPHAS_R3, SPLIT_RSHIFT,             \
    LEFT_CTRL_CLUSTER, SPLIT_SPACE, RIGHT_CTRL_CLUSTER \
) \
{ \
    { ESC_MATRIX, ALPHAS_R0_MATRIX, SPLIT_BACKSPACE_MATRIX },                   \
    { TAB_MATRIX, ALPHAS_R1_ANSI_MATRIX },                                      \
    { CAPS_MATRIX, ALPHAS_R2_MATRIX, ISO_ENTER_MATRIX },                        \
    { SPLIT_LSHIFT_MATRIX, ALPHAS_R3_MATRIX, SPLIT_RSHIFT_MATRIX },             \
    { LEFT_CTRL_CLUSTER_MATRIX, SPLIT_SPACE_MATRIX, RIGHT_CTRL_CLUSTER_MATRIX } \
}

#define LAYOUT_60_ansi( \
    ESC, ALPHAS_R0, BACKSPACE,                   \
    TAB, ALPHAS_R1_ANSI,                         \
    CAPS, ALPHAS_R2, ANSI_ENTER,                 \
    LSHIFT, ALPHAS_R3, RSHIFT,                   \
    LEFT_CTRL_CLUSTER, SPACE, RIGHT_CTRL_CLUSTER \
) \
{ \
    { ESC_MATRIX, ALPHAS_R0_MATRIX, BACKSPACE_MATRIX },                   \
    { TAB_MATRIX, ALPHAS_R1_ANSI_MATRIX },                                \
    { CAPS_MATRIX, ALPHAS_R2_MATRIX, ANSI_ENTER_MATRIX },                 \
    { LSHIFT_MATRIX, ALPHAS_R3_MATRIX, RSHIFT_MATRIX },                   \
    { LEFT_CTRL_CLUSTER_MATRIX, SPACE_MATRIX, RIGHT_CTRL_CLUSTER_MATRIX } \
}

#define LAYOUT_60_ansi_split_bs_rshift( \
    ESC, ALPHAS_R0, SPLIT_BACKSPACE,             \
    TAB, ALPHAS_R1_ANSI,                         \
    CAPS, ALPHAS_R2, ANSI_ENTER,                 \
    LSHIFT, ALPHAS_R3, SPLIT_RSHIFT,             \
    LEFT_CTRL_CLUSTER, SPACE, RIGHT_CTRL_CLUSTER \
) \
{ \
    { ESC_MATRIX, ALPHAS_R0_MATRIX, SPLIT_BACKSPACE_MATRIX },             \
    { TAB_MATRIX, ALPHAS_R1_ANSI_MATRIX },                                \
    { CAPS_MATRIX, ALPHAS_R2_MATRIX, ANSI_ENTER_MATRIX },                 \
    { LSHIFT_MATRIX, ALPHAS_R3_MATRIX, SPLIT_RSHIFT_MATRIX },             \
    { LEFT_CTRL_CLUSTER_MATRIX, SPACE_MATRIX, RIGHT_CTRL_CLUSTER_MATRIX } \
}

#define LAYOUT_60_ansi_tsangan( \
    ESC, ALPHAS_R0, BACKSPACE,                                   \
    TAB, ALPHAS_R1_ANSI,                                         \
    CAPS, ALPHAS_R2, ANSI_ENTER,                                 \
    LSHIFT, ALPHAS_R3, RSHIFT,                                   \
    LEFT_CTRL_CLUSTER_TSANGAN, SPACE, RIGHT_CTRL_CLUSTER_TSANGAN \
) \
{ \
    { ESC_MATRIX, ALPHAS_R0_MATRIX, BACKSPACE_MATRIX },                                    \
    { TAB_MATRIX, ALPHAS_R1_ANSI_MATRIX },                                                 \
    { CAPS_MATRIX, ALPHAS_R2_MATRIX, ANSI_ENTER_MATRIX },                                  \
    { LSHIFT_MATRIX, ALPHAS_R3_MATRIX, RSHIFT_MATRIX },                                    \
    { LEFT_CTRL_CLUSTER_TSANGAN_MATRIX, SPACE_MATRIX, RIGHT_CTRL_CLUSTER_TSANGAN_MATRIX }  \
}

#define LAYOUT_60_hhkb( \
    ESC, ALPHAS_R0, SPLIT_BACKSPACE,                       \
    TAB, ALPHAS_R1_ANSI,                                   \
    CAPS, ALPHAS_R2, ANSI_ENTER,                           \
    LSHIFT, ALPHAS_R3, SPLIT_RSHIFT,                       \
    LEFT_CTRL_CLUSTER_HHKB, SPACE, RIGHT_CTRL_CLUSTER_HHKB \
) \
{ \
    { ESC_MATRIX, ALPHAS_R0_MATRIX, SPLIT_BACKSPACE_MATRIX },                        \
    { TAB_MATRIX, ALPHAS_R1_ANSI_MATRIX },                                           \
    { CAPS_MATRIX, ALPHAS_R2_MATRIX, ANSI_ENTER_MATRIX },                            \
    { LSHIFT_MATRIX, ALPHAS_R3_MATRIX, SPLIT_RSHIFT_MATRIX },                        \
    { LEFT_CTRL_CLUSTER_HHKB_MATRIX, SPACE_MATRIX, RIGHT_CTRL_CLUSTER_HHKB_MATRIX }  \
}

#define LAYOUT_60_tsangan_hhkb( \
    ESC, ALPHAS_R0, SPLIT_BACKSPACE,                             \
    TAB, ALPHAS_R1_ANSI,                                         \
    CAPS, ALPHAS_R2, ANSI_ENTER,                                 \
    LSHIFT, ALPHAS_R3, SPLIT_RSHIFT,                             \
    LEFT_CTRL_CLUSTER_TSANGAN, SPACE, RIGHT_CTRL_CLUSTER_TSANGAN \
) \
{ \
    { ESC_MATRIX, ALPHAS_R0_MATRIX, SPLIT_BACKSPACE_MATRIX },                              \
    { TAB_MATRIX, ALPHAS_R1_ANSI_MATRIX },                                                 \
    { CAPS_MATRIX, ALPHAS_R2_MATRIX, ANSI_ENTER_MATRIX },                                  \
    { LSHIFT_MATRIX, ALPHAS_R3_MATRIX, SPLIT_RSHIFT_MATRIX },                              \
    { LEFT_CTRL_CLUSTER_TSANGAN_MATRIX, SPACE_MATRIX, RIGHT_CTRL_CLUSTER_TSANGAN_MATRIX }  \
}


#define LAYOUT_60_iso( \
    ESC, ALPHAS_R0, BACKSPACE,                   \
    TAB, ALPHAS_R1_ISO,                          \
    CAPS, ALPHAS_R2, ISO_ENTER,                  \
    SPLIT_LSHIFT, ALPHAS_R3, RSHIFT,             \
    LEFT_CTRL_CLUSTER, SPACE, RIGHT_CTRL_CLUSTER \
) \
{ \
    { ESC_MATRIX, ALPHAS_R0_MATRIX, BACKSPACE_MATRIX },                   \
    { TAB_MATRIX, ALPHAS_R1_ISO_MATRIX },                                 \
    { CAPS_MATRIX, ALPHAS_R2_MATRIX, ISO_ENTER_MATRIX },                  \
    { SPLIT_LSHIFT_MATRIX, ALPHAS_R3_MATRIX, RSHIFT_MATRIX },             \
    { LEFT_CTRL_CLUSTER_MATRIX, SPACE_MATRIX, RIGHT_CTRL_CLUSTER_MATRIX } \
}

#define LAYOUT_60_iso_split_bs_rshift( \
    ESC, ALPHAS_R0, SPLIT_BACKSPACE,             \
    TAB, ALPHAS_R1_ISO,                          \
    CAPS, ALPHAS_R2, ISO_ENTER,                  \
    SPLIT_LSHIFT, ALPHAS_R3, SPLIT_RSHIFT,       \
    LEFT_CTRL_CLUSTER, SPACE, RIGHT_CTRL_CLUSTER \
) \
{ \
    { ESC_MATRIX, ALPHAS_R0_MATRIX, SPLIT_BACKSPACE_MATRIX },             \
    { TAB_MATRIX, ALPHAS_R1_ISO_MATRIX },                                 \
    { CAPS_MATRIX, ALPHAS_R2_MATRIX, ISO_ENTER_MATRIX },                  \
    { SPLIT_LSHIFT_MATRIX, ALPHAS_R3_MATRIX, SPLIT_RSHIFT_MATRIX },       \
    { LEFT_CTRL_CLUSTER_MATRIX, SPACE_MATRIX, RIGHT_CTRL_CLUSTER_MATRIX } \
}

#define LAYOUT_60_iso_tsangan( \
    ESC, ALPHAS_R0, BACKSPACE,                                   \
    TAB, ALPHAS_R1_ISO,                                          \
    CAPS, ALPHAS_R2, ISO_ENTER,                                  \
    SPLIT_LSHIFT, ALPHAS_R3, RSHIFT,                             \
    LEFT_CTRL_CLUSTER_TSANGAN, SPACE, RIGHT_CTRL_CLUSTER_TSANGAN \
) \
{ \
    { ESC_MATRIX, ALPHAS_R0_MATRIX, BACKSPACE_MATRIX },                                   \
    { TAB_MATRIX, ALPHAS_R1_ISO_MATRIX },                                                 \
    { CAPS_MATRIX, ALPHAS_R2_MATRIX, ISO_ENTER_MATRIX },                                  \
    { SPLIT_LSHIFT_MATRIX, ALPHAS_R3_MATRIX, RSHIFT_MATRIX },                             \
    { LEFT_CTRL_CLUSTER_TSANGAN_MATRIX, SPACE_MATRIX, RIGHT_CTRL_CLUSTER_TSANGAN_MATRIX } \
}
