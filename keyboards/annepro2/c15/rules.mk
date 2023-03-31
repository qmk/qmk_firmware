# MCU
MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52342_ANNEPRO2
MCU_STARTUP = ht32f523xx

BOARD = ANNEPRO2_C15

# Bootloader selection
BOOTLOADER = custom
PROGRAM_CMD = annepro2_tools --boot $(BUILD_DIR)/$(TARGET).bin

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

# Wear-levelling driver
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = spi_flash

# Custom RGB matrix handling
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = custom

# Keys
CUSTOM_MATRIX = lite
KEY_LOCK_ENABLE = no

# Other features
RAW_ENABLE = no
MIDI_ENABLE = no
VIRTSER_ENABLE = no
COMBO_ENABLE = no

# Anne Pro 2
SRC = \
	matrix.c \
	annepro2_ble.c \
	ap2_led.c \
	protocol.c \
	rgb_driver.c \
	config_led.c
