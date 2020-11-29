# Build Options (yes/no)
#
BOOTMAGIC_ENABLE = no        # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes        # Audio control and System control(+450)
CONSOLE_ENABLE = no          # Console for debug(+400)
COMMAND_ENABLE = no          # Commands for debug and configuration
NKRO_ENABLE = no             # USB Nkey Rollover (see: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work)
BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality on B7 by default
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
MIDI_ENABLE = no             # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE = no          # Unicode
BLUETOOTH_ENABLE = no        # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no            # Audio output on port C6
FAUXCLICKY_ENABLE = no       # Use buzzer to emulate clicky switches
HD44780_ENABLE = no          # Enable support for HD44780 based LCDs (+400)

TAP_DANCE_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
