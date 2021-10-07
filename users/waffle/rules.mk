BOOTMAGIC_ENABLE = yes # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
NRKO_ENABLE = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
LTO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
UNICODEMAP_ENABLE = yes
RANDICT = yes
VIA_ENABLE = yes

SRC +=  waffle.c \
	tapdance.c \
	combos.c \
	pru.c

ifeq ($(strip $(PIMORONI_TRACKBALL)), yes)
    POINTING_DEVICE_ENABLE := yes
    OPT_DEFS += -DPIMORONI_TRACKBALL
    SRC += drivers/sensors/pimoroni_trackball.c
    QUANTUM_LIB_SRC += i2c_master.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif

ifeq ($(strip $(RANDICT)), yes)
	OPT_DEFS += -DRANDICT
endif
