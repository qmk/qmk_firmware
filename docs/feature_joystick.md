## Joystick

The keyboard can be made to be recognized as a joystick HID device by the operating system.

!> Joystick support is not currently available on V-USB devices.

The joystick feature provides two services:
 * reading analog input devices (eg. potentiometers)
 * sending gamepad HID reports

Both services can be used without the other, depending on whether you just want to read a device but not send gamepad reports (for volume control for instance)
or send gamepad reports based on values computed by the keyboard.

### Analog Input

To use analog input you must first enable it in `rules.mk`:

```make
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog # or 'digital'
```

An analog device such as a potentiometer found on a gamepad's analog axes is based on a [voltage divider](https://en.wikipedia.org/wiki/Voltage_divider).
It is composed of three connectors linked to the ground, the power input and power output (usually the middle one). The power output holds the voltage that varies based on the position of the cursor,
which value will be read using your MCU's [ADC](https://en.wikipedia.org/wiki/Analog-to-digital_converter).
Depending on which pins are already used by your keyboard's matrix, the rest of the circuit can get a little bit more complicated,
feeding the power input and ground connection through pins and using diodes to avoid bad interactions with the matrix scanning procedures.

### Configuring the Joystick

By default, two axes and eight buttons are defined. This can be changed in your `config.h`:

```c
// Max 32
#define JOYSTICK_BUTTON_COUNT 16
// Max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXES_COUNT 3
```

When defining axes for your joystick, you have to provide a definition array. You can do this from your keymap.c file.
A joystick will either be read from an input pin that allows the use of the ADC, or can be virtual, so that its value is provided by your code.
You have to define an array of type ''joystick_config_t'' and of proper size.

There are three ways for your circuit to work with the ADC, that relies on the use of 1, 2 or 3 pins of the MCU:
 * 1 pin: your analog device is directly connected to your device GND and VCC. The only pin used is the ADC pin of your choice.
 * 2 pins: your analog device is powered through a pin that allows toggling it on or off. The other pin is used to read the input value through the ADC.
 * 3 pins: both the power input and ground are connected to pins that must be set to a proper state before reading and restored afterwards.

The configuration of each axis is performed using one of four macros:
 * `JOYSTICK_AXIS_VIRTUAL`: no ADC reading must be performed, that value will be provided by keyboard/keymap-level code
 * `JOYSTICK_AXIS_IN(INPUT_PIN, LOW, REST, HIGH)`: a voltage will be read on the provided pin, which must be an ADC-capable pin.
 * `JOYSTICK_AXIS_IN_OUT(INPUT_PIN, OUTPUT_PIN, LOW, REST, HIGH)`: the provided `OUTPUT_PIN` will be set high before `INPUT_PIN` is read.
 * `JOYSTICK_AXIS_IN_OUT_GROUND(INPUT_PIN, OUTPUT_PIN, GROUND_PIN, LOW, REST, HIGH)`: the `OUTPUT_PIN` will be set high and `GROUND_PIN` will be set low before reading from `INPUT_PIN`.

In any case where an ADC reading takes place (when `INPUT_PIN` is provided), additional `LOW`, `REST` and `HIGH` parameters are used.
These implement the calibration of the analog device by defining the range of read values that will be mapped to the lowest, resting position and highest possible value for the axis (-127 to 127).
In practice, you have to provide the lowest/highest raw ADC reading, and the raw reading at resting position, when no deflection is applied. You can provide inverted `LOW` and `HIGH` to invert the axis.

For instance, an axes configuration can be defined in the following way:

```c
//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_IN_OUT_GROUND(A4, B0, A7, 900, 575, 285),
    [1] = JOYSTICK_AXIS_VIRTUAL
};
```

When the ADC reads 900 or higher, the returned axis value will be -127, whereas it will be 127 when the ADC reads 285 or lower. Zero is returned when 575 is read.

In this example, the first axis will be read from the `A4` pin while `B0` is set high and `A7` is set low, using `analogReadPin()`, whereas the second axis will not be read.

#### Virtual Axes

To give a value to virtual axes, call `joystick_set_axis(axis, value)`.

The following example adjusts two virtual axes (X and Y) based on keypad presses, with `KC_P5` as a precision modifier:

```c
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL, // x
    [1] = JOYSTICK_AXIS_VIRTUAL  // y
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
        case KC_P5:
            precision = record->event.pressed;
            return false;
    }
    return true;
}
```

### Axis Resolution

By default, the resolution of each axis is 8 bit, giving a range of -127 to +127. If you need higher precision, you can increase it by defining eg. `JOYSTICK_AXES_RESOLUTION 12` in your `config.h`. The resolution must be between 8 and 16.

Note that the supported AVR MCUs have a 10-bit ADC, and 12-bit for most STM32 MCUs.

### Keycodes

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

You can also trigger joystick buttons in code with `register_joystick_button(button)` and `unregister_joystick_button(button)`, where `button` is the 0-based button index (0 = button 1).
