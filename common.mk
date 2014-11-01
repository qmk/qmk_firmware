ifndef PLATFORM
PLATFORM=avr
endif

COMMON_DIR = common
PLATFORM_DIR = $(COMMON_DIR)/$(PLATFORM)

SRC +=	$(COMMON_DIR)/host.c \
	$(COMMON_DIR)/keyboard.c \
	$(COMMON_DIR)/action.c \
	$(COMMON_DIR)/action_tapping.c \
	$(COMMON_DIR)/action_macro.c \
	$(COMMON_DIR)/action_layer.c \
	$(COMMON_DIR)/action_util.c \
	$(COMMON_DIR)/keymap.c \
	$(COMMON_DIR)/debug.c \
	$(COMMON_DIR)/util.c \
	$(PLATFORM_DIR)/suspend.c \
	$(PLATFORM_DIR)/bootloader.c

ifeq (PLATFORM,avr)
	$(COMMON_DIR)/print.c \
	SRC += $(PLATFORM_DIR)/xprintf.S
else
	SRCPP += $(PLATFORM_DIR)/xprintf.cpp
endif

ifeq (PLATFORM,teensy)
	SRCPP += $(PLATFORM_DIR)/timer.cpp
else
	SRC += $(PLATFORM_DIR)/timer.c
endif

# Option modules
ifdef BOOTMAGIC_ENABLE
    SRC += $(COMMON_DIR)/bootmagic.c
    SRC += $(PLATFORM_DIR)/eeconfig.c
    OPT_DEFS += -DBOOTMAGIC_ENABLE
endif

ifdef MOUSEKEY_ENABLE
    SRC += $(COMMON_DIR)/mousekey.c
    OPT_DEFS += -DMOUSEKEY_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifdef EXTRAKEY_ENABLE
    OPT_DEFS += -DEXTRAKEY_ENABLE
endif

ifdef CONSOLE_ENABLE
    OPT_DEFS += -DCONSOLE_ENABLE
else
    OPT_DEFS += -DNO_PRINT
    OPT_DEFS += -DNO_DEBUG
endif

ifdef COMMAND_ENABLE
    SRC += $(COMMON_DIR)/command.c
    OPT_DEFS += -DCOMMAND_ENABLE
endif

ifdef NKRO_ENABLE
    OPT_DEFS += -DNKRO_ENABLE
endif

ifdef USB_6KRO_ENABLE
    OPT_DEFS += -DUSB_6KRO_ENABLE
endif

ifdef SLEEP_LED_ENABLE
    SRC += $(COMMON_DIR)/sleep_led.c
    OPT_DEFS += -DSLEEP_LED_ENABLE
    OPT_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifdef BACKLIGHT_ENABLE
    SRC += $(COMMON_DIR)/backlight.c
    OPT_DEFS += -DBACKLIGHT_ENABLE
endif

ifdef KEYMAP_SECTION_ENABLE
    OPT_DEFS += -DKEYMAP_SECTION_ENABLE
    EXTRALDFLAGS = -Wl,-L$(TOP_DIR),-Tldscript_keymap_avr5.x
endif

# Version string
OPT_DEFS += -DVERSION=$(shell (git describe --always --dirty || echo 'unknown') 2> /dev/null)


# Search Path
VPATH += $(TOP_DIR)/common
