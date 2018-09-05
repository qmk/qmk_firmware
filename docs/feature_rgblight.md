# RGB Lighting

QMK has the ability to control RGB LEDs attached to your keyboard. This is commonly called *underglow*, due to the LEDs often being mounted on the bottom of the keyboard, producing a nice diffused effect when combined with a translucent case.

![Planck with RGB Underglow](https://raw.githubusercontent.com/qmk/qmk_firmware/3774a7fcdab5544fc787f4c200be05fcd417e31f/keyboards/planck/keymaps/yang/planck-with-rgb-underglow.jpg)

Some keyboards come with RGB LEDs preinstalled. Others must have them installed after the fact. See the [Hardware Modification](#hardware-modification) section for information on adding RGB lighting to your keyboard.

Currently QMK supports the following addressable LEDs on AVR microcontrollers (however, the white LED in RGBW variants is not supported):

 * WS2811, WS2812, WS2812B, WS2812C, etc.
 * SK6812, SK6812MINI, SK6805

These LEDs are called "addressable" because instead of using a wire per color, each LED contains a small microchip that understands a special protocol sent over a single wire. The chip passes on the remaining data to the next LED, allowing them to be chained together. In this way, you can easily control the color of the individual LEDs.

## Usage

On keyboards with onboard RGB LEDs, it is usually enabled by default. If it is not working for you, check that your `rules.mk` includes the following:

```make
RGBLIGHT_ENABLE = yes
```

At minimum you must define the data pin your LED strip is connected to, and the number of LEDs in the strip, in your `config.h`. If your keyboard has onboard RGB LEDs, and you are simply creating a keymap, you usually won't need to modify these.

|Define      |Description                                  |
|------------|---------------------------------------------|
|`RGB_DI_PIN`|The pin connected to the data pin of the LEDs|
|`RGBLED_NUM`|The number of LEDs connected                 |

Then you should be able to use the keycodes below to change the RGB lighting to your liking.

### Color Selection

QMK uses [Hue, Saturation, and Value](https://en.wikipedia.org/wiki/HSL_and_HSV) to select colors rather than RGB. The color wheel below demonstrates how this works.

<img src="gitbook/images/color-wheel.svg" alt="HSV Color Wheel" width="250"/>

Changing the **Hue** cycles around the circle.  
Changing the **Saturation** moves between the inner and outer sections of the wheel, affecting the intensity of the color.  
Changing the **Value** sets the overall brightness.

## Keycodes

|Key                |Aliases   |Description                                                         |
|-------------------|----------|--------------------------------------------------------------------|
|`RGB_TOG`          |          |Toggle RGB lighting on or off                                       |
|`RGB_MODE_FORWARD` |`RGB_MOD` |Cycle through modes, reverse direction when Shift is held           |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|Cycle through modes in reverse, forward direction when Shift is held|
|`RGB_HUI`          |          |Increase hue                                                        |
|`RGB_HUD`          |          |Decrease hue                                                        |
|`RGB_SAI`          |          |Increase saturation                                                 |
|`RGB_SAD`          |          |Decrease saturation                                                 |
|`RGB_VAI`          |          |Increase value (brightness)                                         |
|`RGB_VAD`          |          |Decrease value (brightness)                                         |
|`RGB_MODE_PLAIN`   |`RGB_M_P `|Static (no animation) mode                                          |
|`RGB_MODE_BREATHE` |`RGB_M_B` |Breathing animation mode                                            |
|`RGB_MODE_RAINBOW` |`RGB_M_R` |Rainbow animation mode                                              |
|`RGB_MODE_SWIRL`   |`RGB_M_SW`|Swirl animation mode                                                |
|`RGB_MODE_SNAKE`   |`RGB_M_SN`|Snake animation mode                                                |
|`RGB_MODE_KNIGHT`  |`RGB_M_K` |"Knight Rider" animation mode                                       |
|`RGB_MODE_XMAS`    |`RGB_M_X` |Christmas animation mode                                            |
|`RGB_MODE_GRADIENT`|`RGB_M_G` |Static gradient animation mode                                      |
|`RGB_MODE_RGBTEST` |`RGB_M_T` |Red, Green, Blue test animation mode                                |

?> For backwards compatibility, `RGB_SMOD` is another alias of `RGB_MOD`.

## Configuration

Your RGB lighting can be configured by placing these `#define`s in your `config.h`:

|Define               |Default      |Description                                                                  |
|---------------------|-------------|-----------------------------------------------------------------------------|
|`RGBLIGHT_HUE_STEP`  |`10`         |The number of steps to cycle through the hue by                              |
|`RGBLIGHT_SAT_STEP`  |`17`         |The number of steps to increment the saturation by                           |
|`RGBLIGHT_VAL_STEP`  |`17`         |The number of steps to increment the brightness by                           |
|`RGBLIGHT_LIMIT_VAL` |`255`        |The maximum brightness level                                                 |
|`RGBLIGHT_SLEEP`     |*Not defined*|If defined, the RGB lighting will be switched off when the host goes to sleep|

## Animations

Not only can this lighting be whatever color you want, if `RGBLIGHT_ANIMATIONS` is defined, you also have a number of animation modes at your disposal:

|Mode |Description          |
|-----|---------------------|
|1    |Solid color          |
|2-5  |Solid color breathing|
|6-8  |Cycling rainbow      |
|9-14 |Swirling rainbow     |
|15-20|Snake                |
|21-23|Knight               |
|24   |Christmas            |
|25-34|Static gradient      |
|35   |RGB Test             |
|36   |Alternating          |

Check out [this video](https://youtube.com/watch?v=VKrpPAHlisY) for a demonstration.

The following options can be used to tweak the various animations:

|Define                              |Default      |Description                                                                          |
|------------------------------------|-------------|-------------------------------------------------------------------------------------|
|`RGBLIGHT_ANIMATIONS`               |*Not defined*|If defined, enables additional animation modes                                       |
|`RGBLIGHT_EFFECT_BREATHE_CENTER`    |`1.85`       |Used to calculate the curve for the breathing animation. Valid values are 1.0 to 2.7 |
|`RGBLIGHT_EFFECT_BREATHE_MAX`       |`255`        |The maximum brightness for the breathing mode. Valid values are 1 to 255             |
|`RGBLIGHT_EFFECT_SNAKE_LENGTH`      |`4`          |The number of LEDs to light up for the "Snake" animation                             |
|`RGBLIGHT_EFFECT_KNIGHT_LENGTH`     |`3`          |The number of LEDs to light up for the "Knight" animation                            |
|`RGBLIGHT_EFFECT_KNIGHT_OFFSET`     |`0`          |The number of LEDs to start the "Knight" animation from the start of the strip by    |
|`RGBLIGHT_EFFECT_KNIGHT_LED_NUM`    |`RGBLED_NUM` |The number of LEDs to have the "Knight" animation travel                             |
|`RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL`|`1000`       |How long to wait between light changes for the "Christmas" animation, in milliseconds|
|`RGBLIGHT_EFFECT_CHRISTMAS_STEP`    |`2`          |The number of LEDs to group the red/green colors by for the "Christmas" animation    |

You can also modify the speeds that the different modes animate at:

```c
// How long (in milliseconds) to wait between animation steps for each of the "Solid color breathing" animations
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {30, 20, 10, 5};

// How long (in milliseconds) to wait between animation steps for each of the "Cycling rainbow" animations
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {120, 60, 30};

// How long (in milliseconds) to wait between animation steps for each of the "Swirling rainbow" animations
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 20};

// How long (in milliseconds) to wait between animation steps for each of the "Snake" animations
const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {100, 50, 20};

// How long (in milliseconds) to wait between animation steps for each of the "Knight" animations
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {127, 63, 31};

// These control which hues are selected for each of the "Static gradient" modes
const uint16_t RGBLED_GRADIENT_RANGES[] PROGMEM = {360, 240, 180, 120, 90};
```

## Functions

If you need to change your RGB lighting in code, for example in a macro to change the color whenever you switch layers, QMK provides a set of functions to assist you. See [`rgblight.h`](https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight.h) for the full list, but the most commonly used functions include:

|Function                           |Description                                                                                                                                                            |
|-----------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`rgblight_enable()`                |Turn LEDs on, based on their previous state                                                                                                                            |
|`rgblight_enable_noeeprom()`       |Turn LEDs on, based on their previous state (not written to EEPROM)                                                                                                    |
|`rgblight_disable()`               |Turn LEDs off                                                                                                                                                          |
|`rgblight_disable_noeeprom()`      |Turn LEDs off (not written to EEPROM)                                                                                                                                  |
|`rgblight_mode(x)`                 |Set the mode, if RGB animations are enabled                                                                                                                            |
|`rgblight_mode_noeeprom(x)`        |Set the mode, if RGB animations are enabled (not written to EEPROM)                                                                                                    |
|`rgblight_setrgb(r, g, b)`         |Set all LEDs to the given RGB value where `r`/`g`/`b` are between 0 and 255 (not written to EEPROM)                                                                    |
|`rgblight_setrgb_at(r, g, b, led)` |Set a single LED to the given RGB value, where `r`/`g`/`b` are between 0 and 255 and `led` is between 0 and `RGBLED_NUM` (not written to EEPROM)                       |
|`rgblight_sethsv(h, s, v)`         |Set all LEDs to the given HSV value where `h` is between 0 and 360 and `s`/`v` are between 0 and 255                                                                   |
|`rgblight_sethsv_noeeprom(h, s, v)`|Set all LEDs to the given HSV value where `h` is between 0 and 360 and `s`/`v` are between 0 and 255 (not written to EEPROM)                                           |
|`rgblight_sethsv_at(h, s, v, led)` |Set a single LED to the given HSV value, where `h` is between 0 and 360, `s`/`v` are between 0 and 255, and `led` is between 0 and `RGBLED_NUM` (not written to EEPROM)|

Additionally, [`rgblight_list.h`](https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h) defines several predefined shortcuts for various colors. Feel free to add to this list!

## Hardware Modification

If your keyboard lacks onboard underglow LEDs, you may often be able to solder on an RGB LED strip yourself. You will need to find an unused pin to wire to the data pin of your LED strip. Some keyboards may break out unused pins from the MCU to make soldering easier. The other two pins, VCC and GND, must also be connected to the appropriate power pins.
