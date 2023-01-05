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
# Current options for AVR:
#     halfkay      PJRC Teensy
#     caterina     Pro Micro (Sparkfun/generic)
#     atmel-dfu    Atmel factory DFU
#     lufa-dfu     LUFA DFU
#     qmk-dfu      QMK DFU (LUFA + blinkenlight)
#     qmk-hid      QMK HID (LUFA + blinkenlight)
#     bootloadhid  HIDBootFlash compatible (ATmega32A)
#     usbasploader USBaspLoader (ATmega328P)
#
# If you need to provide your own implementation, you can set inside `rules.mk`
# `BOOTLOADER = custom` -- you'll need to provide your own implementations. See
# the respective file under `platforms/<PLATFORM>/bootloaders/custom.c` to see
# which functions may be overridden.
#
# BOOTLOADER_SIZE can still be defined manually, but it's recommended
# you add any possible configuration to this list

ifeq ($(strip $(BOOTLOADER)), custom)
    OPT_DEFS += -DBOOTLOADER_CUSTOM
    BOOTLOADER_TYPE = custom
endif

ifeq ($(strip $(BOOTLOADER)), atmel-dfu)
    OPT_DEFS += -DBOOTLOADER_ATMEL_DFU
    OPT_DEFS += -DBOOTLOADER_DFU
    BOOTLOADER_TYPE = dfu

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
    BOOTLOADER_TYPE = dfu

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
    BOOTLOADER_TYPE = dfu

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
    BOOTLOADER_TYPE = dfu

    BOOTLOADER_SIZE ?= 4096
endif
ifeq ($(strip $(BOOTLOADER)), halfkay)
    OPT_DEFS += -DBOOTLOADER_HALFKAY
    BOOTLOADER_TYPE = halfkay

    # Teensy 2.0
    ifeq ($(strip $(MCU)), atmega32u4)
        BOOTLOADER_SIZE = 512
    endif
    # Teensy 2.0++
    ifeq ($(strip $(MCU)), at90usb1286)
        BOOTLOADER_SIZE = 1024
    endif
endif
ifeq ($(strip $(BOOTLOADER)), caterina)
    OPT_DEFS += -DBOOTLOADER_CATERINA
    BOOTLOADER_TYPE = caterina

    BOOTLOADER_SIZE = 4096
endif
ifeq ($(strip $(BOOTLOADER)), bootloadhid)
    OPT_DEFS += -DBOOTLOADER_BOOTLOADHID
    BOOTLOADER_TYPE = bootloadhid

    BOOTLOADER_SIZE = 4096
endif
ifeq ($(strip $(BOOTLOADER)), usbasploader)
    OPT_DEFS += -DBOOTLOADER_USBASP
    BOOTLOADER_TYPE = usbasploader

    BOOTLOADER_SIZE = 4096
endif
ifeq ($(strip $(BOOTLOADER)), lufa-ms)
    OPT_DEFS += -DBOOTLOADER_MS
    BOOTLOADER_TYPE = dfu

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

ifeq ($(strip $(BOOTLOADER_TYPE)),)
    ifneq ($(strip $(BOOTLOADER)),)
        $(call CATASTROPHIC_ERROR,Invalid BOOTLOADER,Invalid bootloader specified. Please set an appropriate bootloader in your rules.mk or info.json.)
    else
        $(call CATASTROPHIC_ERROR,Invalid BOOTLOADER,No bootloader specified. Please set an appropriate bootloader in your rules.mk or info.json.)
    endif
endif
