TAP_DANCE_ENABLE   = yes
SLEEP_LED_ENABLE   = no  # Breathing sleep LED during USB suspend
COMMAND_ENABLE     = no  # Commands for debug and configuration
SPACE_CADET_ENABLE = no
ifeq ($(strip $(KEYBOARD)), ergodox_ez)
	RGBLIGHT_ENABLE   = yes
	RGB_MATRIX_ENABLE = no
endif
CONSOLE_ENABLE     = no
BOOTMAGIC_ENABLE   = yes

UNICODE_ENABLE     = yes
UNICDOEMAP_ENABLE  = no

RGBLIGHT_TWINKLE   = no
INDICATOR_LIGHTS   = no
RGBLIGHT_STARTUP_ANIMATION = yes

DEBOUNCE_TYPE     = eager_pr
