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

# Starting byte address of the bootloader, as a byte address - computed via the formula
#   BOOT_START = ((FLASH_SIZE_KB - BOOT_SECTION_SIZE_KB) * 1024)
#
# Note that the bootloader size and start address given in AVRStudio is in words and not
# bytes, and so will need to be doubled to obtain the byte address needed by AVR-GCC.
FLASH_SIZE_KB        := 128
BOOT_SECTION_SIZE_KB := 8

# Formulas used to calculate the starting address of the Bootloader section, and the User Application
# API jump table (for more information on the latter, see the bootloader documentation). These formulas
# should not need to be altered - modify the FLASH_SIZE_KB and BOOT_SECTION_KB values above instead.
BOOT_START           := 0x$(shell echo "obase=16; ($(FLASH_SIZE_KB) - $(BOOT_SECTION_SIZE_KB)) * 1024" | bc)
BOOT_API_TABLESTART  := 0x$(shell echo "obase=16; (($(FLASH_SIZE_KB) * 1024) - 96)" | bc)

MCU          = at90usb1287
ARCH         = AVR8
BOARD        = USBKEY
F_CPU        = 8000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = BootloaderHID
SRC          = $(TARGET).c Descriptors.c $(LUFA_SRC_USB)
LUFA_PATH    = ../../LUFA/
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/
LD_FLAGS     = -Wl,--section-start=.text=$(BOOT_START)

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa.core.in
include $(LUFA_PATH)/Build/lufa.sources.in
include $(LUFA_PATH)/Build/lufa.build.in
include $(LUFA_PATH)/Build/lufa.cppcheck.in
include $(LUFA_PATH)/Build/lufa.doxygen.in
include $(LUFA_PATH)/Build/lufa.avrdude.in
include $(LUFA_PATH)/Build/lufa.atprogram.in
