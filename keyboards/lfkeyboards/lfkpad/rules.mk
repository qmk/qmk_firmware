SRC = TWIlib.c issi.c lighting.c

MCU = atmega32u4
OPT_DEFS += -DBOOTLOADER_SIZE=4096

F_CPU = 16000000
F_USB = $
ARCH = AVR8

# Interrupt driven control endpoint task
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

LAYOUTS = numpad_6x4

BOOTMAGIC_ENABLE = no           # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no            # Mouse keys
EXTRAKEY_ENABLE = yes           # Audio control and System control
CONSOLE_ENABLE = no             # Console for debug
COMMAND_ENABLE = no             # Commands for debug and configuration
NKRO_ENABLE = no               # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no          # Enable keyboard backlight functionality
MIDI_ENABLE = no                # MIDI controls
AUDIO_ENABLE = no               # Audio output on port C6
UNICODE_ENABLE = no             # Unicode
BLUETOOTH_ENABLE = no           # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = yes           # Enable WS2812 RGB underlight.
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lefkeyboards, not qmk base
SLEEP_LED_ENABLE = yes          # Breathing sleep LED during USB suspend
TAP_DANCE_ENABLE = no

ISSI_ENABLE = yes           # If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = no       # Resets keyboard if matrix_scan isn't run every 250ms


ifeq 
    TMK_COMMON_DEFS += -DISSI_ENABLE
endif

ifeq 
    TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
endif
