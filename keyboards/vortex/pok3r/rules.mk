# Vortex POK3R

SRC = \
	matrix.c \
	eeprom.c \
	backlight.c

LAYOUTS += 60_ansi 60_ansi_split_rshift 60_iso

# MCU

MCU = cortex-m3
ARMV = 7
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F165x
MCU_LDSCRIPT = HT32F1655_VORTEX
MCU_STARTUP = ht32f165x

BOARD = VORTEX_DUAL_60

OPT_DEFS = -DCORTEX_VTOR_INIT=0x2c00 -Wno-unused-function -fdump-rtl-dfinish -fstack-usage
#EXTRALDFLAGS = -Wl,--print-memory-usage

# Options

# Keys
CUSTOM_MATRIX = yes
NKRO_ENABLE = yes
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
KEY_LOCK_ENABLE = no

# Backlight
BACKLIGHT_ENABLE = no
BACKLIGHT_CUSTOM_DRIVER = yes
#SLEEP_LED_ENABLE = yes	# Breathing sleep LED during USB suspend

# Other featues
BOOTMAGIC_ENABLE = yes
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
RAW_ENABLE = yes

# EEPROM
EEPROM_CUSTOM_DRIVER = yes
