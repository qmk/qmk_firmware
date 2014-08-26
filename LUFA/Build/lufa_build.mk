#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

LUFA_BUILD_MODULES         += BUILD
LUFA_BUILD_TARGETS         += size symbol-sizes all lib elf bin hex lss clean mostlyclean
LUFA_BUILD_MANDATORY_VARS  += TARGET ARCH MCU SRC F_USB LUFA_PATH
LUFA_BUILD_OPTIONAL_VARS   += BOARD OPTIMIZATION C_STANDARD CPP_STANDARD F_CPU C_FLAGS CPP_FLAGS ASM_FLAGS CC_FLAGS LD_FLAGS OBJDIR OBJECT_FILES DEBUG_TYPE DEBUG_LEVEL LINKER_RELAXATIONS COMPILER_PATH
LUFA_BUILD_PROVIDED_VARS   +=
LUFA_BUILD_PROVIDED_MACROS +=

# -----------------------------------------------------------------------------
#               LUFA GCC Compiler Buildsystem Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Provides a set of targets to build a C, C++ and/or Assembly application
#   via the AVR-GCC compiler.
# -----------------------------------------------------------------------------
# TARGETS:
#
#    size                      - List built application size
#    symbol-sizes              - Print application symbols from the binary ELF
#                                file as a list sorted by size in bytes
#    all                       - Build application and list size
#    lib                       - Build and archive source files into a library
#    elf                       - Build application ELF debug object file
#    bin                       - Build application BIN binary object file
#    hex                       - Build application HEX object file
#    lss                       - Build application LSS assembly listing file
#    clean                     - Remove all project intermediary and binary
#                                output files
#    mostlyclean               - Remove intermediary output files, but
#                                preserve binaries
#    <filename>.s              - Compile C/C++ source file into an assembly file
#                                for manual code inspection
#
# MANDATORY PARAMETERS:
#
#    TARGET                    - Application name
#    ARCH                      - Device architecture name
#    MCU                       - Microcontroller device model name
#    SRC                       - List of input source files (*.c, *.cpp, *.S)
#    F_USB                     - Speed of the input clock of the USB controller
#                                in Hz
#    LUFA_PATH                 - Path to the LUFA library core
#
# OPTIONAL PARAMETERS:
#
#    BOARD                     - LUFA board hardware
#    OPTIMIZATION              - Optimization level
#    C_STANDARD                - C Language Standard to use
#    CPP_STANDARD              - C++ Language Standard to use
#    F_CPU                     - Speed of the CPU, in Hz
#    C_FLAGS                   - Flags to pass to the C compiler only
#    CPP_FLAGS                 - Flags to pass to the C++ compiler only
#    ASM_FLAGS                 - Flags to pass to the assembler only
#    CC_FLAGS                  - Common flags to pass to the C/C++ compiler and
#                                assembler
#    LD_FLAGS                  - Flags to pass to the linker
#    LINKER_RELAXATIONS        - Enable or disable linker relaxations to
#                                decrease binary size (note: can cause link
#                                failures on systems with an unpatched binutils)
#    OBJDIR                    - Directory for the output object and dependency
#                                files; if equal to ".", the output files will
#                                be generated in the same folder as the sources
#    OBJECT_FILES              - Extra object files to link in to the binaries
#    DEBUG_FORMAT              - Format of the debugging information to
#                                generate in the compiled object files
#    DEBUG_LEVEL               - Level the debugging information to generate in
#                                the compiled object files
#    COMPILER_PATH             - Location of the GCC toolchain to use
#
# PROVIDED VARIABLES:
#
#    (None)
#
# PROVIDED MACROS:
#
#    (None)
#
# -----------------------------------------------------------------------------

SHELL = /bin/sh

ERROR_IF_UNSET   ?= $(if $(filter undefined, $(origin $(strip $(1)))), $(error Makefile $(strip $(1)) value not set))
ERROR_IF_EMPTY   ?= $(if $(strip $($(strip $(1)))), , $(error Makefile $(strip $(1)) option cannot be blank))
ERROR_IF_NONBOOL ?= $(if $(filter Y N, $($(strip $(1)))), , $(error Makefile $(strip $(1)) option must be Y or N))

# Default values of optionally user-supplied variables
COMPILER_PATH      ?=
BOARD              ?= NONE
OPTIMIZATION       ?= s
F_CPU              ?=
C_STANDARD         ?= gnu99
CPP_STANDARD       ?= gnu++98
C_FLAGS            ?=
CPP_FLAGS          ?=
ASM_FLAGS          ?=
CC_FLAGS           ?=
OBJDIR             ?= .
OBJECT_FILES       ?=
DEBUG_FORMAT       ?= dwarf-2
DEBUG_LEVEL        ?= 2
LINKER_RELAXATIONS ?= Y

