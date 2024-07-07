

OPT_DEFS += -DBLUETOOTH_ENABLE

BLUETOOTH_DIR = bluetooth
SRC += \
     $(BLUETOOTH_DIR)/bluetooth.c \
     $(BLUETOOTH_DIR)/report_buffer.c \
     $(BLUETOOTH_DIR)/outputselect.c \
     $(BLUETOOTH_DIR)/bhq.c \

VPATH += $(TOP_DIR)/keyboards/keymagichorse/$(BLUETOOTH_DIR)
