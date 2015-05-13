#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

LUFA_BUILD_MODULES         += CORE
LUFA_BUILD_TARGETS         += help list_targets list_modules list_mandatory list_optional list_provided list_macros
LUFA_BUILD_MANDATORY_VARS  +=
LUFA_BUILD_OPTIONAL_VARS   +=
LUFA_BUILD_PROVIDED_VARS   +=
LUFA_BUILD_PROVIDED_MACROS +=

# -----------------------------------------------------------------------------
#               LUFA Core Build System Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Provides a set of core build targets for the LUFA build system
# -----------------------------------------------------------------------------
# TARGETS:
#
#    help                      - Build system help
#    list_targets              - List all build targets
#    list_modules              - List all build modules
#    list_mandatory            - List all mandatory make variables required by
#                                the included build modules of the application
#    list_optional             - List all optional make variables required by
#                                the included build modules of the application
#    list_provided             - List all provided make variables from the
#                                included build modules of the application
#    list_macros               - List all provided make macros from the
#                                included build modules of the application
#
# MANDATORY PARAMETERS:
#
#    (None)
#
# OPTIONAL PARAMETERS:
#
#    (None)
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

# Converts a given input to a printable output using "(None)" if no items are in the list
CONVERT_TO_PRINTABLE           = $(if $(strip $(1)), $(1), (None))


# Build sorted and filtered lists of the included build module data
SORTED_LUFA_BUILD_MODULES      = $(sort $(LUFA_BUILD_MODULES))
SORTED_LUFA_BUILD_TARGETS      = $(sort $(LUFA_BUILD_TARGETS))
SORTED_LUFA_MANDATORY_VARS     = $(sort $(LUFA_BUILD_MANDATORY_VARS))
SORTED_LUFA_OPTIONAL_VARS      = $(filter-out $(SORTED_LUFA_MANDATORY_VARS), $(sort $(LUFA_BUILD_OPTIONAL_VARS)))
SORTED_LUFA_PROVIDED_VARS      = $(sort $(LUFA_BUILD_PROVIDED_VARS))
SORTED_LUFA_PROVIDED_MACROS    = $(sort $(LUFA_BUILD_PROVIDED_MACROS))

# Create printable versions of the sorted build module data (use "(None)" when no data is available)
PRINTABLE_LUFA_BUILD_MODULES   = $(call CONVERT_TO_PRINTABLE, $(SORTED_LUFA_BUILD_MODULES))
PRINTABLE_LUFA_BUILD_TARGETS   = $(call CONVERT_TO_PRINTABLE, $(SORTED_LUFA_BUILD_TARGETS))
PRINTABLE_LUFA_MANDATORY_VARS  = $(call CONVERT_TO_PRINTABLE, $(SORTED_LUFA_MANDATORY_VARS))
PRINTABLE_LUFA_OPTIONAL_VARS   = $(call CONVERT_TO_PRINTABLE, $(SORTED_LUFA_OPTIONAL_VARS))
PRINTABLE_LUFA_PROVIDED_VARS   = $(call CONVERT_TO_PRINTABLE, $(SORTED_LUFA_PROVIDED_VARS))
PRINTABLE_LUFA_PROVIDED_MACROS = $(call CONVERT_TO_PRINTABLE, $(SORTED_LUFA_PROVIDED_MACROS))

