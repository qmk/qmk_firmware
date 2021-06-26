# MCU name
MCU = at90usb1286

# Bootloader selection
BOOTLOADER = halfkay

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
BLUETOOTH_ENABLE = no       # Enable Bluetooth
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
SWAP_HANDS_ENABLE = yes

POINTING_DEVICE_ENABLE = yes
MOUSE_SHARED_EP = no

SPLIT_KEYBOARD = yes

SRC += drivers/sensors/pmw3360.c
QUANTUM_LIB_SRC += spi_master.c tm_sync.c
