# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------

# Enable vpath searching for source files only
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
$(patsubst %.c,$1/%.o,$(patsubst %.cpp,$1/%.o,$(patsubst %.cc,$1/%.o,$(patsubst %.S,$1/%.o,$(patsubst %.clib,$1/%.a,$($1_SRC))))))
endef
$(foreach OUTPUT,$(OUTPUTS),$(eval $(OUTPUT)_OBJ +=$(call OBJ_FROM_SRC,$(OUTPUT))))

# Define a list of all objects
OBJ := $(foreach OUTPUT,$(OUTPUTS),$($(OUTPUT)_OBJ))
NO_LTO_OBJ := $(filter %.a,$(OBJ))

MASTER_OUTPUT := $(firstword $(OUTPUTS))

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Optimization level, can be [0, 1, 2, 3, s].
OPT ?= s

# Compiler flag to set the C and C++ language standard level
CSTANDARD = -std=gnu11
CXXSTANDARD = -std=gnu++14

# Speed up recompilations by opt-in usage of ccache
USE_CCACHE ?= no
ifneq ($(USE_CCACHE),no)
    CC_PREFIX ?= ccache
endif

#---------------- C Compiler Options ----------------

ifeq ($(strip $(LTO_ENABLE)), yes)
    ifeq ($(PLATFORM),ARM_ATSAM)
        $(info Enabling LTO on arm_atsam-targeting boards is known to have a high likelihood of failure.)
        $(info If unsure, set LTO_ENABLE = no.)
    endif
    CDEFS += -flto
    CDEFS += -DLTO_ENABLE
endif

DEBUG_ENABLE ?= yes
ifeq ($(strip $(SKIP_DEBUG_INFO)),yes)
  DEBUG_ENABLE=no
endif

ifeq ($(strip $(DEBUG_ENABLE)),yes)
  CFLAGS += -g$(DEBUG)
endif
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
CFLAGS += $(CSTANDARD)

# This fixes lots of keyboards linking errors but SHOULDN'T BE A FINAL SOLUTION
# Fixing of multiple variable definitions must be made.
CFLAGS += -fcommon

#---------------- C++ Compiler Options ----------------

ifeq ($(strip $(DEBUG_ENABLE)),yes)
  CXXFLAGS += -g$(DEBUG)
endif
CXXFLAGS += $(CXXDEFS)
CXXFLAGS += -O$(OPT)
# to suppress "warning: only initialized variables can be placed into program memory area"
CXXFLAGS += -w
CXXFLAGS += -Wall
CXXFLAGS += -Wundef

ifneq ($(strip $(ALLOW_WARNINGS)), yes)
    CXXFLAGS += -Werror
endif

#---------------- Assembler Options ----------------

ASFLAGS += $(ADEFS)
ifeq ($(VERBOSE_AS_CMD),yes)
	ASFLAGS += -v
endif

#---------------- Linker Options ----------------

CREATE_MAP ?= yes
ifeq ($(CREATE_MAP),yes)
	LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref
endif
ifeq ($(VERBOSE_LD_CMD),yes)
	LDFLAGS += -v
endif
#LDFLAGS += -Wl,--relax
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(patsubst %,-L%,$(EXTRALIBDIRS))
LDFLAGS += -lm
# You can give EXTRALDFLAGS at 'make' command line.
LDFLAGS += $(EXTRALDFLAGS)

#---------------- Assembler Listings ----------------

ADHLNS_ENABLE ?= no
ifeq ($(ADHLNS_ENABLE),yes)
  # Avoid "Options to '-Xassembler' do not match" - only specify assembler options at LTO link time
  ifeq ($(strip $(LTO_ENABLE)), yes)
    LDFLAGS += -Wa,-adhlns=$(BUILD_DIR)/$(TARGET).lst
  else
    CFLAGS += -Wa,-adhlns=$(@:%.o=%.lst)
    CXXFLAGS += -Wa,-adhlns=$(@:%.o=%.lst)
    ifeq ($(strip $(DEBUG_ENABLE)),yes)
      ASFLAGS = -Wa,-adhlns=$(@:%.o=%.lst),-gstabs,--listing-cont-lines=100
    else
      ASFLAGS = -Wa,-adhlns=$(@:%.o=%.lst),--listing-cont-lines=100
    endif
  endif
