# 'serial' Driver
This driver powers the [Split Keyboard](feature_split_keyboard.md) feature.

?> Serial in this context should be read as **sending information one bit at a time**, rather than implementing UART/USART/RS485/RS232 standards.

Drivers in this category have the following characteristics:
* bit bang and USART Half-duplex provide data and signaling over a single conductor
* USART Full-duplex provide data and signaling over two conductors
* They are all limited to single master and single slave communication scheme

## Supported Driver Types

|                   | AVR                | ARM                |
| ----------------- | ------------------ | ------------------ |
| bit bang          | :heavy_check_mark: | :heavy_check_mark: |
| USART Half-duplex |                    | :heavy_check_mark: |
| USART Full-duplex |                    | :heavy_check_mark: |

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
Targeting STM32 boards where communication is offloaded to a USART hardware device. The advantage over bitbang is that this provides fast and accurate timings. `SERIAL_PIN_TX` for this driver is the configured USART TX pin. As this Pin is configured in open-drain mode an **external pull-up resistor is needed to keep the line high** (resistor values of 1.5k to 8.2k are known to work). To configure it, add this to your rules.mk:

```make
SERIAL_DRIVER = usart
```

Configure the hardware via your config.h:
```c
#define SOFT_SERIAL_PIN B6         // USART TX pin
//#define USART1_REMAP             // Remap USART TX and RX pins on STM32F103 MCUs, see table below.
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: about 460800 baud
                                   //  1: about 230400 baud (default)
                                   //  2: about 115200 baud
                                   //  3: about 57600 baud
                                   //  4: about 38400 baud
                                   //  5: about 19200 baud
#define SERIAL_USART_DRIVER SD1    // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 100 // USART driver timeout. default 100
```

You must also enable the ChibiOS `SERIAL` feature:
* In your board's halconf.h: `#define HAL_USE_SERIAL TRUE`
* In your board's mcuconf.h: `#define STM32_SERIAL_USE_USARTn TRUE` (where 'n' matches the peripheral number of your selected USART on the MCU)

Do note that the configuration required is for the `SERIAL` peripheral, not the `UART` peripheral.

### USART Full-duplex
Targeting STM32 boards where communication is offloaded to a USART hardware device. The advantage over bitbang is that this provides fast and accurate timings. USART Full-Duplex requires two conductors **without** pull-up resistors instead of one conductor with a pull-up resistor unlike the Half-duplex driver, but it is more efficent as it uses DMA transfers, which can result in even faster transmission speeds.

#### Pin configuration

`SERIAL_USART_TX_PIN` is the USART `TX` pin, `SERIAL_USART_RX_PIN` is the USART `RX` pin. No external pull-up resistors are needed as the `TX` pin operates in push-pull mode. To use this driver the usart peripherals `TX` and `RX` pins must be configured with the correct Alternate-functions. If you are using a Proton-C everything is already setup, same is true for STM32F103 MCUs. For MCUs which are using a modern flexible GPIO configuration you have to specify these by setting `SERIAL_USART_TX_PAL_MODE` and `SERIAL_USART_RX_PAL_MODE`. Refeer to the corresponding datasheets of your MCU or find those settings in the table below.

#### Connecting the halves and Pin Swap
Please note that `TX` of the master half has to be connected with the `RX` pin of the slave half and `RX` of the master half has to be connected with the `TX` pin of the slave half! Usually this pin swap has to be done outside of the MCU e.g. with cables or on the pcb. Some MCUs like the STM32F303 used on the Proton-C allow this pin swap directly inside the MCU, this feature can be enabled using `#define SERIAL_USART_PIN_SWAP` in your config.h.

#### Setup
To use the driver, add this to your rules.mk:

```make
SERIAL_DRIVER = usart_duplex
```

Next configure the hardware via your config.h:

```c
#define SERIAL_USART_TX_PIN B6     // USART TX pin
#define SERIAL_USART_RX_PIN B7     // USART RX pin
//#define USART1_REMAP             // Remap USART TX and RX pins on STM32F103 MCUs, see table below.
//#define SERIAL_USART_PIN_SWAP    // Swap TX and RX pins if keyboard is master halve.
                                   // Check if this feature is necessary with your keyboard design and available on the mcu.
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: 460800 baud
                                   //  1: 230400 baud (default)
                                   //  2: 115200 baud
                                   //  3: 57600 baud
                                   //  4: 38400 baud
                                   //  5: 19200 baud
#define SERIAL_USART_DRIVER UARTD1 // USART driver of TX and RX pin. default: UARTD1
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 100 // USART driver timeout. default 100
```

