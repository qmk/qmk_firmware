BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no
AUDIO_ENABLE = no
BLUETOOTH_ENABLE = no

# Planck light
ifneq (,$(findstring planck/light,$(KEYBOARD)))
    AUDIO_ENABLE = yes
    RGB_MATRIX_ENABLE = yes
endif

# Planck rev6
# 	No daughterboard yet, so no rgbmatrix
ifneq (,$(findstring planck/rev6,$(KEYBOARD)))
    AUDIO_ENABLE = yes
#    RGBLIGHT_ENABLE = yes
endif

# Planck rev4
# 	Audio + rgblight too big.
ifneq (,$(findstring planck/rev4,$(KEYBOARD)))
    BACKLIGHT_ENABLE = yes
    RGBLIGHT_ENABLE = yes
endif

ifndef QUANTUM_DIR
    include ../../../../Makefile
endif
