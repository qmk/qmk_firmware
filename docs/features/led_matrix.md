# LED Matrix Lighting {#led-matrix-lighting}

This feature allows you to use LED matrices driven by external drivers. It hooks into the backlight system so you can use the same keycodes as backlighting to control it.

If you want to use RGB LED's you should use the [RGB Matrix Subsystem](rgb_matrix) instead.

## Driver Configuration {#driver-configuration}

LED Matrix is an abstraction layer on top of an underlying LED driver API. The list of supported LED drivers is below; see the respective documentation for information on how to configure the driver.

|Driver                               |Max LEDs|
|-------------------------------------|--------|
|[IS31FL3218](../drivers/is31fl3218)  |18      |
|[IS31FL3236](../drivers/is31fl3236)  |36      |
|[IS31FL3729](../drivers/is31fl3729)  |135     |
|[IS31FL3731](../drivers/is31fl3731)  |144     |
|[IS31FL3733](../drivers/is31fl3733)  |192     |
|[IS31FL3736](../drivers/is31fl3736)  |96      |
|[IS31FL3737](../drivers/is31fl3737)  |144     |
|[IS31FL3741](../drivers/is31fl3741)  |351     |
|[IS31FL3742A](../drivers/is31fl3742a)|180     |
|[IS31FL3743A](../drivers/is31fl3743a)|198     |
|[IS31FL3745](../drivers/is31fl3745)  |144     |
|[IS31FL3746A](../drivers/is31fl3746a)|72      |
|[SNLED27351](../drivers/snled27351)  |192     |

To assign the LED Matrix driver, add the following to your `rules.mk`, for example:

```make
LED_MATRIX_DRIVER = is31fl3218
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

As mentioned earlier, the center of the keyboard by default is expected to be `{ 112, 32 }`, but this can be changed if you want to more accurately calculate the LED's physical `{ x, y }` positions. Keyboard designers can implement `#define LED_MATRIX_CENTER { 112, 32 }` in their config.h file with the new center point of the keyboard, or where they want it to be allowing more possibilities for the `{ x, y }` values. Do note that the maximum value for x or y is 255, and the recommended maximum is 224 as this gives animations runoff room before they reset.

`// LED Index to Flag` is a bitmask, whether or not a certain LEDs is of a certain type. It is recommended that LEDs are set to only 1 type.

## Flags {#flags}

|Define                      |Value |Description                                      |
|----------------------------|------|-------------------------------------------------|
|`HAS_FLAGS(bits, flags)`    |*n/a* |Evaluates to `true` if `bits` has all `flags` set|
|`HAS_ANY_FLAGS(bits, flags)`|*n/a* |Evaluates to `true` if `bits` has any `flags` set|
|`LED_FLAG_NONE`             |`0x00`|If this LED has no flags                         |
|`LED_FLAG_ALL`              |`0xFF`|If this LED has all flags                        |
|`LED_FLAG_MODIFIER`         |`0x01`|If the LED is on a modifier key                  |
|`LED_FLAG_KEYLIGHT`         |`0x04`|If the LED is for key backlight                  |
|`LED_FLAG_INDICATOR`        |`0x08`|If the LED is for keyboard state indication      |

## Keycodes {#keycodes}

|Key                            |Aliases  |Description                        |
|-------------------------------|---------|-----------------------------------|
|`QK_LED_MATRIX_ON`             |`LM_ON`  |Turn on LED Matrix                 |
|`QK_LED_MATRIX_OFF`            |`LM_OFF` |Turn off LED Matrix                |
|`QK_LED_MATRIX_TOGGLE`         |`LM_TOGG`|Toggle LED Matrix on or off        |
|`QK_LED_MATRIX_MODE_NEXT`      |`LM_NEXT`|Cycle through animations           |
|`QK_LED_MATRIX_MODE_PREVIOUS`  |`LM_PREV`|Cycle through animations in reverse|
|`QK_LED_MATRIX_BRIGHTNESS_UP`  |`LM_BRIU`|Increase the brightness level      |
|`QK_LED_MATRIX_BRIGHTNESS_DOWN`|`LM_BRID`|Decrease the brightness level      |
|`QK_LED_MATRIX_SPEED_UP`       |`LM_SPDU`|Increase the animation speed       |
|`QK_LED_MATRIX_SPEED_DOWN`     |`LM_SPDD`|Decrease the animation speed       |

