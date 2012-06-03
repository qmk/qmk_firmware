#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Static anlysis of the entire LUFA source tree, using the free cross-platform "cppcheck" tool.

LUFA_ROOT_PATH = ../..

CPPCHECK_EXCLUDES = FATFs/            \
                    PetiteFATFs/      \
                    uip/
CPPCHECK_INCLUDES = $(LUFA_ROOT_PATH)/LUFA/CodeTemplates/   \
                    $(LUFA_ROOT_PATH)/Projects/AVRISP-MKII/
CPPCHECK_PATH     = $(LUFA_ROOT_PATH)

all: begin cppcheck-config cppcheck end

begin:
	@echo Executing build test "StaticAnalysisTest".
	@echo

end:
	@echo Build test "StaticAnalysisTest" complete.
	@echo

%:

.PHONY: all begin end

# Include LUFA build script makefiles
include $(LUFA_ROOT_PATH)/LUFA/Build/lufa.core.in
include $(LUFA_ROOT_PATH)/LUFA/Build/lufa.cppcheck.in