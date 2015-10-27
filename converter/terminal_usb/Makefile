# Target file name (without extension).
TARGET = terminal_lufa

# Directory common source filess exist
TMK_DIR = ../../tmk_core

# Directory keyboard dependent files exist
TARGET_DIR = .

# keyboard dependent files
SRC = 	keymap.c \
	matrix.c \
	led.c

CONFIG_H = config.h


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


#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
ARCH = AVR8

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

# Interrupt driven control endpoint task
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT


# Boot Section Size in bytes
#   Teensy halfKay   512
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
OPT_DEFS += -DBOOTLOADER_SIZE=4096


# Build Options
#   comment out to disable the options.
#
#BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
#MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
#EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = yes	# Console for debug(+400)
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
#NKRO_ENABLE = yes	# USB Nkey Rollover - not yet supported in LUFA


#
# PS/2 protocol implementations
# 	USART is recommended if it is available, others are for reference purpose.
# 	INT implementation will drop simultaneous key strokes.
#
PS2_USE_USART = yes	# uses hardware USART engine for PS/2 signal receive(recomened)
#PS2_USE_INT = yes	# uses external interrupt for falling edge of PS/2 clock pin
#PS2_USE_BUSYWAIT = yes	# uses primitive reference code


#---------------- Programming Options --------------------------
PROGRAM_CMD = teensy_loader_cli -mmcu=$(MCU) -w -v $(TARGET).hex


# Search Path
VPATH += $(TARGET_DIR)
VPATH += $(TMK_DIR)


include $(TMK_DIR)/protocol/lufa.mk
include $(TMK_DIR)/protocol.mk
include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk
