# Bootloader selection
# BOOTLOADER        = qmk-dfu  # Elite C
BOOTLOADER        = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE  = no       # was = lite     # Virtual DIP switch configuration
MOUSEKEY_ENABLE   = no       # Mouse keys
EXTRAKEY_ENABLE   = yes      # Audio control and System control

CONSOLE_ENABLE    = no       # Console for debug
COMMAND_ENABLE    = no       # Commands for debug and configuration

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE

SLEEP_LED_ENABLE  = no       # Breathing sleep LED during USB suspend
NKRO_ENABLE       = yes      # USB Nkey Rollover
BACKLIGHT_ENABLE  = no       # Enable keyboard backlight functionality
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE   = no       # Enable keyboard RGB underglow
BLUETOOTH_ENABLE  = no       # Enable Bluetooth
AUDIO_ENABLE      = no       # Audio output

UNICODE_ENABLE    = no       # Unicode

AUTO_SHIFT_ENABLE = yes      # Auto shift
TAP_DANCE_ENABLE  = yes      # tap dance. One tap one code, two taps another code, three taps, and so on.

COMBO_ENABLE      = yes      # Combos - q+w=Esc
