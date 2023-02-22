# Copyright 2022 Manna Harbour (@manna-harbour)
# https://github.com/manna-harbour/xmk

# SPDX-License-Identifier: GPL-2.0-or-later

ifeq ($(strip $(XMK_DEBUG)), yes)
  CONSOLE_ENABLE = yes
  OPT_DEFS += -DXMK_DEBUG
endif
