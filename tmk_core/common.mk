COMMON_DIR = common
ifeq ($(PLATFORM),AVR)
	PLATFORM_COMMON_DIR = $(COMMON_DIR)/avr
else ifeq ($(PLATFORM),CHIBIOS)
	PLATFORM_COMMON_DIR = $(COMMON_DIR)/chibios
endif

SRC +=	$(COMMON_DIR)/host.c \
	$(COMMON_DIR)/keyboard.c \
	$(COMMON_DIR)/action.c \
	$(COMMON_DIR)/action_tapping.c \
	$(COMMON_DIR)/action_macro.c \
	$(COMMON_DIR)/action_layer.c \
	$(COMMON_DIR)/action_util.c \
	$(COMMON_DIR)/print.c \
	$(COMMON_DIR)/debug.c \
	$(COMMON_DIR)/util.c \
	$(COMMON_DIR)/eeconfig.c \
	$(PLATFORM_COMMON_DIR)/suspend.c \
	$(PLATFORM_COMMON_DIR)/timer.c \
	$(PLATFORM_COMMON_DIR)/bootloader.c \

ifeq ($(PLATFORM),AVR)
	SRC += $(PLATFORM_COMMON_DIR)/xprintf.S
endif 

ifeq ($(PLATFORM),CHIBIOS)
	SRC += $(PLATFORM_COMMON_DIR)/printf.c
	SRC += $(PLATFORM_COMMON_DIR)/eeprom.c
endif



# Option modules
ifeq ($(strip $(BOOTMAGIC_ENABLE)), yes)
    OPT_DEFS += -DBOOTMAGIC_ENABLE
    SRC += $(COMMON_DIR)/bootmagic.c
else
    OPT_DEFS += -DMAGIC_ENABLE
    SRC += $(COMMON_DIR)/magic.c
endif

ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
    SRC += $(COMMON_DIR)/mousekey.c
    OPT_DEFS += -DMOUSEKEY_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifeq ($(strip $(EXTRAKEY_ENABLE)), yes)
    OPT_DEFS += -DEXTRAKEY_ENABLE
endif

ifeq ($(strip $(CONSOLE_ENABLE)), yes)
    OPT_DEFS += -DCONSOLE_ENABLE
else
    OPT_DEFS += -DNO_PRINT
    OPT_DEFS += -DNO_DEBUG
endif

ifeq ($(strip $(COMMAND_ENABLE)), yes)
    SRC += $(COMMON_DIR)/command.c
    OPT_DEFS += -DCOMMAND_ENABLE
endif

ifeq ($(strip $(NKRO_ENABLE)), yes)
    OPT_DEFS += -DNKRO_ENABLE
endif

ifeq ($(strip $(USB_6KRO_ENABLE)), yes)
    OPT_DEFS += -DUSB_6KRO_ENABLE
endif

ifeq ($(strip $(SLEEP_LED_ENABLE)), yes)
    SRC += $(PLATFORM_COMMON_DIR)/sleep_led.c
    OPT_DEFS += -DSLEEP_LED_ENABLE
    OPT_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifeq ($(strip $(BACKLIGHT_ENABLE)), yes)
    SRC += $(COMMON_DIR)/backlight.c
    OPT_DEFS += -DBACKLIGHT_ENABLE
endif

ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
    OPT_DEFS += -DBLUETOOTH_ENABLE
endif

ifeq ($(strip $(KEYMAP_SECTION_ENABLE)), yes)
    OPT_DEFS += -DKEYMAP_SECTION_ENABLE

    ifeq ($(strip $(MCU)),atmega32u2)
	EXTRALDFLAGS = -Wl,-L$(TMK_DIR),-Tldscript_keymap_avr35.x
    else ifeq ($(strip $(MCU)),atmega32u4)
	EXTRALDFLAGS = -Wl,-L$(TMK_DIR),-Tldscript_keymap_avr5.x
    else
	EXTRALDFLAGS = $(error no ldscript for keymap section)
    endif
endif

ifeq ($(MASTER),right)	
	OPT_DEFS += -DMASTER_IS_ON_RIGHT
else 
	ifneq ($(MASTER),left)
$(error MASTER does not have a valid value(left/right))
	endif
endif


# Version string
OPT_DEFS += -DVERSION=$(GIT_VERSION)

# Bootloader address
ifdef STM32_BOOTLOADER_ADDRESS
    OPT_DEFS += -DSTM32_BOOTLOADER_ADDRESS=$(STM32_BOOTLOADER_ADDRESS)
endif

# Search Path
VPATH += $(TMK_PATH)/$(COMMON_DIR)
ifeq ($(PLATFORM),CHIBIOS)
VPATH += $(TMK_PATH)/$(COMMON_DIR)/chibios
endif