ifeq ($(strip $(CTPC)), yes)
    CONVERT_TO_PROTON_C=yes
endif
ifeq ($(strip $(CONVERT_TO_PROTON_C)), yes)
    CONVERT_TO=proton_c
endif

# TODO: opt in rather than assume everything uses a pro micro
PIN_COMPATIBLE ?= promicro
ifneq ($(CONVERT_TO),)
    # glob to search each platfrorm and/or check for valid converter
    CONVERTER := $(wildcard $(PLATFORM_PATH)/*/converters/$(PIN_COMPATIBLE)_to_$(CONVERT_TO)/)
    ifeq ($(CONVERTER),)
        $(call CATASTROPHIC_ERROR,Converting from '$(PIN_COMPATIBLE)' to '$(CONVERT_TO)' not possible!)
    endif

    TARGET := $(TARGET)_$(CONVERT_TO)

    # Configure any defaults
    OPT_DEFS += -DCONVERT_TO_$(strip $(shell echo $(CONVERT_TO) | tr '[:lower:]' '[:upper:]'))
    OPT_DEFS += -DCONVERTER_ENABLED
    VPATH += $(CONVERTER)

    # Finally run any converter specific logic
    include $(CONVERTER)/converter.mk
endif
