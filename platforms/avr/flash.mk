# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Architecture or project specific options
#

# Autodetect teensy loader
ifndef TEENSY_LOADER_CLI
	ifneq (, $(shell which teensy-loader-cli 2>/dev/null))
		TEENSY_LOADER_CLI ?= teensy-loader-cli
	else
		TEENSY_LOADER_CLI ?= teensy_loader_cli
	endif
endif

define EXEC_TEENSY
	$(TEENSY_LOADER_CLI) -mmcu=$(MCU) -w -v $(BUILD_DIR)/$(TARGET).hex
endef

teensy: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_TEENSY)

DFU_PROGRAMMER ?= dfu-programmer
GREP ?= grep

define EXEC_DFU
	if [ "$(1)" ]; then \
		echo "Flashing '$(1)' for EE_HANDS split keyboard support." ;\
	fi; \
	if ! $(DFU_PROGRAMMER) $(MCU) get bootloader-version >/dev/null 2>/dev/null; then\
		printf "$(MSG_BOOTLOADER_NOT_FOUND_QUICK_RETRY)" ;\
		sleep $(BOOTLOADER_RETRY_TIME) ;\
		while ! $(DFU_PROGRAMMER) $(MCU) get bootloader-version >/dev/null 2>/dev/null; do\
			printf "." ;\
			sleep $(BOOTLOADER_RETRY_TIME) ;\
		done ;\
		printf "\n" ;\
	fi; \
	$(DFU_PROGRAMMER) $(MCU) get bootloader-version ;\
	if $(DFU_PROGRAMMER) --version 2>&1 | $(GREP) -q 0.7 ; then\
		$(DFU_PROGRAMMER) $(MCU) erase --force; \
		if [ "$(1)" ]; then \
			$(DFU_PROGRAMMER) $(MCU) flash --force --eeprom $(QUANTUM_PATH)/split_common/$(1);\
		fi; \
		$(DFU_PROGRAMMER) $(MCU) flash --force $(BUILD_DIR)/$(TARGET).hex;\
	else \
		$(DFU_PROGRAMMER) $(MCU) erase; \
		if [ "$(1)" ]; then \
			$(DFU_PROGRAMMER) $(MCU) flash-eeprom $(QUANTUM_PATH)/split_common/$(1);\
		fi; \
		$(DFU_PROGRAMMER) $(MCU) flash $(BUILD_DIR)/$(TARGET).hex;\
	fi; \
	$(DFU_PROGRAMMER) $(MCU) reset
endef

dfu: $(BUILD_DIR)/$(TARGET).hex cpfirmware check-size
	$(call EXEC_DFU)

dfu-start:
	$(DFU_PROGRAMMER) $(MCU) reset
	$(DFU_PROGRAMMER) $(MCU) start

dfu-ee: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).eep
	if $(DFU_PROGRAMMER) --version 2>&1 | $(GREP) -q 0.7 ; then\
		$(DFU_PROGRAMMER) $(MCU) flash --force --eeprom $(BUILD_DIR)/$(TARGET).eep;\
	else\
		$(DFU_PROGRAMMER) $(MCU) flash-eeprom $(BUILD_DIR)/$(TARGET).eep;\
	fi
	$(DFU_PROGRAMMER) $(MCU) reset

dfu-split-left: $(BUILD_DIR)/$(TARGET).hex cpfirmware check-size
	$(call EXEC_DFU,eeprom-lefthand.eep)

dfu-split-right: $(BUILD_DIR)/$(TARGET).hex cpfirmware check-size
	$(call EXEC_DFU,eeprom-righthand.eep)

AVRDUDE_PROGRAMMER ?= avrdude

