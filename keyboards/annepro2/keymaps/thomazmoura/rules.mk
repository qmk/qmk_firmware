# Anne Pro 2
SRC = \
	matrix.c \
	hardfault_handler.c \
	annepro2_ble.c \
	qmk_ap2_led.c \
	protocol.c

ifeq ($(strip $(ANNEPRO2_EEPROM)), yes)
    OPT_DEFS += -DANNEPRO2_EEPROM
    SRC += spi_master.c eeprom_w25x20cl.c
endif

LAYOUTS +=

# MCU
MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523x2
MCU_LDSCRIPT = HT32F52342_ANNEPRO2
MCU_STARTUP = ht32f523x2

BOARD = ANNEPRO2_C18

OPT_DEFS = -Wno-unused-function -fdump-rtl-dfinish -fstack-usage
#EXTRALDFLAGS = -Wl,--print-memory-usage

# Options

# Keys
CUSTOM_MATRIX = yes
NKRO_ENABLE = no
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
EXTRAKEY_ENABLE = yes
KEY_LOCK_ENABLE = no

# Other featues
BOOTMAGIC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = yes
RAW_ENABLE = yes
MIDI_ENABLE = no
VIRTSER_ENABLE = no
COMBO_ENABLE = no
