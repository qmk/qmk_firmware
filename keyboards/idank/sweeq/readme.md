# Sweeq

![sweeq](https://i.imgur.com/TGSyHHxh.png)

*Sweeq is a Ferris Sweep clone that uses diodes, instead of the latter's direct pin matrix.*

The primary goal is to free up the SDA/SCL pins so they can be used by auxiliary devices such as a trackball, trackpoint or an OLED screen.

Other than the diode changes and the ability to use hotswap sockets, this keyboard is identical to the original Sweep.

* Keyboard Maintainer: [@idank](https://github.com/idank)
* Hardware Supported: [sweeq](https://github.com/idank/keyboards/tree/main/sweeq)
* Hardware Availability: *[holykeebs](https://holykeebs.com)*

Make example for this keyboard (after setting up your build environment):

    make idank/sweeq:default

Flashing example for this keyboard:

    make idank/sweeq:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
