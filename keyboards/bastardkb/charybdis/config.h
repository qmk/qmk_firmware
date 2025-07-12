// Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
// Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE

// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT

// Limits the frequency that the sensor is polled for motion.
#define POINTING_DEVICE_TASK_THROTTLE_MS 1

// Invert X axis on mouse reports.
#define POINTING_DEVICE_INVERT_X

/* Trackball angle adjustment. */
#define ROTATIONAL_TRANSFORM_ANGLE -25
