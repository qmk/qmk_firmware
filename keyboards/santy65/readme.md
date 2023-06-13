# santy65

![Santy65](https://i.imgur.com/VcNGcUT.jpg)

A split 65% keyboard using 2 rotary encoders and a trackball. 
Can be built with either:
- 2 elite-C microcontrollers.
- 1 elite-C microcontroller on the left side and a pro-micro on the right side.

* Keyboard Maintainer: [santy](https://github.com/santy81855)
* Hardware Supported: Elite-c, pro-micro, EC11 rotary encoders, pmw 3360 sensor.

Make example for this keyboard (after setting up your build environment):

    make santy65:default

Flashing example for this keyboard:

    make santy65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
