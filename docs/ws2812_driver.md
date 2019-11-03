# WS2812 Driver
This driver powers the [RGB Lighting](feature_rgblight.md) and [RGB Matrix](feature_rgb_matrix.md) features.

Currently QMK supports the following addressable LEDs on AVR microcontrollers (however, the white LED in RGBW variants is not supported):

    WS2811, WS2812, WS2812B, WS2812C, etc.
    SK6812, SK6812MINI, SK6805

These LEDs are called "addressable" because instead of using a wire per color, each LED contains a small microchip that understands a special protocol sent over a single wire. The chip passes on the remaining data to the next LED, allowing them to be chained together. In this way, you can easily control the color of the individual LEDs.

## Driver configuration

### Bitbang
Default driver, the absence of configuration assumes this driver. To configure it, add this to your rules.mk:

```make
WS2812_DRIVER = bitbang
```

!> ARM does not yet support WS2182. Progress is being made, but we are not quite there, yet.

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
