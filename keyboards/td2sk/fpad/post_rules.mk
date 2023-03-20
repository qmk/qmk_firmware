ifeq ($(strip $(ENCODER_ENABLE)), yes)
	ENCODER_ENABLE = no
	OPT_DEFS += -DENCODER_ENABLE
	SRC += encoder.c drivers/xl9555.c
	QUANTUM_LIB_SRC += i2c_master.c
	ifeq ($(strip $(ENCODER_MAP_ENABLE)), yes)
		OPT_DEFS += -DENCODER_MAP_ENABLE
	endif
endif

ifeq ($(strip $(JOYSTICK_ENABLE)), yes)
	JOYSTICK_DRIVER = analog
	SRC += analog.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	RGB_MATRIX_DRIVER = custom
	SRC += ws2812.c drivers/is31fl3208.c drivers/xl9555.c
	QUANTUM_LIB_SRC += i2c_master.c
endif
