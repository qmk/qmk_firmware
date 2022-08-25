# dynamis

## general information
![dynamis](https://i.imgur.com/q2C3D2ul.jpg)

Gasket mounted 65% row staggered keyboard integrated a trackball

* Keyboard Maintainer: [bbrfkr](https://github.com/bbrfkr/)
* Hardware Supported: dynamis PCBs
* Hardware Availability: http://github.com/bbrfkr/keyboards

## bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## build and flash firmware

Make example for this keyboard (after setting up your build environment):

    make bbrfkr/dynamis:default

Flashing example for this keyboard:

    make bbrfkr/dynamis:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
