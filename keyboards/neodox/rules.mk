# Copyright 2022 MatteoDM <matteodalmo@gmail.com>
# SPDX-License-Identifier: GPL-2.0-or-later
# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Drivers
SERIAL_DRIVER = vendor 						# Keyboard comunication
WS2812_DRIVER = vendor
RGB_MATRIX_DRIVER = WS2812
QUANTUM_PAINTER_DRIVERS = gc9a01_spi 		# TFT display driver

SPLIT_KEYBOARD = yes

# Build Options
#   change yes to no to disable
#

RGBLIGHT_ENABLE = no   					# Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no

#TFT options

# Diplays backlight pwm
BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = pwm
#Quantum painter
QUANTUM_PAINTER_ENABLE = yes
# Words per minute counter
WPM_ENABLE = yes

BOOTMAGIC_ENABLE = no       				# Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       				# Mouse keys
EXTRAKEY_ENABLE = yes       				# Audio control and System controliouy
CONSOLE_ENABLE = no         				# Console for debug
COMMAND_ENABLE = yes        				# Commands for debug and configuration
NKRO_ENABLE = no            				# Enable N-Key Rollover
AUDIO_ENABLE = no           				# Audio output
LTO_ENABLE = no            				    # link time optimizations if enabled it gives me problem at startup (rp2040)
TAP_DANCE_ENABLE = no
DEBOUNCE_TYPE = asym_eager_defer_pk
