# RGB Matrix Lighting {#rgb-matrix-lighting}

This feature allows you to use RGB LED matrices driven by external drivers. It hooks into the RGBLIGHT system so you can use the same keycodes as RGBLIGHT to control it.

If you want to use single color LED's you should use the [LED Matrix Subsystem](led_matrix) instead.

## Driver Configuration {#driver-configuration}

RGB Matrix is an abstraction layer on top of an underlying LED driver API. The list of supported LED drivers is below; see the respective documentation for information on how to configure the driver.

|Driver                               |Max LEDs|
|-------------------------------------|--------|
|[APA102](../drivers/apa102)          |?       |
|[AW20216S](../drivers/aw20216s)      |72      |
|[IS31FL3218](../drivers/is31fl3218)  |6       |
|[IS31FL3236](../drivers/is31fl3236)  |12      |
|[IS31FL3729](../drivers/is31fl3729)  |45      |
|[IS31FL3731](../drivers/is31fl3731)  |48      |
|[IS31FL3733](../drivers/is31fl3733)  |64      |
|[IS31FL3736](../drivers/is31fl3736)  |32      |
|[IS31FL3737](../drivers/is31fl3737)  |48      |
|[IS31FL3741](../drivers/is31fl3741)  |117     |
|[IS31FL3742A](../drivers/is31fl3742a)|60      |
|[IS31FL3743A](../drivers/is31fl3743a)|66      |
|[IS31FL3745](../drivers/is31fl3745)  |48      |
|[IS31FL3746A](../drivers/is31fl3746a)|24      |
|[SNLED27351](../drivers/snled27351)  |64      |
|[WS2812](../drivers/ws2812)          |?       |

To assign the RGB Matrix driver, add the following to your `rules.mk`, for example:

```make
RGB_MATRIX_DRIVER = is31fl3218
```

## Common Configuration {#common-configuration}

From this point forward the configuration is the same for all the drivers. The `led_config_t` struct provides a key electrical matrix to led index lookup table, what the physical position of each LED is on the board, and what type of key or usage the LED if the LED represents. Here is a brief example:

```c
led_config_t g_led_config = { {
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

```c
x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
```

Where NUMBER_OF_COLS, NUMBER_OF_ROWS, COL_POSITION, & ROW_POSITION are all based on the physical layout of your keyboard, not the electrical layout.

As mentioned earlier, the center of the keyboard by default is expected to be `{ 112, 32 }`, but this can be changed if you want to more accurately calculate the LED's physical `{ x, y }` positions. Keyboard designers can implement `#define RGB_MATRIX_CENTER { 112, 32 }` in their config.h file with the new center point of the keyboard, or where they want it to be allowing more possibilities for the `{ x, y }` values. Do note that the maximum value for x or y is 255, and the recommended maximum is 224 as this gives animations runoff room before they reset.

`// LED Index to Flag` is a bitmask, whether or not a certain LEDs is of a certain type. It is recommended that LEDs are set to only 1 type.

## Flags {#flags}

|Define                      |Value |Description                                      |
|----------------------------|------|-------------------------------------------------|
|`HAS_FLAGS(bits, flags)`    |*n/a* |Evaluates to `true` if `bits` has all `flags` set|
|`HAS_ANY_FLAGS(bits, flags)`|*n/a* |Evaluates to `true` if `bits` has any `flags` set|
|`LED_FLAG_NONE`             |`0x00`|If this LED has no flags                         |
|`LED_FLAG_ALL`              |`0xFF`|If this LED has all flags                        |
|`LED_FLAG_MODIFIER`         |`0x01`|If the LED is on a modifier key                  |
|`LED_FLAG_UNDERGLOW`        |`0x02`|If the LED is for underglow                      |
|`LED_FLAG_KEYLIGHT`         |`0x04`|If the LED is for key backlight                  |
|`LED_FLAG_INDICATOR`        |`0x08`|If the LED is for keyboard state indication      |

## Keycodes {#keycodes}

