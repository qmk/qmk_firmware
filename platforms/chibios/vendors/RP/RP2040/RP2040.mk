PLATFORM_RP_PATH := $(PLATFORM_PATH)/$(PLATFORM_KEY)/vendors/$(MCU_FAMILY)
PLATFORM_RP2040_PATH := $(PLATFORM_RP_PATH)/$(MCU_SERIES)

include $(PLATFORM_RP_PATH)/rp_common.mk

#
# RP2040 specific source and header files needed by QMK and ChibiOS
##############################################################################
RP2040_INC = $(PICOSDKROOT)/src/rp2040/hardware_regs/include \
             $(PICOSDKROOT)/src/rp2040/hardware_structs/include \
             $(PICOSDKROOT)/src/rp2040/pico_platform/include \
             $(PLATFORM_RP2040_PATH)

RP2040_SRC = $(PLATFORM_RP2040_PATH)/stage2_bootloaders.c

CFLAGS += -DPICO_RP2040=1

#
# RP2040 optimized compiler intrinsics
##############################################################################

# The RP2040 sdk provides optimized compiler intrinsics which override the GCC
# built-ins. Some of these functions are located in the bootrom of the RP2040.
# Execution of these functions is realized via a vtable that is populated on
# bootup. This mechanism needs startup code and linker script support from
# ChibiOS, which is currently not implemented thus these functions are disabled
# ATM.
RP2040_SRC += $(PICOSDKROOT)/src/rp2_common/hardware_divider/divider.S \
              $(PICOSDKROOT)/src/rp2_common/pico_divider/divider_hardware.S \
              $(PICOSDKROOT)/src/rp2_common/pico_int64_ops/pico_int64_ops_aeabi.S

RP2040_INC += $(PICOSDKROOT)/src/rp2_common/hardware_divider/include \
              $(PICOSDKROOT)/src/common/pico_divider_headers/include

# integer division intrinsics utilizing the RP2040 hardware divider
OPT_DEFS += -DPICO_DIVIDER_IN_RAM=1
OPT_DEFS += -DPICO_DIVIDER_DISABLE_INTERRUPTS=1

CFLAGS += -Wl,--wrap=__aeabi_idiv
CFLAGS += -Wl,--wrap=__aeabi_idivmod
CFLAGS += -Wl,--wrap=__aeabi_ldivmod
CFLAGS += -Wl,--wrap=__aeabi_uidiv
CFLAGS += -Wl,--wrap=__aeabi_uidivmod
CFLAGS += -Wl,--wrap=__aeabi_uldivmod

# 64bit integer intrinsics
OPT_DEFS += -DPICO_INT64_OPS_IN_RAM=1

CFLAGS += -Wl,--wrap=__aeabi_lmul

PLATFORM_SRC += $(RP2040_SRC)
EXTRAINCDIRS += $(RP2040_INC)
