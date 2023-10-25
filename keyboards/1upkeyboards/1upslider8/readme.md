# slider8

![slider8](https://i.imgur.com/AiVQySnh.jpg)


This keyboard is the slider8 from 1upkeyboards.com, a small macropad with an oled, slide potentiometer, rotary encoder, and 8 switches in a 2x4 ortholinear arrangement with per-key in-switch rgb leds.

The slide potentiometer presents to the computer as a midi device and will need a seperate program to map to device control.

* Keyboard Maintainer: [ziptyze](https://github.com/ziptyze)

Make example for this keyboard (after setting up your build environment):

    make 1upkeyboards/1upslider8:default

Flashing example for this keyboard:

    make 1upkeyboards/1upslider8:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Hold down the button on the pi pico and plug in the keyboard