## LED Matrix Effects {#led-matrix-effects}

These are the effects that are currently available:

```c
enum led_matrix_effects {
    LED_MATRIX_NONE = 0,
    LED_MATRIX_SOLID = 1,           // Static single val, no speed support
    LED_MATRIX_ALPHAS_MODS,         // Static dual val, speed is val for LEDs marked as modifiers
    LED_MATRIX_BREATHING,           // Cycling brightness animation
    LED_MATRIX_BAND,                // Band fading brightness scrolling left to right
    LED_MATRIX_BAND_PINWHEEL,       // 3 blade spinning pinwheel fades brightness
    LED_MATRIX_BAND_SPIRAL,         // Spinning spiral fades brightness
    LED_MATRIX_CYCLE_LEFT_RIGHT,    // Full gradient scrolling left to right
    LED_MATRIX_CYCLE_UP_DOWN,       // Full gradient scrolling top to bottom
    LED_MATRIX_CYCLE_OUT_IN,        // Full gradient scrolling out to in
    LED_MATRIX_DUAL_BEACON,         // Full gradient spinning around center of keyboard
    LED_MATRIX_SOLID_REACTIVE_SIMPLE,   // Pulses keys hit then fades out
    LED_MATRIX_SOLID_REACTIVE_WIDE,       // Value pulses near a single key hit then fades out
    LED_MATRIX_SOLID_REACTIVE_MULTIWIDE,  // Value pulses near multiple key hits then fades out
    LED_MATRIX_SOLID_REACTIVE_CROSS,      // Value pulses the same column and row of a single key hit then fades out
    LED_MATRIX_SOLID_REACTIVE_MULTICROSS, // Value pulses the same column and row of multiple key hits then fades out
    LED_MATRIX_SOLID_REACTIVE_NEXUS,      // Value pulses away on the same column and row of a single key hit then fades out
    LED_MATRIX_SOLID_REACTIVE_MULTINEXUS, // Value pulses away on the same column and row of multiple key hits then fades out
    LED_MATRIX_SOLID_SPLASH,             // Value pulses away from a single key hit then fades out
    LED_MATRIX_SOLID_MULTISPLASH,        // Value pulses away from multiple key hits then fades out
    LED_MATRIX_WAVE_LEFT_RIGHT,           // Sine wave scrolling from left to right
    LED_MATRIX_WAVE_UP_DOWN,              // Sine wave scrolling from up to down
    LED_MATRIX_EFFECT_MAX
};
```

You can enable a single effect by defining `ENABLE_[EFFECT_NAME]` in your `config.h`:


|Define                                                 |Description                                   |
|-------------------------------------------------------|----------------------------------------------|
|`#define ENABLE_LED_MATRIX_ALPHAS_MODS`                |Enables `LED_MATRIX_ALPHAS_MODS`              |
|`#define ENABLE_LED_MATRIX_BREATHING`                  |Enables `LED_MATRIX_BREATHING`                |
|`#define ENABLE_LED_MATRIX_BAND`                       |Enables `LED_MATRIX_BAND`                     |
|`#define ENABLE_LED_MATRIX_BAND_PINWHEEL`              |Enables `LED_MATRIX_BAND_PINWHEEL`            |
|`#define ENABLE_LED_MATRIX_BAND_SPIRAL`                |Enables `LED_MATRIX_BAND_SPIRAL`              |
|`#define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT`           |Enables `LED_MATRIX_CYCLE_LEFT_RIGHT`         |
|`#define ENABLE_LED_MATRIX_CYCLE_UP_DOWN`              |Enables `LED_MATRIX_CYCLE_UP_DOWN`            |
|`#define ENABLE_LED_MATRIX_CYCLE_OUT_IN`               |Enables `LED_MATRIX_CYCLE_OUT_IN`             |
|`#define ENABLE_LED_MATRIX_DUAL_BEACON`                |Enables `LED_MATRIX_DUAL_BEACON`              |
|`#define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT`            |Enables `LED_MATRIX_WAVE_LEFT_RIGHT`          |
|`#define ENABLE_LED_MATRIX_WAVE_UP_DOWN`               |Enables `LED_MATRIX_WAVE_UP_DOWN`             |

