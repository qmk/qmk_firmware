// Copyright 2024 Shanghai Eastsoft Microelectronics Co., Ltd
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_UNSELECT_DRIVE_HIGH

/* Ensure we jump to bootloader if the RESET keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#ifndef NOP_FUDGE
#    define NOP_FUDGE 0.4
#endif

/*BACKLIGHT pwm setting*/
#define BACKLIGHT_PWM_DRIVER PWM_GP16C4T2
#define BACKLIGHT_PWM_CHANNEL 3

