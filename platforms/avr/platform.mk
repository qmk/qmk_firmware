# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Compiler settings
#
CC = $(CC_PREFIX) avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AR = avr-ar
NM = avr-nm
HEX = $(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature
EEP = $(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT)
BIN =

ifeq ("$(shell echo "int main(){}" | $(CC) --param=min-pagesize=0 -x c - -o /dev/null 2>&1)", "")
COMPILEFLAGS += --param=min-pagesize=0
endif

COMPILEFLAGS += -funsigned-char
COMPILEFLAGS += -funsigned-bitfields
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fdata-sections
COMPILEFLAGS += -fpack-struct
COMPILEFLAGS += -fshort-enums
COMPILEFLAGS += -mcall-prologues
COMPILEFLAGS += -fno-builtin-printf

# Linker relaxation is only possible if
# link time optimizations are not enabled.
ifeq ($(strip $(LTO_ENABLE)), no)
	COMPILEFLAGS += -mrelax
endif

ASFLAGS += $(AVR_ASFLAGS)

CFLAGS += $(COMPILEFLAGS) $(AVR_CFLAGS)
CFLAGS += -fno-inline-small-functions
CFLAGS += -fno-strict-aliasing

CXXFLAGS += $(COMPILEFLAGS)
CXXFLAGS += -fno-exceptions $(CXXSTANDARD)

LDFLAGS += -Wl,--gc-sections

# Use AVR's libc minimal printf implementation which has less features
# and thus can shave ~400 bytes. Usually we use the xprintf
# implementation but keyboards that use s(n)printf automatically
# pull in the AVR libc implementation, which is ~900 bytes heavy.
AVR_USE_MINIMAL_PRINTF ?= no
ifeq ($(strip $(AVR_USE_MINIMAL_PRINTF)), yes)
	LDFLAGS += -Wl,--whole-archive -lprintf_min -Wl,--no-whole-archive
endif

OPT_DEFS += -DF_CPU=$(F_CPU)UL

MCUFLAGS = -mmcu=$(MCU)

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

#---------------- Debugging Options ----------------

# Debugging format.
#     Native formats for AVR-GCC's -g are dwarf-2 [default] or stabs.
#     AVR Studio 4.10 requires dwarf-2.
#     AVR [Extended] COFF format requires stabs, plus an avr-objcopy run.
DEBUG = dwarf-2

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

# Convert hex to bin.
bin: $(BUILD_DIR)/$(TARGET).hex
ifeq ($(BOOTLOADER),lufa-ms)
	$(eval BIN_PADDING=$(shell n=`expr 32768 - $(BOOTLOADER_SIZE)` && echo $$(($$n)) || echo 0))
	$(OBJCOPY) -Iihex -Obinary $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin --pad-to $(BIN_PADDING)
else
	$(OBJCOPY) -Iihex -Obinary $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
endif
	$(COPY) $(BUILD_DIR)/$(TARGET).bin $(TARGET).bin;

# copy bin to FLASH.bin
flashbin: bin
	$(COPY) $(BUILD_DIR)/$(TARGET).bin FLASH.bin;

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

ifeq ($(strip $(BOOTLOADER)), qmk-dfu)
QMK_BOOTLOADER_TYPE = DFU
else ifeq ($(strip $(BOOTLOADER)), qmk-hid)
QMK_BOOTLOADER_TYPE = HID
endif

bootloader:
ifeq ($(strip $(QMK_BOOTLOADER_TYPE)),)
	$(call CATASTROPHIC_ERROR,Invalid BOOTLOADER,Please set BOOTLOADER to "qmk-dfu" or "qmk-hid" first!)
else
	make -C lib/lufa/Bootloaders/$(QMK_BOOTLOADER_TYPE)/ clean
	$(QMK_BIN) generate-dfu-header --quiet --keyboard $(KEYBOARD) --output lib/lufa/Bootloaders/$(QMK_BOOTLOADER_TYPE)/Keyboard.h
	$(eval MAX_SIZE=$(shell n=`$(CC) -E -mmcu=$(MCU) -D__ASSEMBLER__ $(CFLAGS) $(OPT_DEFS) platforms/avr/bootloader_size.c 2> /dev/null | sed -ne 's/\r//;/^#/n;/^AVR_SIZE:/,$${s/^AVR_SIZE: //;p;}'` && echo $$(($$n)) || echo 0))
	$(eval PROGRAM_SIZE_KB=$(shell n=`expr $(MAX_SIZE) / 1024` && echo $$(($$n)) || echo 0))
	$(eval BOOT_SECTION_SIZE_KB=$(shell n=`expr  $(BOOTLOADER_SIZE) / 1024` && echo $$(($$n)) || echo 0))
	$(eval FLASH_SIZE_KB=$(shell n=`expr $(PROGRAM_SIZE_KB) + $(BOOT_SECTION_SIZE_KB)` && echo $$(($$n)) || echo 0))
	make -C lib/lufa/Bootloaders/$(QMK_BOOTLOADER_TYPE)/ MCU=$(MCU) ARCH=$(ARCH) F_CPU=$(F_CPU) FLASH_SIZE_KB=$(FLASH_SIZE_KB) BOOT_SECTION_SIZE_KB=$(BOOT_SECTION_SIZE_KB)
	printf "Bootloader$(QMK_BOOTLOADER_TYPE).hex copied to $(TARGET)_bootloader.hex\n"
	cp lib/lufa/Bootloaders/$(QMK_BOOTLOADER_TYPE)/Bootloader$(QMK_BOOTLOADER_TYPE).hex $(TARGET)_bootloader.hex
endif

production: $(BUILD_DIR)/$(TARGET).hex bootloader cpfirmware
	@cat $(BUILD_DIR)/$(TARGET).hex | awk '/^:00000001FF/ == 0' > $(TARGET)_production.hex
	@cat $(TARGET)_bootloader.hex >> $(TARGET)_production.hex
	echo "File sizes:"
	$(SIZE) $(TARGET).hex $(TARGET)_bootloader.hex $(TARGET)_production.hex
