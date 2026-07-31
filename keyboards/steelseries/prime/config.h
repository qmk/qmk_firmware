// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define POINTING_DEVICE_CS_PIN A4
#define POINTING_DEVICE_MOTION_PIN B0
#define POINTING_DEVICE_TASK_THROTTLE_MS 1

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

#define RGB_PWM_DRIVER PWMD1
#define RGB_BLUE_PIN A10
#define RGB_BLUE_PWM_CHANNEL 3
#define RGB_GREEN_PIN A8
#define RGB_GREEN_PWM_CHANNEL 1
#define RGB_RED_PIN A9
#define RGB_RED_PWM_CHANNEL 2

#define OPTICAL_SW_PWR A2
