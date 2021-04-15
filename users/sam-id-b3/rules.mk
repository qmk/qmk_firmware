WPM_ENABLE = yes # Enable words per minute counting

SRC += sam-id-b3.c
SRC += process_records.c

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    SRC += oled_stuff.c
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += encoder_stuff.c
endif

ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    SRC += pimoroni_trackball.c
endif