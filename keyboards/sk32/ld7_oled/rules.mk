# MCU name: SK32F077 (3Think Cortex-M0, STM32F072-compatible)
MCU = SK32F077

# Linker script selection (defaults to `MCU_LDSCRIPT ?= SK32F077xB` in
# mcu_selection.mk, overridden below).
#   SK32F077x8 -> 64 KB-capable image (46 KB app, tail 2 KB page reserved for
#                 EEPROM).  Runs on SK32F077R8Q6/C8Q6 (64 KB) and on either
#                 64/128 KB SK32F077.  This SAME firmware also runs on a
#                 128 KB SK32F077.
#   SK32F077xB -> 128 KB image (110 KB app).  For SK32F077RBQ6/CBQ6 (128 KB).
MCU_LDSCRIPT = SK32F077x8

# Bootloader selection
# sk32duino: custom DFU bootloader at 0x08000000 (16 KB), VID:PID 1EAF:0003.
# The QMK application is linked at 0x08004000 by
# platforms/chibios/boards/common/ld/.
BOOTLOADER = sk32duino

# EEPROM persistence: wear-leveling driver backed by the SK32F077 internal
# flash (native EFL / embedded_flash) in the last 2 KB page.
EEPROM_DRIVER = vendor

BOOTMAGIC_ENABLE = yes    # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes     # Mouse keys
EXTRAKEY_ENABLE = yes     # Audio control and System control
NKRO_ENABLE = yes         # USB Nkey Rollover
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = no

# RGB MATRIX over WS2812, driven by the native SK32F077 SLED peripheral.
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = sled

# 128x32 SSD1306 OLED on I2C1.
# Auto-detect: keymap.c probes the I2C bus on first use and disables the OLED
# engine (no I2C traffic) when no SSD1306 is present, so the SAME firmware runs
# on boards with and without the OLED without breaking USB enumeration.
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c
