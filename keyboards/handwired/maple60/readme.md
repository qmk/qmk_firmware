# maple60

A handwired 60% keyboard with maple case.

![inside](https://i.imgur.com/mDJDwTth.jpg)
![finished](https://i.imgur.com/gIoEg6ch.jpg)

* Keyboard Maintainer: [Jay](https://github.com/Toofty5)
* Hardware Supported: [Elite C v4](https://keeb.io/products/elite-c-low-profile-version-usb-c-pro-micro-replacement-atmega32u4)
* Hardware Availability: See Above

Make example for this keyboard (after setting up your build environment):

    make handwired/maple60:default

Flashing example for this keyboard:

    make handwired/maple60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
