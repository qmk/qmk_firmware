# Copyright 2024 splitkb.com (support@splitkb.com)
# SPDX-License-Identifier: GPL-2.0-or-later

SPI_DRIVER_REQUIRED = yes
CUSTOM_MATRIX = lite

# Myriad boilerplate
SRC += myriad.c
ANALOG_DRIVER_REQUIRED = yes
POINTING_DEVICE_DRIVER = custom