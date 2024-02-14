# synapse

![synapse](https://i.imgur.com/OQNNPBhh.jpg)

Stagger PCB for Cervello!

* Keyboard Maintainer: https://github.com/qpockets
* Hardware Availability: [P3D Store](https://p3dstore.com/products/cervello-acrylic-keyboard-case-and-pcb-group-buy?_pos=4&_sid=fd078da46&_ss=r&variant=40398412677304) Group Buy

Make example for this keyboard (after setting up your build environment):

    make p3d/synapse:default

Flashing example for this keyboard:

    make p3d/synapse:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* 
