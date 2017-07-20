#
#            DMBS Build System
#     Released into the public domain.
#
#  dean [at] fourwalledcubicle [dot] com
#        www.fourwalledcubicle.com
#

DMBS_BUILD_MODULES         += CPPCHECK
DMBS_BUILD_TARGETS         += cppcheck cppcheck-config
DMBS_BUILD_MANDATORY_VARS  += SRC
DMBS_BUILD_OPTIONAL_VARS   += CPPCHECK_INCLUDES CPPCHECK_EXCLUDES CPPCHECK_MSG_TEMPLATE CPPCHECK_ENABLE \
                              CPPCHECK_SUPPRESS CPPCHECK_FAIL_ON_WARNING CPPCHECK_QUIET CPPCHECK_FLAGS
DMBS_BUILD_PROVIDED_VARS   +=
DMBS_BUILD_PROVIDED_MACROS +=

# Conditionally import the CORE module of DMBS if it is not already imported
DMBS_MODULE_PATH := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
ifeq ($(findstring CORE, $(DMBS_BUILD_MODULES)),)
  include $(DMBS_MODULE_PATH)/core.mk
endif

# Default values of optionally user-supplied variables
CPPCHECK_INCLUDES            ?=
CPPCHECK_EXCLUDES            ?=
CPPCHECK_MSG_TEMPLATE        ?= {file}:{line}: {severity} ({id}): {message}
CPPCHECK_ENABLE              ?= all
CPPCHECK_SUPPRESS            ?= variableScope missingInclude
CPPCHECK_FAIL_ON_WARNING     ?= Y
CPPCHECK_QUIET               ?= Y
CPPCHECK_FLAGS               ?=

# Sanity check user supplied values
$(foreach MANDATORY_VAR, $(DMBS_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
$(call ERROR_IF_EMPTY, SRC)
$(call ERROR_IF_EMPTY, CPPCHECK_MSG_TEMPLATE)
$(call ERROR_IF_EMPTY, CPPCHECK_ENABLE)
$(call ERROR_IF_NONBOOL, CPPCHECK_FAIL_ON_WARNING)
$(call ERROR_IF_NONBOOL, CPPCHECK_QUIET)

# Build a default argument list for cppcheck
BASE_CPPCHECK_FLAGS := --template="$(CPPCHECK_MSG_TEMPLATE)" $(CPPCHECK_INCLUDES:%=-I%) $(CPPCHECK_EXCLUDES:%=-i%) --inline-suppr --force --std=c99

# Sanity check parameters and construct additional command line arguments to cppcheck
ifeq ($(CPPCHECK_FAIL_ON_WARNING), Y)
   BASE_CPPCHECK_FLAGS += --error-exitcode=1
endif
ifeq ($(CPPCHECK_QUIET), Y)
   BASE_CPPCHECK_FLAGS += --quiet
endif

# Output Messages
MSG_CPPCHECK_CMD         := ' [CPPCHECK]:'

# Checks the CPPCheck configuration as used in the user project, to determine if any paths are missing or invalid
cppcheck-config: $(MAKEFILE_LIST)
	@echo $(MSG_CPPCHECK_CMD) Checking cppcheck configuration check on source files
	cppcheck $(BASE_CPPCHECK_FLAGS) --check-config $(CPPCHECK_FLAGS) $(SRC)

# Runs a static analysis using CPPCheck to determine if there are any issues
cppcheck: $(MAKEFILE_LIST)
	@echo $(MSG_CPPCHECK_CMD) Performing static analysis on source files
	cppcheck $(BASE_CPPCHECK_FLAGS) --enable=$(CPPCHECK_ENABLE) $(CPPCHECK_SUPPRESS:%=--suppress=%) $(CPPCHECK_FLAGS) $(SRC)

# Phony build targets for this module
.PHONY: $(DMBS_BUILD_TARGETS)
