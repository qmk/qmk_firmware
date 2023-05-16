# Bad Wings

![Bad Wings](https://i.imgur.com/QpfcEj8h.png)

36 key unibody split

* Keyboard Maintainer: [Jason Hazel](https://github.com/jasonhazel)
* Hardware Supported: Bad Wings v1
* Hardware Availability: [Hazel's Garage](https://shop.hazel.cc/products/bad-wings)

Make example for this keyboard (after setting up your build environment):

    make hazel/bad_wings:default

Flashing example for this keyboard:

    make hazel/bad_wings:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top-left key and plug in the keyboard
* **Physical reset button**: Hold Xiao B button, press Xiao R button, release B
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create