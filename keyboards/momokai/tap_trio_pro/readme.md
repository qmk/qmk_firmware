# momokai/tap_trio_pro

![momokai/tap_trio_pro](imgur.com image replace me!)

Tap trio pro, a 6 key macropad with 3 hall effect switches

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: Tap trio pro
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make momokai/tap_trio_pro:default

Flashing example for this keyboard:

    make momokai/tap_trio_pro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (1,0) in the matrix (the left most micro switch) and plug in the keyboard
* **Physical reset button**: Hold down the BOOT1 button on the back of the PCB While plugging it in
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
