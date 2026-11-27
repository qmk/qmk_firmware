# Bluetooth and battery support use the installed TEX add-on. SHURA_BLE_MODULE selects its driver:
# ble5 for the module sold for the Shura, or ble4 for the older module sold for the Shinobi.
# Keymaps can set BLUETOOTH_ENABLE = no for USB only.
SHURA_BLE_MODULE ?= ble5
ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
    SRC += $(SHURA_BLE_MODULE).c power.c
    ifeq ($(strip $(SHURA_BLE_MODULE)), ble4)
        OPT_DEFS += -DSHURA_BLE4
    endif
endif
