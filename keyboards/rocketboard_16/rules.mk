# Configure for 128K flash
MCU_LDSCRIPT = STM32F103xB

# Extra include
SRC += keycode_lookup.c

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB backlit keys
AUDIO_ENABLE = no           # Audio output
OLED_ENABLE = yes
ENCODER_ENABLE = yes

RAW_ENABLE = yes            # Enables HID RAW communication between the board and the PC

LTO_ENABLE = yes
