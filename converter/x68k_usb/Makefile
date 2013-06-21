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
SRC =	keymap.c \
	matrix.c \
	led.c \
	protocol/serial_uart.c

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


# Boot Section Size in bytes
#   Teensy halfKay   512
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
OPT_DEFS += -DBOOTLOADER_SIZE=4096


# Build Options
#   *Comment out* to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = yes	# Console for debug(+400)
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
#NKRO_ENABLE = yes	# USB Nkey Rollover - not yet supported in LUFA



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


# Search Path
VPATH += $(TARGET_DIR)
VPATH += $(TOP_DIR)


include $(TOP_DIR)/protocol/pjrc.mk
include $(TOP_DIR)/protocol.mk
include $(TOP_DIR)/common.mk
include $(TOP_DIR)/rules.mk
