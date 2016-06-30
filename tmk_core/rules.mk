# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# WinAVR Makefile Template written by Eric B. Weddington, Jg Wunsch, et al.
#
# Released to the Public Domain
#
# Additional material for this makefile was written by:
# Peter Fleury
# Tim Henigan
# Colin O'Flynn
# Reiner Patommel
# Markus Pfaff
# Sander Pool
# Frederik Rouleau
# Carlos Lamas
#



# Output format. (can be srec, ihex, binary)
FORMAT = ihex

BUILD_DIR = .build

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = $(BUILD_DIR)/obj_$(TARGET)


# Optimization level, can be [0, 1, 2, 3, s].
#     0 = turn off optimization. s = optimize for size.
#     (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s


# Debugging format.
#     Native formats for AVR-GCC's -g are dwarf-2 [default] or stabs.
#     AVR Studio 4.10 requires dwarf-2.
#     AVR [Extended] COFF format requires stabs, plus an avr-objcopy run.
DEBUG = dwarf-2

COLOR ?= true

ifeq ($(COLOR),true)
	NO_COLOR=\033[0m
	OK_COLOR=\033[32;01m
	ERROR_COLOR=\033[31;01m
	WARN_COLOR=\033[33;01m
	BLUE=\033[0;34m
	BOLD=\033[1m
endif

ifneq ($(shell awk --version 2>/dev/null),)
	AWK=awk
else
	AWK=cat && test
endif

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)\n
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)\n
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)\n

ifndef $(SILENT)
	SILENT = false
endif

TAB_LOG = printf "\n$$LOG\n\n" | $(AWK) '{ sub(/^/," | "); print }'
TAB_LOG_PLAIN = printf "$$LOG\n"
AWK_STATUS = $(AWK) '{ printf " %-10s\n", $$1; }'
AWK_CMD = $(AWK) '{ printf "%-69s", $$0; }'
PRINT_ERROR = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG) && false
PRINT_WARNING = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG)
PRINT_ERROR_PLAIN = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN) && false
PRINT_WARNING_PLAIN = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN)
PRINT_OK = $(SILENT) || printf " $(OK_STRING)" | $(AWK_STATUS)
BUILD_CMD = LOG=$$($(CMD) 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING); else $(PRINT_OK); fi;

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRAINCDIRS = $(subst :, ,$(VPATH))


# Compiler flag to set the C Standard level.
#     c89   = "ANSI" C
#     gnu89 = c89 plus GCC extensions
#     c99   = ISO C99 standard (not yet fully implemented)
#     gnu99 = c99 plus GCC extensions
CSTANDARD = -std=gnu99


# Place -D or -U options here for C sources
CDEFS = -DF_CPU=$(F_CPU)UL
CDEFS += $(OPT_DEFS)


# Place -D or -U options here for ASM sources
ADEFS = -DF_CPU=$(F_CPU)
ADEFS += $(OPT_DEFS)


# Place -D or -U options here for C++ sources
CPPDEFS = -DF_CPU=$(F_CPU)UL
#CPPDEFS += -D__STDC_LIMIT_MACROS
#CPPDEFS += -D__STDC_CONSTANT_MACROS
CPPDEFS += $(OPT_DEFS)



#---------------- Compiler Options C ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS)
CFLAGS += -O$(OPT)
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -fno-inline-small-functions
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -fno-strict-aliasing
# add color
ifeq ($(COLOR),true)
ifeq ("$(shell echo "int main(){}" | $(CC) -fdiagnostics-color -x c - -o /dev/null 2>&1)", "")
	CFLAGS+= -fdiagnostics-color
endif
endif
CFLAGS += -Wall
CFLAGS += -Wstrict-prototypes
#CFLAGS += -mshort-calls
#CFLAGS += -fno-unit-at-a-time
#CFLAGS += -Wundef
#CFLAGS += -Wunreachable-code
#CFLAGS += -Wsign-compare
CFLAGS += -Wa,-adhlns=$(@:%.o=%.lst)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS += $(CSTANDARD)
ifdef CONFIG_H
    CFLAGS += -include $(CONFIG_H)
