// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#define ENCODERS 1
#define ENCODER_RESOLUTION 4
#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B3 }
#define ENCODERS_CW_KEY { { 2, 1 } }
#define ENCODERS_CCW_KEY { { 0, 1 } }

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 7

#define FORCE_NKRO

#define JOYSTICK_BUTTON_COUNT 13
#define JOYSTICK_AXIS_COUNT 1
#define JOYSTICK_AXIS_RESOLUTION 16
