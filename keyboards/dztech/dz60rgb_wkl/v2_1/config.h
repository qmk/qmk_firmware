// Copyright 2021 trankimtung
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // Turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#    define IS31FL3733_I2C_ADDRESS_1      IS31FL3733_I2C_ADDRESS_GND_GND
#    define RGB_MATRIX_LED_COUNT   62
#endif
