# Copyright 2026 Andreas Hirschauer
# SPDX-License-Identifier: GPL-2.0-or-later

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += reform4_oled.c
endif