|Reactive Defines                                       |Description                                   |
|-------------------------------------------------------|----------------------------------------------|
|`#define ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE`      |Enables `LED_MATRIX_SOLID_REACTIVE_SIMPLE`    |
|`#define ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE`        |Enables `LED_MATRIX_SOLID_REACTIVE_WIDE`      |
|`#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE`   |Enables `LED_MATRIX_SOLID_REACTIVE_MULTIWIDE` |
|`#define ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS`       |Enables `LED_MATRIX_SOLID_REACTIVE_CROSS`     |
|`#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS`  |Enables `LED_MATRIX_SOLID_REACTIVE_MULTICROSS`|
|`#define ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS`       |Enables `LED_MATRIX_SOLID_REACTIVE_NEXUS`     |
|`#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS`  |Enables `LED_MATRIX_SOLID_REACTIVE_MULTINEXUS`|
|`#define ENABLE_LED_MATRIX_SOLID_SPLASH`               |Enables `LED_MATRIX_SOLID_SPLASH`             |
|`#define ENABLE_LED_MATRIX_SOLID_MULTISPLASH`          |Enables `LED_MATRIX_SOLID_MULTISPLASH`        |

::: tip
These modes introduce additional logic that can increase firmware size.
:::

## Custom LED Matrix Effects {#custom-led-matrix-effects}

By setting `LED_MATRIX_CUSTOM_USER = yes` in `rules.mk`, new effects can be defined directly from your keymap or userspace, without having to edit any QMK core files. To declare new effects, create a `led_matrix_user.inc` file in the user keymap directory or userspace folder.

::: tip
Hardware maintainers who want to limit custom effects to a specific keyboard can create a `led_matrix_kb.inc` file in the root of the keyboard directory, and add `LED_MATRIX_CUSTOM_KB = yes` to the keyboard level `rules.mk`.
:::

```c
// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the LED_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
LED_MATRIX_EFFECT(my_cool_effect)
LED_MATRIX_EFFECT(my_cool_effect2)

// Step 2.
// Define effects inside the `LED_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t* params) {
  LED_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    led_matrix_set_value(i, 0xFF);
  }
  return led_matrix_check_finished_leds(led_max);
}

// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
static uint8_t some_global_state;
static void my_cool_effect2_complex_init(effect_params_t* params) {
  some_global_state = 1;
}
static bool my_cool_effect2_complex_run(effect_params_t* params) {
  LED_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    led_matrix_set_value(i, some_global_state++);
  }
  return led_matrix_check_finished_leds(led_max);
}
static bool my_cool_effect2(effect_params_t* params) {
  if (params->init) my_cool_effect2_complex_init(params);
  return my_cool_effect2_complex_run(params);
}

#endif // LED_MATRIX_CUSTOM_EFFECT_IMPLS
```

To switch to your custom effect programmatically, simply call `led_matrix_mode()` and prepend `LED_MATRIX_CUSTOM_` to the effect name your specified in `LED_MATRIX_EFFECT()`. For example, an effect declared as `LED_MATRIX_EFFECT(my_cool_effect)` would be referenced with:

```c
led_matrix_mode(LED_MATRIX_CUSTOM_my_cool_effect);
```

For inspiration and examples, check out the built-in effects under `quantum/led_matrix/animations/`.


## Additional `config.h` Options {#additional-configh-options}

```c
#define LED_MATRIX_KEYRELEASES // reactive effects respond to keyreleases (instead of keypresses)
#define LED_MATRIX_TIMEOUT 0 // number of milliseconds to wait until led automatically turns off
#define LED_MATRIX_SLEEP // turn off effects when suspended
#define LED_MATRIX_LED_PROCESS_LIMIT (LED_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define LED_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define LED_MATRIX_MAXIMUM_BRIGHTNESS 255 // limits maximum brightness of LEDs
#define LED_MATRIX_DEFAULT_ON true // Sets the default enabled state, if none has been set
#define LED_MATRIX_DEFAULT_MODE LED_MATRIX_SOLID // Sets the default mode, if none has been set
#define LED_MATRIX_DEFAULT_VAL LED_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#define LED_MATRIX_DEFAULT_SPD 127 // Sets the default animation speed, if none has been set
#define LED_MATRIX_VAL_STEP 8 // The value by which to increment the brightness per adjustment action
#define LED_MATRIX_SPD_STEP 16 // The value by which to increment the animation speed per adjustment action
#define LED_MATRIX_DEFAULT_FLAGS LED_FLAG_ALL // Sets the default LED flags, if none has been set
#define LED_MATRIX_SPLIT { X, Y }   // (Optional) For split keyboards, the number of LEDs connected on each half. X = left, Y = Right.
                                    // If reactive effects are enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