endif


#---------------- Compiler Options C++ ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CPPFLAGS = -g$(DEBUG)
CPPFLAGS += $(CPPDEFS)
CPPFLAGS += -O$(OPT)
CPPFLAGS += -funsigned-char
CPPFLAGS += -funsigned-bitfields
CPPFLAGS += -fpack-struct
CPPFLAGS += -fshort-enums
CPPFLAGS += -fno-exceptions
CPPFLAGS += -ffunction-sections
CPPFLAGS += -fdata-sections
# to supress "warning: only initialized variables can be placed into program memory area"
CPPFLAGS += -w
CPPFLAGS += -Wall
CPPFLAGS += -Wundef
#CPPFLAGS += -mshort-calls
#CPPFLAGS += -fno-unit-at-a-time
#CPPFLAGS += -Wstrict-prototypes
#CPPFLAGS += -Wunreachable-code
#CPPFLAGS += -Wsign-compare
CPPFLAGS += -Wa,-adhlns=$(@:%.o=%.lst)
CPPFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
#CPPFLAGS += $(CSTANDARD)
ifdef CONFIG_H
    CPPFLAGS += -include $(CONFIG_H)
endif


#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -adhlns:   create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex
#       dump that will be displayed for a given single line of source input.
ASFLAGS = $(ADEFS) -Wa,-adhlns=$(@:%.o=%.lst),-gstabs,--listing-cont-lines=100
ASFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
ifdef CONFIG_H
    ASFLAGS += -include $(CONFIG_H)
endif

#---------------- Library Options ----------------
# Minimalistic printf version
PRINTF_LIB_MIN = -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires MATH_LIB = -lm below)
PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt

# If this is left blank, then it will use the Standard printf version.
PRINTF_LIB =
#PRINTF_LIB = $(PRINTF_LIB_MIN)
#PRINTF_LIB = $(PRINTF_LIB_FLOAT)


# Minimalistic scanf version
SCANF_LIB_MIN = -Wl,-u,vfscanf -lscanf_min

# Floating point + %[ scanf version (requires MATH_LIB = -lm below)
SCANF_LIB_FLOAT = -Wl,-u,vfscanf -lscanf_flt

# If this is left blank, then it will use the Standard scanf version.
SCANF_LIB =
#SCANF_LIB = $(SCANF_LIB_MIN)
#SCANF_LIB = $(SCANF_LIB_FLOAT)


MATH_LIB = -lm


# List any extra directories to look for libraries here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRALIBDIRS =



#---------------- External Memory Options ----------------

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS = -Wl,-Tdata=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS = -Wl,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff

EXTMEMOPTS =



#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
#
# Comennt out "--relax" option to avoid a error such:
# 	(.vectors+0x30): relocation truncated to fit: R_AVR_13_PCREL against symbol `__vector_12'
#
LDFLAGS = -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref
#LDFLAGS += -Wl,--relax
LDFLAGS += -Wl,--gc-sections
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(patsubst %,-L%,$(EXTRALIBDIRS))
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)
#LDFLAGS += -T linker_script.x
# You can give EXTRALDFLAGS at 'make' command line.
LDFLAGS += $(EXTRALDFLAGS)



#---------------- Debugging Options ----------------

# For simulavr only - target MCU frequency.
DEBUG_MFREQ = $(F_CPU)

# Set the DEBUG_UI to either gdb or insight.
# DEBUG_UI = gdb
DEBUG_UI = insight

# Set the debugging back-end to either avarice, simulavr.
DEBUG_BACKEND = avarice
#DEBUG_BACKEND = simulavr

# GDB Init Filename.
GDBINIT_FILE = __avr_gdbinit

# When using avarice settings for the JTAG
JTAG_DEV = /dev/com1

# Debugging port used to communicate between GDB / avarice / simulavr.
DEBUG_PORT = 4242

# Debugging host used to communicate between GDB / avarice / simulavr, normally
#     just set to localhost unless doing some sort of crazy debugging when
#     avarice is running on a different computer.
DEBUG_HOST = localhost



#============================================================================


