MOUSEKEY_ENABLE = yes    # Mouse keys
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes
WPM_ENABLE 			= yes					# Enable word per minute counter
LTO_ENABLE 			= yes					# Makes hex file smaller
OLED_DRIVER_ENABLE = yes	# Enable OLEDs
MIDI_ENABLE = yes           # Enable Midi!

AUDIO_ENABLE = no
ENCODER_ENABLE = no


ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    #... your code here...
    ifdef OCEAN_DREAM_ENABLE
        ifeq ($(strip $(OCEAN_DREAM_ENABLE)), yes)
            SRC += ocean_dream.c
            OPT_DEFS += -DOCEAN_DREAM_ENABLE
        endif
    endif
    ifndef OCEAN_DREAM_ENABLE
        SRC += ocean_dream.c
        OPT_DEFS += -DOCEAN_DREAM_ENABLE
    endif
endif
