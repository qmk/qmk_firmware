COMMON_DIR = common
OBJECTS += \
#	$(COMMON_DIR)/host.o \
#	$(COMMON_DIR)/keyboard.o \
#	$(COMMON_DIR)/action.o \
#	$(COMMON_DIR)/action_tapping.o \
#	$(COMMON_DIR)/action_macro.o \
#	$(COMMON_DIR)/action_layer.o \
#	$(COMMON_DIR)/action_util.o \
#	$(COMMON_DIR)/keymap.o \
#	$(COMMON_DIR)/timer.o \
	$(COMMON_DIR)/print.o \
#	$(COMMON_DIR)/bootloader.o \
#	$(COMMON_DIR)/suspend.o \
	$(COMMON_DIR)/xprintf.o \
	$(COMMON_DIR)/util.o

INCLUDE_PATHS += \
	-I$(TMK_DIR)/$(COMMON_DIR)
