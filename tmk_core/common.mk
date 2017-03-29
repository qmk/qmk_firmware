COMMON_DIR = common
ifeq ($(PLATFORM),AVR)
	PLATFORM_COMMON_DIR = $(COMMON_DIR)/avr
else ifeq ($(PLATFORM),CHIBIOS)
	PLATFORM_COMMON_DIR = $(COMMON_DIR)/chibios
endif

TMK_COMMON_SRC +=	$(COMMON_DIR)/host.c \
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
	TMK_COMMON_SRC += $(PLATFORM_COMMON_DIR)/xprintf.S
endif 

ifeq ($(PLATFORM),CHIBIOS)
	TMK_COMMON_SRC += $(PLATFORM_COMMON_DIR)/printf.c
	TMK_COMMON_SRC += $(PLATFORM_COMMON_DIR)/eeprom.c
endif



# Option modules
ifeq ($(strip $(BOOTMAGIC_ENABLE)), yes)
    TMK_COMMON_DEFS += -DBOOTMAGIC_ENABLE
    TMK_COMMON_SRC += $(COMMON_DIR)/bootmagic.c
else
    TMK_COMMON_DEFS += -DMAGIC_ENABLE
    TMK_COMMON_SRC += $(COMMON_DIR)/magic.c
endif

ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
    TMK_COMMON_SRC += $(COMMON_DIR)/mousekey.c
    TMK_COMMON_DEFS += -DMOUSEKEY_ENABLE
    TMK_COMMON_DEFS += -DMOUSE_ENABLE
endif

ifeq ($(strip $(EXTRAKEY_ENABLE)), yes)
    TMK_COMMON_DEFS += -DEXTRAKEY_ENABLE
endif

ifeq ($(strip $(RAW_ENABLE)), yes)
    TMK_COMMON_DEFS += -DRAW_ENABLE
endif

ifeq ($(strip $(CONSOLE_ENABLE)), yes)
    TMK_COMMON_DEFS += -DCONSOLE_ENABLE
else
    TMK_COMMON_DEFS += -DNO_PRINT
    TMK_COMMON_DEFS += -DNO_DEBUG
endif

ifeq ($(strip $(COMMAND_ENABLE)), yes)
    TMK_COMMON_SRC += $(COMMON_DIR)/command.c
    TMK_COMMON_DEFS += -DCOMMAND_ENABLE
endif

ifeq ($(strip $(NKRO_ENABLE)), yes)
    TMK_COMMON_DEFS += -DNKRO_ENABLE
endif

ifeq ($(strip $(USB_6KRO_ENABLE)), yes)
    TMK_COMMON_DEFS += -DUSB_6KRO_ENABLE
endif

ifeq ($(strip $(SLEEP_LED_ENABLE)), yes)
    TMK_COMMON_SRC += $(PLATFORM_COMMON_DIR)/sleep_led.c
    TMK_COMMON_DEFS += -DSLEEP_LED_ENABLE
    TMK_COMMON_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifeq ($(strip $(NO_UART)), yes)
    TMK_COMMON_DEFS += -DNO_UART
endif

ifeq ($(strip $(NO_SUSPEND_POWER_DOWN)), yes)
    TMK_COMMON_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifeq ($(strip $(BACKLIGHT_ENABLE)), yes)
    TMK_COMMON_SRC += $(COMMON_DIR)/backlight.c
    TMK_COMMON_DEFS += -DBACKLIGHT_ENABLE
endif

ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
    TMK_COMMON_DEFS += -DBLUETOOTH_ENABLE
endif

ifeq ($(strip $(BLUETOOTH)), AdafruitBLE)
		TMK_COMMON_DEFS += -DBLUETOOTH_ENABLE
		TMK_COMMON_DEFS += -DMODULE_ADAFRUIT_BLE
endif

ifeq ($(strip $(BLUETOOTH)), AdafruitEZKey)
		TMK_COMMON_DEFS += -DBLUETOOTH_ENABLE
		TMK_COMMON_DEFS += -DMODULE_ADAFRUIT_EZKEY
endif

ifeq ($(strip $(ONEHAND_ENABLE)), yes)
    TMK_COMMON_DEFS += -DONEHAND_ENABLE
endif

ifeq ($(strip $(KEYMAP_SECTION_ENABLE)), yes)
    TMK_COMMON_DEFS += -DKEYMAP_SECTION_ENABLE

    ifeq ($(strip $(MCU)),atmega32u2)
	TMK_COMMON_LDFLAGS = -Wl,-L$(TMK_DIR),-Tldscript_keymap_avr35.x
    else ifeq ($(strip $(MCU)),atmega32u4)
	TMK_COMMON_LDFLAGS = -Wl,-L$(TMK_DIR),-Tldscript_keymap_avr5.x
    else
	TMK_COMMON_LDFLAGS = $(error no ldscript for keymap section)
    endif
endif

# Bootloader address
ifdef STM32_BOOTLOADER_ADDRESS
    TMK_COMMON_DEFS += -DSTM32_BOOTLOADER_ADDRESS=$(STM32_BOOTLOADER_ADDRESS)
endif

# Search Path
VPATH += $(TMK_PATH)/$(COMMON_DIR)
ifeq ($(PLATFORM),CHIBIOS)
VPATH += $(TMK_PATH)/$(COMMON_DIR)/chibios
endif
