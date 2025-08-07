# Halcyon Corne

![splitkb/halcyon/corne](https://i.imgur.com/Cpo2dM8.png)

The Halcyon Corne rev2 is the second Corne revision and the third keyboard in our Halcyon range. Similar to Aurora, all keyboards in the series share the same feature set. The key highlights:

- Halcyon keyboards come preassembled! You won't need a soldering iron.
- You'll be able to install [VIK](https://github.com/sadekbaroudi/vik) modules.
- It'll come fully documented, which includes the unboxing, assembly (with only a screwdriver), first installation and some advanced use cases.
- Both the connection to the host device as well as the interconnect between the keyboard halves use USB C.
- The controller has full ESD protection on all USB C ports, as well as all switch matrix GPIO!
- The controller is interchangable. If part of your keyboard ever breaks, we can replace just the bits that need replacing.

* Keyboard Maintainer: [splitkb.com](https://github.com/splitkb.com)
* Hardware Availability: [splitkb.com](https://splitkb.com).

Make example for this keyboard (after setting up your build environment):

    make splitkb/halcyon/corne/rev2:default

The keyboard can be flashed by copying the resulting `.uf2` file onto the `RPI-RP2` flash drive.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Reset button**: Double-tap the reset button at the top of the controller, right above the USB-C port.
* **Bootloader reset**: Hold down the "Boot" button and plug in the keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
