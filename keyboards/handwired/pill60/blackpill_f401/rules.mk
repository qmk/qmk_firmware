# MCU name
MCU = STM32F401

# Address of the bootloader in system memory
STM32_BOOTLOADER_ADDRESS = 0x1FFF0000

# Options to pass to dfu-util when flashing
DFU_ARGS = -d 0483:DF11 -a 0 -s 0x08000000:leave
DFU_SUFFIX_ARGS = -v 0483 -p DF11

# Build Options
#   change yes to no to disable
#
KEYBOARD_SHARED_EP       = yes
