# Copyright 2017 Jack Humbert
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# If it's possible that multiple bootloaders can be used for one project,
# you can leave this unset, and the correct size will be selected
# automatically.
#
# Sets the bootloader defined in the keyboard's/keymap's rules.mk
#
# Current options for ARM:
#     halfkay      PJRC Teensy
#     kiibohd      Input:Club Kiibohd bootloader (only used on their boards)
#     stm32duino   STM32Duino (STM32F103x8)
#     stm32-dfu    STM32 USB DFU in ROM
#     apm32-dfu    APM32 USB DFU in ROM
#     wb32-dfu     WB32 USB DFU in ROM
#     tinyuf2      TinyUF2
#     rp2040       Raspberry Pi RP2040
# Current options for RISC-V:
#     gd32v-dfu    GD32V USB DFU in ROM
#
# If you need to provide your own implementation, you can set inside `rules.mk`
# `BOOTLOADER = custom` -- you'll need to provide your own implementations. See
# the respective file under `platforms/<PLATFORM>/bootloaders/custom.c` to see
# which functions may be overridden.

FIRMWARE_FORMAT?=bin

ifeq ($(strip $(BOOTLOADER)), custom)
    OPT_DEFS += -DBOOTLOADER_CUSTOM
    BOOTLOADER_TYPE = custom
endif

ifeq ($(strip $(BOOTLOADER)), halfkay)
    OPT_DEFS += -DBOOTLOADER_HALFKAY
    BOOTLOADER_TYPE = halfkay

    # Teensy LC, 3.0, 3.1/2, 3.5, 3.6
    ifneq (,$(filter $(MCU_ORIG), MKL26Z64 MK20DX128 MK20DX256 MK64FX512 MK66FX1M0))
        FIRMWARE_FORMAT = hex
    endif
endif
ifeq ($(strip $(BOOTLOADER)), stm32-dfu)
    OPT_DEFS += -DBOOTLOADER_STM32_DFU
    BOOTLOADER_TYPE = stm32_dfu

    # Options to pass to dfu-util when flashing
    DFU_ARGS ?= -d 0483:DF11 -a 0 -s 0x08000000:leave
    DFU_SUFFIX_ARGS ?= -v 0483 -p DF11
endif
ifeq ($(strip $(BOOTLOADER)), apm32-dfu)
    OPT_DEFS += -DBOOTLOADER_APM32_DFU
    BOOTLOADER_TYPE = stm32_dfu

    # Options to pass to dfu-util when flashing
    DFU_ARGS ?= -d 314B:0106 -a 0 -s 0x08000000:leave
    DFU_SUFFIX_ARGS ?= -v 314B -p 0106
endif
ifeq ($(strip $(BOOTLOADER)), gd32v-dfu)
    OPT_DEFS += -DBOOTLOADER_GD32V_DFU
    BOOTLOADER_TYPE = gd32v_dfu

    # Options to pass to dfu-util when flashing
    DFU_ARGS ?= -d 28E9:0189 -a 0 -s 0x08000000:leave
    DFU_SUFFIX_ARGS ?= -v 28E9 -p 0189
endif
ifeq ($(strip $(BOOTLOADER)), kiibohd)
    OPT_DEFS += -DBOOTLOADER_KIIBOHD
    BOOTLOADER_TYPE = kiibohd

    ifeq ($(strip $(MCU_ORIG)), MK20DX128)
        MCU_LDSCRIPT = MK20DX128BLDR4
    endif
    ifeq ($(strip $(MCU_ORIG)), MK20DX256)
        MCU_LDSCRIPT = MK20DX256BLDR8
    endif

    # Options to pass to dfu-util when flashing
    DFU_ARGS = -d 1C11:B007
    DFU_SUFFIX_ARGS = -v 1C11 -p B007
endif
ifeq ($(strip $(BOOTLOADER)), stm32duino)
    OPT_DEFS += -DBOOTLOADER_STM32DUINO
    BOARD = STM32_F103_STM32DUINO
    BOOTLOADER_TYPE = stm32duino

    # Options to pass to dfu-util when flashing
    DFU_ARGS = -d 1EAF:0003 -a 2 -R
    DFU_SUFFIX_ARGS = -v 1EAF -p 0003
endif
ifeq ($(strip $(BOOTLOADER)), tinyuf2)
    OPT_DEFS += -DBOOTLOADER_TINYUF2
    BOOTLOADER_TYPE = tinyuf2
    FIRMWARE_FORMAT = uf2
endif
ifeq ($(strip $(BOOTLOADER)), uf2boot)
    OPT_DEFS += -DBOOTLOADER_UF2BOOT
    BOARD = STM32_F103_STM32DUINO
    BOOTLOADER_TYPE = uf2boot
    FIRMWARE_FORMAT = uf2
endif
ifeq ($(strip $(BOOTLOADER)), rp2040)
    OPT_DEFS += -DBOOTLOADER_RP2040
    BOOTLOADER_TYPE = rp2040
endif
ifeq ($(strip $(BOOTLOADER)), wb32-dfu)
    OPT_DEFS += -DBOOTLOADER_WB32_DFU
    BOOTLOADER_TYPE = wb32_dfu
endif

ifeq ($(strip $(BOOTLOADER_TYPE)),)
    ifneq ($(strip $(BOOTLOADER)),)
        $(call CATASTROPHIC_ERROR,Invalid BOOTLOADER,Invalid bootloader specified. Please set an appropriate bootloader in your rules.mk or info.json.)
    else
        $(call CATASTROPHIC_ERROR,Invalid BOOTLOADER,No bootloader specified. Please set an appropriate bootloader in your rules.mk or info.json.)
    endif
endif
