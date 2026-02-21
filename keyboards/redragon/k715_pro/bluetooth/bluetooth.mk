
BLUETOOTH_DIR = bluetooth
SRC += \
     $(BLUETOOTH_DIR)/bluetooth_main.c \
     $(BLUETOOTH_DIR)/btfunc.c \
     $(BLUETOOTH_DIR)/btspi.c \
     $(BLUETOOTH_DIR)/btsys.c

VPATH += $(TOP_DIR)/keyboards/redragon/k715_pro/$(BLUETOOTH_DIR)
