MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
BACKLIGHT_ENABLE = no       # No backlights installed

ifeq ($(strip $(KEYBOARD)), jnao)
	BOOTMAGIC_ENABLE = lite
endif
