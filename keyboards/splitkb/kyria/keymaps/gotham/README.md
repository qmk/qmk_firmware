# Gotham's Keymap for [Kyria](https://github.com/splitkb/kyria)

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
- Current mode of thumbstick

Slave-side OLED currently only displays a static content.

### Thumbstick

A PSP 2000 thumbstick is attached to the right half. It will currently only function when the USB cable is connected to the right half. When I figure out how to transfer data between halves using serial link, I will make this work regardless of which side is the master.

#### Thumbstick Configuration

- __THUMBSTICK_ENABLE:__ Enable thumbstick.
- __THUMBSTICK_PIN_X/Y (mandatory):__ The QMK pins to use for the respective axis. The values are from the [QMK's ADC driver](https://docs.qmk.fm/#/adc_driver). I used F0 and F1, for example.
- __THUMBSTICK_FLIP_X/Y:__ Mirror the direction of the respective axis. Use to compensate for actual orientation of thumbstick.
- __THUMBSTICK_DEBUG:__ Print raw and calculated values from analogReadPin to console. Will only work with CONSOLE_ENABLE turned on.

#### Thumbstick Fine-tuning

More tunables are described here. Values like deadzone threshold are hardware-specific. The theoretical range for analog readings is [0, 1023], but emperical readings don't extend the entire range. To find the right values, turn on CONSOLE_ENABLE in rules.mk and THUMBSTICK_DEBUG in config.h to look at the raw values from the pins using hid_listen (or QMK Toolbox).

- __THUMBSTICK_DEAD_ZONE 90:__ Values below this are ignored (deadzone).
- __THUMBSTICK_FINE_ZONE 180:__  Values below this enable fine movement.

- __THUMBSTICK_MODE <mode>:__ One of THUMBSTICK_MODE_MOUSE, THUMBSTICK_MODE_ARROWS and THUMBSTICK_MODE_SCROLL. This is just the default mode, it can be changed by calling ```void thumbstick_mode_cycle(bool reverse)``` within code.

- __THUMBSTICK_SPEED 127:__ Cursor speed in THUMBSTICK_MODE_MOUSE.
- __THUMBSTICK_FINE_SPEED 64:__ Fine cursor speed in THUMBSTICK_MODE_MOUSE (kicks in when slightly nudging the thumbstick).
- __THUMBSTICK_SCROLL_SPEED 1:__ Scrolling speed in THUMBSTICK_MODE_SCROLL.

- __THUMBSTICK_EIGHT_AXIS true:__ 8-axis toggle for ARROW and SCROLL modes. Disable to fall back to 4 axes (think D-pads vs analog stick).
- __THUMBSTICK_AXIS_SEPARATION 0.5f:__ Float value between 0 and 1, used to discretize the circular range into distinct zones for 8-axis. Imagine the top-right quadrant on a graph, and picture the diagonal. This value indicates the angular "distance" from the diagonal to either axis. Moving from the diagonal to each of the axes, this value changes from 0 to 1. So, a value of 0.5 will "sweep" from the center to half-way towards each axis, creating a zone across the diagonal. Smaller values make narrower diagonal zones, and vice versa.

#### Thanks

- @pyrho and u/\_GEIST\_ for the inspiration and initial reference code.
- @zvecr and @drashna for code review and more pointers.