endif

# Define programs and commands.
SHELL = sh
SED = sed
REMOVE = rm -f
REMOVEDIR = rmdir
COPY = cp
WINSHELL = cmd
SECHO = $(SILENT) || echo
MD5SUM ?= md5sum
ifneq ($(filter Darwin FreeBSD,$(shell uname -s)),)
  MD5SUM = md5
endif

# UF2 format settings
# To produce a UF2 file in your build, add to your keyboard's rules.mk:
#      FIRMWARE_FORMAT = uf2
UF2CONV = $(TOP_DIR)/util/uf2conv.py
UF2_FAMILY ?= 0x0

# Compiler flags to generate dependency files.
#GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d
GENDEPFLAGS = -MMD -MP -MF $(patsubst %.o,%.td,$@)


# Combine all necessary flags and optional flags.
# Add target processor to flags.
# You can give extra flags at 'make' command line like: make EXTRAFLAGS=-DFOO=bar
ALL_CFLAGS = $(MCUFLAGS) $(CFLAGS) $(EXTRAFLAGS)
ALL_CXXFLAGS = $(MCUFLAGS) -x c++ $(CXXFLAGS) $(EXTRAFLAGS)
ALL_ASFLAGS = $(MCUFLAGS) -x assembler-with-cpp $(ASFLAGS) $(EXTRAFLAGS)

define NO_LTO
$(patsubst %.a,%.o,$1): NOLTO_CFLAGS += -fno-lto
endef
$(foreach LOBJ, $(NO_LTO_OBJ), $(eval $(call NO_LTO,$(LOBJ))))

MOVE_DEP = mv -f $(patsubst %.o,%.td,$@) $(patsubst %.o,%.d,$@)

# For a ChibiOS build, ensure that the board files have the hook overrides injected
define BOARDSRC_INJECT_HOOKS
$(KEYBOARD_OUTPUT)/$(patsubst %.c,%.o,$(patsubst ./%,%,$1)): INIT_HOOK_CFLAGS += -include $(TOP_DIR)/tmk_core/protocol/chibios/init_hooks.h
endef
$(foreach LOBJ, $(BOARDSRC), $(eval $(call BOARDSRC_INJECT_HOOKS,$(LOBJ))))

# Add QMK specific flags
DFU_SUFFIX ?= dfu-suffix
DFU_SUFFIX_ARGS ?=


elf: $(BUILD_DIR)/$(TARGET).elf
hex: $(BUILD_DIR)/$(TARGET).hex
uf2: $(BUILD_DIR)/$(TARGET).uf2
cpfirmware: $(FIRMWARE_FORMAT)
	$(SILENT) || printf "Copying $(TARGET).$(FIRMWARE_FORMAT) to qmk_firmware folder" | $(AWK_CMD)
	$(COPY) $(BUILD_DIR)/$(TARGET).$(FIRMWARE_FORMAT) $(TARGET).$(FIRMWARE_FORMAT) && $(PRINT_OK)
eep: $(BUILD_DIR)/$(TARGET).eep
lss: $(BUILD_DIR)/$(TARGET).lss
sym: $(BUILD_DIR)/$(TARGET).sym
LIBNAME=lib$(TARGET).a
lib: $(LIBNAME)

# Display size of file, modifying the output so people don't mistakenly grab the hex output
BINARY_SIZE = $(SIZE) --target=$(FORMAT) $(BUILD_DIR)/$(TARGET).hex | $(SED) -e 's/\.build\/.*$$/$(TARGET).$(FIRMWARE_FORMAT)/g'

sizebefore:
	@if test -f $(BUILD_DIR)/$(TARGET).hex; then $(SECHO) $(MSG_SIZE_BEFORE); $(SILENT) || $(BINARY_SIZE); \
	2>/dev/null; $(SECHO); fi

sizeafter: $(BUILD_DIR)/$(TARGET).hex
	@if test -f $(BUILD_DIR)/$(TARGET).hex; then $(SECHO); $(SECHO) $(MSG_SIZE_AFTER); $(SILENT) || $(BINARY_SIZE); \
	2>/dev/null; $(SECHO); fi

