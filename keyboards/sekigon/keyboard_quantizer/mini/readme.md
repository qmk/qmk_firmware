# Keyboard Quantizer Mini

![sekigon/keyboard_quantizer/mini](https://i.gyazo.com/aca68f4592ff92eea99a55d710bd2ae3.jpg)

*A keyboard converter powered by QMK*

* Keyboard Maintainer: [sekigon-gonnoc](https://github.com/sekigon-gonnoc)
* Hardware Supported: The hardware of [Keyboard Qauntizer](https://github.com/sekigon-gonnoc/keyboard-quantizer-doc)
* Hardware Availability: Available at [BOOTH](https://nogikes.booth.pm/items/2256612)

Make example for this keyboard (after setting up your build environment):

    make sekigon/keyboard_quantizer/mini:default

Flashing example for this keyboard:

    make sekigon/keyboard_quantizer/mini:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Virtser**: Send `b` to the device through virtser
