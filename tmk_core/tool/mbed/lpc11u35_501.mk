# based on Makefile exported form mbed.org
# see http://mbed.org/handbook/Exporting-to-GCC-ARM-Embedded

CPU = -mcpu=cortex-m0 -mthumb

CC_SYMBOLS = \
	-DTARGET_LPC11U35_501 \
	-DTARGET_M0 \
	-DTARGET_CORTEX_M \
	-DTARGET_NXP \
	-DTARGET_LPC11UXX \
	-DTARGET_MCU_LPC11U35_501 \
	-DTOOLCHAIN_GCC_ARM \
	-DTOOLCHAIN_GCC \
	-D__CORTEX_M0 \
	-DARM_MATH_CM0 \
	-D__MBED__=1

OBJECTS += \
	$(OBJDIR)/libraries/USBDevice/USBDevice/USBHAL_LPC11U.o \
	$(OBJDIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM/startup_LPC11xx.o \
	$(OBJDIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/cmsis_nvic.o \
	$(OBJDIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/system_LPC11Uxx.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/TARGET_MCU_LPC11U35_501/PeripheralPins.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/analogin_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/gpio_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/gpio_irq_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/i2c_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/pinmap.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/port_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/pwmout_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/serial_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/sleep.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/spi_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/us_ticker.o

INCLUDE_PATHS += \
	-I$(MBED_DIR)/libraries/mbed/targets \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM/TARGET_LPC11U35_501 \
	-I$(MBED_DIR)/libraries/mbed/targets/hal \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_NXP \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/TARGET_MCU_LPC11U35_501 \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/TARGET_MCU_LPC11U35_501/TARGET_LPC11U35_501

LINKER_SCRIPT = $(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM/TARGET_LPC11U35_501/LPC11U35.ld
