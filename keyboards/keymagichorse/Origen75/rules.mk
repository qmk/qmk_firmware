# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes		# Mouse keys(+4700) shubiao
EXTRAKEY_ENABLE = yes		# Audio control and System control(+450)
NKRO_ENABLE = yes			# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
UNICODE_ENABLE = yes        # Unicode

RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = WS2812
VELOCIKEY_ENABLE = yes

RAW_ENABLE = no

#VIA
VIA_ENABLE = yes
LEADER_ENABLE =NO
FAUXCLICKY_ENABLE =NO
MIDI_ENABLE =NO
BLUETOOTH_ENABLE =NO
KEY_LOCK_ENABLE =NO
TERMINAL_ENABLE =NO
SRC += analog.c
