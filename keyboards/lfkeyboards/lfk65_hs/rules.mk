MCU = atmega32u4
OPT_DEFS += -DBOOTLOADER_SIZE=4096
FLASH_SIZE_KB = 32
BOOT_SECTION_SIZE_KB = 4
BOOT_LOADER = BootloaderHID

# Extra source files for IS3731 lighting
SRC = TWIlib.c issi.c lighting.c
