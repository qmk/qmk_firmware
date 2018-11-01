ifndef QUANTUM_DIR
  include ../../../../Makefile
endif

USER_NAME := bbaserdem-nouserspace

STENO_ENABLE = no      # Additional protocols for Stenography(+1700), requires VIRTSER
MOUSEKEY_ENABLE = no   # Mouse keys(+4700)
EXTRAKEY_ENABLE = no   # Audio control and System control(+450)
CONSOLE_ENABLE = no    # Console for debug(+400)
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
AUDIO_ENABLE = no 	   # Enable audio output from keyboard

NKRO_ENABLE = yes      # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes  # Enable RBG light strips
BACKLIGHT_ENABLE = yes # Enable keyboard backlight functionality
