#
#             LUFA Library
#     Copyright (C) Dean Camera, 2009.
#              
#  dean [at] fourwalledcubicle [dot] com
#      www.fourwalledcubicle.com
#

# Makefile for the LUFA library itself.

LUFA_SRC_FILES =     ./Drivers/USB/LowLevel/DevChapter9.c        \
                     ./Drivers/USB/LowLevel/Endpoint.c           \
                     ./Drivers/USB/LowLevel/Host.c               \
                     ./Drivers/USB/LowLevel/HostChapter9.c       \
                     ./Drivers/USB/LowLevel/LowLevel.c           \
                     ./Drivers/USB/LowLevel/Pipe.c               \
                     ./Drivers/USB/HighLevel/Events.c            \
                     ./Drivers/USB/HighLevel/StdDescriptors.c    \
                     ./Drivers/USB/HighLevel/USBInterrupt.c      \
                     ./Drivers/USB/HighLevel/USBTask.c           \
                     ./Drivers/USB/Class/ConfigDescriptor.c      \
                     ./Drivers/USB/Class/HIDParser.c             \
                     ./Scheduler/Scheduler.c                     \
                     ./MemoryAllocator/DynAlloc.c                \
                     ./Drivers/Board/Temperature.c               \
                     ./Drivers/Peripheral/Serial.c               \
                     ./Drivers/Peripheral/SerialStream.c         \

all:
	
clean:
	rm -f $(LUFA_SRC_FILES:%.c=%.o)
	
clean_list:

doxygen:
	@echo Generating Library Documentation...
	@doxygen Doxygen.conf
	@echo Documentation Generation Complete.

clean_doxygen:
	rm -rf Documentation