# Define programs and commands.
SHELL = sh
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AR = avr-ar rcs
NM = avr-nm
REMOVE = rm -f
REMOVEDIR = rmdir
COPY = cp
WINSHELL = cmd
SECHO = $(SILENT) || echo
# Autodecct teensy loader
ifneq (, $(shell which teensy-loader-cli 2>/dev/null))
  TEENSY_LOADER_CLI = teensy-loader-cli
else
  TEENSY_LOADER_CLI = teensy_loader_cli
endif

# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_COMPILING_CPP = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_CREATING_LIBRARY = Creating library:




# Define all object files.
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(patsubst %.cpp,$(OBJDIR)/%.o,$(patsubst %.S,$(OBJDIR)/%.o,$(SRC))))

# Define all listing files.
LST = $(patsubst %.c,$(OBJDIR)/%.lst,$(patsubst %.cpp,$(OBJDIR)/%.lst,$(patsubst %.S,$(OBJDIR)/%.lst,$(SRC))))


# Compiler flags to generate dependency files.
#GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d
GENDEPFLAGS = -MMD -MP -MF $(BUILD_DIR)/.dep/$(subst /,_,$@).d


# Combine all necessary flags and optional flags.
# Add target processor to flags.
# You can give extra flags at 'make' command line like: make EXTRAFLAGS=-DFOO=bar
ALL_CFLAGS = -mmcu=$(MCU) $(CFLAGS) $(GENDEPFLAGS) $(EXTRAFLAGS)
ALL_CPPFLAGS = -mmcu=$(MCU) -x c++ $(CPPFLAGS) $(GENDEPFLAGS) $(EXTRAFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -x assembler-with-cpp $(ASFLAGS) $(EXTRAFLAGS)

# Default target.
all:
	@$(MAKE) begin
	@$(MAKE) gccversion
	@$(MAKE) sizebefore
	@$(MAKE) clean_list # force clean each time
	@$(MAKE) build
	@$(MAKE) sizeafter
	@$(MAKE) end

# Quick make that doesn't clean
quick:
	@$(MAKE) begin
	@$(MAKE) gccversion
	@$(MAKE) sizebefore
	@$(MAKE) build
	@$(MAKE) sizeafter
	@$(MAKE) end

# Change the build target to build a HEX file or a library.
build: elf hex
#build: elf hex eep lss sym
#build: lib


elf: $(BUILD_DIR)/$(TARGET).elf
hex: $(BUILD_DIR)/$(TARGET).hex
eep: $(BUILD_DIR)/$(TARGET).eep
lss: $(BUILD_DIR)/$(TARGET).lss
sym: $(BUILD_DIR)/$(TARGET).sym
LIBNAME=lib$(TARGET).a
lib: $(LIBNAME)



# Eye candy.
# AVR Studio 3.x does not check make's exit code but relies on
# the following magic strings to be generated by the compile job.
begin:
	@$(SECHO) $(MSG_BEGIN)

end:
	@$(SECHO) $(MSG_END)


# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
#ELFSIZE = $(SIZE) --mcu=$(MCU) --format=avr $(TARGET).elf
ELFSIZE = $(SIZE) $(BUILD_DIR)/$(TARGET).elf

sizebefore:
	@if test -f $(TARGET).hex; then $(SECHO) $(MSG_SIZE_BEFORE); $(SILENT) || $(HEXSIZE); \
	2>/dev/null; $(SECHO); fi

sizeafter:
	@if test -f $(TARGET).hex; then $(SECHO); $(SECHO) $(MSG_SIZE_AFTER); $(SILENT) || $(HEXSIZE); \
	2>/dev/null; $(SECHO); fi
	# test file sizes eventually
	# @if [[ $($(SIZE) --target=$(FORMAT) $(TARGET).hex | $(AWK) 'NR==2 {print "0x"$5}') -gt 0x200 ]]; then $(SECHO) "File is too big!"; fi

# Display compiler version information.
gccversion :
	@$(SILENT) || $(CC) --version



# Program the device.
program: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep
	$(PROGRAM_CMD)

teensy: $(BUILD_DIR)/$(TARGET).hex
	$(TEENSY_LOADER_CLI) -mmcu=$(MCU) -w -v $(BUILD_DIR)/$(TARGET).hex

flip: $(BUILD_DIR)/$(TARGET).hex
	batchisp -hardware usb -device $(MCU) -operation erase f
	batchisp -hardware usb -device $(MCU) -operation loadbuffer $(BUILD_DIR)/$(TARGET).hex program
	batchisp -hardware usb -device $(MCU) -operation start reset 0

dfu: $(BUILD_DIR)/$(TARGET).hex sizeafter
ifneq (, $(findstring 0.7, $(shell dfu-programmer --version 2>&1)))
	dfu-programmer $(MCU) erase --force
else
	dfu-programmer $(MCU) erase
endif
	dfu-programmer $(MCU) flash $(BUILD_DIR)/$(TARGET).hex
	dfu-programmer $(MCU) reset

dfu-start:
	dfu-programmer $(MCU) reset
	dfu-programmer $(MCU) start

flip-ee: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep
	$(COPY) $(BUILD_DIR)/$(TARGET).eep $(BUILD_DIR)/$(TARGET)eep.hex
	batchisp -hardware usb -device $(MCU) -operation memory EEPROM erase
	batchisp -hardware usb -device $(MCU) -operation memory EEPROM loadbuffer $(BUILD_DIR)/$(TARGET)eep.hex program
	batchisp -hardware usb -device $(MCU) -operation start reset 0
	$(REMOVE) $(BUILD_DIR)/$(TARGET)eep.hex

dfu-ee: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep
ifneq (, $(findstring 0.7, $(shell dfu-programmer --version 2>&1)))
	dfu-programmer $(MCU) flash --eeprom $(BUILD_DIR)/$(TARGET).eep
else
	dfu-programmer $(MCU) flash-eeprom $(BUILD_DIR)/$(TARGET).eep
endif
	dfu-programmer $(MCU) reset


# Generate avr-gdb config/init file which does the following:
#     define the reset signal, load the target file, connect to target, and set
#     a breakpoint at main().
gdb-config:
	@$(REMOVE) $(GDBINIT_FILE)
	@echo define reset >> $(GDBINIT_FILE)
	@echo SIGNAL SIGHUP >> $(GDBINIT_FILE)
	@echo end >> $(GDBINIT_FILE)
	@echo file $(BUILD_DIR)/$(TARGET).elf >> $(GDBINIT_FILE)
	@echo target remote $(DEBUG_HOST):$(DEBUG_PORT)  >> $(GDBINIT_FILE)
ifeq ($(DEBUG_BACKEND),simulavr)
	@echo load  >> $(GDBINIT_FILE)
endif
	@echo break main >> $(GDBINIT_FILE)

debug: gdb-config $(BUILD_DIR)/$(TARGET).elf
ifeq ($(DEBUG_BACKEND), avarice)
	@echo Starting AVaRICE - Press enter when "waiting to connect" message displays.
	@$(WINSHELL) /c start avarice --jtag $(JTAG_DEV) --erase --program --file \
	$(BUILD_DIR)/$(TARGET).elf $(DEBUG_HOST):$(DEBUG_PORT)
	@$(WINSHELL) /c pause

else
	@$(WINSHELL) /c start simulavr --gdbserver --device $(MCU) --clock-freq \
	$(DEBUG_MFREQ) --port $(DEBUG_PORT)
endif
	@$(WINSHELL) /c start avr-$(DEBUG_UI) --command=$(GDBINIT_FILE)




# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT = $(OBJCOPY) --debugging
COFFCONVERT += --change-section-address .data-0x800000
COFFCONVERT += --change-section-address .bss-0x800000
COFFCONVERT += --change-section-address .noinit-0x800000
COFFCONVERT += --change-section-address .eeprom-0x810000



coff: $(BUILD_DIR)/$(TARGET).elf
	@$(SECHO) $(MSG_COFF) $(BUILD_DIR)/$(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(BUILD_DIR)/$(TARGET).cof


extcoff: $(BUILD_DIR)/$(TARGET).elf
	@$(SECHO) $(MSG_EXTENDED_COFF) $(BUILD_DIR)/$(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(BUILD_DIR)/$(TARGET).cof



# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@$(SILENT) || printf "$(MSG_FLASH) $@" | $(AWK_CMD)
	$(eval CMD=$(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature $< $@)
	@$(BUILD_CMD)
	@$(COPY) $@ $(TARGET).hex

%.eep: %.elf
	@$(SILENT) || printf "$(MSG_EEPROM) $@" | $(AWK_CMD)
	$(eval CMD=$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) $< $@ || exit 0)
	@$(BUILD_CMD)

# Create extended listing file from ELF output file.
%.lss: %.elf
	@$(SILENT) || printf "$(MSG_EXTENDED_LISTING) $@" | $(AWK_CMD)
	$(eval CMD=$(OBJDUMP) -h -S -z $< > $@)
	@$(BUILD_CMD)

# Create a symbol table from ELF output file.
%.sym: %.elf
	@$(SILENT) || printf "$(MSG_SYMBOL_TABLE) $@" | $(AWK_CMD)
	$(eval CMD=$(NM) -n $< > $@ )
	@$(BUILD_CMD)

# Create library from object files.
.SECONDARY : $(BUILD_DIR)/$(TARGET).a
.PRECIOUS : $(OBJ)
%.a: $(OBJ)
	@$(SILENT) || printf "$(MSG_CREATING_LIBRARY) $@" | $(AWK_CMD)
	$(eval CMD=$(AR) $@ $(OBJ) )
	@$(BUILD_CMD)

# Link: create ELF output file from object files.
.SECONDARY : $(BUILD_DIR)/$(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@$(SILENT) || printf "$(MSG_LINKING) $@" | $(AWK_CMD)
	$(eval CMD=$(CC) $(ALL_CFLAGS) $^ --output $@ $(LDFLAGS))
	@$(BUILD_CMD)

# Compile: create object files from C source files.
$(OBJDIR)/%.o : %.c
	@mkdir -p $(@D)
	@$(SILENT) || printf "$(MSG_COMPILING) $<" | $(AWK_CMD)
	$(eval CMD=$(CC) -c $(ALL_CFLAGS) $< -o $@)
	@$(BUILD_CMD)

# Compile: create object files from C++ source files.
$(OBJDIR)/%.o : %.cpp
	@mkdir -p $(@D)
	@$(SILENT) || printf "$(MSG_COMPILING_CPP) $<" | $(AWK_CMD)
	$(CC) -c $(ALL_CPPFLAGS) $< -o $@
	@$(BUILD_CMD)

# Compile: create assembler files from C source files.
%.s : %.c
	@$(SILENT) || printf "$(MSG_ASSEMBLING) $<" | $(AWK_CMD)
	$(eval CMD=$(CC) -S $(ALL_CFLAGS) $< -o $@)
	@$(BUILD_CMD)

# Compile: create assembler files from C++ source files.
%.s : %.cpp
	@$(SILENT) || printf "$(MSG_ASSEMBLING) $<" | $(AWK_CMD)
	$(eval CMD=$(CC) -S $(ALL_CPPFLAGS) $< -o $@)
	@$(BUILD_CMD)

# Assemble: create object files from assembler source files.
$(OBJDIR)/%.o : %.S
	@mkdir -p $(@D)
	@$(SILENT) || printf "$(MSG_ASSEMBLING) $<" | $(AWK_CMD)
	$(eval CMD=$(CC) -c $(ALL_ASFLAGS) $< -o $@)
	@$(BUILD_CMD)

# Create preprocessed source for use in sending a bug report.
%.i : %.c
	$(CC) -E -mmcu=$(MCU) $(CFLAGS) $< -o $@

# Target: clean project.
clean: begin clean_list end

clean_list :
	$(REMOVE) -r $(TOP_DIR)/$(BUILD_DIR)
	$(REMOVE) -r $(KEYBOARD_PATH)/$(BUILD_DIR)
	$(REMOVE) -r $(KEYMAP_PATH)/$(BUILD_DIR)

show_path:
	@echo VPATH=$(VPATH)
	@echo SRC=$(SRC)

SUBDIRS := $(sort $(dir $(wildcard $(TOP_DIR)/keyboards/*/.)))
all-keyboards-defaults-%:
	@for x in $(SUBDIRS) ; do \
		printf "Compiling with default: $$x" | $(AWK_CMD); \
		LOG=$$($(MAKE) -C $$x $(subst all-keyboards-defaults-,,$@) VERBOSE=$(VERBOSE) COLOR=$(COLOR) SILENT=true 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR_PLAIN); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING_PLAIN); else $(PRINT_OK); fi; \
	done

all-keyboards-defaults: all-keyboards-defaults-all

KEYBOARDS := $(SUBDIRS:$(TOP_DIR)/keyboards/%/=/keyboards/%)
all-keyboards-all: $(addsuffix -all,$(KEYBOARDS))
all-keyboards-quick: $(addsuffix -quick,$(KEYBOARDS))
all-keyboards-clean: $(addsuffix -clean,$(KEYBOARDS))
all-keyboards: all-keyboards-all

define make_keyboard
$(eval KEYBOARD=$(patsubst /keyboards/%,%,$1))
$(eval KEYMAPS=$(notdir $(patsubst %/.,%,$(wildcard $(TOP_DIR)$1/keymaps/*/.))))
@for x in $(KEYMAPS) ; do \
	printf "Compiling $(BOLD)$(KEYBOARD)$(NO_COLOR) with $(BOLD)$$x$(NO_COLOR)" | $(AWK) '{ printf "%-88s", $$0; }'; \
	LOG=$$($(MAKE) -C $(TOP_DIR)$1 $2 keymap=$$x VERBOSE=$(VERBOSE) COLOR=$(COLOR) SILENT=true 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR_PLAIN); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING_PLAIN); else $(PRINT_OK); fi; \
done
endef

define make_keyboard_helper
# Just remove the -quick, -all and so on from the first argument and pass it forward
$(call make_keyboard,$(subst -$2,,$1),$2)
endef

/keyboards/%-quick:
	$(call make_keyboard_helper,$@,quick)
/keyboards/%-all:
	$(call make_keyboard_helper,$@,all)
/keyboards/%-clean:
	$(call make_keyboard_helper,$@,clean)
/keyboards/%:
	$(call make_keyboard_helper,$@,all)

all-keymaps-%:
	$(eval MAKECONFIG=$(call get_target,all-keymaps,$@))
	$(eval KEYMAPS=$(notdir $(patsubst %/.,%,$(wildcard $(TOP_DIR)/keyboards/$(KEYBOARD)/keymaps/*/.))))
	@for x in $(KEYMAPS) ; do \
		printf "Compiling $(BOLD)$(KEYBOARD)$(NO_COLOR) with $(BOLD)$$x$(NO_COLOR)" | $(AWK) '{ printf "%-88s", $$0; }'; \
		LOG=$$($(MAKE) $(subst all-keymaps-,,$@) keyboard=$(KEYBOARD) keymap=$$x VERBOSE=$(VERBOSE) COLOR=$(COLOR) SILENT=true 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR_PLAIN); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING_PLAIN); else $(PRINT_OK); fi; \
	done

all-keymaps: all-keymaps-all

# Create build directory
$(shell mkdir $(BUILD_DIR) 2>/dev/null)

# Create object files directory
$(shell mkdir $(OBJDIR) 2>/dev/null)


# Include the dependency files.
-include $(shell mkdir $(BUILD_DIR)/.dep 2>/dev/null) $(wildcard $(BUILD_DIR)/.dep/*)


# Listing of phony targets.
.PHONY : all quick begin finish end sizebefore sizeafter gccversion \
build elf hex eep lss sym coff extcoff \
clean clean_list debug gdb-config show_path \
program teensy dfu flip dfu-ee flip-ee dfu-start \
all-keyboards-defaults all-keyboards all-keymaps \
all-keyboards-defaults-% all-keyboards-% all-keymaps-%
