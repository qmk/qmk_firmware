# 'serial' Driver
This driver powers the [Split Keyboard](feature_split_keyboard.md) feature.

!> Serial in this context should be read as **sending information one bit at a time**, rather than implementing UART/USART/RS485/RS232 standards.

All drivers in this category have the following characteristics:
* Provides data and signaling over a single conductor
* Limited to single master, single slave

## Supported Driver Types

|                   | AVR                | ARM                |
|-------------------|--------------------|--------------------|
| bit bang          | :heavy_check_mark: | Soon™              |
| USART Half-duplex |                    | :heavy_check_mark: |

## Driver configuration

### Bitbang
Default driver, the absence of configuration assumes this driver. To configure it, add this to your rules.mk:

```make
SERIAL_DRIVER = bitbang
```

Configure the driver via your config.h:
```c
#define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: about 189kbps (Experimental only)
                                   //  1: about 137kbps (default)
                                   //  2: about 75kbps
                                   //  3: about 39kbps
                                   //  4: about 26kbps
                                   //  5: about 20kbps
```

### USART Half-duplex
Targeting STM32 boards where communication is offloaded to a USART hardware device. The advantage is that this provides fast and accurate timings. `SOFT_SERIAL_PIN` for this driver is the configured USART TX pin. **The TX pin must have appropriate pull-up resistors**. To configure it, add this to your rules.mk:

```make
SERIAL_DRIVER = usart
```

Configure the hardware via your config.h:
```c
#define SOFT_SERIAL_PIN B6  // USART TX pin
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: about 230kbps (Experimental only)
                                   //  1: about 115kbps (default)
                                   //  2: about 57kbps
                                   //  3: about 38kbps
                                   //  4: about 19kbps
                                   //  5: about 14kbps
#define SERIAL_USART_DRIVER SD1 // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
```

You must also turn on the SERIAL feature in your halconf.h and mcuconf.h
