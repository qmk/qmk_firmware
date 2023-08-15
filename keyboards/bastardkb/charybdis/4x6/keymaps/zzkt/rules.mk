# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER        = atmel-dfu

SPLIT_KEYBOARD    = yes

# uncode
UNICODE_ENABLE     = yes

# Build Options
BOOTMAGIC_ENABLE   = no    # Bootmagic Lite
EXTRAKEY_ENABLE    = no    # Audio control and System control
CONSOLE_ENABLE     = no    # Console for debug
COMMAND_ENABLE     = no    # Commands for debug and configuration
NKRO_ENABLE        = no    # USB Nkey Rollover

# trackball & mousekeys
MOUSEKEY_ENABLE        = yes   # Mouse keys
POINTING_DEVICE_ENABLE = yes
MOUSE_SHARED_EP        = no

#  enable configuraiton with VIA
VIA_ENABLE             = no

# No lighting or audio
SLEEP_LED_ENABLE  = no    # Breathing sleep LED during USB suspend
BACKLIGHT_ENABLE  = no    # Enable keyboard backlight functionality
RGBLIGHT_ENABLE   = no    # Enable keyboard RGB underglow
AUDIO_ENABLE      = no    # Audio output
RGB_MATRIX_ENABLE = no

SRC += drivers/sensors/pmw3360.c
QUANTUM_LIB_SRC += spi_master.c

EXTRAFLAGS        += -flto
