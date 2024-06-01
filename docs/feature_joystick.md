# Joystick {#joystick}

This feature provides game controller input as a joystick device supporting up to 6 axes and 32 buttons. Axes can be read either from an [ADC-capable input pin](adc_driver), or can be virtual, so that its value is provided by your code.

An analog device such as a [potentiometer](https://en.wikipedia.org/wiki/Potentiometer) found on an analog joystick's axes is based on a voltage divider, where adjusting the movable wiper controls the output voltage which can then be read by the microcontroller's ADC.

## Usage {#usage}

Add the following to your `rules.mk`:

```make
JOYSTICK_ENABLE = yes
```

By default the joystick driver is `analog`, but you can change this with:

```make
JOYSTICK_DRIVER = digital
```

## Configuration {#configuration}

By default, two axes and eight buttons are defined, with a reported resolution of 8 bits (-127 to +127). This can be changed in your `config.h`:

```c
// Min 0, max 32
#define JOYSTICK_BUTTON_COUNT 16
// Min 0, max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXIS_COUNT 3
// Min 8, max 16
#define JOYSTICK_AXIS_RESOLUTION 10
```

::: tip
You must define at least one button or axis. Also note that the maximum ADC resolution of the supported AVR MCUs is 10-bit, and 12-bit for most STM32 MCUs.
:::

### Axes {#axes}

When defining axes for your joystick, you must provide a definition array typically in your `keymap.c`.

For instance, the below example configures two axes. The X axis is read from the `A4` pin. With the default axis resolution of 8 bits, the range of values between 900 and 575 are scaled to -127 through 0, and values 575 to 285 are scaled to 0 through 127. The Y axis is configured as a virtual axis, and its value is not read from any pin. Instead, the user must update the axis value programmatically.

```c
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(A4, 900, 575, 285),
    JOYSTICK_AXIS_VIRTUAL
};
```

Axes can be configured using one of the following macros:

 * `JOYSTICK_AXIS_IN(input_pin, low, rest, high)`  
   The ADC samples the provided pin. `low`, `high` and `rest` correspond to the minimum, maximum, and resting (or centered) analog values of the axis, respectively.
 * `JOYSTICK_AXIS_VIRTUAL`  
   No ADC reading is performed. The value should be provided by user code.

The `low` and `high` values can be swapped to effectively invert the axis.

#### Virtual Axes {#virtual-axes}

The following example adjusts two virtual axes (X and Y) based on keypad presses, with `KC_P0` as a precision modifier:

```c
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL, // x
    JOYSTICK_AXIS_VIRTUAL  // y
};

static bool precision = false;
static uint16_t precision_mod = 64;
static uint16_t axis_val = 127;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int16_t precision_val = axis_val;
    if (precision) {
        precision_val -= precision_mod;
    }

    switch (keycode) {
        case KC_P8:
            joystick_set_axis(1, record->event.pressed ? -precision_val : 0);
            return false;
        case KC_P2:
            joystick_set_axis(1, record->event.pressed ? precision_val : 0);
            return false;
        case KC_P4:
            joystick_set_axis(0, record->event.pressed ? -precision_val : 0);
            return false;
        case KC_P6:
            joystick_set_axis(0, record->event.pressed ? precision_val : 0);
            return false;
        case KC_P0:
            precision = record->event.pressed;
            return false;
    }
    return true;
}
```

## Keycodes {#keycodes}

|Key                    |Aliases|Description|
|-----------------------|-------|-----------|
|`QK_JOYSTICK_BUTTON_0` |`JS_0` |Button 0   |
|`QK_JOYSTICK_BUTTON_1` |`JS_1` |Button 1   |
|`QK_JOYSTICK_BUTTON_2` |`JS_2` |Button 2   |
|`QK_JOYSTICK_BUTTON_3` |`JS_3` |Button 3   |
|`QK_JOYSTICK_BUTTON_4` |`JS_4` |Button 4   |
|`QK_JOYSTICK_BUTTON_5` |`JS_5` |Button 5   |
|`QK_JOYSTICK_BUTTON_6` |`JS_6` |Button 6   |
|`QK_JOYSTICK_BUTTON_7` |`JS_7` |Button 7   |
|`QK_JOYSTICK_BUTTON_8` |`JS_8` |Button 8   |
|`QK_JOYSTICK_BUTTON_9` |`JS_9` |Button 9   |
|`QK_JOYSTICK_BUTTON_10`|`JS_10`|Button 10  |
|`QK_JOYSTICK_BUTTON_11`|`JS_11`|Button 11  |
|`QK_JOYSTICK_BUTTON_12`|`JS_12`|Button 12  |
|`QK_JOYSTICK_BUTTON_13`|`JS_13`|Button 13  |
|`QK_JOYSTICK_BUTTON_14`|`JS_14`|Button 14  |
|`QK_JOYSTICK_BUTTON_15`|`JS_15`|Button 15  |
|`QK_JOYSTICK_BUTTON_16`|`JS_16`|Button 16  |
|`QK_JOYSTICK_BUTTON_17`|`JS_17`|Button 17  |
|`QK_JOYSTICK_BUTTON_18`|`JS_18`|Button 18  |
|`QK_JOYSTICK_BUTTON_19`|`JS_19`|Button 19  |
|`QK_JOYSTICK_BUTTON_20`|`JS_20`|Button 20  |
|`QK_JOYSTICK_BUTTON_21`|`JS_21`|Button 21  |
|`QK_JOYSTICK_BUTTON_22`|`JS_22`|Button 22  |
|`QK_JOYSTICK_BUTTON_23`|`JS_23`|Button 23  |
|`QK_JOYSTICK_BUTTON_24`|`JS_24`|Button 24  |
|`QK_JOYSTICK_BUTTON_25`|`JS_25`|Button 25  |
|`QK_JOYSTICK_BUTTON_26`|`JS_26`|Button 26  |
|`QK_JOYSTICK_BUTTON_27`|`JS_27`|Button 27  |
|`QK_JOYSTICK_BUTTON_28`|`JS_28`|Button 28  |
|`QK_JOYSTICK_BUTTON_29`|`JS_29`|Button 29  |
|`QK_JOYSTICK_BUTTON_30`|`JS_30`|Button 30  |
|`QK_JOYSTICK_BUTTON_31`|`JS_31`|Button 31  |

## API {#api}

### `struct joystick_t` {#api-joystick-t}

Contains the state of the joystick.

#### Members {#api-joystick-t-members}

 - `uint8_t buttons[]`  
   A bit-packed array containing the joystick button states. The size is calculated as `(JOYSTICK_BUTTON_COUNT - 1) / 8 + 1`.
 - `int16_t axes[]`  
   An array of analog values for each defined axis.
 - `bool dirty`  
   Whether the current state needs to be sent to the host.

---

### `struct joystick_config_t` {#api-joystick-config-t}

Describes a single axis.

#### Members {#api-joystick-config-t-members}

 - `pin_t input_pin`  
   The pin to read the analog value from, or `JS_VIRTUAL_AXIS`.
 - `uint16_t min_digit`  
   The minimum analog value.
 - `uint16_t mid_digit`  
   The resting or midpoint analog value.
 - `uint16_t max_digit`  
   The maximum analog value.

---

### `void joystick_flush(void)` {#api-joystick-flush}

Send the joystick report to the host, if it has been marked as dirty.

---

### `void register_joystick_button(uint8_t button)` {#api-register-joystick-button}

Set the state of a button, and flush the report.

#### Arguments {#api-register-joystick-button-arguments}

 - `uint8_t button`  
   The index of the button to press, from 0 to 31.

---

### `void unregister_joystick_button(uint8_t button)` {#api-unregister-joystick-button}

Reset the state of a button, and flush the report.

#### Arguments {#api-unregister-joystick-button-arguments}

 - `uint8_t button`  
   The index of the button to release, from 0 to 31.

---

### `int16_t joystick_read_axis(uint8_t axis)` {#api-joystick-read-axis}

Sample and process the analog value of the given axis.

#### Arguments {#api-joystick-read-axis-arguments}

 - `uint8_t axis`  
   The axis to read.

#### Return Value {#api-joystick-read-axis-return}

A signed 16-bit integer, where 0 is the resting or mid point.

### `void joystick_set_axis(uint8_t axis, int16_t value)` {#api-joystick-set-axis}

Set the value of the given axis.

#### Arguments {#api-joystick-set-axis-arguments}

 - `uint8_t axis`  
   The axis to set the value of.
 - `int16_t value`  
   The value to set.