|Key                            |Aliases  |Description                        |
|-------------------------------|---------|-----------------------------------|
|`QK_RGB_MATRIX_ON`             |`RM_ON`  |Turn on RGB Matrix                 |
|`QK_RGB_MATRIX_OFF`            |`RM_OFF` |Turn off RGB Matrix                |
|`QK_RGB_MATRIX_TOGGLE`         |`RM_TOGG`|Toggle RGB Matrix on or off        |
|`QK_RGB_MATRIX_MODE_NEXT`      |`RM_NEXT`|Cycle through animations           |
|`QK_RGB_MATRIX_MODE_PREVIOUS`  |`RM_PREV`|Cycle through animations in reverse|
|`QK_RGB_MATRIX_HUE_UP`         |`RM_HUEU`|Cycle through hue                  |
|`QK_RGB_MATRIX_HUE_DOWN`       |`RM_HUED`|Cycle through hue in reverse       |
|`QK_RGB_MATRIX_SATURATION_UP`  |`RM_SATU`|Increase the saturation            |
|`QK_RGB_MATRIX_SATURATION_DOWN`|`RM_SATD`|Decrease the saturation            |
|`QK_RGB_MATRIX_VALUE_UP`       |`RM_VALU`|Increase the brightness level      |
|`QK_RGB_MATRIX_VALUE_DOWN`     |`RM_VALD`|Decrease the brightness level      |
|`QK_RGB_MATRIX_SPEED_UP`       |`RM_SPDU`|Increase the animation speed       |
|`QK_RGB_MATRIX_SPEED_DOWN`     |`RM_SPDD`|Decrease the animation speed       |

## RGB Matrix Effects {#rgb-matrix-effects}

All effects have been configured to support current configuration values (Hue, Saturation, Value, & Speed) unless otherwise noted below. These are the effects that are currently available:

```c
enum rgb_matrix_effects {
    RGB_MATRIX_NONE = 0,
    RGB_MATRIX_SOLID_COLOR = 1,     // Static single hue, no speed support
    RGB_MATRIX_ALPHAS_MODS,         // Static dual hue, speed is hue for secondary hue
    RGB_MATRIX_GRADIENT_UP_DOWN,    // Static gradient top to bottom, speed controls how much gradient changes
    RGB_MATRIX_GRADIENT_LEFT_RIGHT,    // Static gradient left to right, speed controls how much gradient changes
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
    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,  // Full gradient Chevron shapped scrolling left to right
    RGB_MATRIX_CYCLE_PINWHEEL,      // Full gradient spinning pinwheel around center of keyboard
    RGB_MATRIX_CYCLE_SPIRAL,        // Full gradient spinning spiral around center of keyboard
    RGB_MATRIX_DUAL_BEACON,         // Full gradient spinning around center of keyboard
    RGB_MATRIX_RAINBOW_BEACON,      // Full tighter gradient spinning around center of keyboard
    RGB_MATRIX_RAINBOW_PINWHEELS,   // Full dual gradients spinning two halves of keyboard
    RGB_MATRIX_FLOWER_BLOOMING,     // Full tighter gradient of first half scrolling left to right and second half scrolling right to left
    RGB_MATRIX_RAINDROPS,           // Randomly changes a single key's hue
    RGB_MATRIX_JELLYBEAN_RAINDROPS, // Randomly changes a single key's hue and saturation
    RGB_MATRIX_HUE_BREATHING,       // Hue shifts up a slight amount at the same time, then shifts back
    RGB_MATRIX_HUE_PENDULUM,        // Hue shifts up a slight amount in a wave to the right, then back to the left
    RGB_MATRIX_HUE_WAVE,            // Hue shifts up a slight amount and then back down in a wave to the right
    RGB_MATRIX_PIXEL_FRACTAL,       // Single hue fractal filled keys pulsing horizontally out to edges
    RGB_MATRIX_PIXEL_FLOW,          // Pulsing RGB flow along LED wiring with random hues
    RGB_MATRIX_PIXEL_RAIN,          // Randomly light keys with random hues
    RGB_MATRIX_TYPING_HEATMAP,      // How hot is your WPM!
    RGB_MATRIX_DIGITAL_RAIN,        // That famous computer simulation
    RGB_MATRIX_SOLID_REACTIVE_SIMPLE,   // Pulses keys hit to hue & value then fades value out
    RGB_MATRIX_SOLID_REACTIVE,      // Static single hue, pulses keys hit to shifted hue then fades to current hue
    RGB_MATRIX_SOLID_REACTIVE_WIDE,       // Hue & value pulse near a single key hit then fades value out
    RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE,  // Hue & value pulse near multiple key hits then fades value out
    RGB_MATRIX_SOLID_REACTIVE_CROSS,      // Hue & value pulse the same column and row of a single key hit then fades value out
    RGB_MATRIX_SOLID_REACTIVE_MULTICROSS, // Hue & value pulse the same column and row of multiple key hits then fades value out
    RGB_MATRIX_SOLID_REACTIVE_NEXUS,      // Hue & value pulse away on the same column and row of a single key hit then fades value out
    RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS, // Hue & value pulse away on the same column and row of multiple key hits then fades value out
    RGB_MATRIX_SPLASH,              // Full gradient & value pulse away from a single key hit then fades value out
    RGB_MATRIX_MULTISPLASH,         // Full gradient & value pulse away from multiple key hits then fades value out
    RGB_MATRIX_SOLID_SPLASH,        // Hue & value pulse away from a single key hit then fades value out
    RGB_MATRIX_SOLID_MULTISPLASH,   // Hue & value pulse away from multiple key hits then fades value out
    RGB_MATRIX_STARLIGHT,           // LEDs turn on and off at random at varying brightness, maintaining user set color
    RGB_MATRIX_STARLIGHT_SMOOTH,    // LEDs slowly increase and decrease in brightness randomly
    RGB_MATRIX_STARLIGHT_DUAL_HUE,  // LEDs turn on and off at random at varying brightness, modifies user set hue by +- 30
    RGB_MATRIX_STARLIGHT_DUAL_SAT,  // LEDs turn on and off at random at varying brightness, modifies user set saturation by +- 30
    RGB_MATRIX_RIVERFLOW,           // Modification to breathing animation, offset's animation depending on key location to simulate a river flowing
    RGB_MATRIX_EFFECT_MAX
};
```

