#
#            DMBS Build System
#     Released into the public domain.
#
#  dean [at] fourwalledcubicle [dot] com
#        www.fourwalledcubicle.com
#

# Run "make help" for target help.

MCU          = atmega128
ARCH         = AVR8
F_CPU        = 1000000
OPTIMIZATION = s
TARGET       = HID_EEPROM_Loader
SRC          = $(TARGET).c
CC_FLAGS     =
LD_FLAGS     =
OBJECT_FILES = InputEEData.o

# Default target
all:

# Determine the AVR sub-architecture of the build main application object file
FIND_AVR_SUBARCH = avr$(shell avr-objdump -f $(TARGET).o | grep architecture | cut -d':' -f3 | cut -d',' -f1)

# Create a linkable object file with the input binary EEPROM data stored in the FLASH section
InputEEData.o: InputEEData.bin $(TARGET).o $(MAKEFILE_LIST)
	@echo $(MSG_OBJCPY_CMD) Converting \"$<\" to a object file \"$@\"
	avr-objcopy -I binary -O elf32-avr -B $(call FIND_AVR_SUBARCH) --rename-section .data=.progmem.data,contents,alloc,readonly,data $< $@

# Include LUFA build script makefiles
include ../core.mk
include ../gcc.mk
include ../hid.mk
