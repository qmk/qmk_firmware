BOOTMAGIC_ENABLE = yes # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes # Audio control and System control
MOUSEKEY_ENABLE = yes # Mouse keys
NRKO_ENABLE = yes # USB Nkey Rollover
CONSOLE_ENABLE = no # Console for debug
COMMAND_ENABLE = no # Commands for debug and configuration
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
LTO_ENABLE = yes
UNICODEMAP_ENABLE = yes
RANDICT = yes
VIA_ENABLE = yes

# User specific files
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
