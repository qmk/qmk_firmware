#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Static anlysis of the entire LUFA source tree, using the free cross-platform "cppcheck" tool.

# Path to the root of the LUFA tree to scan
LUFA_ROOT_PATH    = ../../

# Filenames or directories (including fragments) to exclude from the analysis
EXCLUDE_LIST      = HostLoaderApp/ FATFs/ PetiteFATFs/ uip/

# Output message template for found warnings and errors
MESSAGE_TEMPLATE  = "{file}({line}): {severity} ({id}): {message}"

# Checks to suppress so that generated warnings are discarded
SUPPRESS_WARNINGS = variableScope unusedFunction missingInclude

all:
	cppcheck -q --std=c99 --check-config $(EXCLUDE_LIST:%=-i%) $(LUFA_ROOT_PATH)
	cppcheck -q -f --std=c99 --error-exitcode=1 --inline-suppr --enable=all $(SUPPRESS_WARNINGS:%=--suppress=%) --template $(MESSAGE_TEMPLATE) $(EXCLUDE_LIST:%=-i%) $(LUFA_ROOT_PATH)
	
%: