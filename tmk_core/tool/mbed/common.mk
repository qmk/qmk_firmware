OBJECTS += \
	$(OBJDIR)/common/action.o \
	$(OBJDIR)/common/action_tapping.o \
	$(OBJDIR)/common/action_macro.o \
	$(OBJDIR)/common/action_layer.o \
	$(OBJDIR)/common/action_util.o \
	$(OBJDIR)/common/host.o \
	$(OBJDIR)/common/keymap.o \
	$(OBJDIR)/common/keyboard.o \
	$(OBJDIR)/common/print.o \
	$(OBJDIR)/common/debug.o \
	$(OBJDIR)/common/util.o \
	$(OBJDIR)/common/mbed/suspend.o \
	$(OBJDIR)/common/mbed/timer.o \
	$(OBJDIR)/common/mbed/xprintf.o \
	$(OBJDIR)/common/mbed/bootloader.o \

INCLUDE_PATHS += \
	-I$(TMK_DIR)/common \
	-I$(TMK_DIR)/protocol

CC_FLAGS += -include $(CONFIG_H)



# Option modules
ifdef BOOTMAGIC_ENABLE
    $(error Not Supported)
    OBJECTS += $(OBJDIR)/common/bootmagic.o
    OBJECTS += $(OBJDIR)/common/mbed/eeprom.o
    OPT_DEFS += -DBOOTMAGIC_ENABLE
endif

ifdef MOUSEKEY_ENABLE
    OBJECTS += $(OBJDIR)/common/mousekey.o
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
    SRC += common/command.c
    OPT_DEFS += -DCOMMAND_ENABLE
endif

ifdef NKRO_ENABLE
    $(error Not Supported)
    OPT_DEFS += -DNKRO_ENABLE
endif

ifdef SLEEP_LED_ENABLE
    $(error Not Supported)
    SRC += common/mbed/sleep_led.c
    OPT_DEFS += -DSLEEP_LED_ENABLE
    OPT_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifdef BACKLIGHT_ENABLE
    $(error Not Supported)
    SRC += common/backlight.c
    OPT_DEFS += -DBACKLIGHT_ENABLE
endif

ifdef KEYMAP_SECTION_ENABLE
    $(error Not Supported)
    OPT_DEFS += -DKEYMAP_SECTION_ENABLE
    EXTRALDFLAGS = -Wl,-L$(TMK_DIR),-Tldscript_keymap_avr5.x
endif
