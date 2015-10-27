# based on Makefile exported form mbed.org
# see http://mbed.org/handbook/Exporting-to-GCC-ARM-Embedded

CPU = -mcpu=cortex-m4 -mthumb

CC_SYMBOLS += \
	-DTARGET_INFINITY \
	-DTARGET_K20D50M \
	-DTARGET_M4 \
	-DTARGET_CORTEX_M \
	-DTARGET_Freescale \
	-DTOOLCHAIN_GCC_ARM \
	-DTOOLCHAIN_GCC \
	-D__CORTEX_M4 \
	-DARM_MATH_CM4 \
	-D__MBED__=1

OBJECTS += \
	$(OBJDIR)/mbed-infinity/cmsis_nvic.o \
	$(OBJDIR)/mbed-infinity/system_MK20D5.o \
	$(OBJDIR)/mbed-infinity/USBHAL_KL25Z.o \
	$(OBJDIR)/mbed-infinity/startup_MK20D5.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/analogin_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/gpio_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/gpio_irq_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/i2c_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/pinmap.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/port_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/pwmout_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/rtc_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/serial_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/sleep.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/spi_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/us_ticker.o

INCLUDE_PATHS += \
	-Imbed \
	-I$(MBED_DIR)/libraries/mbed/targets \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_Freescale \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX/TARGET_K20D50M \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX/TARGET_K20D50M/TOOLCHAIN_GCC_ARM \
	-I$(MBED_DIR)/libraries/mbed/targets/hal \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_Freescale \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20XX/TARGET_K20D50M

LINKER_SCRIPT = mbed-infinity/infinity.ld
