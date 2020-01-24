SRC += csc027.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += custom_rgb.c
    SRC += usb_led.c
endif

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += custom_audio.c
    SRC += usb_led.c
endif
