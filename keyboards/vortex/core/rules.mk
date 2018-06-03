# Vortex CORE

SRC = \
	ht32.c \
	util.c \
	matrix.c \
	eeprom.c
#	rgblight.c

LAYOUTS += 60_ansi 60_ansi_split_rshift 60_iso

# MCU

MCU = cortex-m3
ARMV = 7
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F165x
MCU_LDSCRIPT = HT32F1654_CYKB
MCU_STARTUP = ht32f165x

BOARD = CYKB175_V03

OPT_DEFS = -DCORTEX_VTOR_INIT=0x3400 -Wno-unused-function

# Options

# Keys
CUSTOM_MATRIX = yes
NKRO_ENABLE = yes
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
KEY_LOCK_ENABLE = no

# RGB Backlight
RGBLIGHT_ENABLE = no
RGBLIGHT_CUSTOM_DRIVER = yes

# Other featues
BOOTMAGIC_ENABLE = no
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
RAW_ENABLE = yes

# EEPROM
EEPROM_CUSTOM_DRIVER = yes