# Display compiler version information.
gccversion :
	@$(SILENT) || $(CC) --version

# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	$(eval CMD=$(HEX) $< $@)
	#@$(SILENT) || printf "$(MSG_EXECUTING) '$(CMD)':\n"
	@$(SILENT) || printf "$(MSG_FLASH) $@" | $(AWK_CMD)
	@$(BUILD_CMD)

%.uf2: %.elf
	$(eval CMD=$(HEX) $< $(BUILD_DIR)/$(TARGET).tmp && $(UF2CONV) $(BUILD_DIR)/$(TARGET).tmp --output $@ --convert --family $(UF2_FAMILY) >/dev/null 2>&1)
	#@$(SILENT) || printf "$(MSG_EXECUTING) '$(CMD)':\n"
	@$(SILENT) || printf "$(MSG_UF2) $@" | $(AWK_CMD)
	@$(BUILD_CMD)

%.eep: %.elf
	$(eval CMD=$(EEP) $< $@ || exit 0)
	#@$(SILENT) || printf "$(MSG_EXECUTING) '$(CMD)':\n"
	@$(SILENT) || printf "$(MSG_EEPROM) $@" | $(AWK_CMD)
	@$(BUILD_CMD)

# Create extended listing file from ELF output file.
%.lss: %.elf
	$(eval CMD=$(OBJDUMP) -h -S -z $< > $@)
	#@$(SILENT) || printf "$(MSG_EXECUTING) '$(CMD)':\n"
	@$(SILENT) || printf "$(MSG_EXTENDED_LISTING) $@" | $(AWK_CMD)
	@$(BUILD_CMD)

# Create a symbol table from ELF output file.
%.sym: %.elf
	$(eval CMD=$(NM) -n $< > $@ )
	#@$(SILENT) || printf "$(MSG_EXECUTING) '$(CMD)':\n"
	@$(SILENT) || printf "$(MSG_SYMBOL_TABLE) $@" | $(AWK_CMD)
	@$(BUILD_CMD)

%.bin: %.elf
	$(eval CMD=$(BIN) $< $@ || exit 0)
	#@$(SILENT) || printf "$(MSG_EXECUTING) '$(CMD)':\n"
	@$(SILENT) || printf "$(MSG_BIN) $@" | $(AWK_CMD)
	@$(BUILD_CMD)
	if [ ! -z "$(DFU_SUFFIX_ARGS)" ]; then \
		$(DFU_SUFFIX) $(DFU_SUFFIX_ARGS) -a $(BUILD_DIR)/$(TARGET).bin 1>/dev/null ;\
	fi
	#$(SILENT) || printf "$(MSG_EXECUTING) '$(DFU_SUFFIX) $(DFU_SUFFIX_ARGS) -a $(BUILD_DIR)/$(TARGET).bin 1>/dev/null':\n" ;\
	$(COPY) $(BUILD_DIR)/$(TARGET).bin $(TARGET).bin;

BEGIN = gccversion sizebefore

# Link: create ELF output file from object files.
.SECONDARY : $(BUILD_DIR)/$(TARGET).elf
.PRECIOUS : $(OBJ)
# Note the obj.txt depeendency is there to force linking if a source file is deleted
%.elf: $(OBJ) $(MASTER_OUTPUT)/cflags.txt $(MASTER_OUTPUT)/ldflags.txt $(MASTER_OUTPUT)/obj.txt | $(BEGIN)
	@$(SILENT) || printf "$(MSG_LINKING) $@" | $(AWK_CMD)
	$(eval CMD=MAKE=$(MAKE) $(CC) $(ALL_CFLAGS) $(filter-out %.txt,$^) --output $@ $(LDFLAGS))
	@$(BUILD_CMD)


