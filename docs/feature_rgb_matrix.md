# RGB Matrix Lighting

This feature allows you to use RGB LED matrices driven by external drivers. It hooks into the RGBLIGHT system so you can use the same keycodes as RGBLIGHT to control it.

If you want to use single color LED's you should use the [LED Matrix Subsystem](feature_led_matrix.md) instead.

## Driver configuration
---
### IS31FL3731

There is basic support for addressable RGB matrix lighting with the I2C IS31FL3731 RGB controller. To enable it, add this to your `rules.mk`:

```C
RGB_MATRIX_ENABLE = IS31FL3731
```

Configure the hardware via your `config.h`:

```C
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b1110100 AD <-> GND
// 0b1110111 AD <-> VCC
// 0b1110101 AD <-> SCL
// 0b1110110 AD <-> SDA
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110110

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 25
#define DRIVER_2_LED_TOTAL 24
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
```

!> Note the parentheses, this is so when `DRIVER_LED_TOTAL` is used in code and expanded, the values are added together before any additional math is applied to them. As an example, `rand() % (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)` will give very different results than `rand() % DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL`.

Currently only 2 drivers are supported, but it would be trivial to support all 4 combinations.

Define these arrays listing all the LEDs in your `<keyboard>.c`:

```C
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_3,  C2_3,  C3_3},
    ....
}
```

