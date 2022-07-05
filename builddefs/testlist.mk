TEST_LIST = $(sort $(patsubst %/test.mk,%, $(shell find $(ROOT_DIR)tests -type f -name test.mk)))
FULL_TESTS := $(notdir $(TEST_LIST))

include $(QUANTUM_PATH)/debounce/tests/testlist.mk
include $(QUANTUM_PATH)/sequencer/tests/testlist.mk
include $(PLATFORM_PATH)/test/testlist.mk

define VALIDATE_TEST_LIST
    ifneq ($1,)
        ifeq ($$(findstring -,$1),-)
            $$(call CATASTROPHIC_ERROR,Invalid test name,Test names can't contain '-', but '$1' does.)
        else
            $$(eval $$(call VALIDATE_TEST_LIST,$$(firstword $2),$$(wordlist 2,9999,$2)))
        endif
    endif
endef


$(eval $(call VALIDATE_TEST_LIST,$(firstword $(TEST_LIST)),$(wordlist 2,9999,$(TEST_LIST))))
