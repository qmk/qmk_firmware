#
#             LUFA Library
#     Copyright (C) Dean Camera, 2017.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.

AVRISP_PATH  = ../AVRISP-MKII

MCU          = at90usb1287
ARCH         = AVR8
BOARD        = XPLAIN
F_CPU        = 8000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = XPLAINBridge
SRC          = $(TARGET).c Lib/SoftUART.c USARTDescriptors.c $(AVRISP_PATH)/AVRISPDescriptors.c $(AVRISP_PATH)/Lib/V2Protocol.c \
               $(AVRISP_PATH)/Lib/V2ProtocolParams.c $(AVRISP_PATH)/Lib/ISP/ISPProtocol.c $(AVRISP_PATH)/Lib/ISP/ISPTarget.c \
               $(AVRISP_PATH)/Lib/XPROG/XPROGProtocol.c $(AVRISP_PATH)/Lib/XPROG/XPROGTarget.c $(AVRISP_PATH)/Lib/XPROG/XMEGANVM.c \
               $(AVRISP_PATH)/Lib/XPROG/TINYNVM.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    = ../../LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/ -I$(AVRISP_PATH)
LD_FLAGS     =

# Default target
all:

# Since this project borrows files from the AVRISP-MKII project which may also have an
# identical OBJDIR directory, we need to enforce the use of this project's object file
# directory as the one where the build object files are to be stored, by giving it a
# path relative to the current folder.
OBJDIR      := ./obj

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/cppcheck.mk
include $(DMBS_PATH)/doxygen.mk
include $(DMBS_PATH)/dfu.mk
include $(DMBS_PATH)/gcc.mk
include $(DMBS_PATH)/hid.mk
include $(DMBS_PATH)/avrdude.mk
include $(DMBS_PATH)/atprogram.mk
