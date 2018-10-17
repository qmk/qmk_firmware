## Joystick HID Device

The keyboard can be made to be recognized as a joystick HID device by the Operating System. 

This is enabled by adding the following to `rules.mk`

```
JOYSTICK_ENABLE = yes
```

### Configuring the joystick

The default joystick has 2 axes and and 8 buttons. This can be changed from the config.h file : 

```
//max 32 for JOYSTICK_BUTTON_COUNT
#define JOYSTICK_BUTTON_COUNT 16
//max 6 for JOYSTICK_AXES_COUNT
#define JOYSTICK_AXES_COUNT 3
```

When defining axes for your joystick, you have to provide a definition array for it. You can do this from your keymap.c file.
A joystick will either be read from an input pin that allows the use of an ADC, or can be virtual, so that its value is provided by your code.
You have to define an array of type ''joystick_config_t'' and of proper size, in the following way : 

```
//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
  [0] = {A1, D7, 65280, 65472},
  [1] = {JS_VIRTUAL_AXIS, JS_VIRTUAL_AXIS, 65280, 65472}
};
```

In this example, the first axis will be read from the D7 pin while A1 is set high, using an analogRead, whereas the second axis will not be read. 
If you connected the your analog component to Vcc instead of an output pin, you can set the output setting to JS_VIRTUAL_AXIS.
In order to give a value to the second axis, you can do so in any customizable entry point of quantum : as an action, in process_record_user or in matrix_scan_user, or even in joystick_task(void) which is called even when no key has been pressed.
You assign a value by writing to joystick_status.axes[axis_index] a signed 8bit value (-127 to 127). Then it is necessary to assign the flag JS_UPDATED to joystick_status.status in order for the change to be taken into account.

The following example writes two axes based on keypad presses, with KP_5 as a precision modifier : 

```
#ifdef JOYSTICK_ENABLE
static bool precision_on;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode){
#ifdef JOYSTICK_ENABLE
    // virtual joystick
    case KC_P8:
      joystick_status.axes[1] -= (record->event.pressed ? 1 : -1) * (precision_on ?70 : 127);
      joystick_status.status |= JS_UPDATED;
    break;
    case KC_P2:
      joystick_status.axes[1] += (record->event.pressed ? 1 : -1) * (precision_on ?70 : 127);
      joystick_status.status |= JS_UPDATED;
    break;
    case KC_P4:
      joystick_status.axes[0] -= (record->event.pressed ? 1 : -1) * (precision_on ?70 : 127);
      joystick_status.status |= JS_UPDATED;
    break;
    case KC_P6:
      joystick_status.axes[0] += (record->event.pressed ? 1 : -1) * (precision_on ?70 : 127);
      joystick_status.status |= JS_UPDATED;
    break;
    case KC_P5:
    precision_on = record->event.pressed;
    joystick_status.axes[0] *= record->event.pressed ? 70/127.f : 127/70.f;
    joystick_status.axes[1] *= record->event.pressed ? 70/127.f : 127/70.f;
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



