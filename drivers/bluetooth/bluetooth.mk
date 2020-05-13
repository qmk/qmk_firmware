ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
	COMMON_VPATH += $(DRIVER_PATH)/bluetooth
    OPT_DEFS += -DBLUETOOTH_ENABLE
	OPT_DEFS += -DNO_USB_STARTUP_CHECK
	SRC += bluetooth.c
	SRC += bluetooth_classic.c
	SRC += $(TMK_PATH)/protocol/serial_uart.c
endif

ifeq ($(strip $(BLUETOOTH)), AdafruitEZKey)
	COMMON_VPATH += $(DRIVER_PATH)/bluetooth
	OPT_DEFS += -DBLUETOOTH_ENABLE
	OPT_DEFS += -DMODULE_ADAFRUIT_EZKEY
    OPT_DEFS += -DNO_USB_STARTUP_CHECK
	SRC += bluetooth.c
	SRC += bluetooth_classic.c
	SRC += $(TMK_PATH)/protocol/serial_uart.c
endif

ifeq ($(strip $(BLUETOOTH)), RN42)
	COMMON_VPATH += $(DRIVER_PATH)/bluetooth
	OPT_DEFS += -DBLUETOOTH_ENABLE
	OPT_DEFS += -DMODULE_RN42
	OPT_DEFS += -DNO_USB_STARTUP_CHECK
	SRC += bluetooth.c
	SRC += bluetooth_classic.c
	SRC += $(TMK_PATH)/protocol/serial_uart.c
endif

ifeq ($(strip $(BLUETOOTH)), AdafruitBLE)
	COMMON_VPATH += $(DRIVER_PATH)/bluetooth
	COMMON_VPATH += $(DRIVER_PATH)/bluetooth/adafruit_ble
	OPT_DEFS += -DBLUETOOTH_ENABLE
	OPT_DEFS += -DMODULE_ADAFRUIT_BLE
	OPT_DEFS += -DMODULE_ADAFRUIT_BLE_SPI
	OPT_DEFS += -DNO_USB_STARTUP_CHECK
	SRC += bluetooth.c
	SRC += spi_master.c
	SRC += new.cpp
	SRC += FIFO.cpp
	SRC += Print.cpp
	SRC += Stream.cpp
	SRC += ATParser.cpp
	SRC += BLE.cpp
	SRC += BluefruitLE_SPI.cpp
	SRC += adafruit_ble.cpp
endif

ifeq ($(strip $(BLUETOOTH)), AdafruitBLEUART)
	COMMON_VPATH += $(DRIVER_PATH)/bluetooth
	COMMON_VPATH += $(DRIVER_PATH)/bluetooth/adafruit_ble
	OPT_DEFS += -DBLUETOOTH_ENABLE
	OPT_DEFS += -DMODULE_ADAFRUIT_BLE
	OPT_DEFS += -DMODULE_ADAFRUIT_BLE_UART
	OPT_DEFS += -DNO_USB_STARTUP_CHECK
	SRC += bluetooth.c
	SRC += uart.c
	SRC += new.cpp
	SRC += Print.cpp
	SRC += Stream.cpp
	SRC += ATParser.cpp
	SRC += BLE.cpp
	SRC += BluefruitLE_UART.cpp
	SRC += adafruit_ble.cpp
endif

ifeq ($(strip $(BLUETOOTH_BATTERY_ENABLE)), yes)
	COMMON_VPATH += $(DRIVER_PATH)/bluetooth
	COMMON_VPATH += $(DRIVER_PATH)/bluetooth/adafruit_ble
	OPT_DEFS += -DBLUETOOTH_BATTERY_ENABLE
	SRC += analog.c
	SRC += bluetooth.c
	SRC += adafruit_ble/BLEBattery.cpp
endif
