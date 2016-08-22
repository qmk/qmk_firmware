ifndef VERBOSE
.SILENT:
endif

.DEFAULT_GOAL := all

include common.mk

TARGET=test/$(TEST)

GTEST_OUTPUT = $(BUILD_DIR)/gtest

OUTPUTS := $(GTEST_OUTPUT)

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

VPATH +=\
	$(LIB_PATH)/googletest\
	$(LIB_PATH)/googlemock

all: elf

include $(TMK_PATH)/native.mk
include $(TMK_PATH)/rules.mk

$(shell mkdir $(BUILD_DIR)/test 2>/dev/null)