define GEN_OBJRULE
$1_INCFLAGS := $$(patsubst %,-I%,$$($1_INC))
ifdef $1_CONFIG
$1_CONFIG_FLAGS += $$(patsubst %,-include %,$$($1_CONFIG))
endif
$1_CFLAGS = $$(ALL_CFLAGS) $$($1_DEFS) $$($1_INCFLAGS) $$($1_CONFIG_FLAGS) $$(NOLTO_CFLAGS)
$1_CXXFLAGS = $$(ALL_CXXFLAGS) $$($1_DEFS) $$($1_INCFLAGS) $$($1_CONFIG_FLAGS) $$(NOLTO_CFLAGS)
$1_ASFLAGS = $$(ALL_ASFLAGS) $$($1_DEFS) $$($1_INCFLAGS) $$($1_CONFIG_FLAGS)

# Compile: create object files from C source files.
$1/%.o : %.c $1/%.d $1/cflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$$(SILENT) || printf "$$(MSG_COMPILING) $$<" | $$(AWK_CMD)
	$$(eval CC_EXEC := $$(CC))
    ifneq ($$(VERBOSE_C_CMD),)
	$$(if $$(filter $$(notdir $$(VERBOSE_C_CMD)),$$(notdir $$<)),$$(eval CC_EXEC += -v))
    endif
    ifneq ($$(VERBOSE_C_INCLUDE),)
	$$(if $$(filter $$(notdir $$(VERBOSE_C_INCLUDE)),$$(notdir $$<)),$$(eval CC_EXEC += -H))
    endif
	$$(eval CMD := $$(CC_EXEC) -c $$($1_CFLAGS) $$(INIT_HOOK_CFLAGS) $$(GENDEPFLAGS) $$< -o $$@ && $$(MOVE_DEP))
	@$$(BUILD_CMD)
    ifneq ($$(DUMP_C_MACROS),)
	$$(eval CMD := $$(CC) -E -dM $$($1_CFLAGS) $$(INIT_HOOK_CFLAGS) $$(GENDEPFLAGS) $$<)
	@$$(if $$(filter $$(notdir $$(DUMP_C_MACROS)),$$(notdir $$<)),$$(BUILD_CMD))
    endif

# Compile: create object files from C++ source files.
$1/%.o : %.cpp $1/%.d $1/cxxflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$$(SILENT) || printf "$$(MSG_COMPILING_CXX) $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(CC) -c $$($1_CXXFLAGS) $$(INIT_HOOK_CFLAGS) $$(GENDEPFLAGS) $$< -o $$@ && $$(MOVE_DEP))
	@$$(BUILD_CMD)

$1/%.o : %.cc $1/%.d $1/cxxflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$$(SILENT) || printf "$$(MSG_COMPILING_CXX) $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(CC) -c $$($1_CXXFLAGS) $$(INIT_HOOK_CFLAGS) $$(GENDEPFLAGS) $$< -o $$@ && $$(MOVE_DEP))
	@$$(BUILD_CMD)

# Assemble: create object files from assembler source files.
$1/%.o : %.S $1/asflags.txt $1/compiler.txt | $(BEGIN)
	@mkdir -p $$(@D)
	@$(SILENT) || printf "$$(MSG_ASSEMBLING) $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(CC) -c $$($1_ASFLAGS) $$< -o $$@)
	@$$(BUILD_CMD)

$1/%.a : $1/%.o
	@mkdir -p $$(@D)
	@$(SILENT) || printf "Archiving: $$<" | $$(AWK_CMD)
	$$(eval CMD=$$(AR) rcs $$@ $$<)
	@$$(BUILD_CMD)

$1/force:

$1/cflags.txt: $1/force
	echo '$$($1_CFLAGS)' | cmp -s - $$@ || echo '$$($1_CFLAGS)' > $$@

$1/cxxflags.txt: $1/force
	echo '$$($1_CXXFLAGS)' | cmp -s - $$@ || echo '$$($1_CXXFLAGS)' > $$@

$1/asflags.txt: $1/force
	echo '$$($1_ASFLAGS)' | cmp -s - $$@ || echo '$$($1_ASFLAGS)' > $$@

$1/compiler.txt: $1/force
	test -f $$@ || touch $$@
	$$(CC) --version | cmp -s - $$@ || $$(CC) --version > $$@
endef

.PRECIOUS: $(MASTER_OUTPUT)/obj.txt
$(MASTER_OUTPUT)/obj.txt: $(MASTER_OUTPUT)/force
	echo '$(OBJ)' | cmp -s - $@ || echo '$(OBJ)' > $@

