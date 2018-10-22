BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output on port C6

ifeq ("$(KEYBOARD)","vitamins_included")
  RGBLIGHT_ENABLE = no
else
  RGBLIGHT_ENABLE = yes
endif

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
