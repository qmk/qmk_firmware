# Copyright (c) 2022 Takeshi Ishii (mtei@github)
# SPDX-License-Identifier: GPL-2.0-or-later

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DLED_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS_LEVEL=2
endif

ifeq ($(strip $(LED_ANIMATIONS)), mini)
    OPT_DEFS += -DLED_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS_LEVEL=1
endif

ifeq ($(strip $(DEBUG_CONFIG)), yes)
    OPT_DEFS += -DDEBUG_CONFIG
endif

ifeq ($(strip $(CUSTOM_MATRIX_DELAY)),on-demand)
    SRC += matrix_output_unselect_delay_ondemand.c
endif

ifeq ($(strip $(DEBUG_UART)),yes)
    OPT_DEFS += -DAVR_UART_TX
    SRC += avr_uart_tx.c
endif

ifeq ($(strip $(MATRIX_OVERRIDE)),yes)
    SRC += matrix_boost/matrix_read_cols_on_row.c
    OPT_DEFS += -DMATRIX_OVERRIDE # only for users/mtei/debug_config.h
    ifeq ($(strip $(DEBUG_ON_TEST_BENCH)),yes)
        OPT_DEFS += -DDEBUG_ON_TEST_BENCH
        OPT_DEFS += -DDEBUG_CONFIG
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
    ifeq ($(strip $(DIFF_HAND)),yes)
        OPT_DEFS += -DDIFF_HAND # only for users/mtei/debug_config.h
        OPT_DEFS += -DDEBUG_CONFIG
    endif
endif

ifneq ($(strip $(MDELAY)),)
    OPT_DEFS += -DMATRIX_IO_DELAY=$(strip $(MDELAY))
endif

ifeq ($(strip $(ENABLE_COLEMAK)),yes)
    OPT_DEFS += -DENABLE_COLEMAK
endif

ifeq ($(strip $(ENABLE_DVORAK)),yes)
    OPT_DEFS += -DENABLE_DVORAK
endif

ifeq ($(strip $(ENABLE_EUCALYN)),yes)
    OPT_DEFS += -DENABLE_EUCALYN
endif

ifeq ($(strip $(ENCODER_ENABLE)),yes)
    SRC += encoder_update_user.c
endif

ifeq ($(strip $(DEBUG_ENCODER)),yes)
    OPT_DEFS += -DENCODER_DETECT_OVER_SPEED
endif

ifneq ($(strip $(SYNC_TIMER_ENABLE)),yes)
    OPT_DEFS += -DDISABLE_SYNC_TIMER
endif

ifneq ($(strip $(USROPT)),)
    $(info -)
    $(info -  CONSOLE_ENABLE      = $(CONSOLE_ENABLE))
    $(info -  OLED_ENABLE         = $(OLED_ENABLE))
    $(info -  RGBLIGHT_ENABLE     = $(RGBLIGHT_ENABLE))
    $(info -  ENCODER_ENABLE      = $(ENCODER_ENABLE))
    $(info -  MDELAY              = $(MDELAY))
    $(info -  CUSTOM_MATRIX_DELAY = $(CUSTOM_MATRIX_DELAY))
    $(info -  MATRIX_OVERRIDE     = $(MATRIX_OVERRIDE))
    $(info -  DEBUG_MATRIX_SCAN_RATE_ENABLE = $(DEBUG_MATRIX_SCAN_RATE_ENABLE))
    $(info -  MATRIX_IO_DELAY_TYPE = $(MATRIX_IO_DELAY_TYPE))
    $(info -  OPT_DEFS            = $(OPT_DEFS))
endif
