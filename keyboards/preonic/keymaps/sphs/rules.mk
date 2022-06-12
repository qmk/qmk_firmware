SRC += muse.c

# Build Options
# Change to "no" to disable the options, or define them in the Makefile in
# the appropriate keymap folder that will get included automatically
AUDIO_ENABLE     = yes         # Audio output - Enable the audio subsystem
BACKLIGHT_ENABLE = no          # Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no          # Current options are AdafruitBLE, RN42
BOOTMAGIC_ENABLE = no          # Virtual DIP switch configuration
COMMAND_ENABLE   = no          # Commands for debug and configuration
CONSOLE_ENABLE   = no          # Console for debug
EXTRAKEY_ENABLE  = yes         # Enable audio control and system control
LTO_ENABLE       = yes         # Enables Link Time Optimization (LTO) when compiling the keyboard. This makes the process take longer, but it can significantly reduce the compiled size (and since the firmware is small, the added time is not noticeable)
MIDI_ENABLE      = no          # MIDI controls
MOUSEKEY_ENABLE  = yes         # Mouse keys
NKRO_ENABLE      = yes         # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE  = no          # Enable WS2812 RGB underlight - Enable keyboard underlight functionality
SLEEP_LED_ENABLE = no          # Breathing sleep LED during USB suspend
SPLIT_KEYBOARD   = no          # Enables split keyboard support (dual MCU like the let's split and bakingpy's boards) and includes all necessary files located at quantum/split_common

LAYOUTS          = ortho_5x12
