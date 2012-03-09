#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Static anlysis of the entire LUFA source tree, using the free cross-platform "cppcheck" tool.

# Path to the root of the LUFA tree to scan
LUFA_ROOT_PATH    = ../..

# Filenames or directories (including fragments) to exclude from the analysis
EXCLUDE_LIST      = FATFs/            \
                    PetiteFATFs/      \
                    uip/

# Output message template for found warnings and errors
MESSAGE_TEMPLATE  = "{file}:{line}: {severity} ({id}): {message}"

# Checks to suppress so that generated warnings are discarded
SUPPRESS_WARNINGS = variableScope     \
                    unusedFunction    \
                    missingInclude

# Extra paths to search for include files
INCLUDE_PATHS     = $(LUFA_ROOT_PATH)/LUFA/CodeTemplates/


all: begin staticcheck end

begin:
	@echo Executing build test "StaticAnalysisTest".
	@echo

end:
	@echo Build test "StaticAnalysisTest" complete.
	@echo

staticcheck:
	cppcheck --quiet --inline-suppr --check-config --template=$(MESSAGE_TEMPLATE) $(INCLUDE_PATHS:%=-I%) $(EXCLUDE_LIST:%=-i%) $(LUFA_ROOT_PATH)
	cppcheck --quiet --inline-suppr --error-exitcode=1 --std=c99 --force --enable=all --inconclusive $(SUPPRESS_WARNINGS:%=--suppress=%) --template=$(MESSAGE_TEMPLATE) $(INCLUDE_PATHS:%=-I%) $(EXCLUDE_LIST:%=-i%) $(LUFA_ROOT_PATH)

%:
	