ifeq ($(strip $(KEYBOARD)), preonic/rev3)
	SRC += muse.c
endif

MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
BACKLIGHT_ENABLE = no       # No backlights installed

ifeq ($(strip $(KEYBOARD)), jnao)
	BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
endif
