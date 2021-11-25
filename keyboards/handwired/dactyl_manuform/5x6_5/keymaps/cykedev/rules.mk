# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

BOOTMAGIC_ENABLE    = yes     # Enable Bootmagic Lite
MOUSEKEY_ENABLE     = no      # Mouse keys
EXTRAKEY_ENABLE     = yes     # Audio control and System control
CONSOLE_ENABLE      = no      # Console for debug
COMMAND_ENABLE      = no      # Commands for debug and configuration
NKRO_ENABLE         = yes     # USB Nkey Rollover
BLUETOOTH_ENABLE    = no      # Enable Bluetooth
AUDIO_ENABLE        = no      # Audio output
KEY_OVERRIDE_ENABLE = yes     # Enable Key Overrides, see https://docs.qmk.fm/#/feature_key_overrides
SPLIT_KEYBOARD      = yes     # Split Keyboard
LTO_ENABLE          = no