Where `Cx_y` is the location of the LED in the matrix defined by [the datasheet](http://www.issi.com/WW/pdf/31FL3731.pdf) and the header file `drivers/issi/is31fl3731.h`. The `driver` is the index of the driver you defined in your `config.h` (`0` or `1` right now).

---
###  IS31FL3733/IS31FL3737

!> For the IS31FL3737, replace all instances of `IS31FL3733` below with `IS31FL3737`.

There is basic support for addressable RGB matrix lighting with the I2C IS31FL3733 RGB controller. To enable it, add this to your `rules.mk`:

```C
RGB_MATRIX_ENABLE = IS31FL3733
```

Configure the hardware via your `config.h`:

```C
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 00 <-> GND
// 01 <-> SCL
// 10 <-> SDA
// 11 <-> VCC
// ADDR1 represents A1:A0 of the 7-bit address.
// ADDR2 represents A3:A2 of the 7-bit address.
// The result is: 0b101(ADDR2)(ADDR1)
#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010000 // this is here for compliancy reasons.

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 64
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
```

Currently only a single drivers is supported, but it would be trivial to support all 4 combinations. For now define `DRIVER_ADDR_2` as `DRIVER_ADDR_1`

Define these arrays listing all the LEDs in your `<keyboard>.c`:

```C
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, B_1,    A_1,    C_1},
    ....
}
```

Where `X_Y` is the location of the LED in the matrix defined by [the datasheet](http://www.issi.com/WW/pdf/31FL3733.pdf) and the header file `drivers/issi/is31fl3733.h`. The `driver` is the index of the driver you defined in your `config.h` (Only `0` right now).

---

### WS2812

There is basic support for addressable RGB matrix lighting with a WS2811/WS2812{a,b,c} addressable LED strand. To enable it, add this to your `rules.mk`:

```C
RGB_MATRIX_ENABLE = WS2812
```

Configure the hardware via your `config.h`:

```C
// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN D7
// The number of LEDs connected
#define DRIVER_LED_TOTAL 70
```

---

From this point forward the configuration is the same for all the drivers. The `led_config_t` struct provides a key electrical matrix to led index lookup table, what the physical position of each LED is on the board, and what type of key or usage the LED if the LED represents. Here is a brief example:

```C
const led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   5, NO_LED, NO_LED,   0 },
  { NO_LED, NO_LED, NO_LED, NO_LED },
  {   4, NO_LED, NO_LED,   1 },
  {   3, NO_LED, NO_LED,   2 }
}, {
  // LED Index to Physical Position
  { 188,  16 }, { 187,  48 }, { 149,  64 }, { 112,  64 }, {  37,  48 }, {  38,  16 }
}, {
  // LED Index to Flag
  1, 4, 4, 4, 4, 1
} };
```

The first part, `// Key Matrix to LED Index`, tells the system what key this LED represents by using the key's electrical matrix row & col. The second part, `// LED Index to Physical Position` represents the LED's physical `{ x, y }` position on the keyboard. The default expected range of values for `{ x, y }` is the inclusive range `{ 0..224, 0..64 }`. This default expected range is due to effects that calculate the center of the keyboard for their animations. The easiest way to calculate these positions is imagine your keyboard is a grid, and the top left of the keyboard represents `{ x, y }` coordinate `{ 0, 0 }` and the bottom right of your keyboard represents `{ 224, 64 }`. Using this as a basis, you can use the following formula to calculate the physical position:

```C
x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
```

Where NUMBER_OF_COLS, NUMBER_OF_ROWS, COL_POSITION, & ROW_POSITION are all based on the physical layout of your keyboard, not the electrical layout. 

As mentioned earlier, the center of the keyboard by default is expected to be `{ 112, 32 }`, but this can be changed if you want to more accurately calculate the LED's physical `{ x, y }` positions. Keyboard designers can implement `#define RGB_MATRIX_CENTER { 112, 32 }` in their config.h file with the new center point of the keyboard, or where they want it to be allowing more possibilities for the `{ x, y }` values. Do note that the maximum value for x or y is 255, and the recommended maximum is 224 as this gives animations runoff room before they reset.

`// LED Index to Flag` is a bitmask, whether or not a certain LEDs is of a certain type. It is recommended that LEDs are set to only 1 type.

## Flags

|Define                              |Description                                |
|------------------------------------|-------------------------------------------|
|`#define HAS_FLAGS(bits, flags)`    |Returns true if `bits` has all `flags` set.|
|`#define HAS_ANY_FLAGS(bits, flags)`|Returns true if `bits` has any `flags` set.|
|`#define LED_FLAG_NONE      0x00`   |If this LED has no flags.                  |
|`#define LED_FLAG_ALL       0xFF`   |If this LED has all flags.                 |
|`#define LED_FLAG_MODIFIER  0x01`   |If the Key for this LED is a modifier.     |
|`#define LED_FLAG_UNDERGLOW 0x02`   |If the LED is for underglow.               |
|`#define LED_FLAG_KEYLIGHT  0x04`   |If the LED is for key backlight.           |

## Keycodes

All RGB keycodes are currently shared with the RGBLIGHT system:

|Key                |Aliases   |Description                                                                           |
|-------------------|----------|--------------------------------------------------------------------------------------|
|`RGB_TOG`          |          |Toggle RGB lighting on or off                                                         |
|`RGB_MODE_FORWARD` |`RGB_MOD` |Cycle through modes, reverse direction when Shift is held                             |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|Cycle through modes in reverse, forward direction when Shift is held                  |
|`RGB_HUI`          |          |Increase hue, decrease hue when Shift is held                                         |
|`RGB_HUD`          |          |Decrease hue, increase hue when Shift is held                                         |
|`RGB_SAI`          |          |Increase saturation, decrease saturation when Shift is held                           |
|`RGB_SAD`          |          |Decrease saturation, increase saturation when Shift is held                           |
|`RGB_VAI`          |          |Increase value (brightness), decrease value when Shift is held                        |
|`RGB_VAD`          |          |Decrease value (brightness), increase value when Shift is held                        |
|`RGB_SPI`          |          |Increase effect speed (does not support eeprom yet), decrease speed when Shift is held|
|`RGB_SPD`          |          |Decrease effect speed (does not support eeprom yet), increase speed when Shift is held|

* `RGB_MODE_*` keycodes will generally work, but are not currently mapped to the correct effects for the RGB Matrix system

## RGB Matrix Effects

All effects have been configured to support current configuration values (Hue, Saturation, Value, & Speed) unless otherwise noted below. These are the effects that are currently available:

```C
enum rgb_matrix_effects {
    RGB_MATRIX_NONE = 0,
    RGB_MATRIX_SOLID_COLOR = 1,     // Static single hue, no speed support
    RGB_MATRIX_ALPHAS_MODS,         // Static dual hue, speed is hue for secondary hue
    RGB_MATRIX_GRADIENT_UP_DOWN,    // Static gradient top to bottom, speed controls how much gradient changes
    RGB_MATRIX_BREATHING,           // Single hue brightness cycling animation
    RGB_MATRIX_BAND_SAT,        // Single hue band fading saturation scrolling left to right
    RGB_MATRIX_BAND_VAL,        // Single hue band fading brightness scrolling left to right
    RGB_MATRIX_BAND_PINWHEEL_SAT,   // Single hue 3 blade spinning pinwheel fades saturation
    RGB_MATRIX_BAND_PINWHEEL_VAL,   // Single hue 3 blade spinning pinwheel fades brightness
    RGB_MATRIX_BAND_SPIRAL_SAT,     // Single hue spinning spiral fades saturation
    RGB_MATRIX_BAND_SPIRAL_VAL,     // Single hue spinning spiral fades brightness
    RGB_MATRIX_CYCLE_ALL,           // Full keyboard solid hue cycling through full gradient
    RGB_MATRIX_CYCLE_LEFT_RIGHT,    // Full gradient scrolling left to right
    RGB_MATRIX_CYCLE_UP_DOWN,       // Full gradient scrolling top to bottom
    RGB_MATRIX_CYCLE_OUT_IN,        // Full gradient scrolling out to in
    RGB_MATRIX_CYCLE_OUT_IN_DUAL,   // Full dual gradients scrolling out to in
    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,  // Full gradent Chevron shapped scrolling left to right
    RGB_MATRIX_CYCLE_PINWHEEL,      // Full gradient spinning pinwheel around center of keyboard
    RGB_MATRIX_CYCLE_SPIRAL,        // Full gradient spinning spiral around center of keyboard
    RGB_MATRIX_DUAL_BEACON,         // Full gradient spinning around center of keyboard
    RGB_MATRIX_RAINBOW_BEACON,      // Full tighter gradient spinning around center of keyboard
    RGB_MATRIX_RAINBOW_PINWHEELS,   // Full dual gradients spinning two halfs of keyboard
    RGB_MATRIX_RAINDROPS,           // Randomly changes a single key's hue
    RGB_MATRIX_JELLYBEAN_RAINDROPS, // Randomly changes a single key's hue and saturation
#if define(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    RGB_MATRIX_TYPING_HEATMAP,      // How hot is your WPM!
    RGB_MATRIX_DIGITAL_RAIN,        // That famous computer simulation
#endif
#if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
    RGB_MATRIX_SOLID_REACTIVE_SIMPLE,   // Pulses keys hit to hue & value then fades value out
    RGB_MATRIX_SOLID_REACTIVE,      // Static single hue, pulses keys hit to shifted hue then fades to current hue
    RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
    RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
    RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
    RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
    RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
    RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
    RGB_MATRIX_SPLASH,              // Full gradient & value pulse away from a single key hit then fades value out
    RGB_MATRIX_MULTISPLASH,         // Full gradient & value pulse away from multiple key hits then fades value out
    RGB_MATRIX_SOLID_SPLASH,        // Hue & value pulse away from a single key hit then fades value out
    RGB_MATRIX_SOLID_MULTISPLASH,   // Hue & value pulse away from multiple key hits then fades value out
#endif
    RGB_MATRIX_EFFECT_MAX
};
```

You can disable a single effect by defining `DISABLE_[EFFECT_NAME]` in your `config.h`:


|Define                                                 |Description                                    |
|-------------------------------------------------------|-----------------------------------------------|
|`#define DISABLE_RGB_MATRIX_ALPHAS_MODS`               |Disables `RGB_MATRIX_ALPHAS_MODS`              |
|`#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN`          |Disables `RGB_MATRIX_GRADIENT_UP_DOWN`         |
|`#define DISABLE_RGB_MATRIX_BREATHING`                 |Disables `RGB_MATRIX_BREATHING`                |
|`#define DISABLE_RGB_MATRIX_BAND_SAT`                  |Disables `RGB_MATRIX_BAND_SAT`                 |
|`#define DISABLE_RGB_MATRIX_BAND_VAL`                  |Disables `RGB_MATRIX_BAND_VAL`                 |
|`#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT`         |Disables `RGB_MATRIX_BAND_PINWHEEL_SAT`        |
|`#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL`         |Disables `RGB_MATRIX_BAND_PINWHEEL_VAL`        |
|`#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT`           |Disables `RGB_MATRIX_BAND_SPIRAL_SAT`          |
|`#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL`           |Disables `RGB_MATRIX_BAND_SPIRAL_VAL`          |
|`#define DISABLE_RGB_MATRIX_CYCLE_ALL`                 |Disables `RGB_MATRIX_CYCLE_ALL`                |
|`#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT`          |Disables `RGB_MATRIX_CYCLE_LEFT_RIGHT`         |
|`#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN`             |Disables `RGB_MATRIX_CYCLE_UP_DOWN`            |
|`#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN`              |Disables `RGB_MATRIX_CYCLE_OUT_IN`             |
|`#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL`         |Disables `RGB_MATRIX_CYCLE_OUT_IN_DUAL`        |
|`#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON`    |Disables `RGB_MATRIX_RAINBOW_MOVING_CHEVRON`   |
|`#define DISABLE_RGB_MATRIX_DUAL_BEACON`               |Disables `RGB_MATRIX_DUAL_BEACON`              |
|`#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL`            |Disables `RGB_MATRIX_CYCLE_PINWHEEL`           |
|`#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL`              |Disables `RGB_MATRIX_CYCLE_SPIRAL`             |
|`#define DISABLE_RGB_MATRIX_RAINBOW_BEACON`            |Disables `RGB_MATRIX_RAINBOW_BEACON`           |
|`#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS`         |Disables `RGB_MATRIX_RAINBOW_PINWHEELS`        |
|`#define DISABLE_RGB_MATRIX_RAINDROPS`                 |Disables `RGB_MATRIX_RAINDROPS`                |
|`#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS`       |Disables `RGB_MATRIX_JELLYBEAN_RAINDROPS`      |
|`#define DISABLE_RGB_MATRIX_TYPING_HEATMAP`            |Disables `RGB_MATRIX_TYPING_HEATMAP`           |
|`#define DISABLE_RGB_MATRIX_DIGITAL_RAIN`              |Disables `RGB_MATRIX_DIGITAL_RAIN`             |
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE`            |Disables `RGB_MATRIX_SOLID_REACTIVE`           |
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE`     |Disables `RGB_MATRIX_SOLID_REACTIVE_SIMPLE`    |
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE`       |Disables `RGB_MATRIX_SOLID_REACTIVE_WIDE`      |
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE`  |Disables `RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE` |
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS`      |Disables `RGB_MATRIX_SOLID_REACTIVE_CROSS`     |
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS` |Disables `RGB_MATRIX_SOLID_REACTIVE_MULTICROSS`|
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS`      |Disables `RGB_MATRIX_SOLID_REACTIVE_NEXUS`     |
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS` |Disables `RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS`|
|`#define DISABLE_RGB_MATRIX_SPLASH`                    |Disables `RGB_MATRIX_SPLASH`                   |
|`#define DISABLE_RGB_MATRIX_MULTISPLASH`               |Disables `RGB_MATRIX_MULTISPLASH`              |
|`#define DISABLE_RGB_MATRIX_SOLID_SPLASH`              |Disables `RGB_MATRIX_SOLID_SPLASH`             |
|`#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH`         |Disables `RGB_MATRIX_SOLID_MULTISPLASH`        |


## Custom RGB Matrix Effects

By setting `RGB_MATRIX_CUSTOM_USER` (and/or `RGB_MATRIX_CUSTOM_KB`) in `rules.mk`, new effects can be defined directly from userspace, without having to edit any QMK core files.

To declare new effects, create a new `rgb_matrix_user/kb.inc` that looks something like this:

`rgb_matrix_user.inc` should go in the root of the keymap directory.
`rgb_matrix_kb.inc` should go in the root of the keyboard directory.

```C
// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(my_cool_effect)
RGB_MATRIX_EFFECT(my_cool_effect2)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, 0xff, 0x00);
  }
  return led_max < DRIVER_LED_TOTAL;
}

// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
static uint8_t some_global_state;
static void my_cool_effect2_complex_init(effect_params_t* params) {
  some_global_state = 1;
}
static bool my_cool_effect2_complex_run(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, some_global_state++, 0xff);
  }

  return led_max < DRIVER_LED_TOTAL;
}
static bool my_cool_effect2(effect_params_t* params) {
  if (params->init) my_cool_effect2_complex_init(params);
  return my_cool_effect2_complex_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
```

For inspiration and examples, check out the built-in effects under `quantum/rgb_matrix_animation/`


## Colors

These are shorthands to popular colors. The `RGB` ones can be passed to the `setrgb` functions, while the `HSV` ones to the `sethsv` functions.

|RGB                |HSV                |
|-------------------|-------------------|
|`RGB_WHITE`        |`HSV_WHITE`        |
|`RGB_RED`          |`HSV_RED`          |
|`RGB_CORAL`        |`HSV_CORAL`        |
|`RGB_ORANGE`       |`HSV_ORANGE`       |
|`RGB_GOLDENROD`    |`HSV_GOLDENROD`    |
|`RGB_GOLD`         |`HSV_GOLD`         |
|`RGB_YELLOW`       |`HSV_YELLOW`       |
|`RGB_CHARTREUSE`   |`HSV_CHARTREUSE`   |
|`RGB_GREEN`        |`HSV_GREEN`        |
|`RGB_SPRINGGREEN`  |`HSV_SPRINGGREEN`  |
|`RGB_TURQUOISE`    |`HSV_TURQUOISE`    |
|`RGB_TEAL`         |`HSV_TEAL`         |
|`RGB_CYAN`         |`HSV_CYAN`         |
|`RGB_AZURE`        |`HSV_AZURE`        |
|`RGB_BLUE`         |`HSV_BLUE`         |
|`RGB_PURPLE`       |`HSV_PURPLE`       |
|`RGB_MAGENTA`      |`HSV_MAGENTA`      |
|`RGB_PINK`         |`HSV_PINK`         |

These are defined in [`rgblight_list.h`](https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h). Feel free to add to this list!


## Additional `config.h` Options

```C
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT // Sets the default mode, if none has been set
```

## EEPROM storage

The EEPROM for it is currently shared with the RGBLIGHT system (it's generally assumed only one RGB would be used at a time), but could be configured to use its own 32bit address with:

```C
#define EECONFIG_RGB_MATRIX (uint32_t *)28
```

Where `28` is an unused index from `eeconfig.h`.

## Suspended state

To use the suspend feature, add this to your `<keyboard>.c`:

```C
void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}
```
