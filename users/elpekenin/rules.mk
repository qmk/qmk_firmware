VPATH += $(USER_PATH)/eeprom \
         $(USER_PATH)/painter \
         $(USER_PATH)/painter/images \
         $(USER_PATH)/painter/fonts \
         $(USER_PATH)/registers \
         $(USER_PATH)/rgb \
         $(USER_PATH)/spi \
         $(USER_PATH)/touch

TRI_LAYER_ENABLE = yes

# custom keycodes and processing logic
SRC += user_processing.c

# tap dances
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += user_tapdances.c
endif

# check if QP is enabled
ifeq ($(strip $(QUANTUM_PAINTER_ENABLE)), yes)
    # current path (userspace's rules.mk file)
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))

    # include all fonts/images to the compilation
    SRC += $(shell find $(dir $(mkfile_path))/painter/images -name "*.c")
    SRC += $(shell find $(dir $(mkfile_path))/painter/fonts -name "*.c")

    # defines `load_qp_resources` to load them into RAM
    SRC += graphics.c

    # if XAP is also enabled
    ifeq ($(strip $(XAP_ENABLE)), yes)
        # unless user told otherwise, QP over XAP is enabled
        QP_XAP ?= yes
    endif
endif

# ===========================
# ===== Custom features =====
# ===========================
CUSTOM_EEPROM ?= no
ifeq ($(strip $(CUSTOM_EEPROM)), yes)
    OPT_DEFS += -DCUSTOM_EEPROM_ENABLE
    SRC += custom_eeprom.c
endif

ONE_HAND ?= no
ifeq ($(strip $(ONE_HAND)), yes)
    OPT_DEFS += -DONE_HAND_ENABLE
endif

TOUCH_SCREEN ?= no
ifeq ($(strip $(TOUCH_SCREEN)), yes)
    QUANTUM_LIB_SRC += spi_master.c
    OPT_DEFS += -DTOUCH_SCREEN_ENABLE
    SRC += touch_driver.c
endif

QP_XAP ?= no
# include QP over XAP handlers
ifeq ($(strip $(QP_XAP)), yes)
    OPT_DEFS += -DQP_XAP_ENABLE
    SRC += qp_over_xap.c
endif

SIPO_PINS ?= no
ifeq ($(strip $(SIPO_PINS)), yes)
    OPT_DEFS += -DSIPO_PINS_ENABLE
    SRC += sipo_pins.c

    # needs a second SPI driver to work, currently not supported on QMK
    SRC += custom_spi_master.c

    ifeq ($(strip $(TOUCH_SCREEN)), yes)
        SRC += touch_sipo.c
    endif

    ifeq ($(strip $(QUANTUM_PAINTER_ENABLE)), yes)
        SRC += qp_comms_sipo.c
    endif
endif

$(info --- Custom features ---)
$(info CUSTOM_EEPROM = $(CUSTOM_EEPROM))
$(info ONE_HAND      = $(ONE_HAND))
$(info SIPO_PINS     = $(SIPO_PINS))
$(info TOUCH_SCREEN  = $(TOUCH_SCREEN))
$(info QP_XAP        = $(QP_XAP))
$(info -----------------------)
$(info )
