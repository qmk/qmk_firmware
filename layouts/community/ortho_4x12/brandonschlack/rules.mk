ifeq ($(strip $(KEYBOARD)), planck/rev6)
	SRC += muse.c
endif

MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
BACKLIGHT_ENABLE = no       # No backlights installed

ifeq ($(strip $(KEYBOARD)), jnao)
	BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
endif
