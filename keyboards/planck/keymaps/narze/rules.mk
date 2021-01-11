

BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
AUDIO_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

COMBO_ENABLE = yes

ifeq ($(strip $(KEYBOARD)), planck/rev4)
    MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
    MIDI_ENABLE = no
else
    MOUSEKEY_ENABLE = yes
    MIDI_ENABLE = yes
endif
