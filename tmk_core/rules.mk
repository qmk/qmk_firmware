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
vpath %.cc $(VPATH_SRC)
vpath %.hpp $(VPATH_SRC)
vpath %.S $(VPATH_SRC)
VPATH :=

# Convert all SRC to OBJ
define OBJ_FROM_SRC
$(patsubst %.c,$1/%.o,$(patsubst %.cpp,$1/%.o,$(patsubst %.cc,$1/%.o,$(patsubst %.S,$1/%.o,$($1_SRC)))))
endef
$(foreach OUTPUT,$(OUTPUTS),$(eval $(OUTPUT)_OBJ +=$(call OBJ_FROM_SRC,$(OUTPUT))))

# Define a list of all objects
OBJ := $(foreach OUTPUT,$(OUTPUTS),$($(OUTPUT)_OBJ))

MASTER_OUTPUT := $(firstword $(OUTPUTS))



# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Optimization level, can be [0, 1, 2, 3, s].
#     0 = turn off optimization. s = optimize for size.
#     (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

AUTOGEN ?= false


# Compiler flag to set the C Standard level.
#     c89   = "ANSI" C
#     gnu89 = c89 plus GCC extensions
#     c99   = ISO C99 standard (not yet fully implemented)
#     gnu99 = c99 plus GCC extensions
CSTANDARD = -std=gnu99


# Place -D or -U options here for C sources
#CDEFS +=


# Place -D or -U options here for ASM sources
#ADEFS +=


# Place -D or -U options here for C++ sources
#CPPDEFS += -D__STDC_LIMIT_MACROS
#CPPDEFS += -D__STDC_CONSTANT_MACROS
#CPPDEFS +=




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
ifneq ($(strip $(ALLOW_WARNINGS)), yes)
    CFLAGS += -Werror
endif
#CFLAGS += -mshort-calls
#CFLAGS += -fno-unit-at-a-time
#CFLAGS += -Wundef
#CFLAGS += -Wunreachable-code
#CFLAGS += -Wsign-compare
CFLAGS += -Wa,-adhlns=$(@:%.o=%.lst)
CFLAGS += $(CSTANDARD)


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
ifneq ($(strip $(ALLOW_WARNINGS)), yes)
    CPPFLAGS += -Werror
endif
#CPPFLAGS += -mshort-calls
#CPPFLAGS += -fno-unit-at-a-time
#CPPFLAGS += -Wstrict-prototypes
#CPPFLAGS += -Wunreachable-code
#CPPFLAGS += -Wsign-compare
CPPFLAGS += -Wa,-adhlns=$(@:%.o=%.lst)
#CPPFLAGS += $(CSTANDARD)

#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -adhlns:   create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex
#       dump that will be displayed for a given single line of source input.
ASFLAGS += $(ADEFS) 
ASFLAGS += -Wa,-adhlns=$(@:%.o=%.lst),-gstabs,--listing-cont-lines=100

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
CREATE_MAP ?= yes


#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
#
# Comennt out "--relax" option to avoid a error such:
# 	(.vectors+0x30): relocation truncated to fit: R_AVR_13_PCREL against symbol `__vector_12'
#

ifeq ($(CREATE_MAP),yes)
	LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref
endif
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


elf: $(BUILD_DIR)/$(TARGET).elf
hex: $(BUILD_DIR)/$(TARGET).hex
eep: $(BUILD_DIR)/$(TARGET).eep
lss: $(BUILD_DIR)/$(TARGET).lss
sym: $(BUILD_DIR)/$(TARGET).sym
LIBNAME=lib$(TARGET).a
lib: $(LIBNAME)

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
		$(SILENT) || printf "Copying $(TARGET).hex to keymaps/$(KEYMAP)/$(TARGET).hex\n"; \
		$(COPY) $@ $(KEYMAP_PATH)/$(TARGET).hex; \
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

BEGIN = gccversion sizebefore

# Link: create ELF output file from object files.
.SECONDARY : $(BUILD_DIR)/$(TARGET).elf
.PRECIOUS : $(OBJ)
# Note the obj.txt depeendency is there to force linking if a source file is deleted
%.elf: $(OBJ) $(MASTER_OUTPUT)/cflags.txt $(MASTER_OUTPUT)/ldflags.txt $(MASTER_OUTPUT)/obj.txt | $(BEGIN)
	@$(SILENT) || printf "$(MSG_LINKING) $@" | $(AWK_CMD)
	$(eval CMD=$(CC) $(ALL_CFLAGS) $(filter-out %.txt,$^) --output $@ $(LDFLAGS))
	@$(BUILD_CMD)
	

