ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

MOUSEKEY_ENABLE  = yes # Mouse keys(+4700)
COMMAND_ENABLE   = no  # Commands for debug and configuration
CONSOLE_ENABLE   = no  # Console for debug(+400)
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
API_SYSEX_ENABLE = no

ifneq (,$(findstring planck/light,$(KEYBOARD)))
    AUDIO_ENABLE      = yes
    BACKLIGHT_ENABLE  = no
    RGB_MATRIX_ENABLE = yes
else
    AUDIO_ENABLE      = no
    BACKLIGHT_ENABLE  = yes
    RGB_MATRIX_ENABLE = no
endif
