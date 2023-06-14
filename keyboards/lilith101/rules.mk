SRC += custom_keys.c
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
#WS2812_DRIVER = bitbang #Default value
OLED_DRIVER = SSD1306
# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
