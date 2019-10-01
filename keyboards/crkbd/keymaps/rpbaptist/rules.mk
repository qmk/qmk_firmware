# This enables Link Time Optimization. This can save a good chunk of space (several KB for me), but the macro and function ... functions cause it to error out.
LINK_TIME_OPTIMIZATION_ENABLE = yes

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
MOUSEKEY_ENABLE    = yes  # Mouse keys(+4700)
EXTRAKEY_ENABLE    = yes  # Audio control and System control(+450)
NKRO_ENABLE        = yes  # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work

RGBLIGHT_ENABLE    = no  # Enable WS2812 RGB underlight.
BOOTMAGIC_ENABLE   = no   # Virtual DIP switch configuration(+1000)
CONSOLE_ENABLE     = no   # Console for debug(+400)
COMMAND_ENABLE     = no   # Commands for debug and configuration
BACKLIGHT_ENABLE   = no   # Enable keyboard backlight functionality
MIDI_ENABLE        = no   # MIDI controls
AUDIO_ENABLE       = no   # Audio output on port C6
UNICODE_ENABLE     = no   # Unicode
BLUETOOTH_ENABLE   = no   # Enable Bluetooth with the Adafruit EZ-Key HID
SWAP_HANDS_ENABLE  = no   # Enable one-hand typing

RGB_MATRIX_ENABLE = WS2812

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE   = no    # Breathing sleep LED during USB suspend

BOOTLOADER       = qmk-dfu

OLED_DRIVER_ENABLE = yes

# ifneq ($(strip $(OLED_DRIVER_ENABLE)), yes)
#     RGB_MATRIX_SPLIT_RIGHT=yes
# endif
