# Chaz

![Chaz](https://i.imgur.com/FeZQFYAh.png)

Low Profile, Choc Spaced QAZ-alike

* Keyboard Maintainer: [Jason Hazel](https://github.com/jasonhazel)
* Hardware Supported: Chaz, RP2040 Community Edition Compatible Controller
* Hardware Availability: [Open Source](https://github.com/hazels-garage/chaz), [Open Source](https://github.com/hazels-garage/chaz)

Make example for this keyboard (after setting up your build environment):

    make hazel/chaz/rp2040ce:default

Flashing example for this keyboard:

    make hazel/chaz/rp2040ce:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top-left key and plug in the keyboard
* **Physical reset button**: Press Hardware Reset Button
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create