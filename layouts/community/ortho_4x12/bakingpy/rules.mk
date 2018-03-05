# Enable RGB if not a Planck
ifeq (,$(findstring planck,$(KEYBOARD)))
	RGBLIGHT_ENABLE = yes
endif
