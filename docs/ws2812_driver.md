# WS2812 Driver
This driver powers the [RGB Lighting](feature_rgblight.md) and [RGB Matrix](feature_rgb_matrix.md) features.

Currently QMK supports the following addressable LEDs (however, the white LED in RGBW variants is not supported):

    WS2811, WS2812, WS2812B, WS2812C, etc.
    SK6812, SK6812MINI, SK6805

These LEDs are called "addressable" because instead of using a wire per color, each LED contains a small microchip that understands a special protocol sent over a single wire. The chip passes on the remaining data to the next LED, allowing them to be chained together. In this way, you can easily control the color of the individual LEDs.

## Supported Driver Types

|          | AVR                | ARM                |
|----------|--------------------|--------------------|
| bit bang | :heavy_check_mark: | :heavy_check_mark: |
| I2C      | :heavy_check_mark: |                    |
| SPI      |                    | :heavy_check_mark: |
| PWM      |                    | Soon™              |

## Driver configuration

### Bitbang
Default driver, the absence of configuration assumes this driver. To configure it, add this to your rules.mk:

```make
WS2812_DRIVER = bitbang
```

!> This driver is not hardware accelerated and may not be performant on heavily loaded systems.

### I2C
Targeting boards where WS2812 support is offloaded to a 2nd MCU. Currently the driver is limited to AVR given the known consumers are ps2avrGB/BMC. To configure it, add this to your rules.mk:

```make
WS2812_DRIVER = i2c
```

Configure the hardware via your config.h:
```c
#define WS2812_ADDRESS 0xb0 // default: 0xb0
#define WS2812_TIMEOUT 100 // default: 100
```

### SPI
Targeting STM32 boards where WS2812 support is offloaded to an SPI hardware device. The advantage is that the use of DMA offloads processing of the WS2812 protocol from the MCU. `RGB_DI_PIN` for this driver is the configured SPI MOSI pin. Due to the nature of repurposing SPI to drive the LEDs, the other SPI pins, MISO and SCK, **must** remain unused. To configure it, add this to your rules.mk:

```make
WS2812_DRIVER = spi
```

Configure the hardware via your config.h:
```c
#define WS2812_SPI SPID1 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5
```

You must also turn on the SPI feature in your halconf.h and mcuconf.h

#### Testing Notes

While not an exhaustive list, the following table provides the scenarios that have been partially validated:

| | SPI1 | SPI2 | SPI3 |
|-|-|-|-|
| f072 | ? | B15 :heavy_check_mark: | N/A |
| f103 | A7 :heavy_check_mark: | B15 :heavy_check_mark: | N/A |
| f303 | A7 :heavy_check_mark: B5 :heavy_check_mark:  | B15 :heavy_check_mark: | B5 :heavy_check_mark: |

*Other supported ChibiOS boards and/or pins may function, it will be highly chip and configuration dependent.*