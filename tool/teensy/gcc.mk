# The name of your project (used to name the compiled .hex file)
#TARGET = $(notdir $(CURDIR))

TEENSY_DIR=teensy-sdk

VPATH += $(TEENSY_DIR)

# Set to 24000000, 48000000, or 96000000 to set CPU core speed
TEENSY_CORE_SPEED = 48000000

# Some libraries will require this to be defined
# If you define this, you will break the default main.cpp
#ARDUINO = 105

# configurable options
OPT_DEFS += -DUSB_HID -DLAYOUT_US_ENGLISH -D__TEENSY__=$(TEENSY)

# directory to build in
BUILDDIR = $(abspath $(CURDIR)/build)

#************************************************************************
# Location of Teensyduino utilities, Toolchain, and Arduino Libraries.
# To use this makefile without Arduino, copy the resources from these
# locations and edit the pathnames.  The rest of Arduino is not needed.
#************************************************************************

# path location for Teensy Loader, teensy_post_compile and teensy_reboot
TOOLSPATH = $(TOP_DIR)/$(TEENSY_DIR)/tools

ifeq ($(OS),Windows_NT)
    $(error What is Win Dose?)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        TOOLSPATH = /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/
    endif
endif

# path location for Teensy 3 core
COREPATH = $(TOP_DIR)/$(TEENSY_DIR)/teensy3

# path location for Arduino libraries
#LIBRARYPATH = libraries

# path location for the arm-none-eabi compiler
COMPILERPATH = $(TOOLSPATH)/arm-none-eabi/bin

#************************************************************************
# Settings below this point usually do not need to be edited
#************************************************************************

EXTRAINCDIRS = $(subst :, ,$(VPATH))

# CPPFLAGS = compiler options for C and C++
CPPFLAGS  = -Wall -g -Os -mcpu=cortex-m4 -mthumb -nostdlib -MMD 
CPPFLAGS += $(OPT_DEFS) -DF_CPU=$(TEENSY_CORE_SPEED) -I$(COREPATH) 
CPPFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

# compiler options for C++ only
CXXFLAGS = -std=gnu++0x -felide-constructors -fno-exceptions -fno-rtti 

# compiler options for C only
CFLAGS = -std=gnu99 
ifdef CONFIG_H
    CPPFLAGS += -include $(CONFIG_H)
endif

# compiler options specific to teensy version
ifeq ($(TEENSY), 30)
    CPPFLAGS += -D__MK20DX128__
    LDSCRIPT = $(COREPATH)/mk20dx128.ld
else
    ifeq ($(TEENSY), 31)
        CPPFLAGS += -D__MK20DX256__
        LDSCRIPT = $(COREPATH)/mk20dx256.ld
    else
        $(error Invalid setting for TEENSY)
    endif
endif

# set arduino define if given
#ifdef ARDUINO
#	CPPFLAGS += -DARDUINO=$(ARDUINO)
#endif

# linker options
LDFLAGS = -Os -Wl,--gc-sections -mcpu=cortex-m4 -mthumb -T$(LDSCRIPT)

# additional libraries to link
LIBS = -lm

# names for the compiler programs
CC = $(abspath $(COMPILERPATH))/arm-none-eabi-gcc
CXX = $(abspath $(COMPILERPATH))/arm-none-eabi-g++
OBJCOPY = $(abspath $(COMPILERPATH))/arm-none-eabi-objcopy
SIZE = $(abspath $(COMPILERPATH))/arm-none-eabi-size

# automatically create lists of the sources and objects
TC_FILES := $(patsubst $(TOP_DIR)/%,%,$(wildcard $(COREPATH)/*.c))
TCPP_FILES := $(patsubst $(TOP_DIR)/%,%,$(wildcard $(COREPATH)/*.cpp))

SOURCES := $(SRC:.c=.o) $(SRCPP:.cpp=.o) $(TC_FILES:.c=.o) $(TCPP_FILES:.cpp=.o)
OBJS := $(foreach src,$(SOURCES), $(BUILDDIR)/$(src))

all: hex

build: $(TARGET).elf

hex: $(TARGET).hex

post_compile: $(TARGET).hex
	@$(abspath $(TOOLSPATH))/teensy_post_compile -file="$(basename $<)" \
		-path=$(CURDIR) -tools="$(abspath $(TOOLSPATH))"

reboot:
	@-$(abspath $(TOOLSPATH))/teensy_reboot

upload: post_compile reboot

$(BUILDDIR)/%.o: %.c
	@echo "[CC]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o "$@" -c "$<"

$(BUILDDIR)/%.o: %.cpp
	@echo "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o "$@" -c "$<"

$(TARGET).elf: $(OBJS) $(LDSCRIPT)
	@echo "[LD]\t$@"
	@$(CC) $(LDFLAGS) -o "$@" $(OBJS) $(LIBS)

%.hex: %.elf
	@echo "[HEX]\t$@"
	@$(SIZE) "$<"
	@$(OBJCOPY) -O ihex -R .eeprom "$<" "$@"

# compiler generated dependency info
-include $(OBJS:.o=.d)

clean:
	@echo Cleaning...
	@rm -rf "$(BUILDDIR)"
	@rm -f "$(TARGET).elf" "$(TARGET).hex"
