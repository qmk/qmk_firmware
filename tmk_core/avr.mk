# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Compiler settings
#
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AR = avr-ar
NM = avr-nm
HEX = $(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature
EEP = $(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT)
BIN =

COMMON_VPATH += $(DRIVER_PATH)/avr

COMPILEFLAGS += -funsigned-char
COMPILEFLAGS += -funsigned-bitfields
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fdata-sections
COMPILEFLAGS += -fpack-struct
COMPILEFLAGS += -fshort-enums

ASFLAGS += $(AVR_ASFLAGS)

CFLAGS += $(COMPILEFLAGS) $(AVR_CFLAGS)
CFLAGS += -fno-inline-small-functions
CFLAGS += -fno-strict-aliasing

CXXFLAGS += $(COMPILEFLAGS)
CXXFLAGS += -fno-exceptions -std=c++11

LDFLAGS +=-Wl,--gc-sections

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
# Autodetect teensy loader
ifndef TEENSY_LOADER_CLI
	ifneq (, $(shell which teensy-loader-cli 2>/dev/null))
		TEENSY_LOADER_CLI ?= teensy-loader-cli
	else
		TEENSY_LOADER_CLI ?= teensy_loader_cli
	endif
endif

# Program the device.
program: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep check-size
	$(PROGRAM_CMD)

define EXEC_TEENSY
	$(TEENSY_LOADER_CLI) -mmcu=$(MCU) -w -v $(BUILD_DIR)/$(TARGET).hex
endef

teensy: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_TEENSY)

BATCHISP ?= batchisp

flip: $(BUILD_DIR)/$(TARGET).hex check-size
	$(BATCHISP) -hardware usb -device $(MCU) -operation erase f
	$(BATCHISP) -hardware usb -device $(MCU) -operation loadbuffer $(BUILD_DIR)/$(TARGET).hex program
	$(BATCHISP) -hardware usb -device $(MCU) -operation start reset 0

DFU_PROGRAMMER ?= dfu-programmer
GREP ?= grep


define EXEC_DFU
	if [ "$(1)" ]; then \
		echo "Flashing '$(1)' for EE_HANDS split keyboard support." ;\
	fi; \
	until $(DFU_PROGRAMMER) $(MCU) get bootloader-version; do\
		printf "$(MSG_BOOTLOADER_NOT_FOUND)" ;\
		sleep 5 ;\
	done; \
	if $(DFU_PROGRAMMER) --version 2>&1 | $(GREP) -q 0.7 ; then\
		$(DFU_PROGRAMMER) $(MCU) erase --force; \
		if [ "$(1)" ]; then \
			$(DFU_PROGRAMMER) $(MCU) flash --eeprom $(QUANTUM_PATH)/split_common/$(1);\
		fi; \
	else \
		$(DFU_PROGRAMMER) $(MCU) erase; \
		if [ "$(1)" ]; then \
			$(DFU_PROGRAMMER) $(MCU) flash-eeprom $(QUANTUM_PATH)/split_common/$(1);\
		fi; \
	fi; \
	$(DFU_PROGRAMMER) $(MCU) flash $(BUILD_DIR)/$(TARGET).hex;\
	$(DFU_PROGRAMMER) $(MCU) reset
endef

dfu: $(BUILD_DIR)/$(TARGET).hex cpfirmware check-size
	$(call EXEC_DFU)

dfu-start:
	$(DFU_PROGRAMMER) $(MCU) reset
	$(DFU_PROGRAMMER) $(MCU) start

flip-ee: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep
	$(COPY) $(BUILD_DIR)/$(TARGET).eep $(BUILD_DIR)/$(TARGET)eep.hex
	$(BATCHISP) -hardware usb -device $(MCU) -operation memory EEPROM erase
	$(BATCHISP) -hardware usb -device $(MCU) -operation memory EEPROM loadbuffer $(BUILD_DIR)/$(TARGET)eep.hex program
	$(BATCHISP) -hardware usb -device $(MCU) -operation start reset 0
	$(REMOVE) $(BUILD_DIR)/$(TARGET)eep.hex

dfu-ee: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep
	if $(DFU_PROGRAMMER) --version 2>&1 | $(GREP) -q 0.7 ; then\
		$(DFU_PROGRAMMER) $(MCU) flash --eeprom $(BUILD_DIR)/$(TARGET).eep;\
	else\
		$(DFU_PROGRAMMER) $(MCU) flash-eeprom $(BUILD_DIR)/$(TARGET).eep;\
	fi
	$(DFU_PROGRAMMER) $(MCU) reset

dfu-split-left: $(BUILD_DIR)/$(TARGET).hex cpfirmware check-size
	$(call EXEC_DFU,eeprom-lefthand.eep)

dfu-split-right: $(BUILD_DIR)/$(TARGET).hex cpfirmware check-size
	$(call EXEC_DFU,eeprom-righthand.eep)

