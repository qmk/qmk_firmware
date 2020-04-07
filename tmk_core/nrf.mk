# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
#ifeq ($(USE_PROCESS_STACKSIZE),)
#  USE_PROCESS_STACKSIZE = 0x800
#endif
#
## Stack size to the allocated to the Cortex-M main/exceptions stack. This
## stack is used for processing interrupts and exceptions.
#ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
#  USE_EXCEPTIONS_STACKSIZE = 0x400
#endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Imported source files and paths
NRFSDK_VER = 15
NRFCFLAGS += -DNRF_SDK_MAJOR_VER=$(NRFSDK_VER)
NRFCFLAGS += -DMATRIX_ROWS=32
NRFCFLAGS += -DMATRIX_COLS=32
NRFCFLAGS += -DRGBLED_NUM=128
NRFCFLAGS += -DEEPROM_SIZE=32

NRF_VER_DIR = sdk$(NRFSDK_VER)

COMMON_VPATH += $(DRIVER_PATH)/nrf52

GIT_DESCRIBE = $(shell git describe --tags --long --dirty="\\*")
CFLAGS += -DGIT_DESCRIBE=$(GIT_DESCRIBE)
CFLAGS += -DTARGET=$(TARGET)

ifeq ($(MCU_SERIES), NRF52840)
  NRFSRC +=  $(TOP_DIR)/tmk_core/protocol/nrf/gcc_startup_nrf52840.S \

endif

ifeq ($(MCU_SERIES), NRF52832)
  NRFSRC +=  $(TOP_DIR)/tmk_core/protocol/nrf/gcc_startup_nrf52.S \

endif

# Include folders common to all targets
EXTRAINCDIRS += \
  $(TMK_PATH)/protocol/nrf \
  $(TMK_PATH)/protocol/nrf/$(NRF_VER_DIR) \
  $(TMK_PATH)/protocol/nrf/nrf52 \
  $(TMK_PATH)/protocol/chibios/lufa_utils \

  NRFCFLAGS += -DAPP_USBD_VID=VENDOR_ID
  NRFCFLAGS += -DAPP_USBD_PID=PRODUCT_ID
  NRFCFLAGS += -DBOARD_CUSTOM
  NRFCFLAGS += -DCONFIG_NFCT_PINS_AS_GPIOS
  NRFCFLAGS += -DFLOAT_ABI_HARD
  NRFCFLAGS += -DSOFTDEVICE_PRESENT
  NRFCFLAGS += -DSWI_DISABLE0
  NRFCFLAGS += -mcpu=cortex-m4
  NRFCFLAGS += -mthumb -mabi=aapcs
#  NRFCFLAGS += -Wall -Werror
  NRFCFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
  # keep every function in a separate section, this allows linker to discard unused ones
  NRFCFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
  NRFCFLAGS += -fno-builtin -fshort-enums
  NRFCFLAGS += -Os

ifeq ($(MCU_SERIES), NRF52840)
  NRFCFLAGS += -DNRF52840_XXAA
  NRFCFLAGS += -DNRF_SD_BLE_API_VERSION=6
  NRFCFLAGS += -DS140
  ASFLAGS += -DNRF52840_XXAA
  ASFLAGS += -DNRF_SD_BLE_API_VERSION=6
  ASFLAGS += -DS140
endif
ifeq ($(MCU_SERIES), NRF52832)
  NRFCFLAGS += -DNRF52832_XXAA
  NRFCFLAGS += -DNRF_SD_BLE_API_VERSION=6
  NRFCFLAGS += -DS132
  ASMFLAGS += -DFLOAT_ABI_HARD
  ASMFLAGS += -DNRF52
  ASMFLAGS += -DNRF52832_XXAA
  ASMFLAGS += -DNRF52_PAN_74
  NRFCFLAGS += -DCONFIG_GPIO_AS_PINRESET
  ASFLAGS += -DNRF52832_XXAA
  ASFLAGS += -DNRF_SD_BLE_API_VERSION=6
  ASFLAGS += -DS132
  ASFLAGS += -DNRF52_PAN_74
endif

  ASFLAGS += -mcpu=cortex-m4
  ASFLAGS += -mthumb -mabi=aapcs
  ASFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
  ASFLAGS += -DBOARD_CUSTOM
