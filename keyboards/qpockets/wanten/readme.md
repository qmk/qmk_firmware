# wanten

![wanten](https://i.imgur.com/d7o1Edf.png)

an ortho drop in PCB for Van cases

* Keyboard Maintainer: [qpockets](https://github.com/qpockets)
* Hardware Supported: V1 wanten PCB
* Hardware Availability: [pocketspace discord server](https://discord.gg/fKbTxraHc6)

Make example for this keyboard (after setting up your build environment):

    make qpockets/wanten:default

Flashing example for this keyboard:

    make qpockets/wanten:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key or encoder) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
