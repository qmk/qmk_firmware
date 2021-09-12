# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output

SRC += mxss_frontled.c

# Remove the common RGB light code and use my iteration instead
COMMON_VPATH += $(QUANTUM_DIR)/rgblight
OPT_DEFS += -DRGBLIGHT_ENABLE
SRC += rgblight.c
SRC += $(QUANTUM_DIR)/color.c
WS2812_DRIVER_REQUIRED = yes
CIE1931_CURVE = yes
RGB_KEYCODES_ENABLE = yes
