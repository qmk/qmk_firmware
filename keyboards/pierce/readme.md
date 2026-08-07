# Pierce

![Pierce](https://i.imgur.com/JOUH1UIh.jpeg)

A modular wireless / semi-wireless split 36 key keyboard. Wireless version uses a dongle as a receiver for both halves while the semi-wireless version uses the wired half as a receiver for the wireless half.
Supports MX, Choc V1 and Alps switches.

 * Keyboard Maintainer: [durken1](https://github.com/durken1/)
 * Hardware Supported: pierce 2.0
 * Hardware Information: [pierce](https://github.com/durken1/pierce)

Make example for this keyboard (after setting up your build environment):

    make pierce:default

Flashing example for this keyboard:

    make pierce:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the dongle / wired half
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
