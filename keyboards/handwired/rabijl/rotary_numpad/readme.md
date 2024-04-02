# Rotary Numpad


![rotary_numpad](https://i.imgur.com/GwEH4WOh.jpeg)

This is a personal project of mine where I wanted a number pad that I can put on the left side of keyboard that doesn't have a numberpad. I fell in love with the feel of rotary encoders on my 3d printer, so added three to be able to play around with.

* Keyboard Maintainer: [rabijl](https://github.com/rabijl)
* Hardware Supported: Sparkfun Pro Micro 5V (atmega32u4)
* Hardware Availability: https://www.sparkfun.com/products/12640

## How to build from scratch

I handsoldered gateron blue switches to a 3D printed case. The design is modified from the [Ultipad](https://www.thingiverse.com/thing:4248565). \
I used a sparkfun Pro Micro as my microcontroller and the pinout can be found in the `info.json`. I found this [site](https://golem.hu/article/pro-micro-pinout/) \
to be very useful to identify different pins. You can find useful information on rotary encoders from the qmk docs [here](https://docs.qmk.fm/#/reference_info_json?id=encoders) and [here](https://docs.qmk.fm/#/feature_encoders).

### matrix

Due to the three rotary encoders, I had to use most of the available pins. Fortunately, all the buttons still fit in a 6x4 matrix. Looking at the diagram below, the three buttons in the first column correspond to each encoder button.

```
        ┌──┐┌──┐┌──┐┌──┐
        │0A││0B││0C││0D│
┌──┐    └──┘└──┘└──┘└──┘
│5A│
└──┘    ┌──┐┌──┐┌──┐┌──┐
        │1A││1B││1C││1D│
        └──┘└──┘└──┘└──┘
        ┌──┐┌──┐┌──┐┌──┐
        │2A││2B││2C││2D│
┌──┐    └──┘└──┘└──┘│  │
│3D│    ┌──┐┌──┐┌──┐│  │
└──┘    │3A││3B││3C││  │
        └──┘└──┘└──┘└──┘
        ┌──┐┌──┐┌──┐┌──┐
        │4A││4B││4C││4D│
        └──┘└──┘└──┘│  │
┌──┐    ┌──────┐┌──┐│  │
│5D│    │5B    ││5C││  │
└──┘    └──────┘└──┘└──┘

```

## Flashing

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/rabijl/rotary_numpad -km default

Flashing example for this keyboard:

    qmk flash -kb handwired/rabijl/rotary_numpad -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Short reset leads**: tap the reset lead to ground twice quickly after qmk is in flash mode
* **Keycode in layout**: double tap the key mapped to `QK_BOOT`. On the default keymap this can be found by holding in key (0,C) and tapping key (0,A), see the matrix section for the positions of these keys. 
* **Bootmagic reset**: Hold down the key at (0,A) in the matrix (see matrix section) and plug in the keyboard

**Note:** if the keyboard doesn't show up after putting the keyboard in reset mode, check that 
your user is added to the `tty` and/or `uucp` groups. \
You may need to logout after adding these groups to your user, for the changes to take affect.
