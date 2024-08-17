OPT_DEFS += -DANANLOG_MATRIX

ANALOG_MATRX_DIR = common/analog_matrix
SRC += \
     i2c_master.c \
     $(ANALOG_MATRX_DIR)/eeprom_he.c \
     $(ANALOG_MATRX_DIR)/analog_matrix_scan.c \
     $(ANALOG_MATRX_DIR)/profile.c \
     $(ANALOG_MATRX_DIR)/usb_descriptor_override.c \
     $(ANALOG_MATRX_DIR)/action_regular_trigger.c \
     $(ANALOG_MATRX_DIR)/action_rapid_trigger.c \
     $(ANALOG_MATRX_DIR)/action_okmc.c \
     $(ANALOG_MATRX_DIR)/action_toggle.c \
     $(ANALOG_MATRX_DIR)/action_joystick.c \
     $(ANALOG_MATRX_DIR)/action_xinput.c \
     $(ANALOG_MATRX_DIR)/sqrt.c \
     $(ANALOG_MATRX_DIR)/game_controller_common.c \
     $(ANALOG_MATRX_DIR)/analog_matrix.c

VPATH += $(TOP_DIR)/keyboards/keychron/$(ANALOG_MATRX_DIR)

