SRC += muse.c

ifeq ($(strip $(KEYBOARD)),$(filter $(strip $(KEYBOARD)), planck/rev2 planck/rev3 planck/rev4 planck/rev5))
  BACKLIGHT_ENABLE = yes
else
  BACKLIGHT_ENABLE = no
endif

ifeq ($(strip $(KEYBOARD)), vitamins_included/rev1)
  NKRO_ENABLE = no
endif

MIDI_ENABLE=no
RGBLIGHT_ENABLE = no
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no		# Console for debug
COMMAND_ENABLE = no    	# Commands for debug and configuration

BOOTMAGIC_ENABLE = no # mainly to save space