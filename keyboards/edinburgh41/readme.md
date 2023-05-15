# edinburgh41

![edinburgh41](https://i.imgur.com/Lrjyp6nh.png)

A small 40% board based on gtip's reviung41. The gasket mounted edinburgh41 features joystick with versatile functionality and rgb underglow.

* Keyboard Maintainer: [Lalit Mistry](https://github.com/schwarzer-geiger)
* Hardware Supported: edinburgh41 pcb with pro micro or wired equivalent
* Hardware Availability: Contact me, lalitmistry1407@gmail.com

Make example for this keyboard (after setting up your build environment):

    make edinburgh41:default

Flashing example for this keyboard:

    make edinburgh41:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down top left key while plugging keyboard into computer
* **Physical reset button**: Short RST and GND pins
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
