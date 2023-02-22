# Build Options
ifneq (, $(findstring kbd75, $(KEYBOARD)))
	MOUSEKEY_ENABLE = no
endif
BACKLIGHT_ENABLE = no   # No backlights installed
