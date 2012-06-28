# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# WinAVR Makefile Template written by Eric B. Weddington, Jörg Wunsch, et al.
#  >> Modified for use with the LUFA project. <<
#
# Released to the Public Domain
#
# Additional material for this makefile was written by:
# Peter Fleury
# Tim Henigan
# Colin O'Flynn
# Reiner Patommel
# Markus Pfaff
# Sander Pool
# Frederik Rouleau
# Carlos Lamas
# Dean Camera
# Opendous Inc.
# Denver Gingerich
#
#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
# make dfu = Download the hex file to the device, using dfu-programmer (must
#            have dfu-programmer installed).
#
# make flip = Download the hex file to the device, using Atmel FLIP (must
#             have Atmel FLIP installed).
#
# make dfu-ee = Download the eeprom file to the device, using dfu-programmer
#               (must have dfu-programmer installed).
#
# make flip-ee = Download the eeprom file to the device, using Atmel FLIP
#                (must have Atmel FLIP installed).
#
# make doxygen = Generate DoxyGen documentation for the project (must have
#                DoxyGen installed)
#
# make debug = Start either simulavr or avarice as specified for debugging,
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# Directory common source filess exist
TOP_DIR = ../..

# Directory keyboard dependent files exist
TARGET_DIR = .

# MCU name
#MCU = at90usb1287
MCU = atmega32u4


# Target architecture (see library "Board Types" documentation).
ARCH = AVR8


# Target board (see library "Board Types" documentation, NONE for projects not requiring
# LUFA board drivers). If USER is selected, put custom board drivers in a directory called
# "Board" inside the application directory.
BOARD = USBKEY


# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency in Hz. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#
#     This will be an integer division of F_USB below, as it is sourced by
#     F_USB after it has run through any CPU prescalers. Note that this value
#     does not *change* the processor frequency - it should merely be updated to
#     reflect the processor speed set externally so that the code can use accurate
#     software delays.
F_CPU = 16000000


# Input clock frequency.
#     This will define a symbol, F_USB, in all source code files equal to the
#     input clock frequency (before any prescaling is performed) in Hz. This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_USB = $(F_CPU)


# Target file name (without extension).
TARGET = lufa


# Path to the LUFA library
LUFA_PATH = ../../protocol

# Create the LUFA source path variables by including the LUFA root makefile
include $(LUFA_PATH)/LUFA/makefile



# List C source files here. (C dependencies are automatically generated.)
LUFA_SRC = $(TARGET).c \
	  descriptor.c \
	  $(LUFA_SRC_USB) \
	  $(LUFA_SRC_USBCLASS)

SRC = $(subst $(LUFA_PATH)/LUFA/,,$(LUFA_SRC))
SRC +=	keymap.c \
	matrix.c \
	led.c \
	pjrc/bootloader_teensy.c
CONFIG_H = config.h


# Build Options
#   comment out to disable the options.
#
MOUSEKEY_ENABLE = yes	# Mouse keys
#PS2_MOUSE_ENABLE = yes	# PS/2 mouse(TrackPoint) support
EXTRAKEY_ENABLE = yes	# Audio control and System control
#NKRO_ENABLE = yes	# USB Nkey Rollover


# LUFA library compile-time options and predefined tokens
LUFA_OPTS  = -D USB_DEVICE_ONLY
LUFA_OPTS += -D FIXED_CONTROL_ENDPOINT_SIZE=8
LUFA_OPTS += -D FIXED_NUM_CONFIGURATIONS=1
LUFA_OPTS += -D USE_FLASH_DESCRIPTORS
LUFA_OPTS += -D USE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"

OPT_DEFS  = -DF_CPU=$(F_CPU)UL
OPT_DEFS += -DF_USB=$(F_USB)UL
OPT_DEFS += -DBOARD=BOARD_$(BOARD) -DARCH=ARCH_$(ARCH)
OPT_DEFS += $(LUFA_OPTS)



# Search Path
VPATH += $(TARGET_DIR)
VPATH += $(LUFA_PATH)/LUFA


include $(TOP_DIR)/protocol.mk
include $(TOP_DIR)/common.mk
include $(TOP_DIR)/rules.mk

test:
	echo $(SRC)
