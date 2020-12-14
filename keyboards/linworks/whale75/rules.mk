# MCU name
MCU = STM32F303

# Build Options
NKRO_ENABLE = yes		    # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
EXTRAKEY_ENABLE = yes	    # Audio control and System control(+450)
RGBLIGHT_ENABLE = yes
BACKLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
WS2812_DRIVER = bitbang
BOOTMAGIC_ENABLE = lite     # Enable lite mode of bootmagic (boot into BL)
SLEEP_LED_ENABLE = no
MOUSEKEY_ENABLE = no

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
OPT_DEFS += -DSTM32_DMA_REQUIRED=TRUE