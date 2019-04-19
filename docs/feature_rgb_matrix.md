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
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL
```

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

### WS2812 (AVR only)

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

From this point forward the configuration is the same for all the drivers. 

```C
const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
/*  {row | col << 4}
    *    |         {x=0..224, y=0..64}
    *    |            |              modifier
    *    |            |                | */
    {{0|(0<<4)},   {20.36*0, 21.33*0}, 1},
    {{0|(1<<4)},   {20.36*1, 21.33*0}, 1},
    ....
}
```

The format for the matrix position used in this array is `{row | (col << 4)}`. The `x` is between (inclusive) 0-224, and `y` is between (inclusive) 0-64. The easiest way to calculate these positions is:

```C
x = 224 / ( NUMBER_OF_COLS - 1 ) * ROW_POSITION
y = 64 / (NUMBER_OF_ROWS - 1 ) * COL_POSITION
```

Where all variables are decimels/floats.

`modifier` is a boolean, whether or not a certain key is considered a modifier (used in some effects).

## Keycodes

All RGB keycodes are currently shared with the RGBLIGHT system:

* `RGB_TOG` - toggle
* `RGB_MOD` - cycle through modes
* `RGB_HUI` - increase hue
* `RGB_HUD` - decrease hue
* `RGB_SAI` - increase saturation
* `RGB_SAD` - decrease saturation
* `RGB_VAI` - increase value
* `RGB_VAD` - decrease value
* `RGB_SPI` - increase speed effect (no EEPROM support)
* `RGB_SPD` - decrease speed effect (no EEPROM support)
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
    RGB_MATRIX_CYCLE_ALL,           // Full keyboard solid hue cycling through full gradient
    RGB_MATRIX_CYCLE_LEFT_RIGHT,    // Full gradient scrolling left to right 
    RGB_MATRIX_CYCLE_UP_DOWN,       // Full gradient scrolling top to bottom
    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,  // Full gradent Chevron shapped scrolling left to right
    RGB_MATRIX_DUAL_BEACON,         // Full gradient spinning around center of keyboard
    RGB_MATRIX_RAINBOW_BEACON,      // Full tighter gradient spinning around center of keyboard
    RGB_MATRIX_RAINBOW_PINWHEELS,   // Full dual gradients spinning two halfs of keyboard
    RGB_MATRIX_RAINDROPS,           // Randomly changes a single key's hue
    RGB_MATRIX_JELLYBEAN_RAINDROPS, // Randomly changes a single key's hue and saturation
    RGB_MATRIX_DIGITAL_RAIN,        // That famous computer simulation
#if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
    RGB_MATRIX_SOLID_REACTIVE_SIMPLE,   // Pulses keys hit to hue & value then fades value out
    RGB_MATRIX_SOLID_REACTIVE,      // Static single hue, pulses keys hit to shifted hue then fades to current hue
    RGB_MATRIX_SPLASH,              // Full gradient & value pulse away from a single key hit then fades value out
    RGB_MATRIX_MULTISPLASH,         // Full gradient & value pulse away from multiple key hits then fades value out
    RGB_MATRIX_SOLID_SPLASH,        // Hue & value pulse away from a single key hit then fades value out
    RGB_MATRIX_SOLID_MULTISPLASH,   // Hue & value pulse away from multiple key hits then fades value out
#endif
    RGB_MATRIX_EFFECT_MAX
};
```
    
You can disable a single effect by defining `DISABLE_[EFFECT_NAME]` in your `config.h`:


|Define                                             |Description                                 |
|---------------------------------------------------|--------------------------------------------|
|`#define DISABLE_RGB_MATRIX_ALPHAS_MODS`           |Disables `RGB_MATRIX_ALPHAS_MODS`           |
|`#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN`      |Disables `RGB_MATRIX_GRADIENT_UP_DOWN`      |
|`#define DISABLE_RGB_MATRIX_BREATHING`             |Disables `RGB_MATRIX_BREATHING`             |
|`#define DISABLE_RGB_MATRIX_CYCLE_ALL`             |Disables `RGB_MATRIX_CYCLE_ALL`             |
|`#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT`      |Disables `RGB_MATRIX_CYCLE_LEFT_RIGHT`      |
|`#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN`         |Disables `RGB_MATRIX_CYCLE_UP_DOWN`         |
|`#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON`|Disables `RGB_MATRIX_RAINBOW_MOVING_CHEVRON`|
|`#define DISABLE_RGB_MATRIX_DUAL_BEACON`           |Disables `RGB_MATRIX_DUAL_BEACON`           |
|`#define DISABLE_RGB_MATRIX_RAINBOW_BEACON`        |Disables `RGB_MATRIX_RAINBOW_BEACON`        |
|`#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS`     |Disables `RGB_MATRIX_RAINBOW_PINWHEELS`     |
|`#define DISABLE_RGB_MATRIX_RAINDROPS`             |Disables `RGB_MATRIX_RAINDROPS`             |
|`#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS`   |Disables `RGB_MATRIX_JELLYBEAN_RAINDROPS`   |
|`#define DISABLE_RGB_MATRIX_DIGITAL_RAIN`          |Disables `RGB_MATRIX_DIGITAL_RAIN`          |
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE`        |Disables `RGB_MATRIX_SOLID_REACTIVE`        |
|`#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE` |Disables `RGB_MATRIX_SOLID_REACTIVE_SIMPLEE`|
|`#define DISABLE_RGB_MATRIX_SPLASH`                |Disables `RGB_MATRIX_SPLASH`                |
|`#define DISABLE_RGB_MATRIX_MULTISPLASH`           |Disables `RGB_MATRIX_MULTISPLASH`           |
|`#define DISABLE_RGB_MATRIX_SOLID_SPLASH`          |Disables `RGB_MATRIX_SOLID_SPLASH`          |
|`#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH`     |Disables `RGB_MATRIX_SOLID_MULTISPLASH`     |


## Custom layer effects

Custom layer effects can be done by defining this in your `<keyboard>.c`:

```C
void rgb_matrix_indicators_kb(void) {
    rgb_matrix_set_color(index, red, green, blue);
}
```

A similar function works in the keymap as `rgb_matrix_indicators_user`.

## Additional `config.h` Options

```C
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
```

## EEPROM storage

The EEPROM for it is currently shared with the RGBLIGHT system (it's generally assumed only one RGB would be used at a time), but could be configured to use its own 32bit address with:

```C
#define EECONFIG_RGB_MATRIX (uint32_t *)16
```

Where `16` is an unused index from `eeconfig.h`.

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
