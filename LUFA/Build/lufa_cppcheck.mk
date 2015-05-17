#
#             LUFA Library
#     Copyright (C) Dean Camera, 2015.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

LUFA_BUILD_MODULES         += CPPCHECK
LUFA_BUILD_TARGETS         += cppcheck cppcheck-config
LUFA_BUILD_MANDATORY_VARS  += SRC
LUFA_BUILD_OPTIONAL_VARS   += CPPCHECK_INCLUDES CPPCHECK_EXCLUDES CPPCHECK_MSG_TEMPLATE CPPCHECK_ENABLE \
                              CPPCHECK_SUPPRESS CPPCHECK_FAIL_ON_WARNING CPPCHECK_QUIET CPPCHECK_FLAGS
LUFA_BUILD_PROVIDED_VARS   +=
LUFA_BUILD_PROVIDED_MACROS +=

# -----------------------------------------------------------------------------
#                LUFA CPPCheck Buildsystem Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Provides a set of targets to scan a project with the free "cppcheck" static
#   analysis tool, to check for code errors at runtime
#   (see http://cppcheck.sourceforge.net).
# -----------------------------------------------------------------------------
# TARGETS:
#
#    cppcheck                  - Scan the project with CPPCheck
#    cppcheck-config           - Use CPPCheck to look for missing include files
#
# MANDATORY PARAMETERS:
#
#    SRC                       - List of source files to statically analyze
#
# OPTIONAL PARAMETERS:
#
#    CPPCHECK_INCLUDES         - Extra include paths to search for missing
#                                header files
#    CPPCHECK_EXCLUDES         - Source file paths to exclude checking (can be
#                                a path fragment if desired)
#    CPPCHECK_MSG_TEMPLATE     - Template for cppcheck error and warning output
#    CPPCHECK_ENABLE           - General cppcheck category checks to enable
#    CPPCHECK_SUPPRESS         - Specific cppcheck warnings to disable by ID
#    CPPCHECK_FAIL_ON_WARNING  - Set to Y to fail the build on cppcheck
#                                warnings, N to continue even if warnings occur
#    CPPCHECK_QUIET            - Enable cppcheck verbose or quiet output mode
#    CPPCHECK_FLAGS            - Additional flags to pass to cppcheck
#
# PROVIDED VARIABLES:
#
#    (None)
#
# PROVIDED MACROS:
#
#    (None)
#
# -----------------------------------------------------------------------------

SHELL = /bin/sh

ERROR_IF_UNSET   ?= $(if $(filter undefined, $(origin $(strip $(1)))), $(error Makefile $(strip $(1)) value not set))
ERROR_IF_EMPTY   ?= $(if $(strip $($(strip $(1)))), , $(error Makefile $(strip $(1)) option cannot be blank))
ERROR_IF_NONBOOL ?= $(if $(filter Y N, $($(strip $(1)))), , $(error Makefile $(strip $(1)) option must be Y or N))

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
$(foreach MANDATORY_VAR, $(LUFA_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
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
.PHONY: cppcheck-config cppcheck
