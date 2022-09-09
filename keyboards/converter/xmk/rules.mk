# Copyright 2022 Manna Harbour (@manna-harbour)
# https://github.com/manna-harbour/xmk

# SPDX-License-Identifier: GPL-2.0-or-later

#XMK_DEBUG = yes

SRC += xmk_matrix.c
SRC += xmk_shell.c
CUSTOM_MATRIX = lite

ifeq ($(strip $(XMK_DEBUG)), yes)
  CONSOLE_ENABLE = yes
  OPT_DEFS += -DXMK_DEBUG
else
  CONSOLE_ENABLE = no
endif

