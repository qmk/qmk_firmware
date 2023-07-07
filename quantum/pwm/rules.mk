# Quantum PWM Configurables
QUANTUM_PWM_DRIVERS ?=

# The list of permissible drivers that can be listed in QUANTUM_PWM_DRIVERS
VALID_QUANTUM_PWM_DRIVERS := \
    integrated_pwm \
    software_pwm

#-------------------------------------------------------------------------------

OPT_DEFS += -DQUANTUM_PWM_ENABLE
COMMON_VPATH += $(QUANTUM_DIR)/pwm
SRC += \
    $(QUANTUM_DIR)/pwm/qpwm.c \
    $(QUANTUM_DIR)/pwm/qpwm_internal.c

# Handler for each driver
define handle_quantum_pwm_driver
    CURRENT_PWM_DRIVER := $1

    ifeq ($$(filter $$(strip $$(CURRENT_PWM_DRIVER)),$$(VALID_QUANTUM_PWM_DRIVERS)),)
        $$(error "$$(CURRENT_PWM_DRIVER)" is not a valid Quantum PWM driver)

    else ifeq ($$(strip $$(CURRENT_PWM_DRIVER)),integrated_pwm)
        QUANTUM_LIB_SRC += pwm.c
        OPT_DEFS += -DQUANTUM_PWM_INTEGRATED_PWM_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/pwm/integrated
        SRC += \
            $(DRIVER_PATH)/pwm/integrated/qpwm_integrated.c

    else ifeq ($$(strip $$(CURRENT_PWM_DRIVER)),software_pwm)
        OPT_DEFS += -DQUANTUM_PWM_SOFTWARE_PWM_ENABLE
        COMMON_VPATH += \
            $(DRIVER_PATH)/pwm/software
        SRC += \
            $(DRIVER_PATH)/pwm/software/qpwm_software.c
    endif
endef

# Iterate through the listed drivers for the build, including what's necessary
$(foreach qpwm_driver,$(QUANTUM_PWM_DRIVERS),$(eval $(call handle_quantum_pwm_driver,$(qpwm_driver))))
