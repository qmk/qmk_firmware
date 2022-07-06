#
# Raspberry Pi RP2040 specific drivers
##############################################################################
COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/vendor/$(MCU_FAMILY)/$(MCU_SERIES)

ifeq ($(strip $(WS2812_DRIVER)), vendor)
    OPT_DEFS += -DRP_DMA_REQUIRED=TRUE
endif

#
# Raspberry Pi Pico SDK Support
##############################################################################
ADEFS  += -DCRT0_VTOR_INIT=1 \
		  -DCRT0_EXTRA_CORES_NUMBER=0

CFLAGS += -DPICO_NO_FPGA_CHECK \
          -DNDEBUG

#
# Pico SDK source and header files needed by QMK and ChibiOS
##############################################################################
PICOSDKROOT   := $(TOP_DIR)/lib/pico-sdk

PICOSDKSRC     = $(PICOSDKROOT)/src/rp2_common/hardware_clocks/clocks.c \
                 $(PICOSDKROOT)/src/rp2_common/hardware_pll/pll.c \
                 $(PICOSDKROOT)/src/rp2_common/hardware_pio/pio.c \
                 $(PICOSDKROOT)/src/rp2_common/hardware_flash/flash.c \
                 $(PICOSDKROOT)/src/rp2_common/hardware_gpio/gpio.c \
                 $(PICOSDKROOT)/src/rp2_common/hardware_claim/claim.c \
                 $(PICOSDKROOT)/src/rp2_common/hardware_watchdog/watchdog.c \
                 $(PICOSDKROOT)/src/rp2_common/hardware_xosc/xosc.c \
                 $(PICOSDKROOT)/src/rp2_common/pico_bootrom/bootrom.c

PICOSDKINC     = $(CHIBIOS)//os/various/pico_bindings/dumb/include \
                 $(PICOSDKROOT)/src/common/pico_base/include \
                 $(PICOSDKROOT)/src/rp2_common/pico_platform/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_base/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_clocks/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_claim/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_flash/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_gpio/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_irq/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_pll/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_pio/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_sync/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_resets/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_watchdog/include \
                 $(PICOSDKROOT)/src/rp2_common/hardware_xosc/include \
                 $(PICOSDKROOT)/src/rp2040/hardware_regs/include \
                 $(PICOSDKROOT)/src/rp2040/hardware_structs/include \
                 $(PICOSDKROOT)/src/boards/include \
                 $(PICOSDKROOT)/src/rp2_common/pico_bootrom/include

PLATFORM_SRC += $(PICOSDKSRC)
EXTRAINCDIRS += $(PICOSDKINC)

PLATFORM_RP2040_PATH := $(PLATFORM_PATH)/$(PLATFORM_KEY)/vendors/$(MCU_FAMILY)

PLATFORM_SRC +=	$(PLATFORM_RP2040_PATH)/stage2_bootloaders.c \
				$(PLATFORM_RP2040_PATH)/pico_sdk_shims.c

EXTRAINCDIRS += $(PLATFORM_RP2040_PATH)

#
# RP2040 optimized compiler intrinsics
##############################################################################

