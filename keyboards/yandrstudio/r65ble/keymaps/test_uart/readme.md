# BLE_UART SUPPORT FOR ARM

## send source support

## uart support
1. add biu_ble5 support in your $(keymap)/relus.mk
```shell
BIU_BLE5_ENABLE = yes
```

2. add uart.c to src (in file qmk_firmware/tmk_core/protocol/chibios.mk)
```shell
# into end of the chibios.mk
ifeq ($(strip $(BIU_BLE5_ENABLE)), yes)
	SRC += uart.c
	VPATH += $(DRIVER_PATH)/chibios
	OPT_DEFS += -DBIU_BLE5_ENABLE
endif
```
3. add uart support in the main function (in file qmk_firmware/tmk_core/protocol/chibios/main.c)
```c++
// head of the main.c file
#ifdef BIU_BLE5_ENABLE
    #include "uart.h"
#endif

// behind host_set_driver(driver), around line 218
#ifdef BIU_BLE5_ENABLE
    uart_init(9600);
#endif
```
