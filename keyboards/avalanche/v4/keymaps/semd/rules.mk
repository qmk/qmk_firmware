OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # ENables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
RGBLIGHT_STARTUP_ANIMATION = yes

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no

CAPS_WORD_ENABLE = yes

SRC += oled_util.c
SRC += rgb_util.c
EXTRAFLAGS += -flto
