# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite		# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes		# Mouse keys
EXTRAKEY_ENABLE = yes		# Audio control and System control
KEYBOARD_LOCK_ENABLE = yes	# Allow locking of keyboard via magic key
NKRO_ENABLE = no			# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
ENCODER_ENABLE = yes # [2Key2crawl] Make the knobs turn
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
LTO_ENABLE = yes
