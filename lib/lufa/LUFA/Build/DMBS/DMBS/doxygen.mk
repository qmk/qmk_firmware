#
#            DMBS Build System
#     Released into the public domain.
#
#  dean [at] fourwalledcubicle [dot] com
#        www.fourwalledcubicle.com
#

DMBS_BUILD_MODULES         += DOXYGEN
DMBS_BUILD_TARGETS         += doxygen doxygen-upgrade doxygen-create
DMBS_BUILD_MANDATORY_VARS  +=
DMBS_BUILD_OPTIONAL_VARS   += DOXYGEN_CONF DOXYGEN_FAIL_ON_WARNING DOXYGEN_OVERRIDE_PARAMS
DMBS_BUILD_PROVIDED_VARS   +=
DMBS_BUILD_PROVIDED_MACROS +=

# Conditionally import the CORE module of DMBS if it is not already imported
DMBS_MODULE_PATH := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
ifeq ($(findstring CORE, $(DMBS_BUILD_MODULES)),)
  include $(DMBS_MODULE_PATH)/core.mk
endif

# Default values of optionally user-supplied variables
DOXYGEN_CONF            ?= doxyfile
DOXYGEN_FAIL_ON_WARNING ?= Y
DOXYGEN_OVERRIDE_PARAMS ?= QUIET=YES

# Sanity check user supplied values
$(foreach MANDATORY_VAR, $(DMBS_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
$(call ERROR_IF_EMPTY, DOXYGEN_CONF)
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
doxygen-upgrade: $(DOXYGEN_CONF) $(MAKEFILE_LIST)
	@echo $(MSG_DOXYGEN_CMD) Upgrading configuration file \"$(DOXYGEN_CONF)\" with latest template
	doxygen -u $(DOXYGEN_CONF) > /dev/null

# Creates a new Doxygen configuration file with the set file name
doxygen-create: $(MAKEFILE_LIST)
	@echo $(MSG_DOXYGEN_CMD) Creating new configuration file \"$(DOXYGEN_CONF)\" with latest template
	doxygen -g $(DOXYGEN_CONF) > /dev/null


