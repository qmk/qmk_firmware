BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output on port C6

ifeq ("$(KEYBOARD)","vitamins_included")
  RGBLIGHT_ENABLE = yes
else
  RGBLIGHT_ENABLE = no
endif

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
