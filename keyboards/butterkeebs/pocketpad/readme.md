# PocketPad

![PocketPad](https://tinyurl.com/2hffvnvb)

*The PocketPad is a tiny 18 key macropad/numpad using 6mm tactile switches.*

* Keyboard Maintainer: [ButterKeebs](https://github.com/butterkeebs)
* Hardware Supported: *Supports current V1.0.0 PocketPad PCB and Elite C / pin compatible MCU boards.*
* Hardware Availability: *Currently not for sale*

Make example for this keyboard (after setting up your build environment):

    make butterkeebs/pocketpad:default

Flashing example for this keyboard:

    make butterkeebs/pocketpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB. (Not available on Revision 1.0.0 PCB)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