```

## EEPROM storage {#eeprom-storage}

The EEPROM for it is currently shared with the RGB Matrix system (it's generally assumed only one feature would be used at a time).

## Callbacks {#callbacks}

### Indicators {#indicators}

If you want to set custom indicators, such as an LED for Caps Lock, or layer indication, then you can use the `led_matrix_indicators_kb` function on the keyboard level source file, or `led_matrix_indicators_user` function in the user `keymap.c`.
```c
bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) {
        return false;
    }
    led_matrix_set_value(index, value);
    return true;
}
```

In addition, there are the advanced indicator functions.  These are aimed at those with heavily customized displays, where rendering every LED per cycle is expensive.  This includes a special macro to help make this easier to use: `LED_MATRIX_INDICATOR_SET_VALUE(i, v)`.

```c
void led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    LED_MATRIX_INDICATOR_SET_VALUE(index, value);
    return false;
}
```

## API {#api}

### `void led_matrix_toggle(void)` {#api-led-matrix-toggle}

Toggle LED Matrix on or off.

---

### `void led_matrix_toggle_noeeprom(void)` {#api-led-matrix-toggle-noeeprom}

Toggle LED Matrix on or off. New state is not written to EEPROM.

---

### `void led_matrix_enable(void)` {#api-led-matrix-enable}

Turn LED Matrix on.

---

### `void led_matrix_enable_noeeprom(void)` {#api-led-matrix-enable-noeeprom}

Turn LED Matrix on. New state is not written to EEPROM.

---

### `void led_matrix_disable(void)` {#api-led-matrix-disable}

Turn LED Matrix off.

---

### `void led_matrix_disable_noeeprom(void)` {#api-led-matrix-disable-noeeprom}

Turn LED Matrix off. New state is not written to EEPROM.

---

### `bool led_matrix_is_enabled(void)` {#api-led-matrix-is-enabled}

Get the current enabled state of LED Matrix.

#### Return Value {#api-led-matrix-is-enabled-return}

`true` if LED Matrix is enabled.

---

### `void led_matrix_set_value(uint8_t index, uint8_t v)` {#led-matrix-set-value}

Set the brightness of a single LED.

This function can only be run from within an effect or indicator callback, otherwise the currently running animation will simply overwrite it on the next frame.

#### Arguments {#api-led-matrix-set-value-arguments}

 - `uint8_t index`  
   The LED index, from 0 to `LED_MATRIX_LED_COUNT - 1`.
 - `uint8_t v`  
   The brightness value to set.

---

### `void led_matrix_set_value_all(uint8_t v)` {#api-led-matrix-set-value-all}

Set the brightness of all LEDs.

This function can only be run from within an effect or indicator callback, otherwise the currently running animation will simply overwrite it on the next frame.

#### Arguments {#api-led-matrix-set-value-all-arguments}

 - `uint8_t v`  
   The brightness value to set.

---

### `void led_matrix_mode(uint8_t mode)` {#api-led-matrix-mode}

Set the currently running effect.

#### Arguments {#api-led-matrix-mode-arguments}

 - `uint8_t mode`  
   The effect to switch to.

---

### `void led_matrix_mode_noeeprom(uint8_t mode)` {#api-led-matrix-mode-noeeprom}

Set the currently running effect. New state is not written to EEPROM.

#### Arguments {#api-led-matrix-mode-noeeprom-arguments}

 - `uint8_t mode`  
   The effect to switch to.

---

### `void led_matrix_step(void)` {#api-led-matrix-step}

Move to the next enabled effect.

---

### `void led_matrix_step_noeeprom(void)` {#api-led-matrix-step-noeeprom}

Move to the next enabled effect. New state is not written to EEPROM.

---

### `void led_matrix_step_reverse(void)` {#api-led-matrix-step-reverse}

Move to the previous enabled effect.

---

### `void led_matrix_step_reverse_noeeprom(void)` {#api-led-matrix-step-reverse-noeeprom}

Move to the previous enabled effect. New state is not written to EEPROM.

---

### `uint8_t led_matrix_get_mode(void)` {#api-led-matrix-get-mode}

Get the currently running effect.

#### Return Value {#api-led-matrix-get-mode-return}

The index of the currently running effect.

---

### `void val_matrix_increase_val(void)` {#api-led-matrix-increase-val}

Increase the global effect brightness.

---

### `void led_matrix_increase_val_noeeprom(void)` {#api-led-matrix-increase-val-noeeprom}

Increase the global effect brightness. New state is not written to EEPROM.

---

### `void led_matrix_decrease_val(void)` {#api-led-matrix-decrease-val}

Decrease the global effect brightness.

---

### `void led_matrix_decrease_val_noeeprom(void)` {#api-led-matrix-decrease-val-noeeprom}

Decrease the global effect brightness. New state is not written to EEPROM.

---

### `uint8_t led_matrix_get_val(void)` {#api-led-matrix-get-val}

Get the current global effect brightness.

#### Return Value {#api-led-matrix-get-val-return}

The current brightness value, from 0 to 255.

---

### `void led_matrix_increase_speed(void)` {#api-led-matrix-increase-speed}

Increase the effect speed.

---

### `void led_matrix_increase_speed_noeeprom(void)` {#api-led-matrix-increase-speed-noeeprom}

Increase the effect speed. New state is not written to EEPROM.

---

### `void led_matrix_decrease_speed(void)` {#api-led-matrix-decrease-speed}

Decrease the effect speed.

---

### `void led_matrix_decrease_speed_noeeprom(void)` {#api-led-matrix-decrease-speed-noeeprom}

Decrease the effect speed. New state is not written to EEPROM.

---

### `void led_matrix_set_speed(uint8_t speed)` {#api-led-matrix-set-speed}

Set the effect speed.

#### Arguments {#api-led-matrix-set-speed-arguments}

 - `uint8_t speed`  
   The new speed to set, from 0 to 255.

---

### `void led_matrix_set_speed_noeeprom(uint8_t speed)` {#api-led-matrix-set-speed-noeeprom}

Set the effect speed. New state is not written to EEPROM.

#### Arguments {#api-led-matrix-set-speed-noeeprom-arguments}

 - `uint8_t speed`  
   The new speed to set, from 0 to 255.

---

### `uint8_t led_matrix_get_speed(void)` {#api-led-matrix-get-speed}

Get the current effect speed.

#### Return Value {#api-led-matrix-get-speed-return}

The current effect speed, from 0 to 255.

---

### `void led_matrix_reload_from_eeprom(void)` {#api-led-matrix-reload-from-eeprom}

Reload the effect configuration (enabled, mode and brightness) from EEPROM.

---

### `bool led_matrix_get_suspend_state(void)` {#api-led-matrix-get-suspend-state}

Get the current suspend state of LED Matrix.

#### Return Value {#api-led-matrix-get-suspend-state-return}

`true` if LED Matrix is currently in the suspended state.

---

### `bool led_matrix_indicators_kb(void)` {#api-led-matrix-indicators-kb}

Keyboard-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.

#### Return Value {#api-led-matrix-indicators-kb-return}

Currently unused.

---

### `bool led_matrix_indicators_user(void)` {#api-led-matrix-indicators-user}

Keymap-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.

#### Return Value {#api-led-matrix-indicators-user-return}

`true` to continue running the keyboard-level callback.

---

### `bool led_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)` {#api-led-matrix-indicators-advanced-kb}

Keyboard-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.

### Arguments {#api-led-matrix-indicators-advanced-kb-arguments}

 - `uint8_t led_min`  
   The index of the first LED in this batch.
 - `uint8_t led_max`  
   The index of the last LED in this batch.

#### Return Value {#api-led-matrix-indicators-advanced-kb-return}

Currently unused.

---

### `bool led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)` {#api-led-matrix-indicators-advanced-user}

Keymap-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.

### Arguments {#api-led-matrix-indicators-advanced-user-arguments}

 - `uint8_t led_min`  
   The index of the first LED in this batch.
 - `uint8_t led_max`  
   The index of the last LED in this batch.

#### Return Value {#api-led-matrix-indicators-advanced-user-return}

`true` to continue running the keyboard-level callback.
