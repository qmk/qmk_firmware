#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

MCU          = at90usb162
ARCH         = AVR8
BOARD        = USBTINYMKII
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = AVRISP-MKII
SRC          = $(TARGET).c AVRISPDescriptors.c Lib/V2Protocol.c Lib/V2ProtocolParams.c Lib/ISP/ISPProtocol.c Lib/ISP/ISPTarget.c Lib/XPROG/XPROGProtocol.c \
               Lib/XPROG/XPROGTarget.c Lib/XPROG/XMEGANVM.c Lib/XPROG/TINYNVM.c $(LUFA_SRC_USB)
LUFA_PATH    = ../../LUFA/
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/
LD_FLAGS     =

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa.core.in
include $(LUFA_PATH)/Build/lufa.sources.in
include $(LUFA_PATH)/Build/lufa.build.in
include $(LUFA_PATH)/Build/lufa.cppcheck.in
include $(LUFA_PATH)/Build/lufa.doxygen.in
include $(LUFA_PATH)/Build/lufa.dfu.in
include $(LUFA_PATH)/Build/lufa.avrdude.in
include $(LUFA_PATH)/Build/lufa.atprogram.in
