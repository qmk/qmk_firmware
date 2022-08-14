# MCU name
MCU = RP2040
BOOTLOADER = rp2040

# Build Options
# change yes to no to disable
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no       # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no      # Enable Bluetooth
AUDIO_ENABLE = no          # Audio output

#for rgb to work with rp2040
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = vendor
EEPROM_DRIVER = vendor
