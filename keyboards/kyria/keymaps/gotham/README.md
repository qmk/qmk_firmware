#Gotham's Keymap for [Kyria](https://github.com/splitkb/kyria)

## Keymap
This is my personal keymap for Kyria with some mods.

More information about the Kyria keyboard can be found [here](https://blog.splitkb.com/blog/introducing-the-kyria)

### Rotary Encoders

Press the encoder on each half to cycle between:
- Volume
- Word Nav (Ctrl + Left / Right)
- Left / Right
- Up / Down
- Page Up / Page Down

### OLEDs

Master-side OLED displays dynamic data:
- Current layer
- Current mode of each rotary encoder

Slave-side OLED currently only displays a static logo. More changes to come when I figure out how to drive two oleds with serial link.

### Joystick

A PSP 2000 joystick is attached to the right half. It will currently only function when the USB cable is connected to the right half. When I figure out how to transfer data between halves using serial link, I will make this work regardless of which side is the master.

#### Joystick Configuration

- __JOYSTICK_ENABLE:__ Enable joystick.
- __JOYSTICK_CHANNEL_X/Y (mandatory):__ The ADC channels to use for the respective axis. The values are from the [lufa library](http://www.lufa-lib.org/files/LUFA/Doc/120219/html/group___group___a_d_c___a_v_r8.html). I used ADC_CHANNEL0 and ADC_CHANNEL1 (F0 and F1 pinouts on Elite C), for example.
- __JOYSTICK_FLIP_X/Y:__ Mirror the direction of the respective axis. Use to compensate for actual orientation of joystick.
__JOYSTICK_FLIP_CHANNELS:__ Flip the pins used for X and Y axes. Use instead of re-wiring the joystick.
__JOYSTICK_DEBUG:__ Print raw and calculated values from ADC channels to console. Will only work with CONSOLE_ENABLE turned on.
__JOYSTICK_ANGLE_CORRECT <angle>:__ Angle in degrees to correct for physical orientation of joystick. Can be positive or negative.

#### Joystick Fine-tuning

The ADC channels return a number between 0 and 1023, but joysticks usually aren't accurate enough to work in that full range. So we need to set limits on the high and low readings of each channels based on actual readings. In addition, the resting position has a deadzone which needs to be ignored by the code. For PSP 2000 joysticks, this value is typically 50 units around the center. The parameters for each axis are defined below, and can be set in joystick.c. Turn on CONSOLE_ENABLE in rules.mk and JOYSTICK_DEBUG in config.h to look at the raw values from the channels using hid_listen (or QMK Toolbox).

- __STICK_MIN_X/Y <number>__
- __STICK_MAX_X/Y <number>__
- __STICK_DEADZONE_X/Y_MIN <number>__
- __STICK_DEADZONE_X/Y_MAX <number>__

#### Thanks

Thanks to u/pyrho and u/\_GEIST\_ from Reddit for their help.
