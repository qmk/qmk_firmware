AUTO_SHIFT_ENABLE = no
AUTO_SHIFT_MODIFIERS = no
UNICODE_ENABLE = yes
LTO_ENABLE = yes

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
