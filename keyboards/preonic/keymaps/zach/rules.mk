# Zach Preonic Makefile
# Max .hex size is about 28636 bytes

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in 
#   the appropriate keymap folder that will get included automatically
#
TAP_DANCE_ENABLE    = yes   # Enable TapDance functionality
BOOTMAGIC_ENABLE    = no    # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE     = no    # Mouse keys(+4700)
EXTRAKEY_ENABLE     = no    # Audio control and System control(+450)
CONSOLE_ENABLE      = no    # Console for debug(+400)
COMMAND_ENABLE      = no    # Commands for debug and configuration
NKRO_ENABLE         = yes   # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
USB_6KRO_ENABLE     = no    # 6key Rollover
BACKLIGHT_ENABLE    = yes   # Enable keyboard backlight functionality
MIDI_ENABLE         = no    # MIDI controls
AUDIO_ENABLE        = yes   # Audio output on port C6
#VARIABLE_TRACE      = no    # Debug changes to variable values
UNICODE_ENABLE      = no    # Unicode
UNICODEMAP_ENABLE   = yes   # Enable extended unicode
BLUETOOTH_ENABLE    = no    # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE     = no    # Enable WS2812 RGB underlight. 
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE    = no    # Breathing sleep LED during USB suspend

