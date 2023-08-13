# Rotary Numpad


![rotary_numpad](https://i.imgur.com/GwEH4WOh.jpeg)

*A short description of the keyboard/project*

* Keyboard Maintainer: [rabijl](https://github.com/rabijl)
* Hardware Supported: Sparkfun Pro Micro 5V (atmega32u4)
* Hardware Availability: https://www.sparkfun.com/products/12640

This is a personal project of mine where I wanted a number pad that I can put on the left \
side of keyboard that doesn't have a numberpad. I fell in love with the feel of rotary encoders \
on my 3d printer, so added three to be able to play around with.

## How to build from scratch

I handsoldered gateron blue switches to a 3D printed case. The design is modified from the [Ultipad](https://www.thingiverse.com/thing:4248565). \
I used a sparkfun Pro Micro as my microcontroller and the pinout can be found in the `info.json`. I found this [site](https://golem.hu/article/pro-micro-pinout/) \
to be very useful to identify different pins. You can find useful information on rotary encoders from the qmk docs [here](https://docs.qmk.fm/#/reference_info_json?id=encoders) and [here](https://docs.qmk.fm/#/feature_encoders).

### matrix

Due to the three rotary encoders, I had to use most of the available pins. \
I therefore fit their buttons into 6 x 4 matrix at strange positions. See the diagram below. \
In this matrix r1, r2 and r3 are the buttons for each respective encoder.
				  \
┌───┬───┬───┬───┐ \
│Esc│Tab│MO1│Bsp│ \
├───┼───┼───┼───┤ \
│Num│\/ │ * │ - │ \
├───┼───┼───┼───┤ \
│ 7 │ 8 │ 9 │ + │ \
├───┼───┼───┼───┤ \
│ 4 │ 5 │ 6 │ r2│ \
├───┼───┼───┼───┤ \
│ 1 │ 2 │ 3 │Ent│ \
├───┼───┼───┼───┤ \
│ r3│ 0 │ . │ r1│ \
└───┴───┴───┴───┘ 

## Flashing

Make example for this keyboard (after setting up your build environment): \
**note:** you may need to run this in the root of the repository for this to work

    ```
	qmk compile -kb rotary_numpad -km default
    ```

Flashing example for this keyboard:

    ```
	qmk flash -kb rotary_numpad -km default
    ```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Short reset leads**: tab the reset lead to ground twice quickly after qmk is in flash mode
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

**Note:** if the keyboard doesn't show up after putting the keyboard in reset mode, check that 
your user is added to the `tty` and/or `uucp` groups. \
You may need to logout after adding these groups to your user, for the changes to take affect.
