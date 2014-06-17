COMMON_DIR = common
OBJECTS += \
	$(OBJDIR)/$(COMMON_DIR)/action.o \
	$(OBJDIR)/$(COMMON_DIR)/action_tapping.o \
	$(OBJDIR)/$(COMMON_DIR)/action_macro.o \
	$(OBJDIR)/$(COMMON_DIR)/action_layer.o \
	$(OBJDIR)/$(COMMON_DIR)/action_util.o \
	$(OBJDIR)/$(COMMON_DIR)/host.o \
	$(OBJDIR)/$(COMMON_DIR)/keymap.o \
	$(OBJDIR)/$(COMMON_DIR)/keyboard.o \
	$(OBJDIR)/$(COMMON_DIR)/util.o \
	$(OBJDIR)/$(COMMON_DIR)/mbed/suspend.o \
	$(OBJDIR)/$(COMMON_DIR)/mbed/timer.o \
	$(OBJDIR)/$(COMMON_DIR)/mbed/xprintf.o \
	$(OBJDIR)/$(COMMON_DIR)/mbed/bootloader.o \

INCLUDE_PATHS += \
	-I$(TMK_DIR)/$(COMMON_DIR)

CC_FLAGS += -include $(CONFIG_H)



# Option modules
ifdef BOOTMAGIC_ENABLE
    $(error Not Supported)
    OBJECTS += $(OBJDIR)/$(COMMON_DIR)/bootmagic.o
    OBJECTS += $(OBJDIR)/$(COMMON_DIR)/mbed/eeprom.o
    OPT_DEFS += -DBOOTMAGIC_ENABLE
endif

ifdef MOUSEKEY_ENABLE
    OBJECTS += $(OBJDIR)/$(COMMON_DIR)/mousekey.o
    OPT_DEFS += -DMOUSEKEY_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifdef EXTRAKEY_ENABLE
    $(error Not Supported)
    OPT_DEFS += -DEXTRAKEY_ENABLE
endif

ifdef CONSOLE_ENABLE
    $(error Not Supported)
    OPT_DEFS += -DCONSOLE_ENABLE
else
    OPT_DEFS += -DNO_PRINT
    OPT_DEFS += -DNO_DEBUG
endif

ifdef COMMAND_ENABLE
    $(error Not Supported)
    SRC += $(COMMON_DIR)/command.c
    OPT_DEFS += -DCOMMAND_ENABLE
endif

ifdef NKRO_ENABLE
    $(error Not Supported)
    OPT_DEFS += -DNKRO_ENABLE
endif

ifdef SLEEP_LED_ENABLE
    $(error Not Supported)
    SRC += $(COMMON_DIR)/sleep_led.c
    OPT_DEFS += -DSLEEP_LED_ENABLE
    OPT_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifdef BACKLIGHT_ENABLE
    $(error Not Supported)
    SRC += $(COMMON_DIR)/backlight.c
    OPT_DEFS += -DBACKLIGHT_ENABLE
endif

ifdef KEYMAP_SECTION_ENABLE
    $(error Not Supported)
    OPT_DEFS += -DKEYMAP_SECTION_ENABLE
    EXTRALDFLAGS = -Wl,-L$(TOP_DIR),-Tldscript_keymap_avr5.x
endif
