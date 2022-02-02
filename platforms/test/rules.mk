eeprom_flash_emulated_DEFS  := -DEEPROM_TEST_HARNESS -DFLASH_STM32_MOCKED -DNO_PRINT -DFEE_FLASH_BASE=FlashBuf
eeprom_flash_emulated_tiny_DEFS := $(eeprom_flash_emulated_DEFS) \
	-DFEE_MCU_FLASH_SIZE=1 \
	-DMOCK_FLASH_SIZE=1024 \
	-DFEE_PAGE_SIZE=512 \
	-DFEE_PAGE_COUNT=1
eeprom_flash_emulated_large_DEFS := $(eeprom_flash_emulated_DEFS) \
	-DFEE_MCU_FLASH_SIZE=64 \
	-DMOCK_FLASH_SIZE=65536 \
	-DFEE_PAGE_SIZE=2048 \
	-DFEE_PAGE_COUNT=16

eeprom_flash_emulated_INC := \
	$(PLATFORM_PATH)/chibios/ \
	$(PLATFORM_PATH)/chibios/drivers/eeprom
eeprom_flash_emulated_tiny_INC := $(eeprom_flash_emulated_INC)
eeprom_flash_emulated_large_INC := $(eeprom_flash_emulated_INC)

eeprom_flash_emulated_SRC := \
	$(TOP_DIR)/drivers/eeprom/eeprom_driver.c \
	$(PLATFORM_PATH)/$(PLATFORM_KEY)/eeprom_flash_emulated_tests.cpp \
	$(PLATFORM_PATH)/$(PLATFORM_KEY)/flash_stm32_mock.c \
	$(PLATFORM_PATH)/chibios/drivers/eeprom/eeprom_flash_emulated.c
eeprom_flash_emulated_tiny_SRC := $(eeprom_flash_emulated_SRC)
eeprom_flash_emulated_large_SRC := $(eeprom_flash_emulated_SRC)
