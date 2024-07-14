

OPT_DEFS += -DBLUETOOTH_ENABLE
NO_USB_STARTUP_CHECK := yes

BLUETOOTH_DIR = bluetooth
SRC += \
     $(BLUETOOTH_DIR)/bluetooth.c \
     $(BLUETOOTH_DIR)/report_buffer.c \
     $(BLUETOOTH_DIR)/outputselect.c \
     $(BLUETOOTH_DIR)/bhq.c \
     $(BLUETOOTH_DIR)/lpm_stm32f4.c \

VPATH += $(TOP_DIR)/keyboards/keymagichorse/$(BLUETOOTH_DIR)
