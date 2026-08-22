# Infinity 87.5 Rev 1

![Infinity 87.5 Rev 1](https://i.imgur.com/qt4YBwSl.jpeg)

The Infinity 87.5 is in the popular A87 form factor with top-sided USB Type-C and supports BOTH the F12 and F13 footprints, so it is compatible with a number of TKL boards like Geonworks Frog/F1-8x, KFE-CE, and Singa Jaguar, among others.

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Most H87C compatible keyboards
* Hardware Availability: [Mechlovin' Studio](https://mechlovin.studio), [GB](https://geekhack.org/index.php?topic=115251.0), [CBB Planet](https://cbbplanet.com/products/infinity-87-5-pcb)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/infinity875/rev1:default

Flashing example for this keyboard:

    make mechlovin/infinity875/rev1:default:flash

See the [build environment setup](getting_started_build_tools) and the [make instructions](getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape key relative to the default keymap) and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB.
