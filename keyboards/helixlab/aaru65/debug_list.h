// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef FADER_ENABLE
#    include "fader.h"
#    include "ads1100.h"
#endif
#ifdef RGB_INDICATOR_ENABLE
#    include "rgb_indicator.h"
#    include "aw2023.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif

#define YN(x) ((x) ? "yes" : "no")

void debug_custom(void);