# Note for new boards -- CTPC and CONVERT_TO_PROTON_C are deprecated terms
# and should not be replicated for new boards. These will be removed from
# documentation as well as existing keymaps in due course.
ifneq ($(findstring yes, $(CTPC)$(CONVERT_TO_PROTON_C)),)
$(call CATASTROPHIC_ERROR,The `CONVERT_TO_PROTON_C` and `CTPC` options are now deprecated. `CONVERT_TO=proton_c` should be used instead.)
endif

# TODO: opt in rather than assume everything uses a pro micro
PIN_COMPATIBLE ?= promicro
ifneq ($(CONVERT_TO),)
    # stash so we can overwrite env provided vars if needed
    ACTIVE_CONVERTER=$(CONVERT_TO)

    # glob to search each platfrorm and/or check for valid converter
    CONVERTER := $(wildcard $(PLATFORM_PATH)/*/converters/$(PIN_COMPATIBLE)_to_$(CONVERT_TO)/)
    ifeq ($(CONVERTER),)
        $(call CATASTROPHIC_ERROR,Converting from '$(PIN_COMPATIBLE)' to '$(CONVERT_TO)' not possible!)
    endif

    -include $(CONVERTER)/pre_converter.mk

    PLATFORM_KEY = $(shell echo $(CONVERTER) | cut -d "/" -f2)
    TARGET := $(TARGET)_$(CONVERT_TO)

    # Configure any defaults
    OPT_DEFS += -DCONVERT_TO_$(strip $(shell echo $(CONVERT_TO) | tr '[:lower:]' '[:upper:]'))
    OPT_DEFS += -DCONVERTER_TARGET=\"$(strip $(CONVERT_TO))\"
    OPT_DEFS += -DCONVERTER_ENABLED
    VPATH += $(CONVERTER)

    # Configure for "alias" - worst case it produces an idential define
    OPT_DEFS += -DCONVERT_TO_$(strip $(shell echo $(ACTIVE_CONVERTER) | tr '[:lower:]' '[:upper:]'))

    # Finally run any converter specific logic
    include $(CONVERTER)/converter.mk
endif
