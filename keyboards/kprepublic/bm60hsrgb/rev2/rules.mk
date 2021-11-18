# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes        # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes          # Mouse keys
EXTRAKEY_ENABLE = yes          # Audio control and System control
CONSOLE_ENABLE = no            # Console for debug
COMMAND_ENABLE = no            # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no          # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes              # USB Nkey Rollover
BACKLIGHT_ENABLE = no          # Enable keyboard backlight functionality
MIDI_ENABLE = no               # MIDI support
BLUETOOTH_ENABLE = no          # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no              # Audio output on port C6
NO_USB_STARTUP_CHECK = no      # Disable initialization only when usb is plugged in

LTO_ENABLE = yes


# RGB Matrix is required to support per-key LEDs connected to IS31FL3733.
RGB_MATRIX_ENABLE = yes

# The simpler RGB Lighting code can be enabled to control just the underglow
# LEDs from it; leave it disabled to make the RGB Matrix code control all LEDs,
# including underglow.
RGBLIGHT_ENABLE = no

# The custom RGB Matrix driver combines IS31FL3733 and WS2812; things that are
# normally done by common_features.mk for both of these drivers need to be done
# here manually.
RGB_MATRIX_DRIVER = custom
COMMON_VPATH += $(DRIVER_PATH)/led/issi
SRC += is31fl3733.c
QUANTUM_LIB_SRC += i2c_master.c
WS2812_DRIVER_REQUIRED = yes




