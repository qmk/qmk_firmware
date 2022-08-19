# ADM42

![ADM42](https://i.imgur.com/pviCQSQh.jpeg)

A compact ergonomic 40% ortholinear keyboard. [More info on ADM42.dev](https://adm42.dev)

* Keyboard Maintainer: [Lorenzo Leonini](https://github.com/lleonini)  
* Hardware Supported: ADM42
* Hardware Availability: [Shop](https://shop.adm42.dev)

Make example for this keyboard (after setting up your build environment):

    make adm42:default

Flashing example for this keyboard:

    make adm42:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `RESET` if it is available
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
