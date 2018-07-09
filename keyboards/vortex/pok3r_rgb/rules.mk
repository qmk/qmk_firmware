# Vortex POK3R RGB

SRC = \
	ht32.c \
	util.c \
	matrix.c \
	eeprom.c \
	rgblight.c

LAYOUTS += 60_ansi 60_ansi_split_rshift 60_iso

# MCU

MCU = cortex-m3
ARMV = 7
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F165x
MCU_LDSCRIPT = HT32F1654_CYKB
MCU_STARTUP = ht32f165x

BOARD = CYKB167_D_V03

OPT_DEFS = -DCORTEX_VTOR_INIT=0x3400 -Wno-unused-function -fdump-rtl-dfinish -fstack-usage
#EXTRALDFLAGS = -Wl,--print-memory-usage

# Options

# Keys
CUSTOM_MATRIX = yes
NKRO_ENABLE = yes
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = no
KEY_LOCK_ENABLE = no

# RGB Backlight
RGBLIGHT_ENABLE = yes
RGBLIGHT_CUSTOM_DRIVER = yes

# Other featues
BOOTMAGIC_ENABLE = yes
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
RAW_ENABLE = yes
MIDI_ENABLE = no
VIRTSER_ENABLE = no

# EEPROM
EEPROM_CUSTOM_DRIVER = yes
