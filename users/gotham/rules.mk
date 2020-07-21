SRC += gotham.c \
	   process_records.c

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE        = yes
endif

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
	SRC += $(USER_PATH)/oled_utils.c
	ifeq ($(strip $(OLED_ANIMATIONS_ENABLE)), yes)
		OPT_DEFS += -DOLED_ANIMATIONS_ENABLE
		SRC += lib/lib8tion/lib8tion.c
		SRC += $(USER_PATH)/oled_animations/common.c
		SRC += $(USER_PATH)/oled_animations/starfield.c
		SRC += $(USER_PATH)/oled_animations/image_bounce.c
	endif
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
	SRC += $(USER_PATH)/encoder_utils.c
endif

ifeq ($(strip $(SPLIT_TRANSPORT)), custom)
	OPT_DEFS += -DCUSTOM_TRANSPORT
	QUANTUM_SRC += $(USER_PATH)/transport_custom.c
	ifeq ($(PLATFORM),AVR)
		QUANTUM_LIB_SRC += i2c_master.c \
							i2c_slave.c
	endif
	SERIAL_DRIVER ?= bitbang
	ifeq ($(strip $(SERIAL_DRIVER)), bitbang)
		QUANTUM_LIB_SRC += serial.c
	else
		QUANTUM_LIB_SRC += serial_$(strip $(SERIAL_DRIVER)).c
	endif
endif
