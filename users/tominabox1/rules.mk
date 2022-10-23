# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
CONSOLE_ENABLE = no
TAP_DANCE_ENABLE = yes
NKRO_ENABLE = yes
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite

ifeq ($(strip $(KEYBOARD)), crkbd/rev1)
RGB_MATRIX_ENABLE = yes
EXTRAFLAGS += -flto
BOOTLOADER = qmk-dfu
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
endif

ifeq ($(strip $(KEYBOARD)), lazydesigners/dimple)
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality on B7 by default
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
endif


SRC += tominabox1.c
