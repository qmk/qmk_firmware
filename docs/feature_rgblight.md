# RGB Lighting

If you've installed addressable RGB lights on your keyboard you can control them with QMK. Currently we support the following addressable LEDs on Atmel AVR processors:

* WS2811 and variants (WS2812, WS2812B, WS2812C, etc)
* SK6812RGBW

Some keyboards come with RGB LEDs pre-installed. Others have to have LEDs installed after the fact. See below for information on modifying your keyboard.

## Selecting Colors

QMK uses Hue, Saturation, and Value to set color rather than using RGB. You can use the color wheel below to see how this works. Changing the Hue will cycle around the circle. Saturation will affect the intensity of the color, which you can see as you move from the inner part to the outer part of the wheel. Value sets the overall brightness.

<img src="gitbook/images/color-wheel.svg" alt="HSV Color Wheel" width="250">

If you would like to learn more about HSV you can start with the [Wikipedia article](https://en.wikipedia.org/wiki/HSL_and_HSV).

## Configuration

Before RGB Lighting can be used you have to enable it in `rules.mk`:

    RGBLIGHT_ENABLE = yes

You can configure the behavior of the RGB lighting by defining values inside `config.h`.

### Required Configuration

At minimum you have to define the pin your LED strip is connected to and the number of LEDs connected.

```c
#define RGB_DI_PIN D7     // The pin the LED strip is connected to
#define RGBLED_NUM 14     // Number of LEDs in your strip
```

### Optional Configuration

You can change the behavior of the RGB Lighting by setting these configuration values. Use `#define <Option> <Value>` in a `config.h` at the keyboard, revision, or keymap level.

| Option | Default Value | Description |
|--------|---------------|-------------|
| `RGBLIGHT_HUE_STEP` | 10 | How many hues you want to have available. |
| `RGBLIGHT_SAT_STEP` | 17 | How many steps of saturation you'd like. |
| `RGBLIGHT_VAL_STEP` | 17 | The number of levels of brightness you want. |
| `RGBLIGHT_LIMIT_VAL` | 255 | Limit the val of HSV to limit the maximum brightness simply. |
| `RGBLIGHT_SLEEP`     |    |  `#define` this will shut off the lights when the host goes to sleep | 


### Animations

If you have `#define RGBLIGHT_ANIMATIONS` in your `config.h` you will have a number of animation modes you can cycle through using the `RGB_MOD` key. You can also `#define` other options to tweak certain animations.

| Option | Default Value | Description |
|--------|---------------|-------------|
| `RGBLIGHT_ANIMATIONS` | | `#define` this to enable animation modes. |
| `RGBLIGHT_EFFECT_BREATHE_CENTER` | 1.85 | Used to calculate the curve for the breathing animation. Valid values 1.0-2.7. |
| `RGBLIGHT_EFFECT_BREATHE_MAX` | 255 | The maximum brightness for the breathing mode. Valid values 1-255. |
| `RGBLIGHT_EFFECT_SNAKE_LENGTH` | 4 | The number of LEDs to light up for the "snake" animation. |
| `RGBLIGHT_EFFECT_KNIGHT_LENGTH` | 3 | The number of LEDs to light up for the "knight" animation. |
| `RGBLIGHT_EFFECT_KNIGHT_OFFSET` | 0 | Start the knight animation this many LEDs from the start of the strip. |
| `RGBLIGHT_EFFECT_KNIGHT_LED_NUM` | RGBLED_NUM | The number of LEDs to have the "knight" animation travel. |
| `RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL` | 1000 | How long to wait between light changes for the "christmas" animation. Specified in ms. |
| `RGBLIGHT_EFFECT_CHRISTMAS_STEP` | 2 | How many LED's to group the red/green colors by for the christmas mode. |

You can also tweak the behavior of the animations by defining these consts in your `keymap.c`. These mostly affect the speed different modes animate at.

```c
// How long (in ms) to wait between animation steps for the breathing mode
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {30, 20, 10, 5};

// How long (in ms) to wait between animation steps for the rainbow mode
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {120, 60, 30};

// How long (in ms) to wait between animation steps for the swirl mode
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 20};

// How long (in ms) to wait between animation steps for the snake mode
const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {100, 50, 20};

// How long (in ms) to wait between animation steps for the knight modes
const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {127, 63, 31};

// These control which colors are selected for the gradient mode
const uint16_t RGBLED_GRADIENT_RANGES[] PROGMEM = {360, 240, 180, 120, 90};
```

### LED Control

Look in `rgblights.h` for all available functions, but if you want to control all or some LEDs your goto functions are:

```c
// turn all lights off (stored in EEPROM)
rgblight_disable();
// turn lights on, based on their previous state (stored in EEPROM)
rgblight_enable(); 

// turn all lights off (not stored in EEPROM)
rgblight_disable_noeeprom();
// turn lights on, based on their previous state (not stored in EEPROM)
rgblight_enable_noeeprom();

// where r/g/b is a number from 0..255.  Turns all the LEDs to this color (ignores mode, not stored in EEPROM). 
rgblight_setrgb(r, g, b); 
// HSV color control - h is a value from 0..360 and s/v is a value from 0..255 (stored in EEPROM)
rgblight_sethsv(h, s, v);  
// HSV color control - h is a value from 0..360 and s/v is a value from 0..255 (not stored in EEPROM)
rgblight_sethsv_noeeprom(h, s, v);  

// Sets the mode, if rgb animations are enabled (stored in eeprom)
rgblight_mode(x);
// Sets the mode, if rgb animations are enabled (not stored in eeprom)
rgblight_mode_noeeprom(x);
// MODE 1, solid color
// MODE 2-5, breathing
// MODE 6-8, rainbow mood
// MODE 9-14, rainbow swirl
// MODE 15-20, snake
// MODE 21-23, knight
// MODE 24, xmas
// MODE 25-34, static rainbow

rgblight_setrgb_at(r,g,b, LED);  // control a single LED.  0 <= LED < RGBLED_NUM
rgblight_sethsv_at(h,s,v, LED);  // control a single LED.  0 <= LED < RGBLED_NUM
```
You can find a list of predefined colors at [`quantum/rgblight_list.h`](https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h). Free to add to this list!

## RGB Lighting Keycodes

These control the RGB Lighting functionality.

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
|`RGB_MODE_RGBTEST `|`RGB_M_T` |Red,Green,Blue test animation mode                                  |

note: for backwards compatibility, `RGB_SMOD` is an alias for `RGB_MOD`.

## Hardware Modification

![Planck with RGB Underglow](https://raw.githubusercontent.com/qmk/qmk_firmware/3774a7fcdab5544fc787f4c200be05fcd417e31f/keyboards/planck/keymaps/yang/planck-with-rgb-underglow.jpg)

Here is a quick demo on Youtube (with NPKC KC60) (https://www.youtube.com/watch?v=VKrpPAHlisY).

For this mod, you need an unused pin wiring to DI of WS2812 strip. After wiring the VCC, GND, and DI, you can enable the underglow in your Makefile.

    RGBLIGHT_ENABLE = yes

In order to use the underglow animation functions, you need to have `#define RGBLIGHT_ANIMATIONS` in your `config.h`.

Please add the following options into your config.h, and set them up according your hardware configuration. These settings are for the `F4` pin by default:

    #define RGB_DI_PIN F4     // The pin your RGB strip is wired to
    #define RGBLED_NUM 14     // Number of LEDs

You'll need to edit `RGB_DI_PIN` to the pin you have your `DI` on your RGB strip wired to.
