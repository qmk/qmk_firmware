# kuku65

The following is the QMK Firmware for the kuku65 Hotswap PCB.

The PCB features:
* QMK & VIA compatibility
* Hotswap

---

* Keyboard Maintainer: [ToastyStoemp](https://github.com/ToastyStoemp)

Make example for this keyboard (after setting up your build environment):

    make wolf/kuku65:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 3 ways: 
* **Bootmagic reset**: Hold down the key ESC key and plug in the keyboard (Top Left most switch)
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the B key on layer 1 which is mapped to `QK_BOOT`
