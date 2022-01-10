# Quantum Painter Configurables
QUANTUM_PAINTER_DRIVERS ?=

# The list of permissible drivers that can be listed in QUANTUM_PAINTER_DRIVERS
VALID_QUANTUM_PAINTER_DRIVERS :=

#-------------------------------------------------------------------------------

OPT_DEFS += -DQUANTUM_PAINTER_ENABLE
COMMON_VPATH += $(QUANTUM_DIR)/painter
SRC += \
    $(QUANTUM_DIR)/utf8.c \
    $(QUANTUM_DIR)/color.c \
    $(QUANTUM_DIR)/painter/qp.c \
    $(QUANTUM_DIR)/painter/qp_stream.c


# Comms flags
QUANTUM_PAINTER_NEEDS_COMMS_SPI ?= no

# Handler for each driver
define handle_quantum_painter_driver
    CURRENT_PAINTER_DRIVER := $1

    ifeq ($$(filter $$(strip $$(CURRENT_PAINTER_DRIVER)),$$(VALID_QUANTUM_PAINTER_DRIVERS)),)
        $$(error "$$(CURRENT_PAINTER_DRIVER)" is not a valid Quantum Painter driver)

    endif
endef

# Iterate through the listed drivers for the build, including what's necessary
$(foreach qp_driver,$(QUANTUM_PAINTER_DRIVERS),$(eval $(call handle_quantum_painter_driver,$(qp_driver))))

# If SPI comms is needed, set up the required files
ifeq ($(strip $(QUANTUM_PAINTER_NEEDS_COMMS_SPI)), yes)
    OPT_DEFS += -DQUANTUM_PAINTER_SPI_ENABLE
    QUANTUM_LIB_SRC += spi_master.c
    VPATH += $(DRIVER_PATH)/painter/comms
    SRC += \
        $(QUANTUM_DIR)/painter/qp_comms.c \
        $(DRIVER_PATH)/painter/comms/qp_comms_spi.c

    ifeq ($(strip $(QUANTUM_PAINTER_NEEDS_COMMS_SPI_DC_RESET)), yes)
        OPT_DEFS += -DQUANTUM_PAINTER_SPI_DC_RESET_ENABLE
    endif
endif

