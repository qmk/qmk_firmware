# Pointing Device Configurables
POINTING_DEVICE_DRIVERS ?=

# The list of permissible drivers that can be listed in POINTING_DEVICE_DRIVERS
VALID_POINTING_DEVICE_DRIVER_TYPES := adns5050 adns9800 analog_joystick azoteq_iqs5xx cirque_pinnacle_i2c cirque_pinnacle_spi paw3204 pmw3320 pmw3360 pmw3389 pimoroni_trackball custom

OPT_DEFS += -DPOINTING_DEVICE_ENABLE
MOUSE_ENABLE := yes
VPATH += $(QUANTUM_DIR)/pointing_device
SRC += $(QUANTUM_DIR)/pointing_device/pointing_device.c
SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_auto_mouse.c

# Comms flags
POINTING_DEVICE_NEEDS_COMMS_I2C ?= no
POINTING_DEVICE_NEEDS_COMMS_SPI ?= no

# Handler for each driver
define handle_pointing_device_drivers
	CURRENT_POINTING_DEVICE_DRIVER := $1

	ifeq ($$(filter $$(strip $$(CURRENT_POINTING_DEVICE_DRIVER)),$$(VALID_POINTING_DEVICE_DRIVERS)),)
        $$(error "$$(CURRENT_POINTING_DEVICE_DRIVER)" is not a valid pointing driver)

	else ifneq ($$(strip $$(CURRENT_POINTING_DEVICE_DRIVER)), custom)
			SRC += $(DRIVER_PATH)/sensors/$$(strip $$(CURRENT_POINTING_DEVICE_DRIVER)).c
			OPT_DEFS += -DPOINTING_DEVICE_DRIVER_$$(strip $$(shell echo $$(CURRENT_POINTING_DEVICE_DRIVER) | tr '[:lower:]' '[:upper:]'))
	endif
	OPT_DEFS += -DPOINTING_DEVICE_DRIVER_$(strip $(CURRENT_POINTING_DEVICE_DRIVER))
	ifeq ($$(strip $$(CURRENT_POINTING_DEVICE_DRIVER)), adns9800)
		POINTING_DEVICE_NEEDS_COMMS_SPI := yes
	else ifeq ($$(strip $$(CURRENT_POINTING_DEVICE_DRIVER)), analog_joystick)
		OPT_DEFS += -DSTM32_ADC -DHAL_USE_ADC=TRUE
		LIB_SRC += analog.c
	else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), azoteq_iqs5xx)
        I2C_DRIVER_REQUIRED = yes
	else ifeq ($$(strip $$(CURRENT_POINTING_DEVICE_DRIVER)), cirque_pinnacle_i2c)
		POINTING_DEVICE_NEEDS_COMMS_I2C := yes
		SRC += $(DRIVER_PATH)/sensors/cirque_pinnacle.c
		SRC += $(DRIVER_PATH)/sensors/cirque_pinnacle_gestures.c
		SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_gestures.c
	else ifeq ($$(strip $$(CURRENT_POINTING_DEVICE_DRIVER)), cirque_pinnacle_spi)
		POINTING_DEVICE_NEEDS_COMMS_SPI := yes
		SRC += $(DRIVER_PATH)/sensors/cirque_pinnacle.c
		SRC += $(DRIVER_PATH)/sensors/cirque_pinnacle_gestures.c
		SRC += $(QUANTUM_DIR)/pointing_device/pointing_device_gestures.c
	else ifeq ($$(strip $$(CURRENT_POINTING_DEVICE_DRIVER)), pimoroni_trackball)
		POINTING_DEVICE_NEEDS_COMMS_I2C := yes
	else ifneq ($$(filter $$(strip $$(CURRENT_POINTING_DEVICE_DRIVER)),pmw3360 pmw3389),)
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
