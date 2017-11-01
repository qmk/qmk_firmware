ifndef VERBOSE
.SILENT:
endif

.DEFAULT_GOAL := all

include common.mk

TARGET=test/$(TEST)

GTEST_OUTPUT = $(BUILD_DIR)/gtest

TEST_OBJ = $(BUILD_DIR)/test_obj

OUTPUTS := $(TEST_OBJ)/$(TEST) $(GTEST_OUTPUT)

GTEST_INC := \
	$(LIB_PATH)/googletest/googletest/include\
	$(LIB_PATH)/googletest/googlemock/include\
	
GTEST_INTERNAL_INC :=\
	$(LIB_PATH)/googletest/googletest\
	$(LIB_PATH)/googletest/googlemock

$(GTEST_OUTPUT)_SRC :=\
	googletest/src/gtest-all.cc\
	googletest/src/gtest_main.cc\
	googlemock/src/gmock-all.cc

$(GTEST_OUTPUT)_DEFS := 
$(GTEST_OUTPUT)_INC := $(GTEST_INC) $(GTEST_INTERNAL_INC)

LDFLAGS += -lstdc++ -lpthread -shared-libgcc
CREATE_MAP := no

VPATH +=\
	$(LIB_PATH)/googletest\
	$(LIB_PATH)/googlemock

all: elf

VPATH += $(COMMON_VPATH)

include $(TMK_PATH)/common.mk
include $(QUANTUM_PATH)/serial_link/tests/rules.mk

$(TEST_OBJ)/$(TEST)_SRC := $($(TEST)_SRC)
$(TEST_OBJ)/$(TEST)_INC := $($(TEST)_INC) $(VPATH) $(GTEST_INC)
$(TEST_OBJ)/$(TEST)_DEFS := $($(TEST)_DEFS)

include $(TMK_PATH)/native.mk
include $(TMK_PATH)/rules.mk


$(shell mkdir -p $(BUILD_DIR)/test 2>/dev/null)
$(shell mkdir -p $(TEST_OBJ) 2>/dev/null)

