# 'serial' Driver

The Serial driver powers the [Split Keyboard](../features/split_keyboard) feature. Several implementations are available that cater to the platform and capabilities of MCU in use. Note that none of the drivers support split keyboards with more than two halves.

| Driver                                  | AVR                | ARM                | Connection between halves                                                                     |
| --------------------------------------- | ------------------ | ------------------ | --------------------------------------------------------------------------------------------- |
| [Bitbang](#bitbang)                     | :heavy_check_mark: | :heavy_check_mark: | Single wire communication. One wire is used for reception and transmission.                   |
| [USART Half-duplex](#usart-half-duplex) |                    | :heavy_check_mark: | Efficient single wire communication. One wire is used for reception and transmission.         |
| [USART Full-duplex](#usart-full-duplex) |                    | :heavy_check_mark: | Efficient two wire communication. Two distinct wires are used for reception and transmission. |

::: tip
Serial in this context should be read as **sending information one bit at a time**, rather than implementing UART/USART/RS485/RS232 standards.
:::

## Bitbang

This is the Default driver, absence of configuration assumes this driver. It works by [bit banging](https://en.wikipedia.org/wiki/Bit_banging) a GPIO pin using the CPU. It is therefore not as efficient as a dedicated hardware peripheral, which the Half-duplex and Full-duplex drivers use.

::: warning
On ARM platforms the bitbang driver causes connection issues when using it together with the bitbang WS2812 driver. Choosing alternate drivers for both serial and WS2812 (instead of bitbang) is strongly recommended.
:::

### Pin configuration

```
  LEFT                      RIGHT
+-------+      SERIAL     +-------+
|   SSP |-----------------| SSP   |
|       |       VDD       |       |
|       |-----------------|       |
|       |       GND       |       |
|       |-----------------|       |
+-------+                 +-------+
```

One GPIO pin is needed for the bitbang driver, as only one wire is used for receiving and transmitting data. This pin is referred to as the `SOFT_SERIAL_PIN` (SSP) in the configuration. A TRS or USB cable provides enough conductors for this driver to function.

### Setup

To use the bitbang driver follow these steps to activate it.

1. Change the `SERIAL_DRIVER` to `bitbang` in your keyboards `rules.mk` file:

```make
SERIAL_DRIVER = bitbang
```

2. Configure the GPIO pin of your keyboard via the `config.h` file:

```c
#define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6
```

3. On ARM platforms you must turn on ChibiOS PAL callbacks:

```c
#pragma once

#define PAL_USE_CALLBACKS TRUE // [!code focus]

#include_next <halconf.h>
```

## USART Half-duplex

Targeting ARM boards based on ChibiOS, where communication is offloaded to a USART hardware device that supports Half-duplex operation. The advantages over bitbanging are fast, accurate timings and reduced CPU usage. Therefore it is advised to choose Half-duplex over Bitbang if MCU is capable of utilising Half-duplex, and Full-duplex can't be used instead (e.g. lack of available GPIO pins, or incompatible PCB design).

### Pin configuration

```
  LEFT                      RIGHT
+-------+  |           |  +-------+
|       |  R           R  |       |
|       |  |   SERIAL  |  |       |
|    TX |-----------------| TX    |
|       |       VDD       |       |
|       |-----------------|       |
|       |       GND       |       |
|       |-----------------|       |
+-------+                 +-------+
```

Only one GPIO pin is needed for the Half-duplex driver, as only one wire is used for receiving and transmitting data. This pin is referred to as the `SERIAL_USART_TX_PIN` in the configuration. Ensure that the pin chosen for split communication can operate as the TX pin of the contoller's USART peripheral. A TRS or USB cable provides enough conductors for this driver to function. As the split connection is configured to operate in open-drain mode, an **external pull-up resistor is needed to keep the line high**. Resistor values of 1.5kΩ to 8.2kΩ are known to work.

::: warning
***Note:*** A pull-up resistor isn't required for RP2040 controllers configured with PIO subsystem.
:::

### Setup

To use the Half-duplex driver follow these steps to activate it. If you target the Raspberry Pi RP2040 PIO implementation, start at step 2.

1. Change the `SERIAL_DRIVER` to `usart` in your keyboards `rules.mk` file:

```make
SERIAL_DRIVER = usart
```

Skip to step 3.

2. (RP2040 + PIO only!) Change the `SERIAL_DRIVER` to `vendor` in your keyboards `rules.mk` file:

```make
SERIAL_DRIVER = vendor
```

3. Configure the hardware of your keyboard via the `config.h` file:

```c
#define SERIAL_USART_TX_PIN B6     // The GPIO pin that is used split communication.
```

For STM32 MCUs several GPIO configuration options can be changed as well. See the section ["Alternate Functions for selected STM32 MCUs"](#alternate-functions-for-selected-stm32-mcus).

```c
#define USART1_REMAP               // Remap USART TX and RX pins on STM32F103 MCUs, see table below.
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
```

4. Decide either for `SERIAL`, `SIO`, or `PIO` subsystem. See section ["Choosing a driver subsystem"](#choosing-a-driver-subsystem).

## USART Full-duplex

Targeting ARM boards based on ChibiOS where communication is offloaded to an USART hardware device. The advantages over bitbanging are fast, accurate timings and reduced CPU usage; therefore it is advised to choose this driver over all others where possible. Due to its internal design Full-duplex is slightly more efficient than the Half-duplex driver, but Full-duplex should be primarily chosen if Half-duplex operation is not supported by the controller's USART peripheral.

### Pin configuration

```
  LEFT                      RIGHT
+-------+                 +-------+
|       |      SERIAL     |       |
|    TX |-----------------| RX    |
|       |      SERIAL     |       |
|    RX |-----------------| TX    |
|       |       VDD       |       |
|       |-----------------|       |
|       |       GND       |       |
|       |-----------------|       |
+-------+                 +-------+
```

Two GPIO pins are needed for the Full-duplex driver, as two distinct wires are used for receiving and transmitting data. The pin transmitting data is the `TX` pin and refereed to as the `SERIAL_USART_TX_PIN`, the pin receiving data is the `RX` pin and refereed to as the `SERIAL_USART_RX_PIN` in this configuration. Please note that `TX` pin of the master half has to be connected with the `RX` pin of the slave half and the `RX` pin of the master half has to be connected with the `TX` pin of the slave half! Usually this pin swap has to be done outside of the MCU e.g. with cables or on the PCB. Some MCUs like the STM32F303 used on the Proton-C allow this pin swap directly inside the MCU. A TRRS or USB cable provides enough conductors for this driver to function.

To use this driver the USART peripherals `TX` and `RX` pins must be configured with the correct Alternate-functions. If you are using a Proton-C development board everything is already setup, same is true for STM32F103 MCUs. For MCUs which are using a modern flexible GPIO configuration you have to specify these by setting `SERIAL_USART_TX_PAL_MODE` and `SERIAL_USART_RX_PAL_MODE`. Refer to the corresponding datasheets of your MCU or find those settings in the section ["Alternate Functions for selected STM32 MCUs"](#alternate-functions-for-selected-stm32-mcus).

### Setup

To use the Full-duplex driver follow these steps to activate it. If you target the Raspberry Pi RP2040 PIO implementation, start at step 2

1. Change the `SERIAL_DRIVER` to `usart` in your keyboards `rules.mk` file:

```make
SERIAL_DRIVER = usart
```

Skip to step 3

2. (RP2040 + PIO only!) Change the `SERIAL_DRIVER` to `vendor` in your keyboards `rules.mk` file:

```make
SERIAL_DRIVER = vendor
```

3. Configure the hardware of your keyboard via the `config.h` file:

```c
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN B6     // USART TX pin
#define SERIAL_USART_RX_PIN B7     // USART RX pin
```

For STM32 MCUs several GPIO configuration options, including the ability for `TX` to `RX` pin swapping, can be changed as well. See the section ["Alternate Functions for selected STM32 MCUs"](#alternate-functions-for-selected-stm32-mcus).

```c
#define SERIAL_USART_PIN_SWAP      // Swap TX and RX pins if keyboard is master halve. (Only available on some MCUs)
#define USART1_REMAP               // Remap USART TX and RX pins on STM32F103 MCUs, see table below.
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
```

4. Decide either for `SERIAL`, `SIO`, or `PIO` subsystem. See section ["Choosing a driver subsystem"](#choosing-a-driver-subsystem).

## Choosing a driver subsystem

### The `SERIAL` driver

The `SERIAL` Subsystem is supported for the majority of ChibiOS MCUs and should be used whenever supported. Follow these steps in order to activate it:

1. Enable the SERIAL subsystem in the ChibiOS HAL.

   Add the following to your keyboard's `halconf.h`, creating it if necessary:

   ```c
   #pragma once

   #define HAL_USE_SERIAL TRUE // [!code focus]

   #include_next <halconf.h>
   ```

2. Activate the USART peripheral that is used on your MCU. The shown example is for an STM32 MCU, so this will not work on MCUs by other manufacturers. You can find the correct names in the `mcuconf.h` files of your MCU that ship with ChibiOS.

   Add the following to your keyboard's `mcuconf.h`, creating it if necessary:

   ```c
   #pragma once

   #include_next <mcuconf.h>

   #undef STM32_SERIAL_USE_USARTn // [!code focus]
   #define STM32_SERIAL_USE_USARTn TRUE // [!code focus]
   ```

   Where *n* matches the peripheral number of your selected USART on the MCU.

3. Override the default USART `SERIAL` driver if you use a USART peripheral that does not belong to the default selected `SD1` driver. For instance, if you selected `STM32_SERIAL_USE_USART3` the matching driver would be `SD3`.

   Add the following to your keyboard's `config.h`:

   ```c
   #define SERIAL_USART_DRIVER SD3
   ```

### The `SIO` driver

The `SIO` Subsystem was added to ChibiOS with the 21.11 release and is only supported on selected MCUs. It should only be chosen when the `SERIAL` subsystem is not supported by your MCU.

Follow these steps in order to activate it:

1. Enable the SIO subsystem in the ChibiOS HAL.

   Add the following to your keyboard's `halconf.h`, creating it if necessary:

   ```c
   #pragma once

   #define HAL_USE_SIO TRUE // [!code focus]

   #include_next <halconf.h>
   ```

2. Activate the USART peripheral that is used on your MCU. The shown example is for an STM32 MCU, so this will not work on MCUs by other manufacturers. You can find the correct names in the `mcuconf.h` files of your MCU that ship with ChibiOS.

   Add the following to your keyboard's `mcuconf.h`, creating it if necessary:

   ```c
   #pragma once

   #include_next <mcuconf.h>

   #undef STM32_SIO_USE_USARTn // [!code focus]
   #define STM32_SIO_USE_USARTn TRUE // [!code focus]
   ```

   Where *n* matches the peripheral number of your selected USART on the MCU.

3. Override the default USART `SIO` driver if you use a USART peripheral that does not belong to the default selected `SIOD1` driver. For instance, if you selected `STM32_SERIAL_USE_USART3` the matching driver would be `SIOD3`.

   Add the following to your keyboard's `config.h`:

   ```c
   #define SERIAL_USART_DRIVER SIOD3
   ```

### The `PIO` driver

The `PIO` subsystem is a Raspberry Pi RP2040 specific implementation, using an integrated PIO peripheral and is therefore only available on this MCU. Because of the flexible nature of PIO peripherals, **any** GPIO pin can be used as a `TX` or `RX` pin. Half-duplex and Full-duplex operation modes are fully supported with this driver. Half-duplex uses the built-in pull-ups and GPIO manipulation of the RP2040 to drive the line high by default, thus an external pull-up resistor **is not required**.

Optionally, the PIO peripheral utilized for split communication can be changed with the following define in config.h:
```c
#define SERIAL_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the Serial implementation uses the PIO0 peripheral
```

The Serial PIO program uses 2 state machines, 13 instructions and the complete interrupt handler of the PIO peripheral it is running on.

## Advanced Configuration

There are several advanced configuration options that can be defined in your keyboards `config.h` file:

### Baudrate

If you're having issues or need a higher baudrate with serial communication, you can change the baudrate which in turn controls the communication speed for serial. You want to lower the baudrate if you experience failed transactions.

```c
#define SELECT_SOFT_SERIAL_SPEED n
```

Where *n* is one of:

| Speed | Bitbang                    | Half-duplex and Full-duplex |
| ----- | -------------------------- | --------------------------- |
| `0`   | 189000 baud (experimental) | 460800 baud                 |
| `1`   | 137000 baud (default)      | 230400 baud (default)       |
| `2`   | 75000 baud                 | 115200 baud                 |
| `3`   | 39000 baud                 | 57600 baud                  |
| `4`   | 26000 baud                 | 38400 baud                  |
| `5`   | 20000 baud                 | 19200 baud                  |

Alternatively you can specify the baudrate directly by defining `SERIAL_USART_SPEED`.

### Timeout

This is the default time window in milliseconds in which a successful communication has to complete. Usually you don't want to change this value. But you can do so anyways by defining an alternate one in your keyboards `config.h` file:

```c
#define SERIAL_USART_TIMEOUT 20    // USART driver timeout. default 20
```

## Troubleshooting

If you're having issues with serial communication, you can enable debug messages that will give you insights which part of the communication failed. The enable these messages add to your keyboards `config.h` file:

```c
#define SERIAL_DEBUG
```

::: tip
The messages will be printed out to the `CONSOLE` output. For additional information, refer to [Debugging/Troubleshooting QMK](../faq_debug).
:::

## Alternate Functions for selected STM32 MCUs

Pins for USART Peripherals with

### STM32F303 / Proton-C [Datasheet](https://www.st.com/resource/en/datasheet/stm32f303cc.pdf)

Pin Swap available: :heavy_check_mark:

| Pin        | Function | Mode |
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

### STM32F072 [Datasheet](https://www.st.com/resource/en/datasheet/stm32f072c8.pdf)

Pin Swap available: :heavy_check_mark:

| Pin    | Function | Mode |
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

### STM32F103 Medium Density (C8-CB) [Datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)

Pin Swap available: N/A

TX Pin is always Alternate Function Push-Pull, RX Pin is always regular input pin for any USART peripheral. **For STM32F103 no additional Alternate Function configuration is necessary. QMK is already configured.**

Pin remapping:

The pins of USART Peripherals use default Pins that can be remapped to use other pins using the AFIO registers. Default pins are marked **bold**. Add the appropriate defines to your config.h file.

| Pin        | Function | Mode | USART_REMAP         |
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
