OBJECTS += \
	$(OBJDIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM/startup_LPC11xx.o \
	$(OBJDIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/cmsis_nvic.o \
	$(OBJDIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/system_LPC11Uxx.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/port_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/spi_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/analogin_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/gpio_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/gpio_irq_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/serial_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/i2c_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/pwmout_api.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/sleep.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/pinmap.o \
	$(OBJDIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/us_ticker.o \
	$(OBJDIR)/libraries/mbed/common/board.o \
	$(OBJDIR)/libraries/mbed/common/mbed_interface.o \
	$(OBJDIR)/libraries/mbed/common/exit.o \
	$(OBJDIR)/libraries/mbed/common/rtc_time.o \
	$(OBJDIR)/libraries/mbed/common/us_ticker_api.o \
	$(OBJDIR)/libraries/mbed/common/pinmap_common.o \
	$(OBJDIR)/libraries/mbed/common/error.o \
	$(OBJDIR)/libraries/mbed/common/gpio.o \
	$(OBJDIR)/libraries/mbed/common/semihost_api.o \
	$(OBJDIR)/libraries/mbed/common/wait_api.o \
	$(OBJDIR)/libraries/mbed/common/RawSerial.o \
	$(OBJDIR)/libraries/mbed/common/Ticker.o \
	$(OBJDIR)/libraries/mbed/common/FilePath.o \
	$(OBJDIR)/libraries/mbed/common/I2C.o \
	$(OBJDIR)/libraries/mbed/common/FileBase.o \
	$(OBJDIR)/libraries/mbed/common/retarget.o \
	$(OBJDIR)/libraries/mbed/common/Serial.o \
	$(OBJDIR)/libraries/mbed/common/Stream.o \
	$(OBJDIR)/libraries/mbed/common/FileSystemLike.o \
	$(OBJDIR)/libraries/mbed/common/CallChain.o \
	$(OBJDIR)/libraries/mbed/common/InterruptManager.o \
	$(OBJDIR)/libraries/mbed/common/SerialBase.o \
	$(OBJDIR)/libraries/mbed/common/BusInOut.o \
	$(OBJDIR)/libraries/mbed/common/SPISlave.o \
	$(OBJDIR)/libraries/mbed/common/I2CSlave.o \
	$(OBJDIR)/libraries/mbed/common/FunctionPointer.o \
	$(OBJDIR)/libraries/mbed/common/Timer.o \
	$(OBJDIR)/libraries/mbed/common/SPI.o \
	$(OBJDIR)/libraries/mbed/common/Timeout.o \
	$(OBJDIR)/libraries/mbed/common/Ethernet.o \
	$(OBJDIR)/libraries/mbed/common/TimerEvent.o \
	$(OBJDIR)/libraries/mbed/common/CAN.o \
	$(OBJDIR)/libraries/mbed/common/BusOut.o \
	$(OBJDIR)/libraries/mbed/common/FileLike.o \
	$(OBJDIR)/libraries/mbed/common/BusIn.o \
	$(OBJDIR)/libraries/mbed/common/InterruptIn.o \
	$(OBJDIR)/libraries/mbed/common/LocalFileSystem.o \
	$(OBJDIR)/libraries/USBDevice/USBHID/USBMouse.o \
	$(OBJDIR)/libraries/USBDevice/USBHID/USBHID.o \
	$(OBJDIR)/libraries/USBDevice/USBHID/USBMouseKeyboard.o \
	$(OBJDIR)/libraries/USBDevice/USBHID/USBKeyboard.o \
	$(OBJDIR)/libraries/USBDevice/USBDevice/USBHAL_KL25Z.o \
	$(OBJDIR)/libraries/USBDevice/USBDevice/USBDevice.o \
	$(OBJDIR)/libraries/USBDevice/USBDevice/USBHAL_LPC17.o \
	$(OBJDIR)/libraries/USBDevice/USBDevice/USBHAL_LPC40.o \
	$(OBJDIR)/libraries/USBDevice/USBDevice/USBHAL_LPC11U.o \
	$(OBJDIR)/libraries/USBDevice/USBDevice/USBHAL_STM32F4.o \
	$(OBJDIR)/libraries/USBDevice/USBAudio/USBAudio.o \
	$(OBJDIR)/libraries/USBDevice/USBSerial/USBSerial.o \
	$(OBJDIR)/libraries/USBDevice/USBSerial/USBCDC.o \
	$(OBJDIR)/libraries/USBDevice/USBMSD/USBMSD.o \
	$(OBJDIR)/libraries/USBDevice/USBMIDI/USBMIDI.o

INCLUDE_PATHS += \
	-I$(MBED_DIR)/libraries/mbed/targets \
	-I$(MBED_DIR)/libraries/mbed/targets/hal \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_NXP \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX \
	-I$(MBED_DIR)/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/TARGET_LPC11U35_401 \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM \
	-I$(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM/TARGET_LPC11U35_401 \
	-I$(MBED_DIR)/libraries/mbed \
	-I$(MBED_DIR)/libraries/mbed/hal \
	-I$(MBED_DIR)/libraries/mbed/api \
	-I$(MBED_DIR)/libraries/mbed/common \
	-I$(MBED_DIR)/libraries/USBDevice \
	-I$(MBED_DIR)/libraries/USBDevice/USBHID \
	-I$(MBED_DIR)/libraries/USBDevice/USBDevice \
	-I$(MBED_DIR)/libraries/USBDevice/USBAudio \
	-I$(MBED_DIR)/libraries/USBDevice/USBSerial \
	-I$(MBED_DIR)/libraries/USBDevice/USBMSD \
	-I$(MBED_DIR)/libraries/USBDevice/USBMIDI

OBJECTS += \
	$(OBJDIR)/protocol/mbed/mbed_driver.o \
	$(OBJDIR)/protocol/mbed/HIDKeyboard.o \

INCLUDE_PATHS += \
	-I$(TMK_DIR)/protocol/mbed

LINKER_SCRIPT = $(MBED_DIR)/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM/TARGET_LPC11U35_401/LPC11U35.ld
