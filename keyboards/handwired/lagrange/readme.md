# Lagrange

An ergonomic, split, concave keyboard, with convex thumb pads.  See the [project page](https://github.com/dpapavas/lagrange-keyboard) for more info.

![Lagrange](https://github.com/dpapavas/lagrange-keyboard/blob/master/doc/lagrange_keyboard.png?raw=true)

* Keyboard Maintainer: [Dimitris Papavasiliou](https://github.com/dpapavas)
* Hardware Supported: Lagrange PCB Rev A
* Hardware Availability: See the build guide on the [project page](https://github.com/dpapavas/lagrange-keyboard).

Make example for this keyboard (after setting up your build environment):

    make handwired/lagrange:default

Flashing example for this keyboard:

    make handwired/lagrange:default:flash

To program the keyboard you'll need to reset it.  This can be accomplished, either through the reset button, accessible via a hole in the bottom cover, or, if you've assigned the `RESET` keycode to a key, by pressing that key.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
