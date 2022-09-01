# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
LTO_ENABLE = yes			# Optimize size when compiling
BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
SPLIT_KEYBOARD = yes		# Split keyboard is neccesary!

EXTRAKEY_ENABLE = yes       # Audio control and System control

CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration

RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow

NKRO_ENABLE = yes           # USB Nkey Rollover (needed for gaming)

ENCODER_ENABLE = yes		# Support for OLED screens
OLED_ENABLE = yes			# Support for Rotary Encoders

TAP_DANCE_ENABLE = no		# Used in keymap
AUTO_SHIFT_ENABLE = no		# Used in keymap

AUDIO_ENABLE = no           # Audio output
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend # Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
MAGIC_ENABLE = no