You can enable a single effect by defining `ENABLE_[EFFECT_NAME]` in your `config.h`:


|Define                                                |Description                                   |
|------------------------------------------------------|----------------------------------------------|
|`#define ENABLE_RGB_MATRIX_ALPHAS_MODS`               |Enables `RGB_MATRIX_ALPHAS_MODS`              |
|`#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN`          |Enables `RGB_MATRIX_GRADIENT_UP_DOWN`         |
|`#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT`       |Enables `RGB_MATRIX_GRADIENT_LEFT_RIGHT`      |
|`#define ENABLE_RGB_MATRIX_BREATHING`                 |Enables `RGB_MATRIX_BREATHING`                |
|`#define ENABLE_RGB_MATRIX_BAND_SAT`                  |Enables `RGB_MATRIX_BAND_SAT`                 |
|`#define ENABLE_RGB_MATRIX_BAND_VAL`                  |Enables `RGB_MATRIX_BAND_VAL`                 |
|`#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT`         |Enables `RGB_MATRIX_BAND_PINWHEEL_SAT`        |
|`#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL`         |Enables `RGB_MATRIX_BAND_PINWHEEL_VAL`        |
|`#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT`           |Enables `RGB_MATRIX_BAND_SPIRAL_SAT`          |
|`#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL`           |Enables `RGB_MATRIX_BAND_SPIRAL_VAL`          |
|`#define ENABLE_RGB_MATRIX_CYCLE_ALL`                 |Enables `RGB_MATRIX_CYCLE_ALL`                |
|`#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT`          |Enables `RGB_MATRIX_CYCLE_LEFT_RIGHT`         |
|`#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN`             |Enables `RGB_MATRIX_CYCLE_UP_DOWN`            |
|`#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON`    |Enables `RGB_MATRIX_RAINBOW_MOVING_CHEVRON`   |
|`#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN`              |Enables `RGB_MATRIX_CYCLE_OUT_IN`             |
|`#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL`         |Enables `RGB_MATRIX_CYCLE_OUT_IN_DUAL`        |
|`#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL`            |Enables `RGB_MATRIX_CYCLE_PINWHEEL`           |
|`#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL`              |Enables `RGB_MATRIX_CYCLE_SPIRAL`             |
|`#define ENABLE_RGB_MATRIX_DUAL_BEACON`               |Enables `RGB_MATRIX_DUAL_BEACON`              |
|`#define ENABLE_RGB_MATRIX_RAINBOW_BEACON`            |Enables `RGB_MATRIX_RAINBOW_BEACON`           |
|`#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS`         |Enables `RGB_MATRIX_RAINBOW_PINWHEELS`        |
|`#define ENABLE_RGB_MATRIX_FLOWER_BLOOMING`           |Enables `RGB_MATRIX_FLOWER_BLOOMING`          |
|`#define ENABLE_RGB_MATRIX_RAINDROPS`                 |Enables `RGB_MATRIX_RAINDROPS`                |
|`#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS`       |Enables `RGB_MATRIX_JELLYBEAN_RAINDROPS`      |
|`#define ENABLE_RGB_MATRIX_HUE_BREATHING`             |Enables `RGB_MATRIX_HUE_BREATHING`            |
|`#define ENABLE_RGB_MATRIX_HUE_PENDULUM`              |Enables `RGB_MATRIX_HUE_PENDULUM`             |
|`#define ENABLE_RGB_MATRIX_HUE_WAVE`                  |Enables `RGB_MATRIX_HUE_WAVE `                |
|`#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL`             |Enables `RGB_MATRIX_PIXEL_FRACTAL`            |
|`#define ENABLE_RGB_MATRIX_PIXEL_FLOW`                |Enables `RGB_MATRIX_PIXEL_FLOW`               |
|`#define ENABLE_RGB_MATRIX_PIXEL_RAIN`                |Enables `RGB_MATRIX_PIXEL_RAIN`               |
|`#define ENABLE_RGB_MATRIX_STARLIGHT`                 |Enables `RGB_MATRIX_STARLIGHT`                |
|`#define ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH`          |Enables `RGB_MATRIX_STARLIGHT_SMOOTH`         |
|`#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE`        |Enables `RGB_MATRIX_STARLIGHT_DUAL_HUE`       |
|`#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT`        |Enables `RGB_MATRIX_STARLIGHT_DUAL_SAT`       |
|`#define ENABLE_RGB_MATRIX_RIVERFLOW`                 |Enables `RGB_MATRIX_RIVERFLOW`                |

