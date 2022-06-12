MCU = atmega32u4
BOOTLOADER = atmel-dfu

BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
EXTRAKEY_ENABLE = yes       # Audio control and System control
NKRO_ENABLE = no            # USB Nkey Rollover
CONSOLE_ENABLE = no         # Console for debug
MOUSEKEY_ENABLE = no        # Mouse keys
COMMAND_ENABLE = no         # Commands for debug and configuration
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output

DEBOUNCE_TYPE = sym_eager_pk

LTO_ENABLE = yes

DEFAULT_FOLDER = adm42/rev4
