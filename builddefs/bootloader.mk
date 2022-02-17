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
# Current options:
#
# AVR:
#     halfkay      PJRC Teensy
#     caterina     Pro Micro (Sparkfun/generic)
#     atmel-dfu    Atmel factory DFU
#     lufa-dfu     LUFA DFU
#     qmk-dfu      QMK DFU (LUFA + blinkenlight)
#     qmk-hid      QMK HID (LUFA + blinkenlight)
#     bootloadhid  HIDBootFlash compatible (ATmega32A)
#     usbasploader USBaspLoader (ATmega328P)
# ARM:
#     kiibohd      Input:Club Kiibohd bootloader (only used on their boards)
#     stm32duino   STM32Duino (STM32F103x8)
#     stm32-dfu    STM32 USB DFU in ROM
#     apm32-dfu    APM32 USB DFU in ROM
# RISC-V:
#     gd32v-dfu    GD32V USB DFU in ROM
#
# BOOTLOADER_SIZE can still be defined manually, but it's recommended
# you add any possible configuration to this list

ifeq ($(strip $(BOOTLOADER)), atmel-dfu)
    OPT_DEFS += -DBOOTLOADER_ATMEL_DFU
    OPT_DEFS += -DBOOTLOADER_DFU
    ifneq (,$(filter $(MCU), at90usb162 atmega16u2 atmega32u2 atmega16u4 atmega32u4 at90usb646 at90usb647))
        BOOTLOADER_SIZE = 4096
    endif
    ifneq (,$(filter $(MCU), at90usb1286 at90usb1287))
        BOOTLOADER_SIZE = 8192
    endif
endif
ifeq ($(strip $(BOOTLOADER)), lufa-dfu)
    OPT_DEFS += -DBOOTLOADER_LUFA_DFU
    OPT_DEFS += -DBOOTLOADER_DFU
    ifneq (,$(filter $(MCU), at90usb162 atmega16u2 atmega32u2 atmega16u4 atmega32u4 at90usb646 at90usb647))
        BOOTLOADER_SIZE ?= 4096
    endif
    ifneq (,$(filter $(MCU), at90usb1286 at90usb1287))
        BOOTLOADER_SIZE ?= 8192
    endif
endif
ifeq ($(strip $(BOOTLOADER)), qmk-dfu)
    OPT_DEFS += -DBOOTLOADER_QMK_DFU
    OPT_DEFS += -DBOOTLOADER_DFU
    ifneq (,$(filter $(MCU), at90usb162 atmega16u2 atmega32u2 atmega16u4 atmega32u4 at90usb646 at90usb647))
        BOOTLOADER_SIZE ?= 4096
    endif
    ifneq (,$(filter $(MCU), at90usb1286 at90usb1287))
        BOOTLOADER_SIZE ?= 8192
    endif
endif
ifeq ($(strip $(BOOTLOADER)), qmk-hid)
    OPT_DEFS += -DBOOTLOADER_QMK_HID
    OPT_DEFS += -DBOOTLOADER_HID
    BOOTLOADER_SIZE ?= 4096
endif
ifeq ($(strip $(BOOTLOADER)), halfkay)
    OPT_DEFS += -DBOOTLOADER_HALFKAY
    ifeq ($(strip $(MCU)), atmega32u4)
        BOOTLOADER_SIZE = 512
    endif
    ifeq ($(strip $(MCU)), at90usb1286)
        BOOTLOADER_SIZE = 1024
    endif
endif
ifeq ($(strip $(BOOTLOADER)), caterina)
    OPT_DEFS += -DBOOTLOADER_CATERINA
    BOOTLOADER_SIZE = 4096
endif
ifneq (,$(filter $(BOOTLOADER), bootloadhid bootloadHID))
    OPT_DEFS += -DBOOTLOADER_BOOTLOADHID
    BOOTLOADER_SIZE = 4096
endif
ifneq (,$(filter $(BOOTLOADER), usbasploader USBasp))
    OPT_DEFS += -DBOOTLOADER_USBASP
    BOOTLOADER_SIZE = 4096
endif
ifeq ($(strip $(BOOTLOADER)), lufa-ms)
    OPT_DEFS += -DBOOTLOADER_MS
    BOOTLOADER_SIZE ?= 8192
    FIRMWARE_FORMAT = bin
cpfirmware: lufa_warning
.INTERMEDIATE: lufa_warning
lufa_warning: $(FIRMWARE_FORMAT)
	$(info @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@)
	$(info LUFA MASS STORAGE Bootloader selected)
	$(info DO NOT USE THIS BOOTLOADER IN NEW PROJECTS!)
	$(info It is extremely prone to bricking, and is only included to support existing boards.)
	$(info @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@)
endif
ifdef BOOTLOADER_SIZE
    OPT_DEFS += -DBOOTLOADER_SIZE=$(strip $(BOOTLOADER_SIZE))
endif

ifeq ($(strip $(BOOTLOADER)), stm32-dfu)
    OPT_DEFS += -DBOOTLOADER_STM32_DFU

    # Options to pass to dfu-util when flashing
    DFU_ARGS ?= -d 0483:DF11 -a 0 -s 0x08000000:leave
    DFU_SUFFIX_ARGS ?= -v 0483 -p DF11
endif
ifeq ($(strip $(BOOTLOADER)), apm32-dfu)
    OPT_DEFS += -DBOOTLOADER_APM32_DFU

    # Options to pass to dfu-util when flashing
    DFU_ARGS ?= -d 314B:0106 -a 0 -s 0x08000000:leave
    DFU_SUFFIX_ARGS ?= -v 314B -p 0106
endif
ifeq ($(strip $(BOOTLOADER)), gd32v-dfu)
    OPT_DEFS += -DBOOTLOADER_GD32V_DFU

    # Options to pass to dfu-util when flashing
    DFU_ARGS ?= -d 28E9:0189 -a 0 -s 0x08000000:leave
    DFU_SUFFIX_ARGS ?= -v 28E9 -p 0189
endif
ifeq ($(strip $(BOOTLOADER)), kiibohd)
    OPT_DEFS += -DBOOTLOADER_KIIBOHD
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
    MCU_LDSCRIPT = STM32F103x8_stm32duino_bootloader
    BOARD = STM32_F103_STM32DUINO
    # STM32F103 does NOT have an USB bootloader in ROM (only serial), so setting anything here does not make much sense
    STM32_BOOTLOADER_ADDRESS = 0x80000000

    # Options to pass to dfu-util when flashing
    DFU_ARGS = -d 1EAF:0003 -a 2 -R
    DFU_SUFFIX_ARGS = -v 1EAF -p 0003
endif
ifeq ($(strip $(BOOTLOADER)), tinyuf2)
    OPT_DEFS += -DBOOTLOADER_TINYUF2
endif