# Sanity check user supplied values
$(foreach MANDATORY_VAR, $(LUFA_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
$(call ERROR_IF_EMPTY, MCU)
$(call ERROR_IF_EMPTY, TARGET)
$(call ERROR_IF_EMPTY, ARCH)
$(call ERROR_IF_EMPTY, F_USB)
$(call ERROR_IF_EMPTY, LUFA_PATH)
$(call ERROR_IF_EMPTY, BOARD)
$(call ERROR_IF_EMPTY, OPTIMIZATION)
$(call ERROR_IF_EMPTY, C_STANDARD)
$(call ERROR_IF_EMPTY, CPP_STANDARD)
$(call ERROR_IF_EMPTY, OBJDIR)
$(call ERROR_IF_EMPTY, DEBUG_FORMAT)
$(call ERROR_IF_EMPTY, DEBUG_LEVEL)
$(call ERROR_IF_NONBOOL, LINKER_RELAXATIONS)

# Determine the utility prefix to use for the selected architecture
ifeq ($(ARCH), AVR8)
   CROSS        := $(COMPILER_PATH)avr
else ifeq ($(ARCH), XMEGA)
   CROSS        := $(COMPILER_PATH)avr
   $(warning The XMEGA device support is currently EXPERIMENTAL (incomplete and/or non-functional), and is included for preview purposes only.)
else ifeq ($(ARCH), UC3)
   CROSS        := $(COMPILER_PATH)avr32
   $(warning The UC3 device support is currently EXPERIMENTAL (incomplete and/or non-functional), and is included for preview purposes only.)
else
   $(error Unsupported architecture "$(ARCH)")
endif

# Output Messages
MSG_INFO_MESSAGE := ' [INFO]    :'
MSG_COMPILE_CMD  := ' [GCC]     :'
MSG_ASSEMBLE_CMD := ' [GAS]     :'
MSG_NM_CMD       := ' [NM]      :'
MSG_REMOVE_CMD   := ' [RM]      :'
MSG_LINK_CMD     := ' [LNK]     :'
MSG_ARCHIVE_CMD  := ' [AR]      :'
MSG_SIZE_CMD     := ' [SIZE]    :'
MSG_OBJCPY_CMD   := ' [OBJCPY]  :'
MSG_OBJDMP_CMD   := ' [OBJDMP]  :'

# Convert input source file list to differentiate them by type
C_SOURCE   := $(filter %.c, $(SRC))
CPP_SOURCE := $(filter %.cpp, $(SRC))
ASM_SOURCE := $(filter %.S, $(SRC))

# Create a list of unknown source file types, if any are found throw an error
UNKNOWN_SOURCE := $(filter-out $(C_SOURCE) $(CPP_SOURCE) $(ASM_SOURCE), $(SRC))
ifneq ($(UNKNOWN_SOURCE),)
   $(error Unknown input source file formats: $(UNKNOWN_SOURCE))
endif

# Convert input source filenames into a list of required output object files
OBJECT_FILES += $(addsuffix .o, $(basename $(SRC)))

# Check if an output object file directory was specified instead of the input file location
ifneq ($(OBJDIR),.)
   # Prefix all the object filenames with the output object file directory path
   OBJECT_FILES    := $(addprefix $(patsubst %/,%,$(OBJDIR))/, $(notdir $(OBJECT_FILES)))

   # Check if any object file (without path) appears more than once in the object file list
   ifneq ($(words $(sort $(OBJECT_FILES))), $(words $(OBJECT_FILES)))
       $(error Cannot build with OBJDIR parameter set - one or more object file name is not unique)
   endif

   # Create the output object file directory if it does not exist and add it to the virtual path list
   $(shell mkdir $(OBJDIR) 2> /dev/null)
   VPATH           += $(dir $(SRC))
endif

# Create a list of dependency files from the list of object files
DEPENDENCY_FILES := $(OBJECT_FILES:%.o=%.d)

# Create a list of common flags to pass to the compiler/linker/assembler
BASE_CC_FLAGS    := -pipe -g$(DEBUG_FORMAT) -g$(DEBUG_LEVEL)
ifeq ($(ARCH), AVR8)
   BASE_CC_FLAGS += -mmcu=$(MCU) -fshort-enums -fno-inline-small-functions -fpack-struct
else ifeq ($(ARCH), XMEGA)
   BASE_CC_FLAGS += -mmcu=$(MCU) -fshort-enums -fno-inline-small-functions -fpack-struct
else ifeq ($(ARCH), UC3)
   BASE_CC_FLAGS += -mpart=$(MCU:at32%=%) -masm-addr-pseudos
endif
BASE_CC_FLAGS += -Wall -fno-strict-aliasing -funsigned-char -funsigned-bitfields -ffunction-sections
BASE_CC_FLAGS += -I. -I$(patsubst %/,%,$(LUFA_PATH))/..
BASE_CC_FLAGS += -DARCH=ARCH_$(ARCH) -DBOARD=BOARD_$(BOARD) -DF_USB=$(F_USB)UL
ifneq ($(F_CPU),)
   BASE_CC_FLAGS += -DF_CPU=$(F_CPU)UL
endif
ifeq ($(LINKER_RELAXATIONS), Y)
BASE_CC_FLAGS += -mrelax
endif

# This flag is required for bootloaders as GCC will emit invalid jump table
# assembly code for devices with large amounts of flash; the jump table target
# is extracted from FLASH without using the correct ELPM instruction, resulting
# in a pseudo-random jump target.
BASE_CC_FLAGS += -fno-jump-tables

# Additional language specific compiler flags
BASE_C_FLAGS   := -x c -O$(OPTIMIZATION) -std=$(C_STANDARD) -Wstrict-prototypes
BASE_CPP_FLAGS := -x c++ -O$(OPTIMIZATION) -std=$(CPP_STANDARD)
BASE_ASM_FLAGS := -x assembler-with-cpp

# Create a list of flags to pass to the linker
BASE_LD_FLAGS := -lm -Wl,-Map=$(TARGET).map,--cref -Wl,--gc-sections
ifeq ($(LINKER_RELAXATIONS), Y)
   BASE_LD_FLAGS += -Wl,--relax
endif
ifeq ($(ARCH), AVR8)
   BASE_LD_FLAGS += -mmcu=$(MCU)
else ifeq ($(ARCH), XMEGA)
   BASE_LD_FLAGS += -mmcu=$(MCU)
else ifeq ($(ARCH), UC3)
   BASE_LD_FLAGS += -mpart=$(MCU:at32%=%) --rodata-writable --direct-data
endif

# Determine flags to pass to the size utility based on its reported features (only invoke if size target required)
# and on an architecture where this non-standard patch is available
ifneq ($(ARCH), UC3)
size: SIZE_MCU_FLAG    := $(shell $(CROSS)-size --help | grep -- --mcu > /dev/null && echo --mcu=$(MCU) )
size: SIZE_FORMAT_FLAG := $(shell $(CROSS)-size --help | grep -- --format=.*avr > /dev/null && echo --format=avr )
endif

# Pre-build informational target, to give compiler and project name information when building
build_begin:
	@echo $(MSG_INFO_MESSAGE) Begin compilation of project \"$(TARGET)\"...
	@echo ""
	@$(CROSS)-gcc --version

# Post-build informational target, to project name information when building has completed
build_end:
	@echo $(MSG_INFO_MESSAGE) Finished building project \"$(TARGET)\".

# Prints size information of a compiled application (FLASH, RAM and EEPROM usages)
size: $(TARGET).elf
	@echo $(MSG_SIZE_CMD) Determining size of \"$<\"
	@echo ""
	$(CROSS)-size $(SIZE_MCU_FLAG) $(SIZE_FORMAT_FLAG) $<

# Prints size information on the symbols within a compiled application in decimal bytes
symbol-sizes: $(TARGET).elf
	@echo $(MSG_NM_CMD) Extracting \"$<\" symbols with decimal byte sizes
	$(CROSS)-nm --size-sort --demangle --radix=d $<

# Cleans intermediary build files, leaving only the compiled application files
mostlyclean:
	@echo $(MSG_REMOVE_CMD) Removing object files of \"$(TARGET)\"
	rm -f $(OBJECT_FILES)
	@echo $(MSG_REMOVE_CMD) Removing dependency files of \"$(TARGET)\"
	rm -f $(DEPENDENCY_FILES)

# Cleans all build files, leaving only the original source code
clean: mostlyclean
	@echo $(MSG_REMOVE_CMD) Removing output files of \"$(TARGET)\"
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET).bin $(TARGET).eep $(TARGET).map $(TARGET).lss $(TARGET).sym lib$(TARGET).a

# Performs a complete build of the user application and prints size information afterwards
all: build_begin elf hex bin lss sym size build_end

# Helper targets, to build a specific type of output file without having to know the project target name
lib: lib$(TARGET).a
elf: $(TARGET).elf
hex: $(TARGET).hex $(TARGET).eep
bin: $(TARGET).bin
lss: $(TARGET).lss
sym: $(TARGET).sym

# Default target to *create* the user application's specified source files; if this rule is executed by
# make, the input source file doesn't exist and an error needs to be presented to the user
$(SRC):
	$(error Source file does not exist: $@)

# Compiles an input C source file and generates an assembly listing for it
%.s: %.c $(MAKEFILE_LIST)
	@echo $(MSG_COMPILE_CMD) Generating assembly from C file \"$(notdir $<)\"
	$(CROSS)-gcc -S $(BASE_CC_FLAGS) $(BASE_C_FLAGS) $(CC_FLAGS) $(C_FLAGS) $< -o $@

# Compiles an input C++ source file and generates an assembly listing for it
%.s: %.cpp $(MAKEFILE_LIST)
	@echo $(MSG_COMPILE_CMD) Generating assembly from C++ file \"$(notdir $<)\"
	$(CROSS)-gcc -S $(BASE_CC_FLAGS) $(BASE_CPP_FLAGS) $(CC_FLAGS) $(CPP_FLAGS) $< -o $@

# Compiles an input C source file and generates a linkable object file for it
$(OBJDIR)/%.o: %.c $(MAKEFILE_LIST)
	@echo $(MSG_COMPILE_CMD) Compiling C file \"$(notdir $<)\"
	$(CROSS)-gcc -c $(BASE_CC_FLAGS) $(BASE_C_FLAGS) $(CC_FLAGS) $(C_FLAGS) -MMD -MP -MF $(@:%.o=%.d) $< -o $@

# Compiles an input C++ source file and generates a linkable object file for it
$(OBJDIR)/%.o: %.cpp $(MAKEFILE_LIST)
	@echo $(MSG_COMPILE_CMD) Compiling C++ file \"$(notdir $<)\"
	$(CROSS)-gcc -c $(BASE_CC_FLAGS) $(BASE_CPP_FLAGS) $(CC_FLAGS) $(CPP_FLAGS) -MMD -MP -MF $(@:%.o=%.d) $< -o $@

# Assembles an input ASM source file and generates a linkable object file for it
$(OBJDIR)/%.o: %.S $(MAKEFILE_LIST)
	@echo $(MSG_ASSEMBLE_CMD) Assembling \"$(notdir $<)\"
	$(CROSS)-gcc -c $(BASE_CC_FLAGS) $(BASE_ASM_FLAGS) $(CC_FLAGS) $(ASM_FLAGS) -MMD -MP -MF $(@:%.o=%.d) $< -o $@

# Generates a library archive file from the user application, which can be linked into other applications
.PRECIOUS  : $(OBJECT_FILES)
.SECONDARY : %.a
%.a: $(OBJECT_FILES)
	@echo $(MSG_ARCHIVE_CMD) Archiving object files into \"$@\"
	$(CROSS)-ar rcs $@ $(OBJECT_FILES)

# Generates an ELF debug file from the user application, which can be further processed for FLASH and EEPROM data
# files, or used for programming and debugging directly
.PRECIOUS  : $(OBJECT_FILES)
.SECONDARY : %.elf
%.elf: $(OBJECT_FILES)
	@echo $(MSG_LINK_CMD) Linking object files into \"$@\"
	$(CROSS)-gcc $^ -o $@ $(BASE_LD_FLAGS) $(LD_FLAGS)

# Extracts out the loadable FLASH memory data from the project ELF file, and creates an Intel HEX format file of it
%.hex: %.elf
	@echo $(MSG_OBJCPY_CMD) Extracting HEX file data from \"$<\"
	$(CROSS)-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@

# Extracts out the loadable FLASH memory data from the project ELF file, and creates an Binary format file of it
%.bin: %.elf
	@echo $(MSG_OBJCPY_CMD) Extracting BIN file data from \"$<\"
	$(CROSS)-objcopy -O binary -R .eeprom -R .fuse -R .lock -R .signature $< $@

# Extracts out the loadable EEPROM memory data from the project ELF file, and creates an Intel HEX format file of it
%.eep: %.elf
	@echo $(MSG_OBJCPY_CMD) Extracting EEP file data from \"$<\"
	$(CROSS)-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings $< $@ || exit 0

# Creates an assembly listing file from an input project ELF file, containing interleaved assembly and source data
%.lss: %.elf
	@echo $(MSG_OBJDMP_CMD) Extracting LSS file data from \"$<\"
	$(CROSS)-objdump -h -d -S -z $< > $@

# Creates a symbol file listing the loadable and discarded symbols from an input project ELF file
%.sym: %.elf
	@echo $(MSG_NM_CMD) Extracting SYM file data from \"$<\"
	$(CROSS)-nm -n $< > $@

# Include build dependency files
-include $(DEPENDENCY_FILES)

# Phony build targets for this module
.PHONY: build_begin build_end size symbol-sizes lib elf hex lss clean mostlyclean