|Framebuffer Defines                                   |Description                                   |
|------------------------------------------------------|----------------------------------------------|
|`#define ENABLE_RGB_MATRIX_TYPING_HEATMAP`            |Enables `RGB_MATRIX_TYPING_HEATMAP`           |
|`#define ENABLE_RGB_MATRIX_DIGITAL_RAIN`              |Enables `RGB_MATRIX_DIGITAL_RAIN`             |

::: tip
These modes introduce additional logic that can increase firmware size.
:::

|Reactive Defines                                    |Description                                   |
|------------------------------------------------------|----------------------------------------------|
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE`     |Enables `RGB_MATRIX_SOLID_REACTIVE_SIMPLE`    |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE`            |Enables `RGB_MATRIX_SOLID_REACTIVE`           |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE`       |Enables `RGB_MATRIX_SOLID_REACTIVE_WIDE`      |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE`  |Enables `RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE` |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS`      |Enables `RGB_MATRIX_SOLID_REACTIVE_CROSS`     |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS` |Enables `RGB_MATRIX_SOLID_REACTIVE_MULTICROSS`|
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS`      |Enables `RGB_MATRIX_SOLID_REACTIVE_NEXUS`     |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS` |Enables `RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS`|
|`#define ENABLE_RGB_MATRIX_SPLASH`                    |Enables `RGB_MATRIX_SPLASH`                   |
|`#define ENABLE_RGB_MATRIX_MULTISPLASH`               |Enables `RGB_MATRIX_MULTISPLASH`              |
|`#define ENABLE_RGB_MATRIX_SOLID_SPLASH`              |Enables `RGB_MATRIX_SOLID_SPLASH`             |
|`#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH`         |Enables `RGB_MATRIX_SOLID_MULTISPLASH`        |

::: tip
These modes introduce additional logic that can increase firmware size.
:::


### RGB Matrix Effect Typing Heatmap {#rgb-matrix-effect-typing-heatmap}

This effect will color the RGB matrix according to a heatmap of recently pressed keys. Whenever a key is pressed its "temperature" increases as well as that of its neighboring keys. The temperature of each key is then decreased automatically every 25 milliseconds by default.

In order to change the delay of temperature decrease define `RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS`:

```c
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
```

As heatmap uses the physical position of the leds set in the g_led_config, you may need to tweak the following options to get the best effect for your keyboard. Note the size of this grid is `224x64`.

Limit the distance the effect spreads to surrounding keys.

```c
#define RGB_MATRIX_TYPING_HEATMAP_SPREAD 40
```

Limit how hot surrounding keys get from each press.

```c
#define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16
```

Remove the spread effect entirely.

```c
#define RGB_MATRIX_TYPING_HEATMAP_SLIM
```

