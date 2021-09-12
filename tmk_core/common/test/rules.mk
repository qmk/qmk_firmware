eeprom_stm32_DEFS  := -DFLASH_STM32_MOCKED -DNO_PRINT -DFEE_FLASH_BASE=FlashBuf
eeprom_stm32_tiny_DEFS := $(eeprom_stm32_DEFS) \
	-DFEE_MCU_FLASH_SIZE=1 \
	-DMOCK_FLASH_SIZE=1024 \
	-DFEE_PAGE_SIZE=512 \
	-DFEE_PAGE_COUNT=1
eeprom_stm32_large_DEFS := $(eeprom_stm32_DEFS) \
	-DFEE_MCU_FLASH_SIZE=64 \
	-DMOCK_FLASH_SIZE=65536 \
	-DFEE_PAGE_SIZE=2048 \
	-DFEE_PAGE_COUNT=16

eeprom_stm32_INC := \
	$(TMK_PATH)/common/chibios/
eeprom_stm32_tiny_INC := $(eeprom_stm32_INC)
eeprom_stm32_large_INC := $(eeprom_stm32_INC)

eeprom_stm32_SRC := \
	$(TMK_PATH)/common/test/eeprom_stm32_tests.cpp \
	$(TMK_PATH)/common/test/flash_stm32_mock.c \
	$(TMK_PATH)/common/chibios/eeprom_stm32.c
eeprom_stm32_tiny_SRC := $(eeprom_stm32_SRC)
eeprom_stm32_large_SRC := $(eeprom_stm32_SRC)
