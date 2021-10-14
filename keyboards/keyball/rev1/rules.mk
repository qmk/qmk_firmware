# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

# Keyball46 rev.1 is split keyboard.
SPLIT_KEYBOARD = yes

# To support trackball.
POINTING_DEVICE_ENABLE = yes
SRC += trackball.c              # Trackball application interface
SRC += pmw/pmw.c                # Optical sensor firmware and driver
QUANTUM_LIB_SRC += spi_master.c # Optical sensor use SPI to communicate

# To support OLED
OLED_ENABLE = no        # Please Enable this in each keymaps.
SRC += oledkit.c        # OLED utility for Keyball46

# Link Time Optimization required for size.
LTO_ENABLE = yes
