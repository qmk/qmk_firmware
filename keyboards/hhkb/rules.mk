

# project specific files
SRC = matrix.c

# MCU name
MCU = atmega32u4

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

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT


# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
#OPT_DEFS += -DBOOTLOADER_SIZE=4096

# as per original hasu settings
OPT_DEFS += -DBOOTLOADER_SIZE=4096

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes  # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes  # Audio control and System control(+450)
CONSOLE_ENABLE = yes   # Console for debug(+400)
COMMAND_ENABLE = yes   # Commands for debug and configuration
CUSTOM_MATRIX = yes    # Custom matrix file for the HHKB
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
# NKRO_ENABLE = yes       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
# MIDI_ENABLE = yes       # MIDI controls
# UNICODE_ENABLE = yes    # Unicode
# BLUETOOTH_ENABLE = yes  # Enable Bluetooth with the Adafruit EZ-Key HID


# HHKB_RN42_ENABLE = yes  # Enable support for hasu's BT alt controller -- code borrowed from tmk source tree.

# Either uncomment the HHKB_RN42_ENABLE line above, or run make enabling the
# feature. Be sure to clean any existing build before trying to enable rn42
# support. For example:
#
# make hhkb-keymap-clean
# make hhkb-keymap-dfu HHKB_RN42_ENABLE=yes

ifeq ($(strip $(HHKB_RN42_ENABLE)), yes)

OPT_DEFS += -DHHKB_RN42_ENABLE

# Support for the RN42 Bluetooth module. This is the BT module in Hasu's BT
# HHKB Alt controller.
RN42_DIR = rn42

SRC +=  serial_uart.c \
	rn42/suart.S \
	rn42/rn42.c \
	rn42/rn42_task.c \
	rn42/battery.c \
	rn42/main.c

VPATH += $(RN42_DIR)

endif


# debug-on: EXTRAFLAGS += -DDEBUG -DDEBUG_ACTION
# debug-on: all

# debug-off: EXTRAFLAGS += -DNO_DEBUG -DNO_PRINT
# debug-off: OPT_DEFS := $(filter-out -DCONSOLE_ENABLE,$(OPT_DEFS))
# debug-off: all
