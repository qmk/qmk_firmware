# Anne Pro 2
SRC = \
	matrix.c \
	annepro2_ble.c \
	ap2_led.c \
	protocol.c \
	rgb_driver.c \
	config_led.c

# MCU
MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52342_ANNEPRO2
MCU_STARTUP = ht32f523xx

BOARD = ANNEPRO2_C15

# Options

# Keys
CUSTOM_MATRIX = lite
NKRO_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
KEY_LOCK_ENABLE = no
LAYOUTS = 60_ansi

# Other featues
BOOTMAGIC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
RAW_ENABLE = no
MIDI_ENABLE = no
VIRTSER_ENABLE = no
COMBO_ENABLE = no
BOOTLOADER = custom
PROGRAM_CMD = annepro2_tools --boot $(BUILD_DIR)/$(TARGET).bin
