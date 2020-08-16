SPLIT_TRANSPORT = custom

SRC += gotham.c \
       process_records.c

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE        = yes
endif

ifeq ($(COMBO_ENABLE), yes)
    SRC += $(USER_PATH)/combos.c
endif

ifneq ($(strip $(DISABLE_USERSPACE_OLED)), yes)
    KB_WITH_CUSTOM_OLED = $(or $(findstring KEYBOARD_crkbd_rev1,$(OPT_DEFS)))
    ifneq ($(KB_WITH_CUSTOM_OLED),)
        DISABLE_USERSPACE_OLED = yes
        OPT_DEFS += -DDISABLE_USERSPACE_OLED
        $(info Force-disabling userspace OLED code for this keyboard.)
    endif
endif

ifneq ($(strip $(DISABLE_USERSPACE_TRANSPORT)), yes)
    KB_WITH_CUSTOM_TRANSPORT = $(or $(findstring KEYBOARD_crkbd_rev1,$(OPT_DEFS)))
    ifneq ($(KB_WITH_CUSTOM_TRANSPORT),)
        DISABLE_USERSPACE_TRANSPORT = yes
        OPT_DEFS += -DDISABLE_USERSPACE_TRANSPORT
        $(info Force-disabling userspace transport code for this keyboard.)
    endif
endif

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    ifneq ($(strip $(DISABLE_USERSPACE_OLED)), yes)
        SRC += $(USER_PATH)/oled_utils.c
        ifeq ($(strip $(OLED_ANIMATIONS_ENABLE)), yes)
            OPT_DEFS += -DOLED_ANIMATIONS_ENABLE
            SRC += lib/lib8tion/lib8tion.c
            SRC += $(USER_PATH)/oled_animations/common.c
            SRC += $(USER_PATH)/oled_animations/starfield.c
            SRC += $(USER_PATH)/oled_animations/image_bounce.c
        endif
    else
        $(info Disabling userspace OLED code.)
    endif
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += $(USER_PATH)/encoder_utils.c
endif

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DTHUMBSTICK_ENABLE
    SRC += analog.c
    SRC += $(USER_PATH)/thumbstick.c
endif

ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
    SRC += $(USER_PATH)/pointing_devices.c
endif

ifeq ($(strip $(SPLIT_TRANSPORT)), custom)
    ifneq ($(strip $(DISABLE_USERSPACE_TRANSPORT)), yes)
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
    else
        $(info Disabling userspace transport code.)
    endif
endif
