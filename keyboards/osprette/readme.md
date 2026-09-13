# The Osprette

![The Osprette](https://raw.githubusercontent.com/smores56/osprette/main/images/osprette-front.jpg)

*A 34-key unibody columnar keyboard with pinky clusters, running on any Pro Micro compatible controller.*

This is the official firmware for a family of 34-key unibody boards designed by [smores56](https://github.com/smores56),
the first of which was [the Osprette](https://github.com/smores56/osprette). This firmware works for the following boards:

* [The Osprette](https://github.com/smores56/osprette)
* [The Osprette V2](https://github.com/smores56/osprette-v2)
* [The Osprette V3](https://github.com/smores56/osprette-v3)
* [The Osprette MX](https://github.com/smores56/osprette-mx)
* [The Osprangle](https://github.com/smores56/osprangle)

The Osprangle is the fourth revision of the Osprette and shares its matrix, so every board above is built with the `osprette` target.

* Keyboard Maintainer: [Sam Mohr](https://github.com/smores56)
* Hardware Supported: The Osprette, Osprette V2, Osprette V3, Osprette MX and Osprangle (Pro Micro compatible controller)
* Hardware Availability: [smores56/osprette](https://github.com/smores56/osprette), [smores56/osprette-v2](https://github.com/smores56/osprette-v2), [smores56/osprette-v3](https://github.com/smores56/osprette-v3), [smores56/osprette-mx](https://github.com/smores56/osprette-mx), [smores56/osprangle](https://github.com/smores56/osprangle)

Make example for this keyboard (after setting up your build environment):

    make osprette:default

Flashing example for this keyboard:

    make osprette:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the left pinky outer key) and plug in the keyboard
* **Physical reset button**: Briefly press the reset button on the controller - some boards may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
