BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = no  # Mouse keys(+4700)
EXTRAKEY_ENABLE  = no  # Audio control and System control(+450)
CONSOLE_ENABLE   = no  # Console for debug(+400)
COMMAND_ENABLE   = yes # Commands for debug and configuration
NKRO_ENABLE      = yes
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
MIDI_ENABLE      = no  # MIDI controls
AUDIO_ENABLE     = no  # Audio output on port C6
UNICODE_ENABLE   = no  # Unicode
BLUETOOTH_ENABLE = no  # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE  = no  # Enable WS2812 RGB underlight. 

CONFIG_H = keymaps/$(KEYMAP)/config.h