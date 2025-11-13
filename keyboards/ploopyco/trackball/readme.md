# Ploopy Classic Trackball

![Ploopy Trackball](https://i.redd.it/j7z0y83txps31.jpg)

It's a DIY, QMK Powered Trackball!!!!

* Keyboard Maintainer: [Ploopy](https://github.com/ploopyco), [Drashna Jael're](https://github.com/drashna/), [Germ](https://github.com/germ/)
* Hardware Supported: ATMega32u4 8MHz(3.3v), Raspberry RP2040
* Hardware Availability: [Store](https://ploopy.co), [GitHub](https://github.com/ploopyco)

Make example for this keyboard (after setting up your build environment):

    make ploopyco/trackball/rev1_004:default:flash
    make ploopyco/trackball/rev1_005:default:flash
    make ploopyco/trackball/rev1_007:default:flash

To jump to the bootloader, hold down "Button 4" (immediate right of the trackball)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Revisions

There are three main revisions for the Ploopy Classic Trackball:

- Everything up to 1.004 (very rare)
- Revision 1.005 and 1.006 (commonly sold between 2020 and 2024)
- Revision 1.007 (first available in 2025)

In the 1.005 revision, button four was changed from pin B5 to B6, and the debug LED pin was changed from F7 to B5.

In the 1.007 revision, the board was switched from an ATMega32u4 architecture to the Raspberry RP2040 architecture.

The PCB should indicate which revision this is.

# Customizing your PloopyCo Trackball

You can find customziation options [here](../readme.md).
