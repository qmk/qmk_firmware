OLED_ENABLE = yes
ENCODER_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes

WPM_ENABLE = no
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = yes         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = yes        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing

#Debug options
VERBOSE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

LTO_ENABLE = yes

SPLIT_KEYBOARD = yes

# VIA_ENABLE = yes

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball

ifeq ($(PROMICRO), yes)
  BOOTLOADER = caterina
else ifeq ($(ELITEC), yes)
  BOOTLOADER = atmel-dfu
endif
