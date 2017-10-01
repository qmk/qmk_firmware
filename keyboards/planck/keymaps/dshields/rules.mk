ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

MOUSEKEY_ENABLE  = yes # Mouse keys(+4700)
COMMAND_ENABLE   = yes # Commands for debug and configuration
CONSOLE_ENABLE   = yes # Console for debug(+400)
BACKLIGHT_ENABLE = yes # Enable keyboard backlight functionality
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
TAP_DANCE_ENABLE = yes 
AUDIO_ENABLE     = no
API_SYSEX_ENABLE = no
