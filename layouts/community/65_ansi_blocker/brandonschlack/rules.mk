# Build Options
ifeq ($(strip $(KEYBOARD)), gray_studio/space65)
	MOUSEKEY_ENABLE = no
	BACKLIGHT_ENABLE = no
	CONSOLE_ENABLE = yes
	COMMAND_ENABLE = yes
endif
