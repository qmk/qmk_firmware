# Hi-Tek AIM-65

![Hi-Tek AIM-65 Keyboard](https://imgur.com/7Gam1f2l.jpg)

The keboard assembly that came with the Rockwell AIM-65, a microcomputer from the '70s [Wikipedia article](https://en.wikipedia.org/wiki/AIM-65)

The controller is a Pro Micro handwired to the original connector. [This](https://github.com/Bonnee/aim-65_keyboard) repo collects 3D models for the case, schematics for the matrix and pics.

* Keyboard Maintainer: [Matteo Bonora](https://github.com/bonnee)
* Hardware Supported: Pro Micro

The default layout is useless on a modern computer, you can use it as a base for your own though.

Make example for this keyboard (after setting up your build environment):

    make handwired/aim65:default

Flashing example for this keyboard:

    make handwired/aim65:default:flash

To reset the board into bootloader mode, do one of the following:

* Double-tap the Reset switch mounted on the Pro Micro
* Hold the spacebar while connecting the USB cable (also erases persistent settings)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
