# MCU name
MCU = atmega32u4
F_CPU = 8000000
ARCH = AVR8
F_USB = $(F_CPU)
# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Feather uses the caterina bootloader
OPT_DEFS += -DBOOTLOADER_SIZE=4096 -DCATERINA_BOOTLOADER

CUSTOM_MATRIX = yes          # We have a custom matrix
SRC = matrix.c sx1509.c


# Build Options
#   change yes to no to disable
#
ADAFRUIT_BLE_ENABLE ?= yes   # Enable Bluetooth with the Adafruit BLE boards
MOUSEKEY_ENABLE ?= yes       # Mouse keys(+4700)

EXTRAKEY_ENABLE ?= yes       # Audio control and System control(+450)
CONSOLE_ENABLE ?= yes        # Console for debug(+400)
COMMAND_ENABLE ?= yes        # Commands for debug and configuration

BOOTMAGIC_ENABLE ?= no       # Virtual DIP switch configuration(+1000)
SLEEP_LED_ENABLE ?= no       # Breathing sleep LED during USB suspend
NKRO_ENABLE ?= no            # USB Nkey Rollover
BACKLIGHT_ENABLE ?= no       # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE ?= no            # MIDI controls
UNICODE_ENABLE ?= no         # Unicode
BLUETOOTH_ENABLE ?= no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE ?= no           # Audio output on port C6
FAUXCLICKY_ENABLE ?= no      # Use buzzer to emulate clicky switches
