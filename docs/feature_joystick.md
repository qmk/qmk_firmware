## Joystick HID Device

The keyboard can be made to be recognized as a joystick HID device by the Operating System.

This is enabled by adding the following to `rules.mk`

```
JOYSTICK_ENABLE = yes
```

The joystick feature provides two services :
 * reading an analog input device
 * sending gamepad HID reports

Both services can be used without the other, depending on whether you just want to read a device but not send gamepad reports (for volume control for instance)
or send gamepad reports based on values computed by the keyboard.

!> Reading analog axes is not currently functional on ARM MCUs.

### Analog circuit

An analog device such as a potentiometer found on a gamepad's analog axes is based on a [voltage divider](https://en.wikipedia.org/wiki/Voltage_divider).
It is composed of three connectors linked to the ground, the power input and power output (usually the middle one). The power output holds the voltage that varies based on the position of the cursor,
which value will be read using your MCU's [ADC](https://en.wikipedia.org/wiki/Analog-to-digital_converter).
Depending on what pins are already used by your keyboard's matrix, the rest of the circuit can get a little bit more complicated,
feeding the power input and ground connection through pins and using diodes to avoid bad interactions with the matrix scanning procedures.

### Configuring the joystick

The default joystick has 2 axes and and 8 buttons. This can be changed from the config.h file :

```
//max 32 for JOYSTICK_BUTTON_COUNT
#define JOYSTICK_BUTTON_COUNT 16
//max 6 for JOYSTICK_AXES_COUNT
#define JOYSTICK_AXES_COUNT 3
```

When defining axes for your joystick, you have to provide a definition array. You can do this from your keymap.c file.
A joystick will either be read from an input pin that allows the use of the ADC, or can be virtual, so that its value is provided by your code.
You have to define an array of type ''joystick_config_t'' and of proper size.

There are three ways for your circuit to work with the ADC, that relies on the use of 1, 2 or 3 pins of the MCU:
 * 1 pin : your analog device is directly connected to your device Ground and Vcc. The only pin used is the ADC pin of your choice.
 * 2 pins : your analog device is powered through a pin that allows toggling it on or off. The other pin is used to read the input value through the ADC
 * 3 pins : both the power input and ground are connected to pins that must be set to a proper state before reading and restored afterwards.

The configuration of each axis is performed using one of four macros:
 * JOYSTICK_AXIS_VIRTUAL : no ADC reading must be performed, that value will be provided by keyboard/keymap-level code
 * JOYSTICK_AXIS_IN (INPUT_PIN, LOW, REST, HIGH) : a voltage will be read on the provided pin, which must be an ADC-capable pin.
 * JOYSTICK_AXIS_IN_OUT (INPUT_PIN, OUTPUT_PIN, LOW, REST, HIGH) : the provided OUTPUT_PIN will be set high before INPUT_PIN is read.
 * JOYSTICK_AXIS_IN_OUT_GROUND(INPUT_PIN, OUTPUT_PIN, GROUND_PIN, LOW, REST, HIGH) : the OUTPUT_PIN will be set high and GROUND_PIN will be set low before reading from INPUT_PIN

In any case where an ADC reading takes place (when INPUT_PIN is provided), additional LOW, REST and HIGH parameters are used.
They implement the calibration of the analog device by defining the range of read values that will be mapped to the lowest, resting position and highest possible value for the axis (-127 to 127).
In practice, you have to provide the lowest/highest raw adc reading, and the raw reading at resting position, when no deflection is applied. You can provide inverted LOW and HIGH to invert the axis.

For instance, an axes configuration can be defined in the following way :

```
//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
  [0] = JOYSTICK_AXIS_IN_OUT_GROUND(A4, B0, A7, 900, 575, 285)
, [1] = JOYSTICK_AXIS_VIRTUAL
};
```

When the ADC reads 900 or higher, the returned axis value will be -127, whereas it will be 127 when the ADC reads 285 or lower. Zero is returned when 575 is read.

In this example, the first axis will be read from the A4 pin while B0 is set high and A7 is set low, using an analogRead, whereas the second axis will not be read.

In order to give a value to the second axis, you can do so in any customizable entry point of quantum : as an action, in process_record_user or in matrix_scan_user, or even in joystick_task(void) which is called even when no key has been pressed.
You assign a value by writing to joystick_status.axes[axis_index] a signed 8bit value (ranging from -127 to 127). Then it is necessary to assign the flag JS_UPDATED to joystick_status.status in order for an updated HID report to be sent.

The following example writes two axes based on keypad presses, with KP_5 as a precision modifier :

```
#ifdef JOYSTICK_ENABLE
static uint8_t precision_val = 70;
static uint8_t axesFlags = 0;
enum Axes{
  Precision = 1,
  Axis1High = 2,
  Axis1Low = 4,
  Axis2High = 8,
  Axis2Low = 16
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode){
#ifdef JOYSTICK_ENABLE
    // virtual joystick
    #if JOYSTICK_AXES_COUNT>1
    case KC_P8:
      if (record->event.pressed){
        axesFlags |= Axis2Low;
      } else {
        axesFlags &= ~Axis2Low;
      }
      joystick_status.status |= JS_UPDATED;
    break;
    case KC_P2:
      if (record->event.pressed){
        axesFlags |= Axis2High;
      } else {
        axesFlags &= ~Axis2High;
      }
      joystick_status.status |= JS_UPDATED;
    break;
    #endif
    case KC_P4:
      if (record->event.pressed){
        axesFlags |= Axis1Low;
      } else {
        axesFlags &= ~Axis1Low;
      }
      joystick_status.status |= JS_UPDATED;
    break;
    case KC_P6:
      if (record->event.pressed){
        axesFlags |= Axis1High;
      } else {
        axesFlags &= ~Axis1High;
      }
      joystick_status.status |= JS_UPDATED;
    break;
    case KC_P5:
    if (record->event.pressed){
        axesFlags |= Precision;
      } else {
        axesFlags &= ~Precision;
      }
    joystick_status.status |= JS_UPDATED;
    break;
#endif
  }

  return true;
}
```

### Triggering joystick buttons

Joystick buttons are normal quantum keycode, defined as JS_BUTTON0 to JS_BUTTON_MAX, which depends on the number of buttons you have configured.
To trigger a joystick button, just add the corresponding keycode to your keymap.

