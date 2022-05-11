# Defalt to the ansi version
DEFAULT_FOLDER = idobao/id80/v2/ansi

# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no          # Console for debug
COMMAND_ENABLE = no          # Commands for debug and configuration
NKRO_ENABLE = yes            # Enable N-Key Rollover
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow

ifeq ($(findstring no,$(BACKLIGHT)), no)
  $(info NO BACKLIGHT)
  BACKLIGHT_ENABLE = no
  OPT_DEFS += -DID80_NO_BACKLIGHT
else ifeq ($(findstring off,$(BACKLIGHT)), off)
  $(info BACKLIGHT OFF)
  BACKLIGHT_ENABLE = no
  OPT_DEFS += -DID80_NO_BACKLIGHT
else
  BACKLIGHT_ENABLE = yes
endif
