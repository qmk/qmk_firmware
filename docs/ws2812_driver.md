# WS2812 Driver :id=ws2812-driver

This driver provides support for WorldSemi addressable RGB(W) LEDs, and compatible equivalents:

 * WS2811, WS2812, WS2812B, WS2812C, etc.
 * SK6812, SK6812MINI, SK6805

These LEDs are often called "addressable" because instead of using a wire per color (and per LED), each LED contains a small microchip that understands a special protocol sent over a single wire.
The LEDs can be chained together, and the remaining data is passed on to the next. In this way, you can easily control the color of many LEDs using a single GPIO.

## Usage :id=usage

In most cases, the WS2812 driver code is automatically included if you are using either the [RGBLight](feature_rgblight.md) or [RGB Matrix](feature_rgb_matrix.md) feature with the `ws2812` driver set, and you would use those APIs instead.

However, if you need to use the driver standalone, add the following to your `rules.mk`:

```make
WS2812_DRIVER_REQUIRED = yes
```

You can then call the WS2812 API by including `ws2812.h` in your code.

## Basic Configuration :id=basic-configuration

Add the following to your `config.h`:

|Define             |Default                |Description                                                                                     |
|-------------------|-----------------------|------------------------------------------------------------------------------------------------|
|`WS2812_DI_PIN`    |*Not defined*          |The GPIO pin connected to the DI pin of the first LED in the chain                              |
|`WS2812_LED_COUNT` |*Not defined*          |Number of LEDs in the WS2812 chain - automatically set when RGBLight or RGB Matrix is configured|
|`WS2812_TIMING`    |`1250`                 |The total length of a bit (TH+TL) in nanoseconds                                                |
|`WS2812_T1H`       |`900`                  |The length of a "1" bit's high phase in nanoseconds                                             |
|`WS2812_T0H`       |`350`                  |The length of a "0" bit's high phase in nanoseconds                                             |
|`WS2812_TRST_US`   |`280`                  |The length of the reset phase in microseconds                                                   |
|`WS2812_BYTE_ORDER`|`WS2812_BYTE_ORDER_GRB`|The byte order of the RGB data                                                                  |

### Timing Adjustment :id=timing-adjustment

The WS2812 LED communication protocol works by encoding a "1" bit with a long high pulse (T<sub>1</sub>H), and a "0" bit with a shorter pulse (T<sub>0</sub>H). The total cycle length of a bit is the same.
The "reset" pulse (T<sub>RST</sub>) latches the sent RGB data to all of the LEDs and denotes a completed "frame".

Some WS2812 variants have slightly different timing parameter requirements, which can be accounted for if necessary using the above `#define`s in your `config.h`.

### Byte Order :id=byte-order

Some WS2812 variants may have their color components in a different physical or logical order. For example, the WS2812B-2020 has physically swapped red and green LEDs, which causes the wrong color to be displayed, because the default order of the bytes sent over the wire is defined as GRB.
If you find your LED colors are consistently swapped, you may need to change the byte order by adding the following to your `config.h`:

```c
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB
```

Where the byte order may be one of:

|Byte Order|Known Devices               |
|----------|----------------------------|
|`GRB`     |Most WS2812s, SK6812, SK6805|
|`RGB`     |WS2812B-2020                |
|`BGR`     |TM1812                      |

## Driver Configuration :id=driver-configuration

Driver selection can be configured in `rules.mk` as `WS2812_DRIVER`, or in `info.json` as `ws2812.driver`. Valid values are `bitbang` (default), `i2c`, `spi`, `pwm`, `vendor`, or `custom`. See below for information on individual drivers.

### Bitbang Driver :id=bitbang-driver

This is the default WS2812 driver. It operates by "bit-banging" ie. directly toggling the GPIO.

Please note that on AVR devices, due to the tight timing requirements longer chains and/or heavy CPU loads may cause visible lag. Unfortunately this driver is usually the only option for AVR.

```make
WS2812_DRIVER = bitbang
```

### I2C Driver :id=i2c-driver

A specialized driver mainly used for PS2AVRGB (Bootmapper Client) boards, which possess an ATtiny85 that handles the WS2812 LEDs.

```make
WS2812_DRIVER = i2c
```

The following `#define`s apply only to the `i2c` driver:

|Define              |Default|Description                      |
|--------------------|-------|---------------------------------|
|`WS2812_I2C_ADDRESS`|`0xB0` |The I2C address of the ATtiny85. |
|`WS2812_I2C_TIMEOUT`|`100`  |The I2C timeout, in milliseconds.|

### PIO Driver :id=pio-driver

This driver is RP2040-only, and leverages the onboard PIO (programmable I/O) system and DMA to offload processing from the CPU.

The WS2812 PIO program uses one state machine, six instructions and one DMA interrupt handler callback. Due to the implementation the time resolution for this driver is 50 ns - any value not specified in this interval will be rounded to the next matching interval.

```make
WS2812_DRIVER = vendor
```

### PWM Driver :id=pwm-driver

This driver is ARM-only, and leverages the onboard PWM peripheral and DMA to offload processing from the CPU.

```make
WS2812_DRIVER = pwm
```

### SPI Driver :id=spi-driver

This driver is ARM-only, and leverages the onboard SPI peripheral and DMA to offload processing from the CPU. The DI pin **must** be connected to the MOSI pin on the MCU, and all other SPI pins **must** be left unused. This is also very dependent on your MCU's SPI peripheral clock speed, and may or may not be possible depending on the MCU selected.

```make
WS2812_DRIVER = spi
```

