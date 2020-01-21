
# MCU name
MCU = atmega32u4


# Bootloader
#     This definition is optional, and if your keyboard supports multiple bootloaders of
#     different sizes, comment this out, and the correct address will be loaded
#     automatically (+60). See bootloader.mk for all options.
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
#BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
#MIDI_ENABLE = no            # MIDI controls
UNICODE_ENABLE = yes         # Unicode
#BLUETOOTH_ENABLE = yes       # Enable Bluetooth with the Adafruit EZ-Key HID
#TAP_DANCE_ENABLE = yes
RGBLIGHT_ENABLE = no
LED_ANIMATIONS = no

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DLED_ANIMATIONS
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
