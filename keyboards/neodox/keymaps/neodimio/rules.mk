#  Copyright 2022 MatteoDM <matteodalmo@gmail.com>
#  SPDX-License-Identifier: GPL-2.0-or-later

TAP_DANCE_ENABLE = yes

SRC += \
	imgs/big_font.qff.c \
	imgs/logo.qgf.c

EXTRALDFLAGS = -Wl,--defsym,FLASH_LEN=16384k
