# Copyright 2023 QMK
# SPDX-License-Identifier: GPL-2.0-or-later

################################################################################
#
# 88888888888 888      d8b                .d888 d8b 888               d8b
#     888     888      Y8P               d88P"  Y8P 888               Y8P
#     888     888                        888        888
#     888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
#     888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
#     888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
#     888     888  888 888      X88      888    888 888 Y8b.          888      X88
#     888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
#
#                                                       888                 888
#                                                       888                 888
#                                                       888                 888
#    .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
#   d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
#   888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
#   Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
#    "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
#        888
#   Y8b d88P
#    "Y88P"
#
################################################################################

from enum import IntEnum


# version: 0.0.1
class RgblightModes(IntEnum):
    STATIC_LIGHT = 0x00
    BREATHING = 0x01
    BREATHING_2 = 0x02
    BREATHING_3 = 0x03
    BREATHING_4 = 0x04
    RAINBOW_MOOD = 0x05
    RAINBOW_MOOD_2 = 0x06
    RAINBOW_MOOD_3 = 0x07
    RAINBOW_SWIRL = 0x08
    RAINBOW_SWIRL_2 = 0x09
    RAINBOW_SWIRL_3 = 0x0A
    RAINBOW_SWIRL_4 = 0x0B
    RAINBOW_SWIRL_5 = 0x0C
    RAINBOW_SWIRL_6 = 0x0D
    SNAKE = 0x0E
    SNAKE_2 = 0x0F
    SNAKE_3 = 0x10
    SNAKE_4 = 0x11
    SNAKE_5 = 0x12
    SNAKE_6 = 0x13
    KNIGHT = 0x14
    KNIGHT_2 = 0x15
    KNIGHT_3 = 0x16
    CHRISTMAS = 0x17
    STATIC_GRADIENT = 0x18
    STATIC_GRADIENT_2 = 0x19
    STATIC_GRADIENT_3 = 0x1A
    STATIC_GRADIENT_4 = 0x1B
    STATIC_GRADIENT_5 = 0x1C
    STATIC_GRADIENT_6 = 0x1D
    STATIC_GRADIENT_7 = 0x1E
    STATIC_GRADIENT_8 = 0x1F
    STATIC_GRADIENT_9 = 0x20
    STATIC_GRADIENT_10 = 0x21
    RGB_TEST = 0x22
    ALTERNATING = 0x23
    TWINKLE = 0x24
    TWINKLE_2 = 0x25
    TWINKLE_3 = 0x26
    TWINKLE_4 = 0x27
    TWINKLE_5 = 0x28
    TWINKLE_6 = 0x29


# version: 0.0.1
class RgbMatrixModes(IntEnum):
    SOLID_COLOR = 0x00
    ALPHAS_MODS = 0x01
    GRADIENT_UP_DOWN = 0x02
    GRADIENT_LEFT_RIGHT = 0x03
    BREATHING = 0x04
    BAND_SAT = 0x05
    BAND_VAL = 0x06
    BAND_PINWHEEL_SAT = 0x07
    BAND_PINWHEEL_VAL = 0x08
    BAND_SPIRAL_SAT = 0x09
    BAND_SPIRAL_VAL = 0x0A
    CYCLE_ALL = 0x0B
    CYCLE_LEFT_RIGHT = 0x0C
    CYCLE_UP_DOWN = 0x0D
    CYCLE_OUT_IN = 0x0E
    CYCLE_OUT_IN_DUAL = 0x0F
    RAINBOW_MOVING_CHEVRON = 0x10
    CYCLE_PINWHEEL = 0x11
    CYCLE_SPIRAL = 0x12
    DUAL_BEACON = 0x13
    RAINBOW_BEACON = 0x14
    RAINBOW_PINWHEELS = 0x15
    RAINDROPS = 0x16
    JELLYBEAN_RAINDROPS = 0x17
    HUE_BREATHING = 0x18
    HUE_PENDULUM = 0x19
    HUE_WAVE = 0x1A
    PIXEL_FRACTAL = 0x1B
    PIXEL_FLOW = 0x1C
    PIXEL_RAIN = 0x1D
    TYPING_HEATMAP = 0x1E
    DIGITAL_RAIN = 0x1F
    SOLID_REACTIVE_SIMPLE = 0x20
    SOLID_REACTIVE = 0x21
    SOLID_REACTIVE_WIDE = 0x22
    SOLID_REACTIVE_MULTIWIDE = 0x23
    SOLID_REACTIVE_CROSS = 0x24
    SOLID_REACTIVE_MULTICROSS = 0x25
    SOLID_REACTIVE_NEXUS = 0x26
    SOLID_REACTIVE_MULTINEXUS = 0x27
    SPLASH = 0x28
    MULTISPLASH = 0x29
    SOLID_SPLASH = 0x2A
    SOLID_MULTISPLASH = 0x2B

# noqa: W391
