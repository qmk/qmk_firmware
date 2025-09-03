# linworks/fave60a

![linworks/fave60a front](https://i.imgur.com/UeWR8Klh.png)
![linworks/fave60a back](https://i.imgur.com/j3mu8LFh.png)

The Fave60a PCB is a 60 keys keyboard designed by Lx3 (Linworks).
Matrix and Under RGB supported.

* Keyboard Maintainer: [keydler](https://github.com/duilchoi)
* Hardware Supported: Fave 60 PCBs. linworks 60key keyboards.
* Hardware Availability: Groupbuy.Check the ongoing ones on [the Linworks Discord](https://discord.gg/UC8gTdVnsj)

Make example for this keyboard (after setting up your build environment):

    make linworks/fave60a:default

Flashing example for this keyboard:

    make linworks/fave60a:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
