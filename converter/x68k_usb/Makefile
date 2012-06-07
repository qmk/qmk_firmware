#
# Makefile for PJRC Teensy
#


# Target file name (without extension).
TARGET = x68k_usb_pjrc

# Directory common source filess exist
TOP_DIR = ../..

# Directory keyboard dependent files exist
TARGET_DIR = .

# keyboard dependent files
SRC =	main.c \
	keymap.c \
	matrix.c \
	led.c \
	x68k.c

CONFIG_H = config_pjrc.h


# MCU name, you MUST set this to match the board you are using
# type "make clean" after changing this, so all files will be rebuilt
#MCU = at90usb162       # Teensy 1.0
MCU = atmega32u4       # Teensy 2.0
#MCU = at90usb646       # Teensy++ 1.0
#MCU = at90usb1286      # Teensy++ 2.0


# Processor frequency.
#   Normally the first thing your program should do is set the clock prescaler,
#   so your program will run at the correct speed.  You should also set this
#   variable to same clock speed.  The _delay_ms() macro uses this, and many
#   examples use this variable to calculate timings.  Do not add a "UL" here.
F_CPU = 16000000


# Build Options
#   *Comment out* to disable the options.
#
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
NKRO_ENABLE = yes	# USB Nkey Rollover



#---------------- Programming Options --------------------------
AVRDUDE = avrdude
# Type: avrdude -c ? to get a full listing.
AVRDUDE_PROGRAMMER = avr109
AVRDUDE_PORT = /dev/ttyACM0
AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep

# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude> 
# to submit bug reports.
#AVRDUDE_VERBOSE = -v -v

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
#AVRDUDE_FLAGS = -p $(MCU) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)

#PROGRAM_CMD = $(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)
#PROGRAM_CMD = teensy_loader_cli -mmcu=$(MCU) -w -v $(TARGET).hex
PROGRAM_CMD = dfu-programmer atmega32u4 flash $(TARGET).hex



include $(TOP_DIR)/protocol/pjrc.mk
include $(TOP_DIR)/protocol.mk
include $(TOP_DIR)/common.mk
include $(TOP_DIR)/rules.mk
