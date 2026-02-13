#  Copyright 2022 MatteoDM <matteodalmo@gmail.com>
#  SPDX-License-Identifier: GPL-2.0-or-later

# MCU name
MCU = RP2040

# BOARD = GENERIC_RP_RP2040
# Bootloader selection
BOOTLOADER = rp2040
SERIAL_DRIVER = vendor
WS2812_DRIVER = vendor
# specific to using the serial serial driver
# SERIAL_DRIVER = usart
RGBLIGHT_ENABLE = yes   # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no
RGB_MATRIX_DRIVER = WS2812
# OLED_ENABLE = no
# OLED_DRIVER = SSD1306   # Enables the use of OLED displays
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS = gc9a01_spi
QUANTUM_PAINTER_LOAD_FONTS_TO_RAM = TRUE
QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE= 160


# QUANTUM_PAINTER_SUPPORTS_256_PALETTE = TRUE



BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = pwm
BACKLIGHT_SUPPORTED = yes
# ENCODER_ENABLE = no     # Enables the use of one or more encoders
# RGBLIGHT_ENABLE = no   # Enable keyboard RGB underglow
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System controliouy
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
# BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
LTO_ENABLE = yes        # link time optimizations
TAP_DANCE_ENABLE = yes
SPLIT_KEYBOARD = yes
DEFAULT_FOLDER = redox/rev1
DEBOUNCE_TYPE = asym_eager_defer_pk
WPM_ENABLE = yes

SRC += \
	imgs/big_font.qff.c \
	imgs/logo.qgf.c

EXTRALDFLAGS = -Wl,--defsym,FLASH_LEN=16384k
