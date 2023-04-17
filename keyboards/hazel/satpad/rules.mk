# Build Options (yes/no)
#
BOOTMAGIC_ENABLE   = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE    = yes      # Mouse keys
EXTRAKEY_ENABLE    = yes      # Audio control and System control
NKRO_ENABLE        = yes      # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
TAP_DANCE_ENABLE   = yes
ENCODER_ENABLE 	   = yes
ENCODER_MAP_ENABLE = yes
OLED_ENABLE        = yes

LTO_ENABLE 	 = no        # Enabled this causes longer build time, but smaller file.


AUTO_SHIFT_ENABLE  = no      # 24FEB23 Added  26FEB23 Removed
UNICODE_ENABLE   = no        # Unicode
CONSOLE_ENABLE   = no        # Console for debug
COMMAND_ENABLE   = no        # Commands for debug and configuration
RGBLIGHT_ENABLE  = no
BACKLIGHT_ENABLE = no        # Enable keyboard backlight functionality
SLEEP_LED_ENABLE = no        # Breathing sleep LED during USB suspend (it uses the same timer as BACKLIGHT_ENABLE)
AUDIO_ENABLE     = no        # Audio output on port C6
MIDI_ENABLE      = no        # MIDI support
BLUETOOTH_ENABLE = no        # Enable Bluetooth with the Adafruit EZ-Key HID