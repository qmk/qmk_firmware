# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = custom
DIP_SWITCH_ENABLE = yes     # Enable dip switches
DEBOUNCE_TYPE = sym_defer_pk    # Debounce using eager_pk.
CUSTOM_MATRIX = lite
DEFERRED_EXEC_ENABLE = yes
NO_USB_STARTUP_CHECK = yes
# EEPROM_DRIVER = i2c

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

OPT_DEFS += -DWS2812

# Project specific files
SRC += matrix.c \
	   common/shift_register.c \
       common/ws2812_custom.c
