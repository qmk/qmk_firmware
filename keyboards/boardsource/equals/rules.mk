WS2812_DRIVER = vendor
AUDIO_DRIVER = pwm_hardware
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7735_spi
ifeq ($(strip $(QUANTUM_PAINTER_ENABLE)), yes)
SRC += ui.c
endif