It's also possible to adjust the tempo of *heating up*. It's defined as the number of shades that are
increased on the [HSV scale](https://en.wikipedia.org/wiki/HSL_and_HSV). Decreasing this value increases
the number of keystrokes needed to fully heat up the key.

```c
#define RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP 32
```

### RGB Matrix Effect Solid Reactive {#rgb-matrix-effect-solid-reactive}

Solid reactive effects will pulse RGB light on key presses with user configurable hues. To enable gradient mode that will automatically change reactive color, add the following define:

```c
#define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
```

Gradient mode will loop through the color wheel hues over time and its duration can be controlled with the effect speed keycodes (`RM_SPDU`/`RM_SPDD`).

## Custom RGB Matrix Effects {#custom-rgb-matrix-effects}

By setting `RGB_MATRIX_CUSTOM_USER = yes` in `rules.mk`, new effects can be defined directly from your keymap or userspace, without having to edit any QMK core files. To declare new effects, create a `rgb_matrix_user.inc` file in the user keymap directory or userspace folder.

::: tip
Hardware maintainers who want to limit custom effects to a specific keyboard can create a `rgb_matrix_kb.inc` file in the root of the keyboard directory, and add `RGB_MATRIX_CUSTOM_KB = yes` to the keyboard level `rules.mk`.
:::

```c
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
  return rgb_matrix_check_finished_leds(led_max);
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
  return rgb_matrix_check_finished_leds(led_max);
}
static bool my_cool_effect2(effect_params_t* params) {
  if (params->init) my_cool_effect2_complex_init(params);
  return my_cool_effect2_complex_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
```

To switch to your custom effect programmatically, simply call `rgb_matrix_mode()` and prepend `RGB_MATRIX_CUSTOM_` to the effect name you specified in `RGB_MATRIX_EFFECT()`. For example, an effect declared as `RGB_MATRIX_EFFECT(my_cool_effect)` would be referenced with:

```c
rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_cool_effect);
```

For inspiration and examples, check out the built-in effects under `quantum/rgb_matrix/animations/`.


## Colors {#colors}

These are shorthands to popular colors. The `RGB` ones can be passed to the `setrgb` functions, while the `HSV` ones to the `sethsv` functions.

|RGB                  |HSV                  |
|---------------------|---------------------|
|`RGB_AZURE`          |`HSV_AZURE`          |
|`RGB_BLACK`/`RGB_OFF`|`HSV_BLACK`/`HSV_OFF`|
|`RGB_BLUE`           |`HSV_BLUE`           |
|`RGB_CHARTREUSE`     |`HSV_CHARTREUSE`     |
|`RGB_CORAL`          |`HSV_CORAL`          |
|`RGB_CYAN`           |`HSV_CYAN`           |
|`RGB_GOLD`           |`HSV_GOLD`           |
|`RGB_GOLDENROD`      |`HSV_GOLDENROD`      |
|`RGB_GREEN`          |`HSV_GREEN`          |
|`RGB_MAGENTA`        |`HSV_MAGENTA`        |
|`RGB_ORANGE`         |`HSV_ORANGE`         |
|`RGB_PINK`           |`HSV_PINK`           |
|`RGB_PURPLE`         |`HSV_PURPLE`         |
|`RGB_RED`            |`HSV_RED`            |
|`RGB_SPRINGGREEN`    |`HSV_SPRINGGREEN`    |
|`RGB_TEAL`           |`HSV_TEAL`           |
|`RGB_TURQUOISE`      |`HSV_TURQUOISE`      |
|`RGB_WHITE`          |`HSV_WHITE`          |
|`RGB_YELLOW`         |`HSV_YELLOW`         |

These are defined in [`color.h`](https://github.com/qmk/qmk_firmware/blob/master/quantum/color.h). Feel free to add to this list!


## Naming

If you wish to be able to use the name of an effect in your code -- say for a display indicator -- then you can enable the function `rgb_matrix_get_mode_name` in the following manner:

In your keymap's `config.h`:
```c
#define RGB_MATRIX_MODE_NAME_ENABLE
```

In your `keymap.c`
```c
const char* effect_name = rgb_matrix_get_mode_name(rgb_matrix_get_mode());
// do something with `effect_name`, like `oled_write_ln(effect_name, false);`
```

::: info
`rgb_matrix_get_mode_name()` is not enabled by default as it increases the amount of flash memory used by the firmware based on the number of effects enabled.
:::


## Additional `config.h` Options {#additional-configh-options}

```c
#define RGB_MATRIX_MODE_NAME_ENABLE // enables rgb_matrix_get_mode_name()
#define RGB_MATRIX_KEYRELEASES // reactive effects respond to keyreleases (instead of keypresses)
#define RGB_MATRIX_TIMEOUT 0 // number of milliseconds to wait until rgb automatically turns off
#define RGB_MATRIX_SLEEP // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_DEFAULT_ON true // Sets the default enabled state, if none has been set
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT // Sets the default mode, if none has been set
#define RGB_MATRIX_DEFAULT_HUE 0 // Sets the default hue value, if none has been set
#define RGB_MATRIX_DEFAULT_SAT 255 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#define RGB_MATRIX_DEFAULT_SPD 127 // Sets the default animation speed, if none has been set
#define RGB_MATRIX_HUE_STEP 8 // The value by which to increment the hue per adjustment action
#define RGB_MATRIX_SAT_STEP 16 // The value by which to increment the saturation per adjustment action
#define RGB_MATRIX_VAL_STEP 16 // The value by which to increment the brightness per adjustment action
#define RGB_MATRIX_SPD_STEP 16 // The value by which to increment the animation speed per adjustment action
#define RGB_MATRIX_DEFAULT_FLAGS LED_FLAG_ALL // Sets the default LED flags, if none has been set
#define RGB_MATRIX_SPLIT { X, Y } // (Optional) For split keyboards, the number of LEDs connected on each half. X = left, Y = Right.
                                  // If reactive effects are enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
#define RGB_TRIGGER_ON_KEYDOWN      // Triggers RGB keypress events on key down. This makes RGB control feel more responsive. This may cause RGB to not function properly on some boards
```

## EEPROM storage {#eeprom-storage}

The EEPROM for it is currently shared with the LED Matrix system (it's generally assumed only one feature would be used at a time).

## Callbacks {#callbacks}

### Indicators {#indicators}

If you want to set custom indicators, such as an LED for Caps Lock, or layer indication, then you can use the `rgb_matrix_indicators_kb` function on the keyboard level source file, or `rgb_matrix_indicators_user` function in the user `keymap.c`.
```c
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    rgb_matrix_set_color(index, red, green, blue);
    return true;
}
```

In addition, there are the advanced indicator functions.  These are aimed at those with heavily customized displays, where rendering every LED per cycle is expensive.  Such as some of the "drashna" layouts.  This includes a special macro to help make this easier to use: `RGB_MATRIX_INDICATOR_SET_COLOR(i, r, g, b)`.

```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    RGB_MATRIX_INDICATOR_SET_COLOR(index, red, green, blue);
    return false;
}
```

### Indicator Examples {#indicator-examples}

Caps Lock indicator on alphanumeric flagged keys:
```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }
    return false;
}
```

Layer indicator on all keys:
```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 2:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case 1:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            default:
                break;
        }
    }
    return false;
}
```

Layer indicator only on keys with configured keycodes:
```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
            }
        }
    }
    return false;
}
```

::: tip
Split keyboards will require layer state data syncing with `#define SPLIT_LAYER_STATE_ENABLE`. See [Data Sync Options](split_keyboard#data-sync-options) for more details.
:::

#### Examples {#indicator-examples-2}

This example sets the modifiers to be a specific color based on the layer state.  You can use a switch case here, instead, if you would like.  This uses HSV and then converts to RGB, because this allows the brightness to be limited (important when using the WS2812 driver).

```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    hsv_t hsv = {0, 255, 255};

    if (get_highest_layer(layer_state|default_layer_state) == 2) {
        hsv = (hsv_t){130, 255, 255};
    } else {
        hsv = (hsv_t){30, 255, 255};
    }

    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    rgb_t rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return false;
}
```

If you want to indicate a Host LED status (caps lock, num lock, etc), you can use something like this to light up the caps lock key:

```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(5, 255, 255, 255); // assuming caps lock is at led #5
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(5, 0, 0, 0);
    }
    return false;
}
```

::: tip
RGB indicators on split keyboards will require state information synced to the slave half (e.g. `#define SPLIT_LAYER_STATE_ENABLE`). See [data sync options](split_keyboard#data-sync-options) for more details.
:::

#### Indicators without RGB Matrix Effect

If you want to just use RGB indicators without RGB matrix effect, it is not possible to disable the latter because toggling RGB off will disable everything. You can workaround it with solid effect and colors off using this init function:
```c
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}
```

## API {#api}

### `void rgb_matrix_toggle(void)` {#api-rgb-matrix-toggle}

Toggle RGB Matrix on or off.

---

### `void rgb_matrix_toggle_noeeprom(void)` {#api-rgb-matrix-toggle-noeeprom}

Toggle RGB Matrix on or off. New state is not written to EEPROM.

---

### `void rgb_matrix_enable(void)` {#api-rgb-matrix-enable}

Turn RGB Matrix on.

---

### `void rgb_matrix_enable_noeeprom(void)` {#api-rgb-matrix-enable-noeeprom}

Turn RGB Matrix on. New state is not written to EEPROM.

---

### `void rgb_matrix_disable(void)` {#api-rgb-matrix-disable}

Turn RGB Matrix off.

---

### `void rgb_matrix_disable_noeeprom(void)` {#api-rgb-matrix-disable-noeeprom}

Turn RGB Matrix off. New state is not written to EEPROM.

---

### `bool rgb_matrix_is_enabled(void)` {#api-rgb-matrix-is-enabled}

Get the current enabled state of RGB Matrix.

#### Return Value {#api-rgb-matrix-is-enabled-return}

`true` if RGB Matrix is enabled.

---

### `void rgb_matrix_set_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b)` {#api-rgb-matrix-set-color}

Set the color of a single LED.

This function can only be run from within an effect or indicator callback, otherwise the currently running animation will simply overwrite it on the next frame.

#### Arguments {#api-rgb-matrix-set-color-arguments}

 - `uint8_t index`  
   The LED index, from 0 to `RGB_MATRIX_LED_COUNT - 1`.
 - `uint8_t r`  
   The red value to set.
 - `uint8_t g`  
   The green value to set.
 - `uint8_t b`  
   The blue value to set.

---

### `void rgb_matrix_set_color_all(uint8_t r, uint8_t g, uint8_t b)` {#api-rgb-matrix-set-color-all}

Set the color of all LEDs.

This function can only be run from within an effect or indicator callback, otherwise the currently running animation will simply overwrite it on the next frame.

#### Arguments {#api-rgb-matrix-set-color-all-arguments}

 - `uint8_t r`  
   The red value to set.
 - `uint8_t g`  
   The green value to set.
 - `uint8_t b`  
   The blue value to set.

---

### `void rgb_matrix_mode(uint8_t mode)` {#api-rgb-matrix-mode}

Set the currently running effect.

#### Arguments {#api-rgb-matrix-mode-arguments}

 - `uint8_t mode`  
   The effect to switch to.

---

### `void rgb_matrix_mode_noeeprom(uint8_t mode)` {#api-rgb-matrix-mode-noeeprom}

Set the currently running effect. New state is not written to EEPROM.

#### Arguments {#api-rgb-matrix-mode-noeeprom-arguments}

 - `uint8_t mode`  
   The effect to switch to.

---

### `void rgb_matrix_step(void)` {#api-rgb-matrix-step}

Move to the next enabled effect.

---

### `void rgb_matrix_step_noeeprom(void)` {#api-rgb-matrix-step-noeeprom}

Move to the next enabled effect. New state is not written to EEPROM.

---

### `void rgb_matrix_step_reverse(void)` {#api-rgb-matrix-step-reverse}

Move to the previous enabled effect.

---

### `void rgb_matrix_step_reverse_noeeprom(void)` {#api-rgb-matrix-step-reverse-noeeprom}

Move to the previous enabled effect. New state is not written to EEPROM.

---

### `uint8_t rgb_matrix_get_mode(void)` {#api-rgb-matrix-get-mode}

Get the currently running effect.

#### Return Value {#api-rgb-matrix-get-mode-return}

The index of the currently running effect.

---

### `void rgb_matrix_increase_hue(void)` {#api-rgb-matrix-increase-hue}

Increase the global effect hue.

---

### `void rgb_matrix_increase_hue_noeeprom(void)` {#api-rgb-matrix-increase-hue-noeeprom}

Increase the global effect hue. New state is not written to EEPROM.

---

### `void rgb_matrix_decrease_hue(void)` {#api-rgb-matrix-decrease-hue}

Decrease the global effect hue.

---

### `void rgb_matrix_decrease_hue_noeeprom(void)` {#api-rgb-matrix-decrease-hue-noeeprom}

Decrease the global effect hue. New state is not written to EEPROM.

---

### `uint8_t rgb_matrix_get_hue(void)` {#api-rgb-matrix-get-hue}

Get the current global effect hue.

#### Return Value {#api-rgb-matrix-get-hue-return}

The current hue value, from 0 to 255.

---

### `void rgb_matrix_increase_sat(void)` {#api-rgb-matrix-increase-sat}

Increase the global effect saturation.

---

### `void rgb_matrix_increase_sat_noeeprom(void)` {#api-rgb-matrix-increase-sat-noeeprom}

Increase the global effect saturation. New state is not written to EEPROM.

---

### `void rgb_matrix_decrease_sat(void)` {#api-rgb-matrix-decrease-sat}

Decrease the global effect saturation.

---

### `void rgb_matrix_decrease_sat_noeeprom(void)` {#api-rgb-matrix-decrease-sat-noeeprom}

Decrease the global effect saturation. New state is not written to EEPROM.

---

### `uint8_t rgb_matrix_get_sat(void)` {#api-rgb-matrix-get-sat}

Get the current global effect saturation.

#### Return Value {#api-rgb-matrix-get-sat-return}

The current saturation value, from 0 to 255.

---

### `void rgb_matrix_increase_val(void)` {#api-rgb-matrix-increase-val}

Increase the global effect value (brightness).

---

### `void rgb_matrix_increase_val_noeeprom(void)` {#api-rgb-matrix-increase-val-noeeprom}

Increase the global effect value (brightness). New state is not written to EEPROM.

---

### `void rgb_matrix_decrease_val(void)` {#api-rgb-matrix-decrease-val}

Decrease the global effect value (brightness).

---

### `void rgb_matrix_decrease_val_noeeprom(void)` {#api-rgb-matrix-decrease-val-noeeprom}

Decrease the global effect value (brightness). New state is not written to EEPROM.

---

### `uint8_t rgb_matrix_get_val(void)` {#api-rgb-matrix-get-val}

Get the current global effect value (brightness).

#### Return Value {#api-rgb-matrix-get-val-return}

The current brightness value, from 0 to 255.

---

### `void rgb_matrix_increase_speed(void)` {#api-rgb-matrix-increase-speed}

Increase the effect speed.

---

### `void rgb_matrix_increase_speed_noeeprom(void)` {#api-rgb-matrix-increase-speed-noeeprom}

Increase the effect speed. New state is not written to EEPROM.

---

### `void rgb_matrix_decrease_speed(void)` {#api-rgb-matrix-decrease-speed}

Decrease the effect speed.

---

### `void rgb_matrix_decrease_speed_noeeprom(void)` {#api-rgb-matrix-decrease-speed-noeeprom}

Decrease the effect speed. New state is not written to EEPROM.

---

### `void rgb_matrix_set_speed(uint8_t speed)` {#api-rgb-matrix-set-speed}

Set the effect speed.

#### Arguments {#api-rgb-matrix-set-speed-arguments}

 - `uint8_t speed`  
   The new speed to set, from 0 to 255.

---

### `void rgb_matrix_set_speed_noeeprom(uint8_t speed)` {#api-rgb-matrix-set-speed-noeeprom}

Set the effect speed. New state is not written to EEPROM.

#### Arguments {#api-rgb-matrix-set-speed-noeeprom-arguments}

 - `uint8_t speed`  
   The new speed to set, from 0 to 255.

---

### `uint8_t rgb_matrix_get_speed(void)` {#api-rgb-matrix-get-speed}

Get the current effect speed.

#### Return Value {#api-rgb-matrix-get-speed-return}

The current effect speed, from 0 to 255.

---

### `void rgb_matrix_sethsv(uint8_t h, uint8_t s, uint8_t v)` {#api-rgb-matrix-sethsv}

Set the global effect hue, saturation, and value (brightness).

### Arguments {#api-rgb-matrix-sethsv-arguments}

 - `uint8_t h`  
   The hue to set, from 0 to 255.
 - `uint8_t s`  
   The saturation to set, from 0 to 255.
 - `uint8_t v`  
   The value (brightness) to set, from 0 to 255.

---

### `void rgb_matrix_sethsv_noeeprom(uint8_t h, uint8_t s, uint8_t v)` {#api-rgb-matrix-sethsv-noeeprom}

Set the global effect hue, saturation, and value (brightness). New state is not written to EEPROM.

#### Arguments {#api-rgb-matrix-sethsv-noeeprom-arguments}

 - `uint8_t h`  
   The hue to set, from 0 to 255.
 - `uint8_t s`  
   The saturation to set, from 0 to 255.
 - `uint8_t v`  
   The value (brightness) to set, from 0 to 255.

---

### `hsv_t rgb_matrix_get_hsv(void)` {#api-rgb-matrix-get-hsv}

Get the current global effect hue, saturation, and value (brightness).

#### Return Value {#api-rgb-matrix-get-hsv-return}

The current effect HSV as an `hsv_t` struct.

---

### `void rgb_matrix_reload_from_eeprom(void)` {#api-rgb-matrix-reload-from-eeprom}

Reload the effect configuration (enabled, mode and color) from EEPROM.

---

### `bool rgb_matrix_get_suspend_state(void)` {#api-rgb-matrix-get-suspend-state}

Get the current suspend state of RGB Matrix.

#### Return Value {#api-rgb-matrix-get-suspend-state-return}

`true` if RGB Matrix is currently in the suspended state.

---

### `bool rgb_matrix_indicators_kb(void)` {#api-rgb-matrix-indicators-kb}

Keyboard-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.

#### Return Value {#api-rgb-matrix-indicators-kb-return}

Currently unused.

---

### `bool rgb_matrix_indicators_user(void)` {#api-rgb-matrix-indicators-user}

Keymap-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.

#### Return Value {#api-rgb-matrix-indicators-user-return}

`true` to continue running the keyboard-level callback.

---

### `bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)` {#api-rgb-matrix-indicators-advanced-kb}

Keyboard-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.

### Arguments {#api-rgb-matrix-indicators-advanced-kb-arguments}

 - `uint8_t led_min`  
   The index of the first LED in this batch.
 - `uint8_t led_max`  
   The index of the last LED in this batch.

#### Return Value {#api-rgb-matrix-indicators-advanced-kb-return}

Currently unused.

---

### `bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)` {#api-rgb-matrix-indicators-advanced-user}

Keymap-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.

### Arguments {#api-rgb-matrix-indicators-advanced-user-arguments}

 - `uint8_t led_min`  
   The index of the first LED in this batch.
 - `uint8_t led_max`  
   The index of the last LED in this batch.

#### Return Value {#api-rgb-matrix-indicators-advanced-user-return}

`true` to continue running the keyboard-level callback.
