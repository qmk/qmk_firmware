#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

LUFA_BUILD_MODULES         += DOXYGEN
LUFA_BUILD_TARGETS         += doxygen doxygen_upgrade doxygen_create
LUFA_BUILD_MANDATORY_VARS  += LUFA_PATH
LUFA_BUILD_OPTIONAL_VARS   += DOXYGEN_CONF DOXYGEN_FAIL_ON_WARNING DOXYGEN_OVERRIDE_PARAMS
LUFA_BUILD_PROVIDED_VARS   +=
LUFA_BUILD_PROVIDED_MACROS +=

# -----------------------------------------------------------------------------
#                 LUFA Doxygen Buildsystem Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Provides a set of targets to automatically build Doxygen documentation for
#   a project (see www.doxygen.org).
# -----------------------------------------------------------------------------
# TARGETS:
#
#    doxygen                   - Build Doxygen Documentation
#    doxygen_create            - Create a new Doxygen configuration file using
#                                the latest template
#    doxygen_upgrade           - Upgrade an existing Doxygen configuration file
#                                to the latest template
#
# MANDATORY PARAMETERS:
#
#    LUFA_PATH                 - Path to the LUFA library core
#
# OPTIONAL PARAMETERS:
#
#    DOXYGEN_CONF              - Doxygen configuration filename
#    DOXYGEN_FAIL_ON_WARNING   - Set to Y to fail the build on Doxygen warnings,
#                                N to continue even if warnings occur
#    DOXYGEN_OVERRIDE_PARAMS   - Parameters to override in the doxygen
#                                configuration file
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
DOXYGEN_CONF            ?= doxyfile
DOXYGEN_FAIL_ON_WARNING ?= Y
DOXYGEN_OVERRIDE_PARAMS ?= QUIET=YES HTML_EXTRA_STYLESHEET=$(patsubst %/,%,$(LUFA_PATH))/DoxygenPages/Style/Style.css

# Sanity check user supplied values
$(foreach MANDATORY_VAR, $(LUFA_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
$(call ERROR_IF_EMPTY, DOXYGEN_CONF)
$(call ERROR_IF_EMPTY, LUFA_PATH)
$(call ERROR_IF_NONBOOL, DOXYGEN_FAIL_ON_WARNING)

# Output Messages
MSG_DOXYGEN_CMD         := ' [DOXYGEN] :'

# Determine Doxygen invocation command
BASE_DOXYGEN_CMD := ( cat $(DOXYGEN_CONF) $(DOXYGEN_OVERRIDE_PARAMS:%=; echo "%") ) | doxygen -
ifeq ($(DOXYGEN_FAIL_ON_WARNING), Y)
   DOXYGEN_CMD := if ( $(BASE_DOXYGEN_CMD) 2>&1 | grep -v "warning: ignoring unsupported tag" ;); then exit 1; fi;
else
   DOXYGEN_CMD := $(BASE_DOXYGEN_CMD)
endif

# Error if the specified Doxygen configuration file does not exist
$(DOXYGEN_CONF):
	$(error Doxygen configuration file $@ does not exist)

# Builds the project documentation using the specified configuration file and the DOXYGEN tool
doxygen: $(DOXYGEN_CONF) $(MAKEFILE_LIST)
	@echo $(MSG_DOXYGEN_CMD) Configuration file \"$(DOXYGEN_CONF)\" with parameters \"$(DOXYGEN_OVERRIDE_PARAMS)\"
	$(DOXYGEN_CMD)

# Upgrades an existing Doxygen configuration file to the latest Doxygen template, preserving settings
doxygen_upgrade: $(DOXYGEN_CONF) $(MAKEFILE_LIST)
	@echo $(MSG_DOXYGEN_CMD) Upgrading configuration file \"$(DOXYGEN_CONF)\" with latest template
	doxygen -u $(DOXYGEN_CONF) > /dev/null

# Creates a new Doxygen configuration file with the set file name
doxygen_create: $(MAKEFILE_LIST)
	@echo $(MSG_DOXYGEN_CMD) Creating new configuration file \"$(DOXYGEN_CONF)\" with latest template
	doxygen -g $(DOXYGEN_CONF) > /dev/null

# Phony build targets for this module
.PHONY: doxygen doxygen_upgrade doxygen_create