You must also enable the ChibiOS `UART` with blocking api feature:
* In your board's halconf.h: `#define HAL_USE_UART TRUE` and `#define UART_USE_WAIT TRUE`
* In your board's mcuconf.h: `#define STM32_UART_USE_USARTn TRUE` (where 'n' matches the peripheral number of your selected USART on the MCU)

Do note that the configuration required is for the `UART` peripheral, not the `SERIAL` peripheral.

#### Pins for USART Peripherals with Alternate Functions for selected STM32 MCUs

##### STM32F303 / Proton-C [Datasheet](https://www.st.com/resource/en/datasheet/stm32f303cc.pdf)

Pin Swap available: :heavy_check_mark:

|    Pin     | Function | Mode |
| ---------- | -------- | ---- |
| **USART1** |          |      |
| PA9        | TX       | AF7  |
| PA10       | RX       | AF7  |
| PB6        | TX       | AF7  |
| PB7        | RX       | AF7  |
| PC4        | TX       | AF7  |
| PC5        | RX       | AF7  |
| PE0        | TX       | AF7  |
| PE1        | RX       | AF7  |
| **USART2** |          |      |
| PA2        | TX       | AF7  |
| PA3        | RX       | AF7  |
| PA14       | TX       | AF7  |
| PA15       | RX       | AF7  |
| PB3        | TX       | AF7  |
| PB4        | RX       | AF7  |
| PD5        | TX       | AF7  |
| PD6        | RX       | AF7  |
| **USART3** |          |      |
| PB10       | TX       | AF7  |
| PB11       | RX       | AF7  |
| PC10       | TX       | AF7  |
| PC11       | RX       | AF7  |
| PD8        | TX       | AF7  |
| PD9        | RX       | AF7  |

##### STM32F072 [Datasheet](https://www.st.com/resource/en/datasheet/stm32f072c8.pdf)

Pin Swap available: :heavy_check_mark:

|  Pin   | Function | Mode |
| ------ | -------- | ---- |
| USART1 |          |      |
| PA9    | TX       | AF1  |
| PA10   | RX       | AF1  |
| PB6    | TX       | AF0  |
| PB7    | RX       | AF0  |
| USART2 |          |      |
| PA2    | TX       | AF1  |
| PA3    | RX       | AF1  |
| PA14   | TX       | AF1  |
| PA15   | RX       | AF1  |
| USART3 |          |      |
| PB10   | TX       | AF4  |
| PB11   | RX       | AF4  |
| PC4    | TX       | AF1  |
| PC5    | RX       | AF1  |
| PC10   | TX       | AF1  |
| PC11   | RX       | AF1  |
| PD8    | TX       | AF0  |
| PD9    | RX       | AF0  |
| USART4 |          |      |
| PA0    | TX       | AF4  |
| PA1    | RX       | AF4  |

##### STM32F103 Medium Density (C8-CB) [Datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)

Pin Swap available: N/A

TX Pin is always Alternate Function Push-Pull, RX Pin is always regular input pin for any USART peripheral. **For STM32F103 no additional Alternate Function configuration is necessary. QMK is already configured.**

Pin remapping:

The pins of USART Peripherals use default Pins that can be remapped to use other pins using the AFIO registers. Default pins are marked **bold**. Add the appropriate defines to your config.h file.

|    Pin     | Function | Mode |     USART_REMAP     |
| ---------- | -------- | ---- | ------------------- |
| **USART1** |          |      |                     |
| **PA9**    | TX       | AFPP |                     |
| **PA10**   | RX       | IN   |                     |
| PB6        | TX       | AFPP | USART1_REMAP        |
| PB7        | RX       | IN   | USART1_REMAP        |
| **USART2** |          |      |                     |
| **PA2**    | TX       | AFPP |                     |
| **PA3**    | RX       | IN   |                     |
| PD5        | TX       | AFPP | USART2_REMAP        |
| PD6        | RX       | IN   | USART2_REMAP        |
| **USART3** |          |      |                     |
| **PB10**   | TX       | AFPP |                     |
| **PB11**   | RX       | IN   |                     |
| PC10       | TX       | AFPP | USART3_PARTIALREMAP |
| PC11       | RX       | IN   | USART3_PARTIALREMAP |
| PD8        | TX       | AFPP | USART3_FULLREMAP    |
| PD9        | RX       | IN   | USART3_FULLREMAP    |
