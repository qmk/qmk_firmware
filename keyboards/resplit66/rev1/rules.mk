ARMV = 7
MCU = STM32L443
# Added by my own ChibiOS branch (remove to used default platform.mk)
PLATFORM_NAME = platform_l443
DEBUG_ENABLE = yes

SRC += transport.c

# For board.mk to use own rgb_leds and oled driver.
USE_RGB_LEDS = y
USE_SSD1306 = n

ifeq ($(USE_RGB_LEDS),y)
SRC += rgb_matrix.c
endif
ifeq ($(USE_OLED),y)
SRC += oled.c
endif
