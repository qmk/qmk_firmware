# Copyright 2024 splitkb.com (support@splitkb.com)
# SPDX-License-Identifier: GPL-2.0-or-later

# Note: this list is not exhaustive!
# See https://docs.qmk.fm for more features

## Hardware features

# OLED: optional, can be installed in socket
OLED_ENABLE = yes          # Enable OLEDs, `yes` or `no`

# Audio: optional, requires soldering
# The Elora is equipped with a footprint
# for the PKLCS1212E4001-R1
AUDIO_ENABLE = no          # Enable audio support, `yes` or `no`

## Software features

# Supported keycodes
MOUSEKEY_ENABLE = yes      # Mouse movement using keys
EXTRAKEY_ENABLE = yes      # Audio and system control

# N-key rollover instead of 6-key rollover
NKRO_ENABLE = yes          # Enable N-Key Rollover
