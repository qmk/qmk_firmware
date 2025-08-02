# Plank Handwired

![plank handwired](https://i.imgur.com/khseWs7.jpeg)

A compact 40% (12x4) ortholinear keyboard kit sold by OLKB before the PCB was released.

Keyboard Maintainer: [Wholteza](https://github.com/wholteza)
Hardware Supported: [Teensy 2.0](https://www.pjrc.com/store/teensy.html)
Hardware Availability: [PJRC](https://www.pjrc.com/store/teensy.html)

Make example for this keyboard (after setting up your build environment):

    make handwired/planck:default

Flashing example for this keyboard:

    make handwired/planck:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (The left key closest to the USB Port) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
