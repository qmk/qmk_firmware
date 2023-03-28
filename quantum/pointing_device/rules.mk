# Pointing Device Configurables
POINTING_DEVICE_DRIVERS ?=

# The list of permissible drivers that can be listed in POINTING_DEVICE_DRIVERS
VALID_POINTING_DEVICE_DRIVERS := adns5050 adns9800 analog_joystick azoteq_iqs5xx cirque_pinnacle_i2c cirque_pinnacle_spi paw3204 pmw3360 pmw3389 pimoroni_trackball custom_i2c custom_spi

OPT_DEFS += -DPOINTING_DEVICE_ENABLE
MOUSE_ENABLE := yes
COMMON_VPATH += $(QUANTUM_DIR)/pointing_device
COMMON_VPATH += $(DRIVER_PATH)/sensors
SRC += $(QUANTUM_DIR)/pointing_device/pointing_device.c
SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_auto_mouse.c

# Comms flags
POINTING_DEVICE_NEEDS_COMMS_I2C ?= no
POINTING_DEVICE_NEEDS_COMMS_SPI ?= no

# Handler for each driver
define handle_pointing_device_drivers
    CURRENT_POINTING_DEVICE_DRIVER := $1

    ifeq ($$(filter $$(strip $1),$$(VALID_POINTING_DEVICE_DRIVERS)),)
        $$(error "$1" is not a valid pointing driver)
    else
        ifeq ($$(filter $$(strip $1), custom_i2c custom_spi),)
            SRC += $(DRIVER_PATH)/sensors/$$(strip $1).c
            OPT_DEFS += -DPOINTING_DEVICE_DRIVER_$$(strip $$(shell echo $1 | tr '[:lower:]' '[:upper:]'))
        endif
    endif

    ifeq ($$(strip $1),adns9800)
        POINTING_DEVICE_NEEDS_COMMS_SPI := yes
    else ifeq ($$(strip $1),analog_joystick)
        OPT_DEFS += -DSTM32_ADC -DHAL_USE_ADC=TRUE
        LIB_SRC += analog.c
    else ifeq ($$(strip $1),cirque_pinnacle_i2c)
        POINTING_DEVICE_NEEDS_COMMS_I2C := yes
        SRC += $(DRIVER_PATH)/sensors/cirque_pinnacle.c
        SRC += $(DRIVER_PATH)/sensors/cirque_pinnacle_gestures.c
        SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_gestures.c
    else ifeq ($$(strip $1),cirque_pinnacle_spi)
        POINTING_DEVICE_NEEDS_COMMS_SPI := yes
        SRC += $(DRIVER_PATH)/sensors/cirque_pinnacle.c
        SRC += $(DRIVER_PATH)/sensors/cirque_pinnacle_gestures.c
        SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_gestures.c
    else ifeq ($$(strip $1),pimoroni_trackball)
        POINTING_DEVICE_NEEDS_COMMS_I2C := yes
    else ifeq ($$(strip $1),azoteq_iqs5xx)
        POINTING_DEVICE_NEEDS_COMMS_I2C := yes
    else ifeq ($$(strip $1),custom_i2c)
        POINTING_DEVICE_NEEDS_COMMS_I2C := yes
    else ifeq ($$(strip $1),custom_spi)
        POINTING_DEVICE_NEEDS_COMMS_SPI := yes
    else ifneq ($$(filter $$(strip $1),pmw3360 pmw3389),)
        POINTING_DEVICE_NEEDS_COMMS_SPI := yes
        SRC += $(DRIVER_PATH)/sensors/pmw33xx_common.c
    endif

endef

# Iterate through the listed drivers for the build, including what's necessary
$(foreach pd_driver,$(POINTING_DEVICE_DRIVERS),$(eval $(call handle_pointing_device_drivers,$(pd_driver))))

# If SPI comms is needed, set up the required files
ifeq ($(strip $(POINTING_DEVICE_NEEDS_COMMS_SPI)), yes)
    OPT_DEFS += -DSTM32_SPI -DHAL_USE_SPI=TRUE
    QUANTUM_LIB_SRC += spi_master.c
endif

# If I2C comms is needed, set up the required files
ifeq ($(strip $(POINTING_DEVICE_NEEDS_COMMS_I2C)), yes)
    OPT_DEFS += -DSTM32_SPI -DHAL_USE_I2C=TRUE
    QUANTUM_LIB_SRC += i2c_master.c
endif
