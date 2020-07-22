# Gotham's QMK Userspace

## License

Copyright 2020 Gautham Yerroju @GauthamYerroju

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Intro

This contains a self-sufficient base keymap for 42 keys (the Corne layout). Extra keys on larger keyboards can be defined on their keymaps.

## Userspace Hooks

Search for functions ending in __\_keymap__. These can be overriden in keymap.c files. This includes:

### QMK Hooks

- keyboard_pre_init_keymap
- matrix_init_keymap
- keyboard_post_init_keymap
- matrix_scan_keymap
- suspend_power_down_keymap
- suspend_wakeup_init_keymap
- layer_state_set_keymap
- led_update_keymap
- process_record_keymap

### Encoder Hooks

- encoder_init_keymap
- encoder_update_keymap
- process_record_keymap_encoder

### OLED Hooks

- oled_init_keymap
- process_record_keymap_oled

### Thumbstick hooks

- thumbstick_init_keymap
- thumbstick_update_keymap
- process_record_keymap_thumbstick

## Rotary Encoders

Press the encoder to cycle between:
- Volume
- Word Nav (Ctrl + Left / Right)
- Left / Right
- Up / Down
- Page Up / Page Down

## OLEDs

Primary OLED displays dynamic data:
- Current layout
- Current layer
- Current mode of each rotary encoder
- Current mode of thumbstick

Secondary OLED only displays encoder mode dynamically.

### OLED Animations

Enable OLED_ANIMATIONS_ENABLE in rules.mk and define one of the following animations in config.h:
1. __OLED_ANIM_STARFIELD:__ Zoom through starfield.
  - OLED_ANIM_STARFIELD_WANDER: Reset starfield origin each time the screen turns on.
  - OLED_ANIM_STARFIELD_DUALLAYER: Enable an extra layer of slow moving stars.
2. __OLED_ANIM_IMAGE_BOUNCE:__ Bounce an image against the screen edges. Define the image in oled_animations/image_bounce.c.

Some of these might be too much for AVR MCUs to handle depending on what other features are enabled. Values for each animation can be tweaked in the header files to make thenm less intensive.

## Thumbstick

Support one thumbstick as a pointing device.

### Thumbstick Configuration

- __THUMBSTICK_ENABLE:__ Enable thumbstick.
- __THUMBSTICK_PIN_X/Y (mandatory):__ The QMK pins to use for the respective axis. The values are from the [QMK's ADC driver](https://docs.qmk.fm/#/adc_driver). I used F0 and F1, for example.
- __THUMBSTICK_FLIP_X/Y:__ Mirror the direction of the respective axis. Use to compensate for actual orientation of thumbstick.
- __THUMBSTICK_DEBUG:__ Print raw and calculated values from analogReadPin to console. Will only work with CONSOLE_ENABLE turned on.

### Thumbstick Fine-tuning

More tunables are described here. Values like deadzone threshold are hardware-specific. The theoretical range for analog readings is [0, 1023], but emperical readings don't extend the entire range. To find the right values, turn on CONSOLE_ENABLE in rules.mk and THUMBSTICK_DEBUG in config.h to look at the raw values from the pins using hid_listen (or QMK Toolbox).

- __THUMBSTICK_DEAD_ZONE:__ Values below this are ignored (deadzone).
- __THUMBSTICK_FINE_ZONE:__  Values below this enable fine movement.

- __THUMBSTICK_MODE <mode>:__ One of THUMBSTICK_MODE_MOUSE, THUMBSTICK_MODE_ARROWS and THUMBSTICK_MODE_SCROLL. This is just the default mode, it can be changed by calling ```thumbstick_mode_cycle_forward()``` and ```thumbstick_mode_cycle_backward()``` within code.

- __THUMBSTICK_SPEED:__ Cursor speed in THUMBSTICK_MODE_MOUSE, automatically limited to 127.
- __THUMBSTICK_FINE_SPEED:__ Fine cursor speed in THUMBSTICK_MODE_MOUSE (kicks in when slightly nudging the thumbstick). Automatically limited to 127.
- __THUMBSTICK_SCROLL_SPEED:__ Scrolling speed in THUMBSTICK_MODE_SCROLL.

- __THUMBSTICK_EIGHT_AXIS true:__ 8-axis toggle for ARROW and SCROLL modes. Disable to fall back to 4 axes (think D-pads vs analog stick).
- __THUMBSTICK_AXIS_SEPARATION:__ Range is [0 - 127], used to discretize the circular range into distinct zones for 8-axis. Imagine the top-right quadrant on a graph, and picture the diagonal. This value indicates the angular "distance" from the diagonal to either axis. Moving from the diagonal to each of the axes, this value changes from 0 to 127. So, a value of 64 will "sweep" from the diagonal to half-way towards each axis, creating a zone across the diagonal. Smaller values make narrower diagonal zones, and vice versa.

## Thanks

- @pyrho and u/\_GEIST\_ for the inspiration and initial reference code.
- @drashna and @zvecr for code review and more pointers.
- QMK Docs and Discord.
