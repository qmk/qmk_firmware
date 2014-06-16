COMMON_DIR = common
OBJECTS += \
	$(OBJDIR)/$(COMMON_DIR)/mbed/timer.o \
	$(OBJDIR)/$(COMMON_DIR)/mbed/xprintf.o \

INCLUDE_PATHS += \
	-I$(TMK_DIR)/$(COMMON_DIR)



#	$(OBJDIR)/$(COMMON_DIR)/action.o \

#	$(OBJDIR)/$(COMMON_DIR)/host.o \
#	$(OBJDIR)/$(COMMON_DIR)/keyboard.o \
#	$(OBJDIR)/$(COMMON_DIR)/action_tapping.o \
#	$(OBJDIR)/$(COMMON_DIR)/action_macro.o \
#	$(OBJDIR)/$(COMMON_DIR)/action_layer.o \
#	$(OBJDIR)/$(COMMON_DIR)/action_util.o \
#	$(OBJDIR)/$(COMMON_DIR)/keymap.o \
#	$(OBJDIR)/$(COMMON_DIR)/bootloader.o \
#	$(OBJDIR)/$(COMMON_DIR)/suspend.o \
