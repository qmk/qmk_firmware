TEST_LIST = $(notdir $(patsubst %/rules.mk,%,$(wildcard $(ROOT_DIR)/tests/*/rules.mk)))
FULL_TESTS := $(TEST_LIST)

include $(ROOT_DIR)/quantum/sequencer/tests/testlist.mk
include $(ROOT_DIR)/quantum/serial_link/tests/testlist.mk

define VALIDATE_TEST_LIST
    ifneq ($1,)
        ifeq ($$(findstring -,$1),-)
            $$(error Test names can't contain '-', but '$1' does)
        else
            $$(eval $$(call VALIDATE_TEST_LIST,$$(firstword $2),$$(wordlist 2,9999,$2)))
        endif
    endif
endef


$(eval $(call VALIDATE_TEST_LIST,$(firstword $(TEST_LIST)),$(wordlist 2,9999,$(TEST_LIST))))
