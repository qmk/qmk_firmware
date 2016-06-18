COMMON_DIR = common
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
	$(COMMON_DIR)/avr/suspend.c \
	$(COMMON_DIR)/avr/xprintf.S \
	$(COMMON_DIR)/avr/timer.c \
	$(COMMON_DIR)/avr/bootloader.c


# Option modules
ifeq ($(strip $(BOOTMAGIC_ENABLE)), yes)
    SRC += $(COMMON_DIR)/bootmagic.c
    SRC += $(COMMON_DIR)/avr/eeconfig.c
    OPT_DEFS += -DBOOTMAGIC_ENABLE
else
    SRC += $(COMMON_DIR)/magic.c
    SRC += $(COMMON_DIR)/avr/eeconfig.c
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

ifeq ($(strip $(MIDI_ENABLE)), yes)
    OPT_DEFS += -DMIDI_ENABLE
endif

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    OPT_DEFS += -DAUDIO_ENABLE
endif

ifeq ($(strip $(UNICODE_ENABLE)), yes)
    OPT_DEFS += -DUNICODE_ENABLE
endif

ifeq ($(strip $(USB_6KRO_ENABLE)), yes)
    OPT_DEFS += -DUSB_6KRO_ENABLE
endif

ifeq ($(strip $(SLEEP_LED_ENABLE)), yes)
    SRC += $(COMMON_DIR)/sleep_led.c
    OPT_DEFS += -DSLEEP_LED_ENABLE
    OPT_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifeq ($(strip $(BACKLIGHT_ENABLE)), yes)
    SRC += $(COMMON_DIR)/backlight.c
    SRC += $(COMMON_DIR)/avr/eeconfig.c
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

# Version string
OPT_DEFS += -DVERSION=$(shell (git describe --always --dirty || echo 'unknown') 2> /dev/null)


# Search Path
VPATH += $(TMK_PATH)/$(COMMON_DIR)
