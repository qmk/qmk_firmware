SRC += muse.c

ifeq ($(strip $(KEYBOARD)), planck/rev6)
  BACKLIGHT_ENABLE = no
else
  BACKLIGHT_ENABLE = yes
endif

MIDI_ENABLE=no
RGBLIGHT_ENABLE = no
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no		# Console for debug
COMMAND_ENABLE = no    	# Commands for debug and configuration

BOOTMAGIC_ENABLE = no # mainly to save space