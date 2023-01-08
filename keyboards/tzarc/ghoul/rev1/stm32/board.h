// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include_next "board.h"

#ifdef BOARD_OTG_NOVBUSSENS
#    undef BOARD_OTG_NOVBUSSENS
#endif
