# 'serial' Driver
This driver powers the [Split Keyboard](feature_split_keyboard.md) feature.

?> Serial in this context should be read as **sending information one bit at a time**, rather than implementing UART/USART/RS485/RS232 standards.

All drivers in this category have the following characteristics:
* Provides data and signaling over a single conductor
* Limited to single master, single slave

## Supported Driver Types

|                   | AVR                | ARM                |
|-------------------|--------------------|--------------------|
| bit bang          | :heavy_check_mark: | :heavy_check_mark: |
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

#### ARM

!> The bitbang driver causes connection issues with bitbang WS2812 driver

Along with the generic options above, you must also turn on the `PAL_USE_CALLBACKS` feature in your halconf.h.

### USART Half-duplex
Targeting STM32 boards where communication is offloaded to a USART hardware device. The advantage is that this provides fast and accurate timings. `SOFT_SERIAL_PIN` for this driver is the configured USART TX pin. **The TX pin must have appropriate pull-up resistors**. To configure it, add this to your rules.mk:

```make
SERIAL_DRIVER = usart
```

Configure the hardware via your config.h:
```c
#define SOFT_SERIAL_PIN B6  // USART TX pin
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: about 460800 baud
                                   //  1: about 230400 baud (default)
                                   //  2: about 115200 baud
                                   //  3: about 57600 baud
                                   //  4: about 38400 baud
                                   //  5: about 19200 baud
#define SERIAL_USART_DRIVER SD1 // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 100 // USART driver timeout. default 100
```

You must also enable the ChibiOS `SERIAL` feature:
* In your board's halconf.h: `#define HAL_USE_SERIAL TRUE`
* In your board's mcuconf.h: `#define STM32_SERIAL_USE_USARTn TRUE` (where 'n' matches the peripheral number of your selected USART on the MCU)

Do note that the configuration required is for the `SERIAL` peripheral, not the `UART` peripheral.
