# Copyright 2022 LucW (@luc-languagetools)
# SPDX-License-Identifier: GPL-2.0-or-later

MOUSEKEY_ENABLE = yes    # Mouse keys
RGBLIGHT_ENABLE = no # Enable WS2812 RGB underlight.
# RGB_MATRIX_ENABLE = no
OLED_ENABLE     = no
LTO_ENABLE      = yes
CONVERT_TO      = elite_pi
# VIA_ENABLE		= yes # Enable VIA configurator. Does not support TAPPPING
SRC += oneshot.c
