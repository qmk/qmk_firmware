#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Static anlysis of the entire LUFA source tree, using the free cross-platform "cppcheck" tool.

# Path to the root of the LUFA tree to scan
LUFA_ROOT_PATH   = ../../

# Filenames or directories (including fragments) to exclude from the analysis
EXCLUDE_LIST     = HostLoaderApp/ FATFs/ PetiteFATFs/ uip/

# Output message template for found warnings and errors
MESSAGE_TEMPLATE = "{file}({line}): {severity} ({id}): {message}"

all:
	cppcheck -q -f --error-exitcode=1 --template $(MESSAGE_TEMPLATE) --enable=style --suppress=variableScope $(EXCLUDE_LIST:%=-i%) $(LUFA_ROOT_PATH)
	
%: