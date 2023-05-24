# jels88

![jels88](https://i.imgur.com/7kuYR4G.png)

* Keyboard Maintainer: [jels](https://github.com/Jels02)
* Hardware Supported: jels88b/jels88c PCB
* Hardware Availabililty: Group buys, Various dates.

Make example for this keyboard (after setting up your build environment):
    
    make jels/jels88:default

Flashing example for this keyboard:

    make jels/jels88:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top right key (ESC) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
