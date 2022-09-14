# Copyright 2021 Your Name (@yourgithub)
# SPDX-License-Identifier: GPL-2.0-or-later

# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina		# Caterina is the correct bootloader for a standard Pro Micro

# Link Time Optimization
LTO_ENABLE = yes			# Optimize size at compile (takes longer time)

# Debug otions
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration

# Build Options
BOOTMAGIC_ENABLE = yes      # Bootmagic Lite allows reset from key on plug-in

MOUSEKEY_ENABLE = no        # Mouse keys
AUDIO_ENABLE = no           # Audio output

EXTRAKEY_ENABLE = yes       # Audio control and System control
ENCODER_ENABLE = yes		# Rotary encoder

NKRO_ENABLE = no            # USB Nkey Rollover, if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work

# RGB and Backlight
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no		# Enable RGB matrix
#RGB_MATRIX_DRIVER = WS2812	# Define matrix type

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

