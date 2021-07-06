# Reduce firmware size
# 	https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
# also requires in config.h
#	NO_ACTION_MACRO
#	NO_ACTION_FUNCTION
EXTRAFLAGS += -flto

SRC += muppetjones.c
SRC += ./features/casemodes.c

ifdef ENCODER_ENABLE
	SRC += ./features/etchamouse.c
endif

ifdef TAP_DANCE_ENABLE
	SRC += ./features/dancelayers.c
endif
