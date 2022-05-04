# AKIRA

* Keyboard Maintainer: [eugenepy](https://github.com/eugenepy)
* Hardware Supported: ARKIA pcb, both Hotswap and solderable. *The PCBs, controllers supported*
* Hardware Availability: Not yet on groupbuy *Links to where you can find this hardware*
# Build
Make example for this keyboard (after setting up your build environment):

    make ekow/akira:default

Flashing example for this keyboard:

    make ekow/akira:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the Buttom on the back of the PCB, the board will enter the dfu-mode, no extra pads need to short.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

