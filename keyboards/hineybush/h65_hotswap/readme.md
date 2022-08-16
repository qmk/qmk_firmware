# h65 hotswap

![h65 hotswap](https://i.imgur.com/QKeHtDrh.png)

A 65%, hotswap, USB 2.0 Type C PCB. 

* Keyboard Maintainer: [hineybush](https://github.com/hineybush)
* Hardware Supported: h65hs, Singa Kohaku 
* Hardware Availability: Singa Kohaku Group Buy 

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Make example for this keyboard (after setting up your build environment):

    make hineybush/h65:default

Flashing example for this keyboard:

    make hineybush/h65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
