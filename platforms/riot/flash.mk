# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Architecture or project specific options
#

#BOSSAC_CLI ?= $(abspath $(RIOTBASE))/dist/tools/bossa-1.9/bossac
BOSSAC_CLI ?= bossac
GREP ?= grep

define EXEC_BOSSAC
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
	$(BOSSAC_CLI) -p $$USB -o $(ROM_OFFSET) -e -i -w -v -b -R $(BUILD_DIR)/$(TARGET).bin
endef

MDLOADER_CLI ?= mdloader

define EXEC_MDLOADER
	$(MDLOADER_CLI) --first --download $(BUILD_DIR)/$(TARGET).bin --restart
endef

flash: $(FIRMWARE_FORMAT)
ifneq ($(strip $(PROGRAM_CMD)),)
	$(UNSYNC_OUTPUT_CMD) && $(PROGRAM_CMD)
else ifeq ($(strip $(BOOTLOADER)), md-boot)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_MDLOADER)
else ifeq ($(strip $(BOOTLOADER)), sam-ba)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_BOSSAC)
else
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_ARCH)"
endif
