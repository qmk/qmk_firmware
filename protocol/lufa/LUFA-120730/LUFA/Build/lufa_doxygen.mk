#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

LUFA_BUILD_MODULES         += DOXYGEN
LUFA_BUILD_TARGETS         += doxygen
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
DOXYGEN_CONF            ?= Doxygen.conf
DOXYGEN_FAIL_ON_WARNING ?= Y
DOXYGEN_OVERRIDE_PARAMS ?= QUIET=YES HTML_STYLESHEET=$(patsubst %/,%,$(LUFA_PATH))/DoxygenPages/Style/Style.css

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

doxygen:
	@echo $(MSG_DOXYGEN_CMD) Configuration file \"$(DOXYGEN_CONF)\" with parameters \"$(DOXYGEN_OVERRIDE_PARAMS)\"
	$(DOXYGEN_CMD)

# Phony build targets for this module
.PHONY: doxygen