# Enables optimized Compiler intrinsics which are located in the RP2040
# bootrom. This needs startup code and linker script support from ChibiOS,
# which is WIP. Therefore disabled by default for now.
RP2040_INTRINSICS_ENABLED ?= no
ifeq ($(strip $(RP2040_INTRINSICS_ENABLED)), yes)
    PICOSDKINTRINSICSSRC =  $(PICOSDKROOT)/src/rp2_common/pico_float/float_aeabi.S \
                            $(PICOSDKROOT)/src/rp2_common/pico_float/float_math.c \
                            $(PICOSDKROOT)/src/rp2_common/pico_float/float_init_rom.c \
                            $(PICOSDKROOT)/src/rp2_common/pico_float/float_v1_rom_shim.S \
                            $(PICOSDKROOT)/src/rp2_common/pico_double/double_aeabi.S \
                            $(PICOSDKROOT)/src/rp2_common/pico_double/double_math.c \
                            $(PICOSDKROOT)/src/rp2_common/pico_double/double_init_rom.c \
                            $(PICOSDKROOT)/src/rp2_common/pico_double/double_v1_rom_shim.S \
                            $(PICOSDKROOT)/src/rp2_common/pico_divider/divider.S \
                            $(PICOSDKROOT)/src/rp2_common/pico_int64_ops/pico_int64_ops_aeabi.S \
                            $(PICOSDKROOT)/src/rp2_common/pico_mem_ops/mem_ops_aeabi.S \
                            $(PICOSDKROOT)/src/rp2_common/pico_malloc/pico_malloc.c \
                            $(PICOSDKROOT)/src/rp2_common/pico_bit_ops/bit_ops_aeabi.S

    PICOSDKINTRINSICSINC =  $(PICOSDKROOT)/src/common/pico_base/include \
                            $(PICOSDKROOT)/src/rp2_common/pico_platfrom/include \
                            $(PICOSDKROOT)/src/rp2_common/pico_bootrom/include \
                            $(PICOSDKROOT)/src/rp2_common/hardware_divider/include \
                            $(PICOSDKROOT)/src/rp2_common/pico_float/include \
                            $(PICOSDKROOT)/src/rp2_common/pico_double/include \
                            $(PICOSDKROOT)/src/rp2_common/pico_malloc/include

    OPT_DEFS += -DPICO_FLOAT_SUPPORT_ROM_V1=0 -DPICO_DOUBLE_SUPPORT_ROM_V1=0

    CFLAGS += -Wl,--defsym=__StackLimit=__heap_end__
    CFLAGS += -Wl,--defsym=__unhandled_user_irq=_unhandled_exception
    CFLAGS += -Wl,--build-id=none

    # single precision floating point intrinsics
    OPT_DEFS += -DPICO_FLOAT_IN_RAM=1
    OPT_DEFS += -DPICO_FLOAT_PROPAGATE_NANS=0

    CFLAGS += -Wl,--wrap=__aeabi_fdiv
    CFLAGS += -Wl,--wrap=__aeabi_fmul
    CFLAGS += -Wl,--wrap=__aeabi_frsub
    CFLAGS += -Wl,--wrap=__aeabi_fsub
    CFLAGS += -Wl,--wrap=__aeabi_cfcmpeq
    CFLAGS += -Wl,--wrap=__aeabi_cfrcmple
    CFLAGS += -Wl,--wrap=__aeabi_cfcmple
    CFLAGS += -Wl,--wrap=__aeabi_fcmpeq
    CFLAGS += -Wl,--wrap=__aeabi_fcmplt
    CFLAGS += -Wl,--wrap=__aeabi_fcmple
    CFLAGS += -Wl,--wrap=__aeabi_fcmpge
    CFLAGS += -Wl,--wrap=__aeabi_fcmpgt
    CFLAGS += -Wl,--wrap=__aeabi_fcmpun
    CFLAGS += -Wl,--wrap=__aeabi_i2f
    CFLAGS += -Wl,--wrap=__aeabi_l2f
    CFLAGS += -Wl,--wrap=__aeabi_ui2f
    CFLAGS += -Wl,--wrap=__aeabi_ul2f
    CFLAGS += -Wl,--wrap=__aeabi_i2f
    CFLAGS += -Wl,--wrap=__aeabi_f2iz
    CFLAGS += -Wl,--wrap=__aeabi_f2lz
    CFLAGS += -Wl,--wrap=__aeabi_f2uiz
    CFLAGS += -Wl,--wrap=__aeabi_f2ulz
    CFLAGS += -Wl,--wrap=__aeabi_f2d
    CFLAGS += -Wl,--wrap=sqrtf
    CFLAGS += -Wl,--wrap=cosf
    CFLAGS += -Wl,--wrap=sinf
    CFLAGS += -Wl,--wrap=tanf
    CFLAGS += -Wl,--wrap=atan2f
    CFLAGS += -Wl,--wrap=expf
    CFLAGS += -Wl,--wrap=logf
    CFLAGS += -Wl,--wrap=ldexpf
    CFLAGS += -Wl,--wrap=copysignf
    CFLAGS += -Wl,--wrap=truncf
    CFLAGS += -Wl,--wrap=floorf
    CFLAGS += -Wl,--wrap=ceilf
    CFLAGS += -Wl,--wrap=roundf
    CFLAGS += -Wl,--wrap=sincosf
    CFLAGS += -Wl,--wrap=asinf
    CFLAGS += -Wl,--wrap=acosf
    CFLAGS += -Wl,--wrap=atanf
    CFLAGS += -Wl,--wrap=sinhf
    CFLAGS += -Wl,--wrap=coshf
    CFLAGS += -Wl,--wrap=tanhf
    CFLAGS += -Wl,--wrap=asinhf
    CFLAGS += -Wl,--wrap=acoshf
    CFLAGS += -Wl,--wrap=atanhf
    CFLAGS += -Wl,--wrap=exp2f
    CFLAGS += -Wl,--wrap=log2f
    CFLAGS += -Wl,--wrap=exp10f
    CFLAGS += -Wl,--wrap=log10f
    CFLAGS += -Wl,--wrap=powf
    CFLAGS += -Wl,--wrap=powintf
    CFLAGS += -Wl,--wrap=hypotf
    CFLAGS += -Wl,--wrap=cbrtf
    CFLAGS += -Wl,--wrap=fmodf
    CFLAGS += -Wl,--wrap=dremf
    CFLAGS += -Wl,--wrap=remainderf
    CFLAGS += -Wl,--wrap=remquof
    CFLAGS += -Wl,--wrap=expm1f
    CFLAGS += -Wl,--wrap=log1pf
    CFLAGS += -Wl,--wrap=fmaf

    # double precision floating point intrinsics
    OPT_DEFS += -DPICO_DOUBLE_IN_RAM=1
    OPT_DEFS += -DPICO_DOUBLE_PROPAGATE_NANS=0

    CFLAGS += -Wl,--wrap=__aeabi_dadd
    CFLAGS += -Wl,--wrap=__aeabi_ddiv
    CFLAGS += -Wl,--wrap=__aeabi_dmul
    CFLAGS += -Wl,--wrap=__aeabi_drsub
    CFLAGS += -Wl,--wrap=__aeabi_dsub
    CFLAGS += -Wl,--wrap=__aeabi_cdcmpeq
    CFLAGS += -Wl,--wrap=__aeabi_cdrcmple
    CFLAGS += -Wl,--wrap=__aeabi_cdcmple
    CFLAGS += -Wl,--wrap=__aeabi_dcmpeq
    CFLAGS += -Wl,--wrap=__aeabi_dcmplt
    CFLAGS += -Wl,--wrap=__aeabi_dcmple
    CFLAGS += -Wl,--wrap=__aeabi_dcmpge
    CFLAGS += -Wl,--wrap=__aeabi_dcmpgt
    CFLAGS += -Wl,--wrap=__aeabi_dcmpun
    CFLAGS += -Wl,--wrap=__aeabi_i2d
    CFLAGS += -Wl,--wrap=__aeabi_l2d
    CFLAGS += -Wl,--wrap=__aeabi_ui2d
    CFLAGS += -Wl,--wrap=__aeabi_ul2d
    CFLAGS += -Wl,--wrap=__aeabi_d2iz
    CFLAGS += -Wl,--wrap=__aeabi_d2lz
    CFLAGS += -Wl,--wrap=__aeabi_d2uiz
    CFLAGS += -Wl,--wrap=__aeabi_d2ulz
    CFLAGS += -Wl,--wrap=__aeabi_d2f
    CFLAGS += -Wl,--wrap=sqrt
    CFLAGS += -Wl,--wrap=cos
    CFLAGS += -Wl,--wrap=sin
    CFLAGS += -Wl,--wrap=tan
    CFLAGS += -Wl,--wrap=atan2
    CFLAGS += -Wl,--wrap=exp
    CFLAGS += -Wl,--wrap=log
    CFLAGS += -Wl,--wrap=ldexp
    CFLAGS += -Wl,--wrap=copysign
    CFLAGS += -Wl,--wrap=trunc
    CFLAGS += -Wl,--wrap=floor
    CFLAGS += -Wl,--wrap=ceil
    CFLAGS += -Wl,--wrap=round
    CFLAGS += -Wl,--wrap=sincos
    CFLAGS += -Wl,--wrap=asin
    CFLAGS += -Wl,--wrap=acos
    CFLAGS += -Wl,--wrap=atan
    CFLAGS += -Wl,--wrap=sinh
    CFLAGS += -Wl,--wrap=cosh
    CFLAGS += -Wl,--wrap=tanh
    CFLAGS += -Wl,--wrap=asinh
    CFLAGS += -Wl,--wrap=acosh
    CFLAGS += -Wl,--wrap=atanh
    CFLAGS += -Wl,--wrap=exp2
    CFLAGS += -Wl,--wrap=log2
    CFLAGS += -Wl,--wrap=exp10
    CFLAGS += -Wl,--wrap=log10
    CFLAGS += -Wl,--wrap=pow
    CFLAGS += -Wl,--wrap=powint
    CFLAGS += -Wl,--wrap=hypot
    CFLAGS += -Wl,--wrap=cbrt
    CFLAGS += -Wl,--wrap=fmod
    CFLAGS += -Wl,--wrap=drem
    CFLAGS += -Wl,--wrap=remainder
    CFLAGS += -Wl,--wrap=remquo
    CFLAGS += -Wl,--wrap=expm1
    CFLAGS += -Wl,--wrap=log1p
    CFLAGS += -Wl,--wrap=fma

    # bit operation intrinsics
    OPT_DEFS += -DPICO_BITS_IN_RAM=1

    CFLAGS += -Wl,--wrap=__clzsi2
    CFLAGS += -Wl,--wrap=__clzsi2
    CFLAGS += -Wl,--wrap=__clzdi2
    CFLAGS += -Wl,--wrap=__ctzsi2
    CFLAGS += -Wl,--wrap=__ctzdi2
    CFLAGS += -Wl,--wrap=__popcountsi2
    CFLAGS += -Wl,--wrap=__popcountdi2
    CFLAGS += -Wl,--wrap=__clz
    CFLAGS += -Wl,--wrap=__clzl
    CFLAGS += -Wl,--wrap=__clzsi2
    CFLAGS += -Wl,--wrap=__clzll

    # integer division intrinsics
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

    # malloc and friends functions
    OPT_DEFS += -DPICO_USE_MALLOC_MUTEX=0
    OPT_DEFS += -DPICO_DEBUG_MALLOC=0
    OPT_DEFS ?= -DPICO_MALLOC_PANIC=0

    CFLAGS += -Wl,--wrap=malloc
    CFLAGS += -Wl,--wrap=calloc
    CFLAGS += -Wl,--wrap=free

    # memory operation intrinsics
    OPT_DEFS += -DPICO_MEM_IN_RAM=1

    CFLAGS += -Wl,--wrap=memcpy
    CFLAGS += -Wl,--wrap=memset
    CFLAGS += -Wl,--wrap=__aeabi_memcpy
    CFLAGS += -Wl,--wrap=__aeabi_memset
    CFLAGS += -Wl,--wrap=__aeabi_memcpy4
    CFLAGS += -Wl,--wrap=__aeabi_memset4
    CFLAGS += -Wl,--wrap=__aeabi_memcpy8
    CFLAGS += -Wl,--wrap=__aeabi_memset8

    PLATFORM_SRC += $(PICOSDKINTRINSICSSRC)
    EXTRAINCDIRS += $(PICOSDKINTRINSICSINC)
endif
