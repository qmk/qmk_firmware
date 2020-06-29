# MCU name
MCU = atmega32u4

# Bootloader
BOOTLOADER = atmel-dfu

# Build Options
# See https://beta.docs.qmk.fm/developing-qmk/qmk-reference/config_options#feature-options-id-feature-options
BOOTMAGIC_ENABLE = no # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no # Console for debug
COMMAND_ENABLE = no # Commands for debug and configuration
COMBO_ENABLE = yes # Key combo feature
NKRO_ENABLE = no # USB N-Key Rollover
AUDIO_ENABLE = no # Enable the audio subsystem.
RGBLIGHT_ENABLE = no # Enable keyboard underlight functionality
LEADER_ENABLE = yes # Enable leader key chording
MIDI_ENABLE = no # MIDI controls
UNICODE_ENABLE = yes # Unicode
BLUETOOTH_ENABLE = no # Legacy option to Enable Bluetooth with the Adafruit EZ-Key HID
BLUETOOTH = no # Current options are AdafruitEzKey, AdafruitBLE, RN42
# Note: this is a split keyboard, but not a dual-MCU one, so we can't use this feature
SPLIT_KEYBOARD = no # Enables split keyboard support (dual MCU like the let's split and bakingpy's boards) and includes all necessary files located at quantum/split_common
CUSTOM_MATRIX = yes # Allows replacing the standard matrix scanning routine with a custom one.
# Using eager_pr for debounce as it was recommended in a comment in the ergodox_ez keymap
# as a solution to issues with the slow i2c connection between keyboard halves
#DEBOUNCE_TYPE = eager_pr # Allows replacing the standard key debouncing routine with an alternative or custom one.
WAIT_FOR_USB = no # Forces the keyboard to wait for a USB connection to be established before it starts up
NO_USB_STARTUP_CHECK = yes # Disables usb suspend check after keyboard startup. Usually the keyboard waits for the host to wake it up before any tasks are performed. This is useful for split keyboards as one half will not get a wakeup call but must send commands to the master.
LTO_ENABLE = yes # Enable link time optimization

SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
