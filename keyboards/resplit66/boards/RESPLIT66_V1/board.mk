BOARDDIR = $(BOARD_PATH)/boards/RESPLIT66_V1

# STM32L4x3CC have 256KB of flash so must define this to 128.
# STM32L4x3CB have 128KB of flash so must define this to 64.
BOARDDEFS = -DSTM32_FLASH_SECTORS_PER_BANK=128

ifeq ($(USE_RGB_LEDS),y)
# Include RGB leds driver
include $(BOARDDIR)/rgb_leds/rgb_leds.mk
BOARDDEFS += -DUSE_RGB_LEDS
endif

ifeq ($(USE_SSD1306),y)
# Include SSD1306 driver
include $(BOARDDIR)/ssd1306/ssd1306.mk
BOARDDEFS += -DUSE_SSD1306
endif

# List of all the board related files.
BOARDSRC = $(BOARDDIR)/board.c $(RGBLEDSSRC) $(SSD1306SRC)

# Required include directories
BOARDINC = $(BOARDDIR) $(RGBLEDSINC) $(SSD1306INC)

# Shared variables (not used by QMK)
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)

# QMK don't use any define from this Makefile, add needed ones.
OPT_DEFS += $(BOARDDEFS)
