#
# Raspberry Pi specific drivers, same for all RP2xxx based boards
##############################################################################
COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/vendor/$(MCU_FAMILY)/rp2040

ifeq ($(strip $(WS2812_DRIVER)), vendor)
    OPT_DEFS += -DRP_DMA_REQUIRED=TRUE
endif

#
# Raspberry Pi Pico SDK Support
##############################################################################
ADEFS  += -DCRT0_VTOR_INIT=1 \
		  -DCRT0_EXTRA_CORES_NUMBER=0 \
          -DCRT0_INIT_VECTORS=1 \
          -DPICO_CONFIG_RTOS_ADAPTER_HEADER=$(PLATFORM_RP_PATH)/pico_sdk_shims.h

CFLAGS += -DNDEBUG \
          -DPICO_CONFIG_RTOS_ADAPTER_HEADER=$(PLATFORM_RP_PATH)/pico_sdk_shims.h

#
# Pico SDK source and header files needed by QMK and ChibiOS
##############################################################################
PICOSDKROOT := $(TOP_DIR)/lib/pico-sdk

PICOSDKSRC  = $(PICOSDKROOT)/src/common/hardware_claim/claim.c \
              $(PICOSDKROOT)/src/rp2_common/hardware_clocks/clocks.c \
              $(PICOSDKROOT)/src/rp2_common/hardware_flash/flash.c \
              $(PICOSDKROOT)/src/rp2_common/hardware_gpio/gpio.c \
              $(PICOSDKROOT)/src/rp2_common/hardware_pio/pio.c \
              $(PICOSDKROOT)/src/rp2_common/hardware_pll/pll.c \
              $(PICOSDKROOT)/src/rp2_common/hardware_ticks/ticks.c \
              $(PICOSDKROOT)/src/rp2_common/hardware_timer/timer.c \
              $(PICOSDKROOT)/src/rp2_common/hardware_watchdog/watchdog.c \
              $(PICOSDKROOT)/src/rp2_common/hardware_xosc/xosc.c \
              $(PICOSDKROOT)/src/rp2_common/pico_bootrom/bootrom.c \
              $(PICOSDKROOT)/src/rp2_common/pico_runtime_init/runtime_init_clocks.c \
              $(PICOSDKROOT)/src/rp2_common/pico_runtime_init/runtime_init.c

PICOSDKINC  = $(CHIBIOS)/os/various/pico_bindings/dumb/include \
              $(PICOSDKROOT)/src/boards/include \
              $(PICOSDKROOT)/src/common/boot_picobin_headers/include \
              $(PICOSDKROOT)/src/common/boot_picoboot_headers/include \
              $(PICOSDKROOT)/src/common/hardware_claim/include \
              $(PICOSDKROOT)/src/common/pico_base_headers/include \
              $(PICOSDKROOT)/src/rp2_common/boot_bootrom_headers/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_base/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_boot_lock/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_clocks/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_flash/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_gpio/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_irq/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_pio/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_pll/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_resets/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_sync_spin_lock/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_sync/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_ticks/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_timer/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_watchdog/include \
              $(PICOSDKROOT)/src/rp2_common/hardware_xosc/include \
              $(PICOSDKROOT)/src/rp2_common/pico_bootrom/include \
              $(PICOSDKROOT)/src/rp2_common/pico_flash/include \
              $(PICOSDKROOT)/src/rp2_common/pico_platform_compiler/include \
              $(PICOSDKROOT)/src/rp2_common/pico_platform_panic/include \
              $(PICOSDKROOT)/src/rp2_common/pico_platform_sections/include \
              $(PICOSDKROOT)/src/rp2_common/pico_runtime_init/include \
              $(PICOSDKROOT)/src/rp2_common/pico_runtime/include

PICOSDKSRC += $(PLATFORM_RP_PATH)/pico_sdk_shims.c
PICOSDKINC += $(PLATFORM_RP_PATH)

PLATFORM_SRC += $(PICOSDKSRC)
EXTRAINCDIRS += $(PICOSDKINC)
