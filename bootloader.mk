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
# halfkay        PJRC Teensy
# caterina       Pro Micro (Sparkfun/generic)
# atmel-dfu      Atmel factory DFU
# lufa-dfu       LUFA DFU
# qmk-dfu        QMK DFU (LUFA + blinkenlight)
# bootloadHID    HIDBootFlash compatible (ATmega32A)
# USBasp         USBaspLoader (ATmega328P)
#
# BOOTLOADER_SIZE can still be defined manually, but it's recommended
# you add any possible configuration to this list

ifeq ($(strip $(BOOTLOADER)), atmel-dfu)
    OPT_DEFS += -DBOOTLOADER_ATMEL_DFU
    OPT_DEFS += -DBOOTLOADER_DFU
    ifneq (,$(filter $(MCU), at90usb646 atmega16u2 atmega16u4 atmega32u2 atmega32u4))
        BOOTLOADER_SIZE = 4096
    endif
    ifeq ($(strip $(MCU)), at90usb1286)
        BOOTLOADER_SIZE = 8192
    endif
endif
ifeq ($(strip $(BOOTLOADER)), lufa-dfu)
    OPT_DEFS += -DBOOTLOADER_LUFA_DFU
    OPT_DEFS += -DBOOTLOADER_DFU
    ifneq (,$(filter $(MCU), at90usb646 atmega16u2 atmega16u4 atmega32u2 atmega32u4))
        BOOTLOADER_SIZE = 4096
    endif
    ifeq ($(strip $(MCU)), at90usb1286)
        BOOTLOADER_SIZE = 8192
    endif
endif
ifeq ($(strip $(BOOTLOADER)), qmk-dfu)
    OPT_DEFS += -DBOOTLOADER_QMK_DFU
    OPT_DEFS += -DBOOTLOADER_DFU
    ifneq (,$(filter $(MCU), at90usb646 atmega16u2 atmega16u4 atmega32u2 atmega32u4))
        BOOTLOADER_SIZE = 4096
    endif
    ifeq ($(strip $(MCU)), at90usb1286)
        BOOTLOADER_SIZE = 8192
    endif
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
ifeq ($(strip $(BOOTLOADER)), bootloadHID)
    OPT_DEFS += -DBOOTLOADER_BOOTLOADHID
    BOOTLOADER_SIZE = 4096
endif
ifeq ($(strip $(BOOTLOADER)), USBasp)
    OPT_DEFS += -DBOOTLOADER_USBASP
    BOOTLOADER_SIZE = 4096
endif

ifdef BOOTLOADER_SIZE
    OPT_DEFS += -DBOOTLOADER_SIZE=$(strip $(BOOTLOADER_SIZE))
endif