define EXEC_AVRDUDE
	USB= ;\
	if $(GREP) -q -s Microsoft /proc/version; then \
		echo 'ERROR: AVR flashing cannot be automated within the Windows Subsystem for Linux (WSL) currently. Instead, take the .hex file generated and flash it using AVRDUDE, AVRDUDESS, or XLoader.'; \
	else \
		printf "Detecting USB port, reset your controller now."; \
		ls /dev/tty* > /tmp/1; \
		while [ -z $$USB ]; do \
			sleep 0.5; \
			printf "."; \
			ls /dev/tty* > /tmp/2; \
			USB=`comm -13 /tmp/1 /tmp/2 | $(GREP) -o '/dev/tty.*'`; \
			mv /tmp/2 /tmp/1; \
		done; \
		echo ""; \
		echo "Device $$USB has appeared; assuming it is the controller."; \
		if $(GREP) -q -s 'MINGW\|MSYS' /proc/version; then \
			USB=`echo "$$USB" | perl -pne 's/\/dev\/ttyS(\d+)/COM.($$1+1)/e'`; \
			echo "Remapped MSYS2 USB port to $$USB"; \
			sleep 1; \
		else \
			printf "Waiting for $$USB to become writable."; \
			while [ ! -w "$$USB" ]; do sleep 0.5; printf "."; done; echo ""; \
		fi; \
		if [ -z "$(1)" ]; then \
			avrdude -p $(MCU) -c avr109 -P $$USB -U flash:w:$(BUILD_DIR)/$(TARGET).hex; \
		else \
			avrdude -p $(MCU) -c avr109 -P $$USB -U flash:w:$(BUILD_DIR)/$(TARGET).hex -U eeprom:w:$(QUANTUM_PATH)/split_common/$(1); \
		fi \
	fi
endef

avrdude: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_AVRDUDE)

avrdude-loop: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	while true; do \
		$(call EXEC_AVRDUDE) ; \
	done

avrdude-split-left: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_AVRDUDE,eeprom-lefthand.eep)

avrdude-split-right: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_AVRDUDE,eeprom-righthand.eep)

define EXEC_USBASP
	avrdude -p $(AVRDUDE_MCU) -c usbasp -U flash:w:$(BUILD_DIR)/$(TARGET).hex
endef

usbasp: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_USBASP)

BOOTLOADHID_PROGRAMMER ?= bootloadHID

define EXEC_BOOTLOADHID
	# bootloadHid executable has no cross platform detect methods
	# so keep running bootloadHid if the output contains "The specified device was not found"
	until $(BOOTLOADHID_PROGRAMMER) -r $(BUILD_DIR)/$(TARGET).hex 2>&1 | tee /dev/stderr | grep -v "device was not found"; do\
		printf "$(MSG_BOOTLOADER_NOT_FOUND)" ;\
		sleep 5 ;\
	done
endef

bootloadHID: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_BOOTLOADHID)

# Convert hex to bin.
bin: $(BUILD_DIR)/$(TARGET).hex
	$(OBJCOPY) -Iihex -Obinary $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
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

bootloader:
	make -C lib/lufa/Bootloaders/DFU/ clean
	$(TMK_DIR)/make_dfu_header.sh $(ALL_CONFIGS)
	$(eval MAX_SIZE=$(shell n=`$(CC) -E -mmcu=$(MCU) $(CFLAGS) $(OPT_DEFS) tmk_core/common/avr/bootloader_size.c 2> /dev/null | sed -ne 's/\r//;/^#/n;/^AVR_SIZE:/,$${s/^AVR_SIZE: //;p;}'` && echo $$(($$n)) || echo 0))
	$(eval PROGRAM_SIZE_KB=$(shell n=`expr $(MAX_SIZE) / 1024` && echo $$(($$n)) || echo 0))
	$(eval BOOT_SECTION_SIZE_KB=$(shell n=`expr  $(BOOTLOADER_SIZE) / 1024` && echo $$(($$n)) || echo 0))
	$(eval FLASH_SIZE_KB=$(shell n=`expr $(PROGRAM_SIZE_KB) + $(BOOT_SECTION_SIZE_KB)` && echo $$(($$n)) || echo 0))
	make -C lib/lufa/Bootloaders/DFU/ MCU=$(MCU) ARCH=$(ARCH) F_CPU=$(F_CPU) FLASH_SIZE_KB=$(FLASH_SIZE_KB) BOOT_SECTION_SIZE_KB=$(BOOT_SECTION_SIZE_KB)
	printf "BootloaderDFU.hex copied to $(TARGET)_bootloader.hex\n"
	cp lib/lufa/Bootloaders/DFU/BootloaderDFU.hex $(TARGET)_bootloader.hex

production: $(BUILD_DIR)/$(TARGET).hex bootloader cpfirmware
	@cat $(BUILD_DIR)/$(TARGET).hex | awk '/^:00000001FF/ == 0' > $(TARGET)_production.hex
	@cat $(TARGET)_bootloader.hex >> $(TARGET)_production.hex
	echo "File sizes:"
	$(SIZE) $(TARGET).hex $(TARGET)_bootloader.hex $(TARGET)_production.hex

flash:  $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
ifeq ($(strip $(BOOTLOADER)), caterina)
	$(call EXEC_AVRDUDE)
else ifeq ($(strip $(BOOTLOADER)), halfkay)
	$(call EXEC_TEENSY)
else ifeq (dfu,$(findstring dfu,$(BOOTLOADER)))
	$(call EXEC_DFU)
else ifeq ($(strip $(BOOTLOADER)), USBasp)
	$(call EXEC_USBASP)
else ifeq ($(strip $(BOOTLOADER)), bootloadHID)
	$(call EXEC_BOOTLOADHID)
else
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_BOOTLOADER)"
endif
