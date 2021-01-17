# XO87 RGB PCB

![XO87](https://cdn.imweb.me/thumbnail/20201120/c90a5bdb75264.png) 

A TKL custom keyboard made by Monstargear 

* Keyboard Maintainer: qmk
* Hardware Supported: XO87 RGB Hot-Swap version
* Hardware Availability: [Monstargear](https://monstargears.com)

Make example for this keyboard (after setting up your build environment):

```sh
make xo87/rgb:default        # builds the default firmware
make xo87/rgb:via            # builds the via firmware
```
The keyboard uses a DFU bootloader. To make a keymap and use dfu to flash it:

```sh
make xo87/rgb:default:flash  # builds and flashes the default version
make xo87/rgb:via:flash      # builds and flashes the via version
```

Please be aware that Monstargear has not yet switched to this firmware and any PCB that is running the pre-installed firmware will need to use ISP to flash their board for the first time.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
