#
#             LUFA Library
#     Copyright (C) Dean Camera, 2010.
#              
#  dean [at] fourwalledcubicle [dot] com
#      www.fourwalledcubicle.com
#

# Makefile for the LUFA library itself. This can be used to generate the library documentation.


# Check to see if the LUFA_PATH variable has not been set (the makefile is not being included from a project makefile)
ifeq ($(origin LUFA_PATH), undefined)
   LUFA_ROOT_PATH = .
else
   LUFA_ROOT_PATH = $(LUFA_PATH)/LUFA
endif

# Define module source file lists
LUFA_SRC_USB          = $(LUFA_ROOT_PATH)/Drivers/USB/LowLevel/Device.c             \
                        $(LUFA_ROOT_PATH)/Drivers/USB/LowLevel/Endpoint.c           \
                        $(LUFA_ROOT_PATH)/Drivers/USB/LowLevel/Host.c               \
                        $(LUFA_ROOT_PATH)/Drivers/USB/LowLevel/Pipe.c               \
                        $(LUFA_ROOT_PATH)/Drivers/USB/LowLevel/USBController.c      \
                        $(LUFA_ROOT_PATH)/Drivers/USB/LowLevel/USBInterrupt.c       \
                        $(LUFA_ROOT_PATH)/Drivers/USB/HighLevel/ConfigDescriptor.c  \
                        $(LUFA_ROOT_PATH)/Drivers/USB/HighLevel/DeviceStandardReq.c \
                        $(LUFA_ROOT_PATH)/Drivers/USB/HighLevel/Events.c            \
                        $(LUFA_ROOT_PATH)/Drivers/USB/HighLevel/HostStandardReq.c   \
                        $(LUFA_ROOT_PATH)/Drivers/USB/HighLevel/USBTask.c           \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/HIDParser.c
LUFA_SRC_USBCLASS     = $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/Audio.c          \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/CDC.c            \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/HID.c            \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/MassStorage.c    \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/MIDI.c           \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/RNDIS.c          \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/CDC.c              \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/HID.c              \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/MassStorage.c      \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/MIDI.c             \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/Printer.c          \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/RNDIS.c            \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/StillImage.c
LUFA_SRC_TEMPERATURE  = $(LUFA_ROOT_PATH)/Drivers/Board/Temperature.c
LUFA_SRC_SERIAL       = $(LUFA_ROOT_PATH)/Drivers/Peripheral/Serial.c
LUFA_SRC_SERIALSTREAM = $(LUFA_ROOT_PATH)/Drivers/Peripheral/SerialStream.c
LUFA_SRC_TWI          = $(LUFA_ROOT_PATH)/Drivers/Peripheral/TWI.c
LUFA_SRC_SCHEDULER    = $(LUFA_ROOT_PATH)/Scheduler/Scheduler.c


# Check to see if the LUFA_PATH variable has not been set (the makefile is not being included from a project makefile)
ifeq ($(origin LUFA_PATH), undefined)
   LUFA_SRC_ALL_FILES  = $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)       \
                         $(LUFA_SRC_TEMPERATURE) $(LUFA_SRC_SERIAL) \
                         $(LUFA_SRC_SERIALSTREAM) $(LUFA_SRC_TWI)   \
                         $(LUFA_SRC_SCHEDULER)

   all:

   clean:
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.o)
	
   clean_list:

   doxygen:
	@echo Generating Library Documentation...
	( cat Doxygen.conf ; echo "PROJECT_NUMBER=`grep LUFA_VERSION_STRING Version.h | cut -d'"' -f2`" ) | doxygen -
	@echo Documentation Generation Complete.

   clean_doxygen:
	rm -rf Documentation

   .PHONY: all clean clean_list doxygen clean_doxygen
endif