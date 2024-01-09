# infinity875

![infinity875](https://i.imgur.com/OELfHUvh.jpeg)

The Infinity 87.5 is in the popular A87 form factor with Top-sided USB Type-C and supports BOTH the F12 and F13 footprints, so it’s compatible with a number of TKL boards like Geonworks Frog/F1-8x; KFE-CE; Singa Jaguar, among others.

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Infinity87.5 Rev.2 , APM32F103CBT6
* Hardware Availability: [CBB Planet](https://cbbplanet.com/products/infinity-87-5-pcb), [Mechlovin' Studio](https://mechlovin.studio)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/infinity875/rev2:default

Flashing example for this keyboard:

    make mechlovin/infinity875/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- By keycode: Press the key mapped to `QK_BOOT` if it is available.
- By bootmagic: hold ESC key while plugging in.
- By hardware: Push reset button on bottom of the PCB while the PCB is plugged in.