#  ASFLAGS += -DCONFIG_GPIO_AS_PINRESET
  ASFLAGS += -DFLOAT_ABI_HARD
  ASFLAGS += -DSOFTDEVICE_PRESENT
  ASFLAGS += -DSWI_DISABLE0

  NRFCFLAGS += -D__HEAP_SIZE=0
  NRFCFLAGS += -D__STACK_SIZE=16384
  ASMFLAGS += -D__HEAP_SIZE=0
  ASMFLAGS += -D__STACK_SIZE=16384

  # Linker flags
  LDFLAGS += -mthumb -mabi=aapcs -L$(TOP_DIR)/tmk_core/protocol/nrf -T$(LDSCRIPT)
  LDFLAGS += -mcpu=cortex-m4
  LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
  # let linker to dump unused sections
  LDFLAGS += -Wl,--gc-sections
  # use newlib in nano version
  LDFLAGS += --specs=nano.specs -lc -lnosys
#  LDFLAGS += -L. $(NRFLIB)

# Project, sources and paths
##############################################################################

# Define linker script file here
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_5)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_4)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_3)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_2)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_1)/ld/$(MCU_LDSCRIPT).ld
else
    LDSCRIPT = $(STARTUPLD)/$(MCU_LDSCRIPT).ld
endif


##############################################################################
# Compiler settings
#
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
AR = arm-none-eabi-ar
NM = arm-none-eabi-nm
HEX = $(OBJCOPY) -O $(FORMAT)
EEP =
BIN = $(OBJCOPY) -O binary

#THUMBFLAGS = -DTHUMB_PRESENT -mno-thumb-interwork -DTHUMB_NO_INTERWORKING -mthumb -DTHUMB

#COMPILEFLAGS += -fomit-frame-pointer
#COMPILEFLAGS += -falign-functions=16
#COMPILEFLAGS += -ffunction-sections
#COMPILEFLAGS += -fdata-sections
#COMPILEFLAGS += -fno-common
#COMPILEFLAGS += -fshort-wchar
#COMPILEFLAGS += $(THUMBFLAGS)

NRFCFLAGS += $(COMPILEFLAGS)

#ASFLAGS += $(THUMBFLAGS)

CPPFLAGS += $(COMPILEFLAGS)
CPPFLAGS += -fno-rtti

# let linker to dump unused sections


MCUFLAGS = -mcpu=$(MCU)

OPT_DEFS += -DPROTOCOL_NRF

# FPU options default (Cortex-M4 and Cortex-M7 single precision).
ifeq ($(USE_FPU_OPT),)
  USE_FPU_OPT = -mfloat-abi=$(USE_FPU) -mfpu=fpv4-sp-d16 -fsingle-precision-constant
endif

# FPU-related options
ifeq ($(USE_FPU),)
  USE_FPU = no
endif
ifneq ($(USE_FPU),no)
  OPT    += $(USE_FPU_OPT)
  OPT_DEFS  += -DCORTEX_USE_FPU=TRUE
else
  OPT_DEFS  += -DCORTEX_USE_FPU=FALSE
endif

DEBUG = gdb

DFU_ARGS ?=
ifneq ("$(SERIAL)","")
	DFU_ARGS += -S $(SERIAL)
endif

# List any extra directories to look for libraries here.
EXTRALIBDIRS = $(RULESPATH)/ld .

DFU_UTIL ?= dfu-util

BOARD_INC :=

ifneq ("$(wildcard $(KEYBOARD_PATH_5)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_5)
    BOARD_INC += $(KEYBOARD_PATH_5)/board
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_4)
    BOARD_INC += $(KEYBOARD_PATH_4)/board
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_3)
    BOARD_INC += $(KEYBOARD_PATH_3)/board
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_2)
    BOARD_INC += $(KEYBOARD_PATH_2)/board
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_1)
    BOARD_INC += $(KEYBOARD_PATH_1)/board
else ifneq ("$(wildcard $(TOP_DIR)/drivers/board/custom_board.h)","")
    BOARD_PATH = $(TOP_DIR)/drivers
    BOARD_INC += $(TOP_DIR)/drivers/board/custom_board.h
endif

ifneq ("$(wildcard $(BOARD_INC))","")
    EXTRAINCDIRS += $(BOARD_INC)
endif

