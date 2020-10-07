# MCU name
MCU = STM32F411
# BOARD = BLACKPILL_STM32_F411

# Address of the bootloader in system memory
STM32_BOOTLOADER_ADDRESS = 0x1FFF0000
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
