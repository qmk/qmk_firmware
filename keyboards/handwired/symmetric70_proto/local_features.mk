# Copyright (c) 2022 Takeshi Ishii (mtei@github)
# SPDX-License-Identifier: GPL-2.0-or-later

ifneq ($(strip $(MDELAY)),)
    OPT_DEFS += -DMATRIX_IO_DELAY=$(strip $(MDELAY))
endif

ifeq ($(strip $(ADAPTIVE_DELAY)),yes)
    OPT_DEFS += -DMATRIX_IO_DELAY_ADAPTIVE
endif

ifeq ($(strip $(ADAPTIVE_DELAY2)),yes)
    OPT_DEFS += -DMATRIX_IO_DELAY_ADAPTIVE2
endif

ifeq ($(strip $(ADAPTIVE_DELAY_FAST)),yes)
    OPT_DEFS += -DMATRIX_IO_DELAY_ADAPTIVE_FAST
endif

ifeq ($(strip $(ALWAYS_DELAY)),yes)
    OPT_DEFS += -DMATRIX_IO_DELAY_ALWAYS
endif

ifeq ($(strip $(MATRIX_DEBUG_DELAY)),yes)
    OPT_DEFS += -DMATRIX_DEBUG_DELAY
    DEBUG_CONFIG = yes
endif

ifeq ($(strip $(CUSTOM_MATRIX_DELAY)),adaptive)
    OPT_DEFS += -DMATRIX_IO_DELAY_TYPE=ADAPTIVE_TO_INPUT
endif
ifeq ($(strip $(CUSTOM_MATRIX_DELAY)),adaptive-time)
    OPT_DEFS += -DMATRIX_IO_DELAY_TYPE=ADAPTIVE_TO_INPUT_WITH_TIME
endif
ifeq ($(strip $(CUSTOM_MATRIX_DELAY)),time)
    OPT_DEFS += -DMATRIX_IO_DELAY_TYPE=WAIT_SPECIFIED_TIME
endif
ifeq ($(strip $(CUSTOM_MATRIX_DELAY)),input-pullup)
    OPT_DEFS += -DMATRIX_IO_DELAY_TYPE=FORCE_INPUT_UP_TO_VCC
endif

ifeq ($(strip $(MATRIX_USE_OPENDRAIN_PULLUP)),yes)
    OPT_DEFS += -DMATRIX_USE_OPENDRAIN_PULLUP
endif

ifeq ($(strip $(MATRIX_DEBUG_SCAN)),yes)
    OPT_DEFS += -DMATRIX_DEBUG_SCAN
    DEBUG_CONFIG = yes
endif

ifeq ($(strip $(DEBUG_CONFIG)),yes)
    # include "debug_config.h" from {promicro|proton_c}/config.h
    OPT_DEFS += -DDEBUG_CONFIG
endif

$(info -)
$(info -  DEBUG_MATRIX_SCAN_RATE_ENABLE = $(DEBUG_MATRIX_SCAN_RATE_ENABLE))
$(info -  CONSOLE_ENABLE      = $(CONSOLE_ENABLE))
$(info -  MDELAY              = $(MDELAY))
$(info -  OPT_DEFS            = $(OPT_DEFS))