define GEN_OBJRULE
$1_INCFLAGS := $$(patsubst %,-I%,$$($1_INC))
ifdef $1_CONFIG
$1_CONFIG_FLAGS += -include $$($1_CONFIG)
endif
$1_CFLAGS = $$(ALL_CFLAGS) $$($1_DEFS) $$($1_INCFLAGS) $$($1_CONFIG_FLAGS)
$1_CPPFLAGS= $$(ALL_CPPFLAGS) $$($1_DEFS) $$($1_INCFLAGS) $$($1_CONFIG_FLAGS)
$1_ASFLAGS= $$(ALL_ASFLAGS) $$($1_DEFS) $$($1_INCFLAGS) $$($1_CONFIG_FLAGS)

# Compile: create object files from C source files.
$1/%.o : %.c $1/%.d $1/cflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$$(SILENT) || printf "$$(MSG_COMPILING) $$<" | $$(AWK_CMD)
	$$(eval CMD := $$(CC) -c $$($1_CFLAGS) $$(GENDEPFLAGS) $$< -o $$@ && $$(MOVE_DEP))
	@$$(BUILD_CMD)

# Compile: create object files from C++ source files.
$1/%.o : %.cpp $1/%.d $1/cppflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$$(SILENT) || printf "$$(MSG_COMPILING_CPP) $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(CC) -c $$($1_CPPFLAGS) $$(GENDEPFLAGS) $$< -o $$@ && $$(MOVE_DEP))
	@$$(BUILD_CMD)

$1/%.o : %.cc $1/%.d $1/cppflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$$(SILENT) || printf "$$(MSG_COMPILING_CPP) $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(CC) -c $$($1_CPPFLAGS) $$(GENDEPFLAGS) $$< -o $$@ && $$(MOVE_DEP))
	@$$(BUILD_CMD)

# Assemble: create object files from assembler source files.
$1/%.o : %.S $1/asflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$(SILENT) || printf "$$(MSG_ASSEMBLING) $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(CC) -c $$($1_ASFLAGS) $$< -o $$@)
	@$$(BUILD_CMD)

$1/force:

$1/cflags.txt: $1/force
	echo '$$($1_CFLAGS)' | cmp -s - $$@ || echo '$$($1_CFLAGS)' > $$@

$1/cppflags.txt: $1/force
	echo '$$($1_CPPFLAGS)' | cmp -s - $$@ || echo '$$($1_CPPFLAGS)' > $$@

$1/asflags.txt: $1/force
	echo '$$($1_ASFLAGS)' | cmp -s - $$@ || echo '$$($1_ASFLAGS)' > $$@

$1/compiler.txt: $1/force
	$$(CC) --version | cmp -s - $$@ || $$(CC) --version > $$@
endef

.PRECIOUS: $(MASTER_OUTPUT)/obj.txt
$(MASTER_OUTPUT)/obj.txt: $(MASTER_OUTPUT)/force
	echo '$(OBJ)' | cmp -s - $@ || echo '$(OBJ)' > $@

.PRECIOUS: $(MASTER_OUTPUT)/ldflags.txt
$(MASTER_OUTPUT)/ldflags.txt: $(MASTER_OUTPUT)/force
	echo '$(LDFLAGS)' | cmp -s - $@ || echo '$(LDFLAGS)' > $@


# We have to use static rules for the .d files for some reason
DEPS = $(patsubst %.o,%.d,$(OBJ))
# Keep the .d files
.PRECIOUS: $(DEPS)
# Empty rule to force recompilation if the .d file is missing
$(DEPS):
	

$(foreach OUTPUT,$(OUTPUTS),$(eval $(call GEN_OBJRULE,$(OUTPUT))))

# Create preprocessed source for use in sending a bug report.
%.i : %.c | $(BEGIN)
	$(CC) -E -mmcu=$(MCU) $(CFLAGS) $< -o $@

# Target: clean project.
clean:
	$(foreach OUTPUT,$(OUTPUTS), $(REMOVE) -r $(OUTPUT) 2>/dev/null)
	$(REMOVE) $(BUILD_DIR)/$(TARGET).*

show_path:
	@echo VPATH=$(VPATH)
	@echo SRC=$(SRC)
	@echo OBJ=$(OBJ)

# Create build directory
$(shell mkdir -p $(BUILD_DIR) 2>/dev/null)

# Create object files directory
$(eval $(foreach OUTPUT,$(OUTPUTS),$(shell mkdir -p $(OUTPUT) 2>/dev/null)))

# Include the dependency files.
-include $(patsubst %.o,%.d,$(OBJ))


# Listing of phony targets.
.PHONY : all finish sizebefore sizeafter qmkversion \
gccversion build elf hex eep lss sym coff extcoff \
clean clean_list debug gdb-config show_path \
program teensy dfu flip dfu-ee flip-ee dfu-start 
