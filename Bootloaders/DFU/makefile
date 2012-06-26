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

MCU          = at90usb1287
ARCH         = AVR8
BOARD        = USBKEY
F_CPU        = 8000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = BootloaderDFU
SRC          = $(TARGET).c Descriptors.c BootloaderAPI.c BootloaderAPITable.S $(LUFA_SRC_USB)
LUFA_PATH    = ../../LUFA/
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/ -DBOOT_START_ADDR=$(BOOT_START_OFFSET)
LD_FLAGS     = -Wl,--section-start=.text=$(BOOT_START_OFFSET) $(BOOT_API_LD_FLAGS)

# Flash size and bootloader section sizes of the target, in KB. These must
# match the target's total FLASH size and the bootloader size set in the
# device's fuses.
FLASH_SIZE_KB         = 128
BOOT_SECTION_SIZE_KB  = 8

# Bootloader address calculation formulas (requires the "bc" unix utility)
# Do not modify these macros, but rather modify the depedant values above.
BOOT_START_OFFSET     = 0x$(shell echo "obase=16; ($(FLASH_SIZE_KB) - $(BOOT_SECTION_SIZE_KB)) * 1024" | bc)
BOOT_SEC_OFFSET       = 0x$(shell echo "obase=16; (($(FLASH_SIZE_KB) * 1024) - $(strip $(1)))" | bc)

# Bootloader linker section flags for relocating the API table sections to
# known FLASH addresses - these should not normally be user-edited.
BOOT_SECTION_LD_FLAG  = -Wl,--section-start=.apitable_$(strip $(1))=$(call BOOT_SEC_OFFSET, $(3)) -Wl,--undefined=BootloaderAPI_$(strip $(2))
BOOT_API_LD_FLAGS     = $(call BOOT_SECTION_LD_FLAG, trampolines, Trampolines, (48 + 32 + 8))
BOOT_API_LD_FLAGS    += $(call BOOT_SECTION_LD_FLAG, jumptable,   JumpTable,   (32 + 8))
BOOT_API_LD_FLAGS    += $(call BOOT_SECTION_LD_FLAG, signatures,  Signatures,  8)

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
