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
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/analogin_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/gpio_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/gpio_irq_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/i2c_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/pinmap.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/port_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/pwmout_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/rtc_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/serial_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/sleep.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/spi_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M/us_ticker.o

INCLUDE_PATHS += \
	-Imbed \
	-I$(MBED_DIR)/libraries/mbed/targets \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_Freescale \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20D50M \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20D50M/TOOLCHAIN_GCC_ARM \
	-I$(MBED_DIR)/libraries/mbed/targets/hal \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_Freescale \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_Freescale/TARGET_K20D50M

LINKER_SCRIPT = mbed-infinity/infinity.ld
