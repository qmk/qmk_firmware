# Copyright 2023 binepad (@binepad)
# SPDX-License-Identifier: GPL-2.0-or-later

CUSTOM_MATRIX = yes

SRC += matrix.c \
       candypad_oled.c

OPT_DEFS += -DHAL_USE_I2C=TRUE