# Generate a .qmk for the QMK-FF
qmk: $(BUILD_DIR)/$(TARGET).bin
	zip $(TARGET).qmk -FSrj $(KEYMAP_PATH)/*
	zip $(TARGET).qmk -u $<
	printf "@ $<\n@=firmware.bin\n" | zipnote -w $(TARGET).qmk
	printf "{\n  \"generated\": \"%s\"\n}" "$$(date)" > $(BUILD_DIR)/$(TARGET).json
	if [ -f $(KEYBOARD_PATH_5)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_5)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_4)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_4)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_3)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_3)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_2)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_2)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_1)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_1)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	zip $(TARGET).qmk -urj $(BUILD_DIR)/$(TARGET).json
	printf "@ $(TARGET).json\n@=info.json\n" | zipnote -w $(TARGET).qmk

dfu-util: $(BUILD_DIR)/$(TARGET).bin cpfirmware sizeafter
	$(DFU_UTIL) $(DFU_ARGS) -D $(BUILD_DIR)/$(TARGET).bin

bin: $(BUILD_DIR)/$(TARGET).bin sizeafter
	$(COPY) $(BUILD_DIR)/$(TARGET).bin $(TARGET).bin;

GREP ?= grep
NRFUTIL ?= nrfutil

$(TARGET).ble.zip: $(TARGET).bin
	if ! type "nrfutil" > /dev/null 2>&1; then \
		echo 'ERROR: nrfutil is not found'; exit 1;\
	fi
	$(NRFUTIL) pkg generate --debug-mode --hw-version 0 --sd-req 0x8C --key-file $(PRIV_KEY) --application $(TARGET).bin $(TARGET).zip

dfu_ble: $(TARGET).ble.zip

zip: $(BUILD_DIR)/$(TARGET).bin
	if ! type "nrfutil" > /dev/null 2>&1; then \
		echo 'ERROR: nrfutil is not found'; exit 1;\
	fi
	$(NRFUTIL) pkg generate --debug-mode --hw-version 52 --sd-req 0xA9 --application $(TARGET).bin $(TARGET).zip

nrfutil: zip
	if $(GREP) -q -s Microsoft /proc/version; then \
		echo 'ERROR: nrfutil cannot be automated within the Windows Subsystem for Linux (WSL) currently.'; \
	else \
		printf "Detecting USB port, put your controller into dfu-mode now."; \
		ls /dev/tty* > /tmp/1; \
		while [ -z $$USB ]; do \
			sleep 0.5; \
			printf "."; \
			ls /dev/tty* > /tmp/2; \
			USB=`comm -13 /tmp/1 /tmp/2 | $(GREP) -o '/dev/tty.*' | head -n 1`; \
			mv /tmp/2 /tmp/1; \
		done; \
		echo ""; \
		echo "Detected controller on USB port at $$USB"; \
		if $(GREP) -q -s 'MINGW\|MSYS' /proc/version; then \
			USB=`echo "$$USB" | perl -pne 's/\/dev\/ttyS(\d+)/COM.($$1+1)/e'`; \
			echo "Remapped MSYS2 USB port to $$USB"; \
		fi; \
		sleep 1; \
		echo "Programming Started"; \
		$(NRFUTIL) dfu usb-serial -pkg $(TARGET).zip -p $$USB; \
	fi

uf2: $(BUILD_DIR)/$(TARGET).bin
	./util/uf2conv.py -f nrf52 -b 0x26000 -o $(TARGET).uf2 $(TARGET).bin -c
	-./util/uf2conv.py -f nrf52 -b 0x26000 $(TARGET).bin

elf: $(NRFLIB)

NRFLIBOBJ := $(NRFLIBSRC:%.c=$(BUILD_DIR)/$(NRFLIB)/%.o)
NRFLIBINC := $(patsubst %,-I%,$(EXTRAINCDIRS))
NRFLIBDEPS := $(patsubst %.o,%.d,$(NRFLIBOBJ))

$(BUILD_DIR)/$(NRFLIB)/%.o: %.c $(BUILD_DIR)/$(NRFLIB)/%.d $(BUILD_DIR)/$(NRFLIB)/cflags.txt
	@mkdir -p $(@D)
	@$(SILENT) || printf "$(MSG_COMPILING) $<" | $(AWK_CMD)
	$(CC) -c $(NRFCFLAGS) $(NRFLIBINC) -MMD -MP -MF $(patsubst %.o,%.td,$@) $< -o $@ && mv -f $(patsubst %.o,%.td,$@) $(patsubst %.o,%.d,$@)
	@$(BUILD_CMD)

$(BUILD_DIR)/$(NRFLIB)/force:

$(BUILD_DIR)/$(NRFLIB)/cflags.txt: $(BUILD_DIR)/$(NRFLIB)/force
	@mkdir -p $(@D)
	echo '$(NRFCFLAGS)' | cmp -s - $@ || echo '$(NRFCFLAGS)' > $@

# Keep the .d files
.PRECIOUS: $(NRFLIBDEPS)
# Empty rule to force recompilation if the .d file is missing
$(NRFLIBDEPS):

$(NRFLIB): $(NRFLIBOBJ)
	$(AR) rcs $@ $^

# Include the dependency files.
-include $(patsubst %.o,%.d,$(NRFLIBOBJ))

CFLAGS += $(NRFCFLAGS) $(EXTNRFCFLAGS)
EXTRAOBJ += $(NRFLIBOBJ)
