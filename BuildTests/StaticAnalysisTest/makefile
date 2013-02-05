#
#             LUFA Library
#     Copyright (C) Dean Camera, 2013.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Static anlysis of the entire LUFA source tree, using the free cross-platform "cppcheck" tool.

# Path to the LUFA library core
LUFA_PATH := ../../LUFA/

CPPCHECK_EXCLUDES := FATFs/            \
                     PetiteFATFs/      \
                     uip/

CPPCHECK_INCLUDES := $(patsubst %/,%,$(LUFA_PATH))/CodeTemplates/               \
                     $(patsubst %/,%,$(LUFA_PATH))/../Projects/AVRISP-MKII/

CPPCHECK_FLAGS    := -U TEMPLATE_FUNC_NAME -U __GNUC__ -U __DOXYGEN__

CPPCHECK_SUPPRESS := variableScope missingInclude unusedFunction

SRC               := $(patsubst %/,%,$(LUFA_PATH))/..

# Build test cannot be run with multiple parallel jobs
.NOTPARALLEL:

all: begin cppcheck end

begin:
	@echo Executing build test "StaticAnalysisTest".
	@echo

end:
	@echo Build test "StaticAnalysisTest" complete.
	@echo

%:
	

.PHONY: all begin end

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk