SRC += greatwizard.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dances.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += underglow.c
endif

ifeq ($(strip $(LAYER_GAME)), yes)
    SRC += game.c
endif

ifeq ($(strip $(LAYER_GIT)), yes)
    SRC += git.c
endif

ifeq ($(strip $(LAYERS_ORTHO)), yes)
    SRC += ortho.c
endif

ifeq ($(strip $(LAYERS_PROGRAMMER)), yes)
    SRC += programmer.c
endif

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE = yes               # Enable link time optimization
endif

AUTO_SHIFT_ENABLE = yes            # Autoshift by holding down a key