## ChibiOS/ARM Configuration :id=arm-configuration

The following defines apply only to ARM devices:

|Define      |Default                       |Description                                                                      |
|------------|------------------------------|---------------------------------------------------------------------------------|
|`WS2812_T1L`|`(WS2812_TIMING - WS2812_T1H)`|The length of a "1" bit's low phase in nanoseconds (bitbang and PIO drivers only)|
|`WS2812_T0L`|`(WS2812_TIMING - WS2812_T0H)`|The length of a "0" bit's low phase in nanoseconds (bitbang and PIO drivers only)|

### Push-Pull and Open Drain :id=push-pull-open-drain

By default, the GPIO used for data transmission is configured as a *push-pull* output, meaning the pin is effectively always driven either to VCC or to ground.

For situations where the logic level voltage is lower than the power supply voltage, however, this can pose an issue. The solution is to configure the pin for *open drain* mode instead, and use a pullup resistor between the DI pin and VCC. In this mode, the MCU can only pull the GPIO *low*, or leave it floating. The pullup resistor is then responsible for pulling the line high, when the MCU is not driving the GPIO.

To configure the DI pin for open drain configuration, add the following to your `config.h`:

```c
#define WS2812_EXTERNAL_PULLUP
```

### SPI Driver :id=arm-spi-driver

Depending on the ChibiOS board configuration, you may need to enable SPI at the keyboard level. For STM32, this would look like:

`halconf.h`:
```c
#define HAL_USE_SPI TRUE
```
`mcuconf.h`:
```c
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE
```

The following `define`s apply only to the `spi` driver:

|Define                          |Default      |Description                                                                    |
|--------------------------------|-------------|-------------------------------------------------------------------------------|
|`WS2812_SPI_DRIVER`             |`SPID1`      |The SPI driver to use                                                          |
|`WS2812_SPI_MOSI_PAL_MODE`      |`5`          |The MOSI pin alternative function to use                                       |
|`WS2812_SPI_SCK_PIN`            |*Not defined*|The SCK pin - required for F072 and possibly others                            |
|`WS2812_SPI_SCK_PAL_MODE`       |`5`          |The SCK pin alternative function to use - required for F072 and possibly others|
|`WS2812_SPI_DIVISOR`            |`16`         |The divisor used to adjust the baudrate                                        |
|`WS2812_SPI_USE_CIRCULAR_BUFFER`|*Not defined*|Enable a circular buffer for improved rendering                                |

#### Setting the Baudrate :id=arm-spi-baudrate

To adjust the SPI baudrate, you will need to derive the target baudrate from the clock tree provided by STM32CubeMX, and add the following to your `config.h`:

```c
#define WS2812_SPI_DIVISOR 16
```

Only divisors of 2, 4, 8, 16, 32, 64, 128 and 256 are supported on STM32 devices. Other MCUs may have similar constraints -- check the reference manual for your respective MCU for specifics.

#### Circular Buffer :id=arm-spi-circular-buffer

A circular buffer can be enabled if you experience flickering.

To enable the circular buffer, add the following to your `config.h`:

```c
#define WS2812_SPI_USE_CIRCULAR_BUFFER
```

### PIO Driver :id=arm-pio-driver

The following `#define`s apply only to the PIO driver:

|Define               |Default      |Description                            |
|---------------------|-------------|---------------------------------------|
|`WS2812_PIO_USE_PIO1`|*Not defined*|Use the PIO1 peripheral instead of PIO0|

### PWM Driver :id=arm-pwm-driver

Depending on the ChibiOS board configuration, you may need to enable PWM at the keyboard level. For STM32, this would look like:

`halconf.h`:
```c
#define HAL_USE_PWM TRUE
```
`mcuconf.h`:
```c
#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE
```

The following `#define`s apply only to the `pwm` driver:

|Define                           |Default             |Description                                                                               |
|---------------------------------|--------------------|------------------------------------------------------------------------------------------|
|`WS2812_PWM_DRIVER`              |`PWMD2`             |The PWM driver to use                                                                     |
|`WS2812_PWM_CHANNEL`             |`2`                 |The PWM channel to use                                                                    |
|`WS2812_PWM_PAL_MODE`            |`2`                 |The pin alternative function to use                                                       |
|`WS2812_DMA_STREAM`              |`STM32_DMA1_STREAM2`|The DMA Stream for `TIMx_UP`                                                              |
|`WS2812_DMA_CHANNEL`             |`2`                 |The DMA Channel for `TIMx_UP`                                                             |
|`WS2812_DMAMUX_ID`               |*Not defined*       |The DMAMUX configuration for `TIMx_UP` - only required if your MCU has a DMAMUX peripheral|
|`WS2812_PWM_COMPLEMENTARY_OUTPUT`|*Not defined*       |Whether the PWM output is complementary (`TIMx_CHyN`)                                     |

?> Using a complementary timer output (`TIMx_CHyN`) is possible only for advanced-control timers (1, 8 and 20 on STM32), and the `STM32_PWM_USE_ADVANCED` option in `mcuconf.h` must be set to `TRUE`. Complementary outputs of general-purpose timers are not supported due to ChibiOS limitations.

## API :id=api

### `void ws2812_setleds(rgb_led_t *ledarray, uint16_t number_of_leds)` :id=api-ws2812-setleds

Send RGB data to the WS2812 LED chain.

#### Arguments :id=api-ws2812-setleds-arguments

 - `rgb_led_t *ledarray`  
   A pointer to the LED array.
 - `uint16_t number_of_leds`  
   The length of the LED array.
