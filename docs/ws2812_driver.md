# WS2812 Driver
This driver powers the [RGB Lighting](feature_rgblight.md) and [RGB Matrix](feature_rgb_matrix.md) features.

Currently QMK supports the following addressable LEDs (however, the white LED in RGBW variants is not supported):

    WS2811, WS2812, WS2812B, WS2812C, etc.
    SK6812, SK6812MINI, SK6805

These LEDs are called "addressable" because instead of using a wire per color, each LED contains a small microchip that understands a special protocol sent over a single wire. The chip passes on the remaining data to the next LED, allowing them to be chained together. In this way, you can easily control the color of the individual LEDs.

## Supported Driver Types

|          | AVR                | ARM                |
| -------- | ------------------ | ------------------ |
| bit bang | :heavy_check_mark: | :heavy_check_mark: |
| I2C      | :heavy_check_mark: |                    |
| SPI      |                    | :heavy_check_mark: |
| PWM      |                    | :heavy_check_mark: |
| PIO      |                    | :heavy_check_mark: |

## Driver configuration

### All drivers

Different versions of the addressable LEDs have differing requirements for the T<sub>RST</sub> period between frames.
The default setting is 280 µs, which should work for most cases, but this can be overridden in your config.h. e.g.:

```c
#define WS2812_TRST_US 80
```

#### Byte Order

Some variants of the WS2812 may have their color components in a different physical or logical order. For example, the WS2812B-2020 has physically swapped red and green LEDs, which causes the wrong color to be displayed, because the default order of the bytes sent over the wire is defined as GRB.
In this case, you can change the byte order by defining `WS2812_BYTE_ORDER` as one of the following values:

| Byte order                        | Known devices                 |
| --------------------------------- | ----------------------------- |
| `WS2812_BYTE_ORDER_GRB` (default) | Most WS2812's, SK6812, SK6805 |
| `WS2812_BYTE_ORDER_RGB`           | WS2812B-2020                  |
| `WS2812_BYTE_ORDER_BGR`           | TM1812                        |


### Bitbang
Default driver, the absence of configuration assumes this driver. To configure it, add this to your rules.mk:

```make
WS2812_DRIVER = bitbang
```

!> This driver is not hardware accelerated and may not be performant on heavily loaded systems.

#### Adjusting bit timings

The WS2812 LED communication topology depends on a serialized timed window. Different versions of the addressable LEDs have differing requirements for the timing parameters, for instance, of the SK6812.
You can tune these parameters through the definition of the following macros:

| Macro           | Default                      | AVR                | ARM                |
| --------------- | ---------------------------- | ------------------ | ------------------ |
| `WS2812_TIMING` | `1250`                       | :heavy_check_mark: | :heavy_check_mark: |
| `WS2812_T0H`    | `350`                        | :heavy_check_mark: | :heavy_check_mark: |
| `WS2812_T0L`    | `WS2812_TIMING - WS2812_T0H` |                    | :heavy_check_mark: |
| `WS2812_T1H`    | `900`                        | :heavy_check_mark: | :heavy_check_mark: |
| `WS2812_T1L`    | `WS2812_TIMING - WS2812_T1H` |                    | :heavy_check_mark: |

### I2C
Targeting boards where WS2812 support is offloaded to a 2nd MCU. Currently the driver is limited to AVR given the known consumers are ps2avrGB/BMC. To configure it, add this to your rules.mk:

```make
WS2812_DRIVER = i2c
```

Configure the hardware via your config.h:
```c
#define WS2812_I2C_ADDRESS 0xB0 // default: 0xB0
#define WS2812_I2C_TIMEOUT 100 // default: 100
```

### SPI
Targeting STM32 boards where WS2812 support is offloaded to an SPI hardware device. The advantage is that the use of DMA offloads processing of the WS2812 protocol from the MCU. `WS2812_DI_PIN` for this driver is the configured SPI MOSI pin. Due to the nature of repurposing SPI to drive the LEDs, the other SPI pins, MISO and SCK, **must** remain unused. To configure it, add this to your rules.mk:

```make
WS2812_DRIVER = spi
```

