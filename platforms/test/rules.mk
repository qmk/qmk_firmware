eeprom_legacy_emulated_flash_DEFS  := -DEEPROM_TEST_HARNESS -DLEGACY_FLASH_OPS_MOCKED -DNO_PRINT -DFEE_FLASH_BASE=FlashBuf
eeprom_legacy_emulated_flash_tiny_DEFS := $(eeprom_legacy_emulated_flash_DEFS) \
	-DFEE_MCU_FLASH_SIZE=1 \
	-DMOCK_FLASH_SIZE=1024 \
	-DFEE_PAGE_SIZE=512 \
	-DFEE_PAGE_COUNT=1
eeprom_legacy_emulated_flash_large_DEFS := $(eeprom_legacy_emulated_flash_DEFS) \
	-DFEE_MCU_FLASH_SIZE=64 \
	-DMOCK_FLASH_SIZE=65536 \
	-DFEE_PAGE_SIZE=2048 \
	-DFEE_PAGE_COUNT=16

eeprom_legacy_emulated_flash_INC := \
	$(PLATFORM_PATH)/chibios/drivers/eeprom/ \
	$(PLATFORM_PATH)/chibios/drivers/flash/
eeprom_legacy_emulated_flash_tiny_INC := $(eeprom_legacy_emulated_flash_INC)
eeprom_legacy_emulated_flash_large_INC := $(eeprom_legacy_emulated_flash_INC)

eeprom_legacy_emulated_flash_SRC := \
	$(TOP_DIR)/drivers/eeprom/eeprom_driver.c \
	$(PLATFORM_PATH)/$(PLATFORM_KEY)/eeprom_legacy_emulated_flash_tests.cpp \
	$(PLATFORM_PATH)/$(PLATFORM_KEY)/legacy_flash_ops_mock.c \
	$(PLATFORM_PATH)/chibios/drivers/eeprom/eeprom_legacy_emulated_flash.c
eeprom_legacy_emulated_flash_tiny_SRC := $(eeprom_legacy_emulated_flash_SRC)
eeprom_legacy_emulated_flash_large_SRC := $(eeprom_legacy_emulated_flash_SRC)
