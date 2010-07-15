#
#             LUFA Library
#     Copyright (C) Dean Camera, 2010.
#              
#  dean [at] fourwalledcubicle [dot] com
#      www.fourwalledcubicle.com
#

# Makefile for the LUFA library itself.

LUFA_SRC_FILES =     ./Drivers/USB/LowLevel/DevChapter9.c        \
                     ./Drivers/USB/LowLevel/Device.c             \
                     ./Drivers/USB/LowLevel/Endpoint.c           \
                     ./Drivers/USB/LowLevel/Host.c               \
                     ./Drivers/USB/LowLevel/HostChapter9.c       \
                     ./Drivers/USB/LowLevel/LowLevel.c           \
                     ./Drivers/USB/LowLevel/Pipe.c               \
                     ./Drivers/USB/LowLevel/USBInterrupt.c       \
                     ./Drivers/USB/HighLevel/ConfigDescriptor.c  \
                     ./Drivers/USB/HighLevel/Events.c            \
                     ./Drivers/USB/HighLevel/USBTask.c           \
                     ./Drivers/USB/Class/Device/Audio.c          \
                     ./Drivers/USB/Class/Device/CDC.c            \
                     ./Drivers/USB/Class/Device/HID.c            \
                     ./Drivers/USB/Class/Device/MIDI.c           \
                     ./Drivers/USB/Class/Device/MassStorage.c    \
                     ./Drivers/USB/Class/Device/RNDIS.c          \
                     ./Drivers/USB/Class/Host/CDC.c              \
                     ./Drivers/USB/Class/Host/HID.c              \
                     ./Drivers/USB/Class/Host/HIDParser.c        \
                     ./Drivers/USB/Class/Host/MassStorage.c      \
                     ./Drivers/USB/Class/Host/Printer.c          \
                     ./Drivers/USB/Class/Host/StillImage.c       \
                     ./Drivers/Board/Temperature.c               \
                     ./Drivers/Peripheral/Serial.c               \
                     ./Drivers/Peripheral/SerialStream.c         \
                     ./Drivers/Peripheral/TWI.c                  \
					 ./Scheduler/Scheduler.c                     \

all:

clean:
	rm -f $(LUFA_SRC_FILES:%.c=%.o)
	
clean_list:

doxygen:
	@echo Generating Library Documentation...
	( cat Doxygen.conf ; echo "PROJECT_NUMBER=`grep LUFA_VERSION_STRING Version.h | cut -d'"' -f2`" ) | doxygen -
	@echo Documentation Generation Complete.

clean_doxygen:
	rm -rf Documentation
