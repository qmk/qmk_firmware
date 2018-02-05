#
#             LUFA Library
#     Copyright (C) Dean Camera, 2015.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_PATH)/gcc.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk
