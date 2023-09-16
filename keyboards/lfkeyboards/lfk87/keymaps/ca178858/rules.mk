BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no            # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes           # Audio control and System control(+450)
CONSOLE_ENABLE = yes            # Console for debug(+400)
COMMAND_ENABLE = yes            # Commands for debug and configuration
NKRO_ENABLE = yes
BACKLIGHT_ENABLE = yes          # Enable keyboard backlight functionality
MIDI_ENABLE = no                # MIDI controls
AUDIO_ENABLE = yes              # Audio output on port C6
UNICODE_ENABLE = no             # Unicode
BLUETOOTH_ENABLE = no           # Disable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = yes           # Enable RGB underlight
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lefkeyboards, not WS2812
SLEEP_LED_ENABLE = yes
TAP_DANCE_ENABLE = yes

ISSI_ENABLE = yes			# If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = yes		# Resets keyboard if matrix_scan isn't run every 250ms