help:
	@echo "==================================================================="
	@echo "                       LUFA Build System 2.0                       "
	@echo "      (C) Dean Camera, 2014 { dean @ fourwalledcubicle . com }     "
	@echo "==================================================================="
	@echo "DESCRIPTION:                                                       "
	@echo " This build system is a set of makefile modules for (GNU) Make, to "
	@echo " provide a simple system for building LUFA powered applications.   "
	@echo " Each makefile module can be included from within a user makefile, "
	@echo " to expose the build rules documented in the comments at the top of"
	@echo " each build module.                                                "
	@echo "                                                                   "
	@echo "USAGE:                                                             "
	@echo " To execute a rule, define all variables indicated in the desired  "
	@echo " module as a required parameter before including the build module  "
	@echo " in your project makefile. Parameters marked as optional will      "
	@echo " assume a default value in the modules if not user-assigned.       "
	@echo "                                                                   "
	@echo " By default the target output shows both a friendly summary, as    "
	@echo " well as the actual invoked command. To suppress the output of the "
	@echo " invoked commands and show only the friendly command output, run   "
	@echo " make with the \"-s\" switch added before the target(s).           "
	@echo "                                                                   "
	@echo "SEE ALSO:                                                          "
	@echo " For more information, see the 'Build System' chapter of the LUFA  "
	@echo " project documentation.                                            "
	@echo "==================================================================="
	@echo "                                                                   "
	@echo "  Currently used build system modules in this application:         "
	@echo "                                                                   "
	@printf " %b" "$(PRINTABLE_LUFA_BUILD_MODULES:%=   - %\n)"
	@echo "                                                                   "
	@echo "                                                                   "
	@echo "  Currently available build targets in this application:           "
	@echo "                                                                   "
	@printf " %b" "$(PRINTABLE_LUFA_BUILD_TARGETS:%=   - %\n)"
	@echo "                                                                   "
	@echo "                                                                   "
	@echo "  Mandatory variables required by the selected build Modules:      "
	@echo "                                                                   "
	@printf " %b" "$(PRINTABLE_LUFA_MANDATORY_VARS:%=   - %\n)"
	@echo "                                                                   "
	@echo "                                                                   "
	@echo "  Optional variables required by the selected build Modules:       "
	@echo "                                                                   "
	@printf " %b" "$(PRINTABLE_LUFA_OPTIONAL_VARS:%=   - %\n)"
	@echo "                                                                   "
	@echo "                                                                   "
	@echo "  Variables provided by the selected build Modules:                "
	@echo "                                                                   "
	@printf " %b" "$(PRINTABLE_LUFA_PROVIDED_VARS:%=   - %\n)"
	@echo "                                                                   "
	@echo "                                                                   "
	@echo "  Macros provided by the selected build Modules:                   "
	@echo "                                                                   "
	@printf " %b" "$(PRINTABLE_LUFA_PROVIDED_MACROS:%=   - %\n)"
	@echo "                                                                   "
	@echo "==================================================================="
	@echo "   The LUFA BuildSystem 2.0 - Powered By Positive Thinking (tm)    "
	@echo "==================================================================="

# Lists build modules included by the project makefile, in alphabetical order
list_modules:
	@echo Currently Used Build System Modules:
	@printf " %b" "$(PRINTABLE_LUFA_BUILD_MODULES:%=   - %\n)"

# Lists build targets included by the project makefile, in alphabetical order
list_targets:
	@echo Currently Available Build Targets:
	@printf " %b" "$(PRINTABLE_LUFA_BUILD_TARGETS:%=   - %\n)"

# Lists mandatory variables that must be set by the project makefile, in alphabetical order
list_mandatory:
	@echo Mandatory Variables for Included Modules:
	@printf " %b" "$(PRINTABLE_LUFA_MANDATORY_VARS:%=   - %\n)"

# Lists optional variables that must be set by the project makefile, in alphabetical order
list_optional:
	@echo Optional Variables for Included Modules:
	@printf " %b" "$(PRINTABLE_LUFA_OPTIONAL_VARS:%=   - %\n)"

# Lists variables provided by the included build modules, in alphabetical order
list_provided:
	@echo Variables Provided by the Included Modules:
	@printf " %b" "$(PRINTABLE_LUFA_PROVIDED_VARS:%=   - %\n)"

# Lists macros provided by the included build modules, in alphabetical order
list_macros:
	@echo Macros Provided by the Included Modules:
	@printf " %b" "$(PRINTABLE_LUFA_PROVIDED_MACROS:%=   - %\n)"

# Disable default in-built make rules (those that are needed are explicitly
# defined, and doing so has performance benefits when recursively building)
ifeq ($(filter -r,$(MAKEFLAGS)),)
  MAKEFLAGS += -r
endif
.SUFFIXES:

# Phony build targets for this module
.PHONY: help list_modules list_targets list_mandatory list_optional list_provided list_macros
