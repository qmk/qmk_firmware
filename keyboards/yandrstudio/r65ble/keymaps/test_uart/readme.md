# BLE_UART SUPPORT FOR ARM


## method 1


### send source support
1. move host_driver declarations from "qmk_firmware/tmk_core/protocol/chibios/main.c" to "qmk_firmware/tmk_core/protocol/chibios/usb_main.h"
```c++
#include "host_driver.h"
/* declarations */
uint8_t keyboard_leds(void);
void    send_keyboard(report_keyboard_t *report);
void    send_mouse(report_mouse_t *report);
void    send_system(uint16_t data);
void    send_consumer(uint16_t data);
```
### set no usb check

```shell
NO_USB_STARTUP_CHECK = yes
```

### uart support

1. add biu_ble5 support in your $(keymap)/relus.mk
```shell
BIU_BLE5_ENABLE = yes
```

2. add uart.c to src (in file "qmk_firmware/tmk_core/protocol/chibios.mk")
```shell
# into end of the chibios.mk
ifeq ($(strip $(BIU_BLE5_ENABLE)), yes)
	SRC += uart.c
	# VPATH += $(DRIVER_PATH)/chibios #optional. For stability, it is recommended to add this line.
	OPT_DEFS += -DBIU_BLE5_ENABLE
endif
```
3. add uart support in the main function (in file "qmk_firmware/tmk_core/protocol/chibios/main.c")
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

4. copy outputselect.h and outputselect.c into "qmk_firmware/tmk_core/protocol/chibios/"


## method 2


## some important file 
1. chibios usb state: "qmk_firmware/lib/chibios/os/hal/include/hal_usb.h"