.PRECIOUS: $(MASTER_OUTPUT)/ldflags.txt
$(MASTER_OUTPUT)/ldflags.txt: $(MASTER_OUTPUT)/force
	echo '$(LDFLAGS)' | cmp -s - $@ || echo '$(LDFLAGS)' > $@


# We have to use static rules for the .d files for some reason
DEPS = $(patsubst %.o,%.d,$(patsubst %.a,%.o,$(OBJ)))
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

dump_vars: ERROR_IF_EMPTY=""
dump_vars: ERROR_IF_NONBOOL=""
dump_vars: ERROR_IF_UNSET=""
dump_vars: CATASTROPHIC_ERROR=""
dump_vars:
	@$(foreach V,$(sort $(.VARIABLES)),$(if $(filter-out environment% default automatic,$(origin $V)),$(info $V=$($V))))

objs-size:
	for i in $(OBJ); do echo $$i; done | sort | xargs $(SIZE)

ifeq ($(findstring avr-gcc,$(CC)),avr-gcc)
SIZE_MARGIN = 1024

check-size:
	$(eval MAX_SIZE=$(shell n=`$(CC) -E -mmcu=$(MCU) -D__ASSEMBLER__ $(CFLAGS) $(OPT_DEFS) platforms/avr/bootloader_size.c 2> /dev/null | $(SED) -ne 's/\r//;/^#/n;/^AVR_SIZE:/,$${s/^AVR_SIZE: //;p;}'` && echo $$(($$n)) || echo 0))
	$(eval CURRENT_SIZE=$(shell if [ -f $(BUILD_DIR)/$(TARGET).hex ]; then $(SIZE) --target=$(FORMAT) $(BUILD_DIR)/$(TARGET).hex | $(AWK) 'NR==2 {print $$4}'; else printf 0; fi))
	$(eval FREE_SIZE=$(shell expr $(MAX_SIZE) - $(CURRENT_SIZE)))
	$(eval OVER_SIZE=$(shell expr $(CURRENT_SIZE) - $(MAX_SIZE)))
	$(eval PERCENT_SIZE=$(shell expr $(CURRENT_SIZE) \* 100 / $(MAX_SIZE)))
	if [ $(MAX_SIZE) -gt 0 ] && [ $(CURRENT_SIZE) -gt 0 ]; then \
		$(SILENT) || printf "$(MSG_CHECK_FILESIZE)" | $(AWK_CMD); \
		if [ $(CURRENT_SIZE) -gt $(MAX_SIZE) ]; then \
		    printf "\n * $(MSG_FILE_TOO_BIG)"; $(PRINT_ERROR_PLAIN); \
		else \
		    if [ $(FREE_SIZE) -lt $(SIZE_MARGIN) ]; then \
			$(PRINT_WARNING_PLAIN); printf " * $(MSG_FILE_NEAR_LIMIT)"; \
		    else \
			$(PRINT_OK); $(SILENT) || printf " * $(MSG_FILE_JUST_RIGHT)"; \
		    fi ; \
		fi ; \
	fi
else
check-size:
	$(SILENT) || echo "$(MSG_CHECK_FILESIZE_SKIPPED)"
endif

check-md5:
	$(MD5SUM) $(BUILD_DIR)/$(TARGET).$(FIRMWARE_FORMAT)

# Create build directory
$(shell mkdir -p $(BUILD_DIR) 2>/dev/null)

# Create object files directory
$(eval $(foreach OUTPUT,$(OUTPUTS),$(shell mkdir -p $(OUTPUT) 2>/dev/null)))

# Include the dependency files.
-include $(patsubst %.o,%.d,$(patsubst %.a,%.o,$(OBJ)))


# Listing of phony targets.
.PHONY : all dump_vars finish sizebefore sizeafter qmkversion \
gccversion build elf hex uf2 eep lss sym coff extcoff \
clean clean_list debug gdb-config show_path \
program teensy dfu dfu-ee dfu-start \
flash dfu-split-left dfu-split-right \
avrdude-split-left avrdude-split-right \
avrdude-loop usbasp
