# MCU configuration
MCU_FAMILY = ES32
MCU_SERIES = FS026

# Bootloader selection
BOOTLOADER = custom

# linker script to use
MCU_LDSCRIPT = FS026

# startup code to use
MCU_STARTUP = FS026

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = FS026

# FS026 series is Cortex M0
MCU  = cortex-m0
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 6

# Build Options
#   change yes to no to disable
#
EEPROM_CUSTOM = custom
EEPROM_DRIVER = custom
NO_USB_STARTUP_CHECK = yes
BLUETOOTH_CUSTOM = yes

# Include common library (replaces rdr_lib)
VPATH += lib/rdmctmzt_common
EXTRAINCDIRS += $(TOP_DIR)/lib/rdmctmzt_common
SRC += rdmctmzt_common.c \
	keyboard_common.c \
	three_mode.c \
	user_battery.c \
	user_eeprom.c \
	user_emi.c \
	user_led_custom.c \
	user_spi.c \
	user_system.c

# Include dynamic keymap support
SRC += quantum/dynamic_keymap.c

# Include FS026 SPI driver
VPATH += lib/chibios-contrib/os/common/ext/CMSIS/ES32/FS026/md
SRC += lib/chibios-contrib/os/common/ext/CMSIS/ES32/FS026/md/md_spi.c

DEBOUNCE_TYPE = asym_eager_defer_pk
