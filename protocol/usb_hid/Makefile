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
# make program = Download the hex file to the device.
#                Please customize your programmer settings(PROGRAM_CMD)
#
# make teensy = Download the hex file to the device, using teensy_loader_cli.
#               (must have teensy_loader_cli installed).
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

# Target file name (without extension).
TARGET = usbkbd

# Directory keyboard dependent files exist
TARGET_DIR = .

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




ARDUINO_DIR = arduino-1.0.1/cores
ARDUINO_SRC = \
	arduino/Print.cpp \
	arduino/Stream.cpp \
	arduino/wiring.c

#	arduino/main.cpp \
#	arduino/USBCore.cpp \
#	arduino/CDC.cpp \
#	arduino/HID.cpp \
#	arduino/HardwareSerial.cpp \
#	arduino/IPAddress.cpp \
#	arduino/Tone.cpp \
#	arduino/WMath.cpp \
#	arduino/WInterrupts.c \
#	arduino/wiring_analog.c \
#	arduino/wiring_pulse.c \
#	arduino/wiring_shift.c
#	arduino/wiring_digital.c \
#	arduino/WString.cpp \
#	arduino/new.cpp \

USB_HOST_DIR = ./USB_Host_Shield_2.0
USB_HOST_SRC = \
	Usb.cpp \
	cdcacm.cpp \
	cdcftdi.cpp \
	cdcprolific.cpp \
	hid.cpp \
	hidboot.cpp \
	hiduniversal.cpp \
	hidusagetitlearrays.cpp \
	hidescriptorparser.cpp \
	message.cpp \
	parsetools.cpp

	#PS3BT.cpp \
	#PS3USB.cpp \
	#RFCOMM.cpp \
	#XBOXUSB.cpp \
	#adk.cpp \
	#masstorage.cpp \
	#max_LCD.cpp \
	#usbhub.cpp

#SRC =  host_kbd.cpp
SRC =  main.cpp
SRC +=  parser.cpp
SRC +=  NullSerial.cpp
SRC += $(USB_HOST_SRC)
SRC += $(ARDUINO_SRC)

OPT_DEFS = -DARDUINO=101 -DUSB_VID=0x2341 -DUSB_PID=0x8036

# Search Path
VPATH += $(TARGET_DIR)
VPATH += $(USB_HOST_DIR)
VPATH += $(ARDUINO_DIR)
# for Arduino.h
VPATH += arduino-1.0.1/cores/arduino
# for pins_arduino.h
VPATH += arduino-1.0.1/variants/leonardo


# Ad hoc workaround to override original arduino/USBAPI.h with our own USBAPI.h.
# Obsolete but needed in order to remove directory including the current input file from search list.
# Option -iquote can't replace -I- for this purpose.
EXTRAFLAGS += -I-


# program Leonardo
PROGRAM_CMD = avrdude -patmega32u4 -cavr109 -P$(DEV) -b57600 -Uflash:w:$(TARGET).hex


include ../../rules.mk
