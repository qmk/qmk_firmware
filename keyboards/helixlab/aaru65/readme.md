# aaru65

![aaru65](https://i.imgur.com/GPkDN26h.jpg)

The aaru65 is a 63-key keyboard supporting 65% layout and MIDI fader. This keyboard also features RGB matrix for hotswap PCB, and a single auto-breathing RGB indicator for soldered PCB.

* Keyboard Maintainer: [luantty2](https://github.com/luantty2)
* Hardware Supported: Aaru65 soldered PCB, Aaru65 hotswap PCB
* Hardware Availability: [HelixLab Store](https://helix.site/)

## Compiling

Make example for this keyboard (after setting up your build environment):

    make helixlab/aaru65/soldered:default

Alternatively:

    qmk compile -kb helixlab/aaru65/soldered -km default


## Flashing

Flashing example for this keyboard:

    make helixlab/aaru65/soldered:default:flash

Alternatively:

    qmk flash -kb helixlab/aaru65/soldered -km default

For hotswap PCB, replace "soldered" with "hotswap".

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. 

Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the ESC key and plug in the keyboard.
* **Physical reset button**: Hold down the reset button on the back of the PCB and plug in the keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
