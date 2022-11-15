# Jorne

<img src="https://i.imgur.com/ywDcw2w.jpg" data-canonical-src="Jorne" width="600"/>

Jorne is essentially [Corne](https://github.com/foostan/crkbd) but with an extra keys for brackets and international layouts (44 keys instead of 42).

* Keyboard Maintainer: [joric](https://github.com/joric)
* Hardware Supported: Jorne 2.1, 3.0
* Layout: [keyboard-layout-editor.com](http://www.keyboard-layout-editor.com/#/gists/df19fba80500d1179dfda8c41b9f221a)
* Hardware Availability: [wiki](https://github.com/joric/jorne/wiki)

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the reset button on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT`

## Make 

Make example for this keyboard (after setting up your build environment):

    make jorne/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
