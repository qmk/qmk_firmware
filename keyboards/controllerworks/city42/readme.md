# city42

![city42](https://i.imgur.com/xrSKhqRh.png)
![city42PCB](https://i.imgur.com/R7u1KB8h.png)

*A pre-built, low profile, unibody split keyboard based on the RP2040 processor*

* Keyboard Maintainer: [Kevin Gee](https://github.com/controller-works)
* Hardware Supported: *city42 split ergonomic keyboard*
* Hardware Availability: *https://controller.works/products/city42-low-profile-ergonomic-keyboard* Hardware is available as pre-built units only.

Make example for this keyboard (after setting up your build environment):

```sh
    make controllerworks/city42:default
```

Flashing example for this keyboard:

```sh
    make controllerworks/city42:default:flash
```
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Features
- Highly integrated design with microcontroller and USB connectors on the main board
- RP2040 processor by Raspberry Pi Foundation running at 130 MHz with 16MB flash memory
- CNC milled aluminum case with only 8mm thickness
- 42 per-key RGB LEDs
- ESD and over-current protection on USB
- Reset and boot tactile switches
- USB C host connection
- Hot swap connectors for Kailh Chocolate PG1350 switches
- Chocolate key spacing (18mm horizontal x 17mm vertical) 
## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the upper left key while plugging in USB
* **Physical reset button**: Press the RST button twice, rapidly
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available