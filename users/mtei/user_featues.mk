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
    ifeq ($(KEYBOARD),helix/rev3_5rows)
        ifeq ($(strip $(DEBUG_ENCODER)),slave)
          ENCODER_ENABLE = no
          RGBLIGHT_ENABLE = no
          LED_BACK_ENABLE = no
          LED_UNDERGLOW_ENABLE = no
          SRC += encoder_debug.c
          OPT_DEFS += -DDEBUG_CONFIG
          OPT_DEFS += -DENCODER_ENABLE
          OPT_DEFS += -DENCODER_DETECT_OVER_SPEED
          OPT_DEFS += -DENCODER_DEBUG_PIN=D3
        endif
        ifeq ($(strip $(DEBUG_ENCODER)),check-over-speed)
          ENCODER_ENABLE = no
          RGBLIGHT_ENABLE = no
          LED_BACK_ENABLE = no
          LED_UNDERGLOW_ENABLE = no
          DEBUG_UART = yes
          SRC += encoder_debug.c
          OPT_DEFS += -DDEBUG_CONFIG
          OPT_DEFS += -DENCODER_ENABLE
          OPT_DEFS += -DENCODER_DETECT_OVER_SPEED
        endif
    endif
endif

ifneq ($(strip $(SYNC_TIMER_ENABLE)),yes)
    OPT_DEFS += -DDISABLE_SYNC_TIMER
endif

ifeq ($(strip $(DEBUG_UART)),yes)
    OPT_DEFS += -DAVR_UART_TX
    SRC += avr_uart_tx.c
endif

ifneq ($(strip $(USROPT)),)
    $(info -)
    $(info -  KEYBOARD            = $(KEYBOARD))
    $(info -  KEYMAP              = $(KEYMAP))
    $(info -  CONSOLE_ENABLE      = $(CONSOLE_ENABLE))
    $(info -  OLED_ENABLE         = $(OLED_ENABLE))
    $(info -  RGBLIGHT_ENABLE     = $(RGBLIGHT_ENABLE))
    $(info -  ENCODER_ENABLE      = $(ENCODER_ENABLE))
    $(info -  MDELAY              = $(MDELAY))
    $(info -  CUSTOM_MATRIX_DELAY = $(CUSTOM_MATRIX_DELAY))
    $(info -  DEBUG_MATRIX_SCAN_RATE_ENABLE = $(DEBUG_MATRIX_SCAN_RATE_ENABLE))
    $(info -  OPT_DEFS            = $(OPT_DEFS))
endif
