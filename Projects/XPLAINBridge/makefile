#
#             LUFA Library
#     Copyright (C) Dean Camera, 2013.
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
# directory as the one where the build object files are to be stored by pre-pending the
# absolute path of the current project to the OBJDIR variable.
ifneq ($(OBJDIR),)
  override OBJDIR:=$(shell pwd)/$(OBJDIR)
endif

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