Configure the hardware via your config.h:
```c
#define WS2812_SPI_DRIVER SPID1 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5 // MOSI pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5
#define WS2812_SPI_SCK_PIN B3 // Required for F072, may be for others -- SCK pin, see the respective datasheet for the appropriate values for your MCU. default: unspecified
#define WS2812_SPI_SCK_PAL_MODE 5 // SCK pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5
```

You must also turn on the SPI feature in your halconf.h and mcuconf.h

#### Circular Buffer Mode
Some boards may flicker while in the normal buffer mode. To fix this issue, circular buffer mode may be used to rectify the issue. 

By default, the circular buffer mode is disabled.

To enable this alternative buffer mode, place this into your `config.h` file:
```c
#define WS2812_SPI_USE_CIRCULAR_BUFFER
```

#### Setting baudrate with divisor
To adjust the baudrate at which the SPI peripheral is configured, users will need to derive the target baudrate from the clock tree provided by STM32CubeMX.

Only divisors of 2, 4, 8, 16, 32, 64, 128 and 256 are supported by hardware.

| Define               | Default | Description                         |
| -------------------- | ------- | ----------------------------------- |
| `WS2812_SPI_DIVISOR` | `16`    | SPI source clock peripheral divisor |

#### Testing Notes

While not an exhaustive list, the following table provides the scenarios that have been partially validated:

|      | SPI1                                        | SPI2                                    | SPI3                  |
| ---- | ------------------------------------------- | --------------------------------------- | --------------------- |
| f072 | ?                                           | B15 :heavy_check_mark: (needs SCK: B13) | N/A                   |
| f103 | A7 :heavy_check_mark:                       | B15 :heavy_check_mark:                  | N/A                   |
| f303 | A7 :heavy_check_mark: B5 :heavy_check_mark: | B15 :heavy_check_mark:                  | B5 :heavy_check_mark: |

*Other supported ChibiOS boards and/or pins may function, it will be highly chip and configuration dependent.*

### PWM

Targeting STM32 boards where WS2812 support is offloaded to an PWM timer and DMA stream. The advantage is that the use of DMA offloads processing of the WS2812 protocol from the MCU. To configure it, add this to your rules.mk:

```make
WS2812_DRIVER = pwm
```

Configure the hardware via your config.h:
```c
#define WS2812_PWM_DRIVER PWMD2  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
//#define WS2812_PWM_COMPLEMENTARY_OUTPUT // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 2  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM2_UP // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.
```

Note that using a complementary timer output (TIMx_CHyN) is possible only for advanced-control timers (TIM1, TIM8, TIM20 on STM32), and the `STM32_PWM_USE_ADVANCED` option in mcuconf.h must be set to `TRUE`.  Complementary outputs of general-purpose timers are not supported due to ChibiOS limitations.

You must also turn on the PWM feature in your halconf.h and mcuconf.h

#### Testing Notes

While not an exhaustive list, the following table provides the scenarios that have been partially validated:

|           | Status             |
| --------- | ------------------ |
| f072      | ?                  |
| f103      | :heavy_check_mark: |
| f303      | :heavy_check_mark: |
| f401/f411 | :heavy_check_mark: |

*Other supported ChibiOS boards and/or pins may function, it will be highly chip and configuration dependent.*

### PIO

Targeting Raspberry Pi RP2040 boards only where WS2812 support is offloaded to an dedicated PIO implementation. This offloads processing of the WS2812 protocol from the MCU to a dedicated PIO program using DMA transfers.

To configure it, add this to your rules.mk:

```make
WS2812_DRIVER = vendor
```

Configure the hardware via your config.h:
```c
#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral
```

The WS2812 PIO programm uses 1 state machine, 6 instructions and one DMA interrupt handler callback. Due to the implementation the time resolution for this drivers is 50ns, any value not specified in this interval will be rounded to the next matching interval.

### Push Pull and Open Drain Configuration
The default configuration is a push pull on the defined pin.
This can be configured for bitbang, PWM and SPI.

Note: This only applies to STM32 boards.

 To configure the `WS2812_DI_PIN` to open drain configuration add this to your config.h file: 
```c
#define WS2812_EXTERNAL_PULLUP
```
