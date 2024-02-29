# APA102 Driver :id=apa102-driver

This driver provides support for APA102 addressable RGB LEDs. They are similar to the [WS2812](ws2812_driver.md) LEDs, but have increased data and refresh rates.

## Usage :id=usage

In most cases, the APA102 driver code is automatically included if you are using either the [RGBLight](feature_rgblight.md) or [RGB Matrix](feature_rgb_matrix.md) feature with the `apa102` driver set, and you would use those APIs instead.

However, if you need to use the driver standalone, add the following to your `rules.mk`:

```make
APA102_DRIVER_REQUIRED = yes
```

You can then call the APA102 API by including `apa102.h` in your code.

## Basic Configuration :id=basic-configuration

Add the following to your `config.h`:

|Define                     |Default      |Description                                                       |
|---------------------------|-------------|------------------------------------------------------------------|
|`APA102_DI_PIN`            |*Not defined*|The GPIO pin connected to the DI pin of the first LED in the chain|
|`APA102_CI_PIN`            |*Not defined*|The GPIO pin connected to the CI pin of the first LED in the chain|
|`APA102_DEFAULT_BRIGHTNESS`|`31`         |The default global brightness level of the LEDs, from 0 to 31     |

## API :id=api

### `void apa102_setleds(rgb_led_t *start_led, uint16_t num_leds)`

Send RGB data to the APA102 LED chain.

#### Arguments :id=api-apa102-setleds-arguments

 - `rgb_led_t *start_led`  
   A pointer to the LED array.
 - `uint16_t num_leds`  
   The length of the LED array.

---

### `void apa102_set_brightness(uint8_t brightness)`

Set the global brightness.

#### Arguments :id=api-apa102-set-brightness-arguments

 - `uint8_t brightness`  
   The brightness level to set, from 0 to 31.
