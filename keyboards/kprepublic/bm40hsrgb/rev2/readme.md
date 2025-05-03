# bm40hsrgb

![BM40 RGB](https://i.imgur.com/eOqXMlNh.jpg)

An ortholinear 40% hotswap keyboard with per-key RGB in-switch LEDs and RGB Backlighting, from KP Republic.

This firmware was originally taken from a kbfirmware.json and manually converted. You may find the original `.json` files [here](https://drive.google.com/drive/folders/1tlTHQIFcluK2mjZ4UbbKCsdRLgSRSPw6).

* Keyboard Maintainer: [rgoulter](https://github.com/rgoulter)
* Hardware Supported: bm40hsrgb PCB
* Hardware Availability: [KPRepublic](https://www.aliexpress.com/item/4001147779116.html)

Make example for this keyboard (after setting up your build environment):

    make kprepublic/bm40hsrgb/rev2:default

Flashing example for this keyboard:

    make kprepublic/bm40hsrgb/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

There are multiple ways to enter the bootloader so that firmware can be flashed onto the keyboard:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard.
* **Physical reset button**: Briefly press the button labeled 'RST' on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available.