define EXEC_AVRDUDE
	list_devices() { \
		if $(GREP) -q -s icrosoft /proc/version; then \
		    wmic.exe path Win32_SerialPort get DeviceID 2>/dev/null | LANG=C perl -pne 's/COM(\d+)/COM.($$1-1)/e' | sed 's!COM!/dev/ttyS!' | xargs echo -n | sort; \
		elif [ "`uname`" = "FreeBSD" ]; then \
			ls /dev/tty* | grep -v '\.lock$$' | grep -v '\.init$$'; \
		else \
			ls /dev/tty*; \
		fi; \
	}; \
	USB= ;\
	printf "Waiting for USB serial port - reset your controller now (Ctrl+C to cancel)"; \
	TMP1=`mktemp`; \
	TMP2=`mktemp`; \
	list_devices > $$TMP1; \
	while [ -z "$$USB" ]; do \
		sleep $(BOOTLOADER_RETRY_TIME); \
		printf "."; \
		list_devices > $$TMP2; \
		USB=`comm -13 $$TMP1 $$TMP2 | $(GREP) -o '/dev/tty.*'`; \
		mv $$TMP2 $$TMP1; \
	done; \
	rm $$TMP1; \
	echo ""; \
	echo "Device $$USB has appeared; assuming it is the controller."; \
	if $(GREP) -q -s 'MINGW\|MSYS\|icrosoft' /proc/version; then \
		USB=`echo "$$USB" | LANG=C perl -pne 's/\/dev\/ttyS(\d+)/COM.($$1+1)/e'`; \
		echo "Remapped USB port to $$USB"; \
		sleep 1; \
	else \
		printf "Waiting for $$USB to become writable."; \
		while [ ! -w "$$USB" ]; do sleep $(BOOTLOADER_RETRY_TIME); printf "."; done; echo ""; \
	fi; \
	if [ -z "$(1)" ]; then \
		$(AVRDUDE_PROGRAMMER) -p $(MCU) -c avr109 -P $$USB -U flash:w:$(BUILD_DIR)/$(TARGET).hex; \
	else \
		$(AVRDUDE_PROGRAMMER) -p $(MCU) -c avr109 -P $$USB -U flash:w:$(BUILD_DIR)/$(TARGET).hex -U eeprom:w:$(QUANTUM_PATH)/split_common/$(1); \
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
	$(AVRDUDE_PROGRAMMER) -p $(AVRDUDE_MCU) -c usbasp -U flash:w:$(BUILD_DIR)/$(TARGET).hex
endef

usbasp: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_USBASP)

BOOTLOADHID_PROGRAMMER ?= bootloadHID

# bootloadHid executable has no cross platform detect methods
# so keep running bootloadHid if the output contains "The specified device was not found"
define EXEC_BOOTLOADHID
	until $(BOOTLOADHID_PROGRAMMER) -r $(BUILD_DIR)/$(TARGET).hex 2>&1 | tee /dev/stderr | grep -v "device was not found"; do\
		printf "$(MSG_BOOTLOADER_NOT_FOUND)" ;\
		sleep 5 ;\
	done
endef

bootloadhid: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_BOOTLOADHID)

HID_BOOTLOADER_CLI ?= hid_bootloader_cli

define EXEC_HID_LUFA
	$(HID_BOOTLOADER_CLI) -mmcu=$(MCU) -w -v $(BUILD_DIR)/$(TARGET).hex
endef

hid_bootloader: $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
	$(call EXEC_HID_LUFA)

flash:  $(BUILD_DIR)/$(TARGET).hex check-size cpfirmware
ifneq ($(strip $(PROGRAM_CMD)),)
	$(UNSYNC_OUTPUT_CMD) && $(PROGRAM_CMD)
else ifeq ($(strip $(BOOTLOADER)), caterina)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_AVRDUDE)
else ifeq ($(strip $(BOOTLOADER)), halfkay)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_TEENSY)
else ifeq (dfu,$(findstring dfu,$(BOOTLOADER)))
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_DFU)
else ifneq (,$(filter $(BOOTLOADER), usbasploader USBasp))
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_USBASP)
else ifneq (,$(filter $(BOOTLOADER), bootloadhid bootloadHID))
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_BOOTLOADHID)
else ifeq ($(strip $(BOOTLOADER)), qmk-hid)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_HID_LUFA)
else
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_BOOTLOADER)"
endif
