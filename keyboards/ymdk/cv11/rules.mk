# SPDX-License-Identifier: BSD-2-Clause
## Tell the linker about the DapBoot Bootloader in the first 16KB of Flash.
MCU_LDSCRIPT = STM32F103xB_dapboot

## These option will automatically generate a UF2 file, suitable for
## copying to the UF2 USB-Mass-Storage partition that will appear
## when the keyboard is booted info DFU/Bootloader mode.
##
## Comment these out to generate a ".bin" firmware that is suitable
## for direct flashing with ST-Link-V2/OpenOCD .
STM32_BOOTLOADER_ADDRESS = 0x08004000
UF2_FAMILY = 0x5ee21072
