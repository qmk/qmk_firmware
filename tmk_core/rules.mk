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

# Enable vpath seraching for source files only
# Without this, output files, could be read from the wrong .build directories
VPATH_SRC := $(VPATH)
vpath %.c $(VPATH_SRC)
vpath %.h $(VPATH_SRC)
vpath %.cpp $(VPATH_SRC)
vpath %.hpp $(VPATH_SRC)
vpath %.S $(VPATH_SRC)
VPATH :=


# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Optimization level, can be [0, 1, 2, 3, s].
#     0 = turn off optimization. s = optimize for size.
#     (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

COLOR ?= true

ifeq ($(COLOR),true)
	NO_COLOR=\033[0m
	OK_COLOR=\033[32;01m
	ERROR_COLOR=\033[31;01m
	WARN_COLOR=\033[33;01m
	BLUE=\033[0;34m
	BOLD=\033[1m
endif

AUTOGEN ?= false

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
AWK_CMD = $(AWK) '{ printf "%-99s", $$0; }'
PRINT_ERROR = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG) && exit 1
PRINT_WARNING = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG)
PRINT_ERROR_PLAIN = ($(SILENT) ||printf " $(ERROR_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN) && exit 1
PRINT_WARNING_PLAIN = ($(SILENT) || printf " $(WARN_STRING)" | $(AWK_STATUS)) && $(TAB_LOG_PLAIN)
PRINT_OK = $(SILENT) || printf " $(OK_STRING)" | $(AWK_STATUS)
BUILD_CMD = LOG=$$($(CMD) 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING); else $(PRINT_OK); fi;

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRAINCDIRS += $(subst :, ,$(VPATH_SRC))


# Compiler flag to set the C Standard level.
#     c89   = "ANSI" C
#     gnu89 = c89 plus GCC extensions
#     c99   = ISO C99 standard (not yet fully implemented)
#     gnu99 = c99 plus GCC extensions
CSTANDARD = -std=gnu99


# Place -D or -U options here for C sources
CDEFS += $(OPT_DEFS)


# Place -D or -U options here for ASM sources
ADEFS += $(OPT_DEFS)


# Place -D or -U options here for C++ sources
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
CFLAGS += -g$(DEBUG)
CFLAGS += $(CDEFS)
CFLAGS += -O$(OPT)
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
CPPFLAGS += -g$(DEBUG)
CPPFLAGS += $(CPPDEFS)
CPPFLAGS += -O$(OPT)
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
ASFLAGS += $(ADEFS) -Wa,-adhlns=$(@:%.o=%.lst),-gstabs,--listing-cont-lines=100
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


#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
#
# Comennt out "--relax" option to avoid a error such:
# 	(.vectors+0x30): relocation truncated to fit: R_AVR_13_PCREL against symbol `__vector_12'
#
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref
#LDFLAGS += -Wl,--relax
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(patsubst %,-L%,$(EXTRALIBDIRS))
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)
#LDFLAGS += -T linker_script.x
# You can give EXTRALDFLAGS at 'make' command line.
LDFLAGS += $(EXTRALDFLAGS)

# Define programs and commands.
SHELL = sh
REMOVE = rm -f
REMOVEDIR = rmdir
COPY = cp
WINSHELL = cmd
SECHO = $(SILENT) || echo

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
MSG_BIN = Creating binary load file for Flash:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_COMPILING_CPP = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_CREATING_LIBRARY = Creating library:
MSG_SUBMODULE_DIRTY = $(WARN_COLOR)WARNING:$(NO_COLOR)\n \
	Some git sub-modules are out of date or modified, please consider runnning:$(BOLD)\n\
	git submodule sync --recursive\n\
	git submodule update --init --recursive$(NO_COLOR)\n\n\
	You can ignore this warning if you are not compiling any ChibiOS keyboards,\n\
	or if you have modified the ChibiOS libraries yourself. \n\n


# Define all object files.
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(patsubst %.cpp,$(OBJDIR)/%.o,$(patsubst %.S,$(OBJDIR)/%.o,$(SRC))))
# The files in the lib folder are shared between all keymaps, so generate that folder name by removing
# the keymap from the name
KBOBJDIR=$(subst _$(KEYMAP),,$(OBJDIR))
# And fixup the object files to match
LIBOBJ = $(foreach v,$(OBJ),$(if $(findstring /lib/,$v),$v))
NONLIBOBJ := $(filter-out $(LIBOBJ),$(OBJ))
LIBOBJ := $(subst _$(KEYMAP)/,/,$(LIBOBJ))
OBJ := $(LIBOBJ) $(NONLIBOBJ)

# Define all listing files.
LST = $(patsubst %.c,$(OBJDIR)/%.lst,$(patsubst %.cpp,$(OBJDIR)/%.lst,$(patsubst %.S,$(OBJDIR)/%.lst,$(SRC))))


# Compiler flags to generate dependency files.
#GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d
GENDEPFLAGS = -MMD -MP -MF $(patsubst %.o,%.td,$@)


# Combine all necessary flags and optional flags.
# Add target processor to flags.
# You can give extra flags at 'make' command line like: make EXTRAFLAGS=-DFOO=bar
ALL_CFLAGS = $(MCUFLAGS) $(CFLAGS) $(EXTRAFLAGS)
ALL_CPPFLAGS = $(MCUFLAGS) -x c++ $(CPPFLAGS) $(EXTRAFLAGS)
ALL_ASFLAGS = $(MCUFLAGS) -x assembler-with-cpp $(ASFLAGS) $(EXTRAFLAGS)

MOVE_DEP = mv -f $(patsubst %.o,%.td,$@) $(patsubst %.o,%.d,$@)

# Default target.
all: build sizeafter

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

check_submodule:
	git submodule status --recursive | \
	while IFS= read -r x; do \
		case "$$x" in \
			\ *) ;; \
			*) printf "$(MSG_SUBMODULE_DIRTY)";break;; \
		esac \
	done

# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
#ELFSIZE = $(SIZE) --mcu=$(MCU) --format=avr $(TARGET).elf
ELFSIZE = $(SIZE) $(BUILD_DIR)/$(TARGET).elf

sizebefore:
	@if test -f $(TARGET).hex; then $(SECHO) $(MSG_SIZE_BEFORE); $(SILENT) || $(HEXSIZE); \
	2>/dev/null; $(SECHO); fi

sizeafter: $(BUILD_DIR)/$(TARGET).hex
	@if test -f $(TARGET).hex; then $(SECHO); $(SECHO) $(MSG_SIZE_AFTER); $(SILENT) || $(HEXSIZE); \
	2>/dev/null; $(SECHO); fi
	# test file sizes eventually
	# @if [[ $($(SIZE) --target=$(FORMAT) $(TARGET).hex | $(AWK) 'NR==2 {print "0x"$5}') -gt 0x200 ]]; then $(SECHO) "File is too big!"; fi

# Display compiler version information.
gccversion :
	@$(SILENT) || $(CC) --version

# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@$(SILENT) || printf "$(MSG_FLASH) $@" | $(AWK_CMD)
	$(eval CMD=$(HEX) $< $@)
	@$(BUILD_CMD)
	@if $(AUTOGEN); then \
		$(SILENT) || printf "Copying $(TARGET).hex to keymaps/$(KEYMAP)/$(KEYBOARD)_$(KEYMAP).hex\n"; \
		$(COPY) $@ $(KEYMAP_PATH)/$(KEYBOARD)_$(KEYMAP).hex; \
	else \
		$(COPY) $@ $(TARGET).hex; \
	fi

%.eep: %.elf
	@$(SILENT) || printf "$(MSG_EEPROM) $@" | $(AWK_CMD)
	$(eval CMD=$(EEP) $< $@ || exit 0)
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

%.bin: %.elf
	@$(SILENT) || printf "$(MSG_BIN) $@" | $(AWK_CMD)
	$(eval CMD=$(BIN) $< $@ || exit 0)
	@$(BUILD_CMD)

# Create library from object files.
.SECONDARY : $(BUILD_DIR)/$(TARGET).a
.PRECIOUS : $(OBJ)
%.a: $(OBJ)
	@$(SILENT) || printf "$(MSG_CREATING_LIBRARY) $@" | $(AWK_CMD)
	$(eval CMD=$(AR) $@ $(OBJ) )
	@$(BUILD_CMD)

BEGIN = gccversion check_submodule sizebefore

# Link: create ELF output file from object files.
.SECONDARY : $(BUILD_DIR)/$(TARGET).elf
.PRECIOUS : $(OBJ)
# Note the obj.txt depeendency is there to force linking if a source file is deleted
%.elf: $(OBJ) $(OBJDIR)/cflags.txt $(OBJDIR)/ldflags.txt $(OBJDIR)/obj.txt | $(BEGIN)
	@$(SILENT) || printf "$(MSG_LINKING) $@" | $(AWK_CMD)
	$(eval CMD=$(CC) $(ALL_CFLAGS) $(filter-out %.txt,$^) --output $@ $(LDFLAGS))
	@$(BUILD_CMD)

define GEN_OBJRULE
# Compile: create object files from C source files.
$1/%.o : %.c $1/%.d $1/cflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$$(SILENT) || printf "$$(MSG_COMPILING) $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(CC) -c $$(ALL_CFLAGS) $$(GENDEPFLAGS) $$< -o $$@ && $$(MOVE_DEP))
	@$$(BUILD_CMD)

# Compile: create object files from C++ source files.
$1/%.o : %.cpp $1/%.d $1/cppflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$$(SILENT) || printf "$$(MSG_COMPILING_CPP) $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(CC) -c $$(ALL_CPPFLAGS) $$(GENDEPFLAGS) $$< -o $$@ && $$(MOVE_DEP))
	@$(BUILD_CMD)

# Assemble: create object files from assembler source files.
$1/%.o : %.S $1/asflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$(SILENT) || printf "$$(MSG_ASSEMBLING) $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(CC) -c $$(ALL_ASFLAGS) $$< -o $$@)
	@$$(BUILD_CMD)

$1/force:

$1/cflags.txt: $1/force
	echo '$$(ALL_CFLAGS)' | cmp -s - $$@ || echo '$$(ALL_CFLAGS)' > $$@

$1/cppflags.txt: $1/force
	echo '$$(ALL_CPPFLAGS)' | cmp -s - $$@ || echo '$$(ALL_CPPFLAGS)' > $$@

$1/asflags.txt: $1/force
	echo '$$(ALL_ASFLAGS)' | cmp -s - $$@ || echo '$$(ALL_ASFLAGS)' > $$@

$1/ldflags.txt: $1/force
	echo '$$(LDFLAGS)' | cmp -s - $$@ || echo '$$(LDFLAGS)' > $$@

$1/obj.txt: $1/force
	echo '$$(OBJ)' | cmp -s - $$@ || echo '$$(OBJ)' > $$@

$1/compiler.txt: $1/force
	$$(CC) --version | cmp -s - $$@ || $$(CC) --version > $$@
endef

# We have to use static rules for the .d files for some reason
DEPS = $(patsubst %.o,%.d,$(OBJ))
# Keep the .d files
.PRECIOUS: $(DEPS)
# Empty rule to force recompilation if the .d file is missing
$(DEPS):

# Since the object files could be in two different folders, generate
# separate rules for them, rather than having too generic rules
$(eval $(call GEN_OBJRULE,$(OBJDIR)))
$(eval $(call GEN_OBJRULE,$(KBOBJDIR)))

# Compile: create assembler files from C source files.
%.s : %.c | $(BEGIN)
	@$(SILENT) || printf "$(MSG_ASSEMBLING) $<" | $(AWK_CMD)
	$(eval CMD=$(CC) -S $(ALL_CFLAGS) $< -o $@)
	@$(BUILD_CMD)

# Compile: create assembler files from C++ source files.
%.s : %.cpp | $(BEGIN)
	@$(SILENT) || printf "$(MSG_ASSEMBLING) $<" | $(AWK_CMD)
	$(eval CMD=$(CC) -S $(ALL_CPPFLAGS) $< -o $@)
	@$(BUILD_CMD)

# Create preprocessed source for use in sending a bug report.
%.i : %.c | $(BEGIN)
	$(CC) -E -mmcu=$(MCU) $(CFLAGS) $< -o $@

# Target: clean project.
clean:
	$(REMOVE) -r $(OBJDIR) 2>/dev/null
	$(REMOVE) -r $(KBOBJDIR) 2>/dev/null
	$(REMOVE) $(BUILD_DIR)/$(TARGET).*

show_path:
	@echo VPATH=$(VPATH)
	@echo SRC=$(SRC)

SUBDIRS := $(filter-out %/util/ %/doc/ %/keymaps/ %/old_keymap_files/,$(dir $(wildcard $(TOP_DIR)/keyboards/**/*/Makefile)))
SUBDIRS := $(SUBDIRS) $(dir $(wildcard $(TOP_DIR)/keyboards/*/.))
SUBDIRS := $(sort $(SUBDIRS))
# $(error $(SUBDIRS))
all-keyboards-defaults-%:
	@for x in $(SUBDIRS) ; do \
		printf "Compiling with default: $$x" | $(AWK_CMD); \
		LOG=$$($(MAKE) -C $$x $(subst all-keyboards-defaults-,,$@) VERBOSE=$(VERBOSE) COLOR=$(COLOR) SILENT=true 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR_PLAIN); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING_PLAIN); else $(PRINT_OK); fi; \
	done

all-keyboards-defaults: all-keyboards-defaults-all

KEYBOARDS := $(SUBDIRS:$(TOP_DIR)/keyboards/%/=/keyboards/%)
all-keyboards-all: $(addsuffix -all,$(KEYBOARDS))
all-keyboards-clean: $(addsuffix -clean,$(KEYBOARDS))
all-keyboards: all-keyboards-all

define make_keyboard
$(eval KEYBOARD=$(patsubst /keyboards/%,%,$1))
$(eval SUBPROJECT=$(lastword $(subst /, ,$(KEYBOARD))))
$(eval KEYBOARD=$(firstword $(subst /, ,$(KEYBOARD))))
$(eval KEYMAPS=$(notdir $(patsubst %/.,%,$(wildcard $(TOP_DIR)/keyboards/$(KEYBOARD)/keymaps/*/.))))
$(eval KEYMAPS+=$(notdir $(patsubst %/.,%,$(wildcard $(TOP_DIR)/keyboards/$(KEYBOARD)/$(SUBPROJECT)/keymaps/*/.))))
@for x in $(KEYMAPS) ; do \
	printf "Compiling $(BOLD)$(KEYBOARD)/$(SUBPROJECT)$(NO_COLOR) with $(BOLD)$$x$(NO_COLOR)" | $(AWK) '{ printf "%-118s", $$0; }'; \
	LOG=$$($(MAKE) -C $(TOP_DIR)$1 $2 keymap=$$x VERBOSE=$(VERBOSE) COLOR=$(COLOR) SILENT=true 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR_PLAIN); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING_PLAIN); else $(PRINT_OK); fi; \
done
endef

define make_keyboard_helper
# Just remove the -all and so on from the first argument and pass it forward
$(call make_keyboard,$(subst -$2,,$1),$2)
endef

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
		printf "Compiling $(BOLD)$(KEYBOARD)$(NO_COLOR) with $(BOLD)$$x$(NO_COLOR)" | $(AWK) '{ printf "%-118s", $$0; }'; \
		LOG=$$($(MAKE) $(subst all-keymaps-,,$@) keyboard=$(KEYBOARD) keymap=$$x VERBOSE=$(VERBOSE) COLOR=$(COLOR) SILENT=true 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR_PLAIN); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING_PLAIN); else $(PRINT_OK); fi; \
	done

all-keymaps: all-keymaps-all

# Create build directory
$(shell mkdir $(BUILD_DIR) 2>/dev/null)

# Create object files directory
$(shell mkdir $(OBJDIR) 2>/dev/null)
$(shell mkdir $(KBOBJDIR) 2>/dev/null)

# Include the dependency files.
-include $(patsubst %.o,%.d,$(OBJ))


# Listing of phony targets.
.PHONY : all finish sizebefore sizeafter gccversion \
build elf hex eep lss sym coff extcoff check_submodule \
clean clean_list debug gdb-config show_path \
program teensy dfu flip dfu-ee flip-ee dfu-start \
all-keyboards-defaults all-keyboards all-keymaps \
all-keyboards-defaults-% all-keyboards-% all-keymaps-%
