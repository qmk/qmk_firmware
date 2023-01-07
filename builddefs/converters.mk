# Note for new boards -- CTPC and CONVERT_TO_PROTON_C are deprecated terms
# and should not be replicated for new boards. These will be removed from
# documentation as well as existing keymaps in due course.
ifeq ($(strip $(CTPC)), yes)
    CONVERT_TO_PROTON_C=yes
endif
ifeq ($(strip $(CONVERT_TO_PROTON_C)), yes)
    CONVERT_TO=proton_c

cpfirmware: ctpc_warning
.INTERMEDIATE: ctpc_warning
ctpc_warning: elf
	$(info @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@)
	$(info The `CONVERT_TO_PROTON_C` and `CTPC` options are soon to be deprecated.)
	$(info Boards should be changed to use `CONVERT_TO=proton_c` instead.)
	$(info @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@)
endif

# TODO: opt in rather than assume everything uses a pro micro
PIN_COMPATIBLE ?= promicro
ifneq ($(CONVERT_TO),)
    CONVERTER_GEN=$(shell $(QMK_BIN) generate-converter-mk --quiet --pin-compatible $(PIN_COMPATIBLE) --converter $(CONVERT_TO) --output $(KEYBOARD_OUTPUT)/src/converter.mk)
    -include $(CONVERTER_GEN)

    ifeq ($(CONVERTER_PATH),)
        $(call CATASTROPHIC_ERROR,Converting from '$(PIN_COMPATIBLE)' to '$(CONVERT_TO)' not possible!)
    endif

    TARGET := $(TARGET)_$(CONVERT_TO)

    # Configure any defaults
    OPT_DEFS += -DCONVERT_TO_$(strip $(shell echo $(CONVERT_TO) | tr '[:lower:]' '[:upper:]'))
    OPT_DEFS += -DCONVERTER_TARGET=\"$(strip $(CONVERT_TO))\"
    OPT_DEFS += -DCONVERTER_ENABLED
    VPATH += $(CONVERTER_PATH)

    # and defaults if alias used
    ifneq ($(CONVERTER_ACTIVE),$(CONVERT_TO))
    OPT_DEFS += -DCONVERT_TO_$(strip $(shell echo $(CONVERTER_ACTIVE) | tr '[:lower:]' '[:upper:]'))
    endif

    # Finally run any converter specific logic
    include $(CONVERTER_PATH)/converter.mk
endif
