// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Override the initialisation functions inside the ChibiOS board.c files
#define __early_init __chibios_override___early_init
#define boardInit __chibios_override_boardInit
