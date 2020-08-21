AUTO_SHIFT_ENABLE = yes
AUTO_SHIFT_MODIFIERS = yes
UNICODE_ENABLE = yes
LINK_TIME_OPTIMIZATION_ENABLE = yes

ifeq ($(strip $(KEYBOARD)), planck/rev5)
BACKLIGHT_ENABLE = yes
CONSOLE_ENABLE = no
endif
ifeq ($(strip $(KEYBOARD)), planck/rev6)
BACKLIGHT_ENABLE = no
CONSOLE_ENABLE = yes
EXTRALDFLAGS = -Wl,--build-id=none
UNICODE_ENABLE = yes
endif
