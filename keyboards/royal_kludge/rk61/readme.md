# Royal Kludge RK61

![Royal Kludge RK61](https://imgur.com/9YoEEkH.jpg)

* Keyboard Maintainer: [DEREFERENC3D](https://github.com/DEREFERENC3D)
* Hardware Supported: Royal Kludge RK61 - wired-only QMK version
* Hardware Availability: [RKGaming.com](https://en.rkgaming.com/product/43/), [Amazon.com](https://www.amazon.com/RK-ROYAL-KLUDGE-Mechanical-Ultra-Compact/dp/B0832LSV8N)

Make example for this keyboard (after setting up your build environment):

    make royal_kludge/rk61:default

Flashing example for this keyboard:

    make royal_kludge/rk61:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Escape key and plug in the keyboard (this one might be disabled on the stock firmware)
* **Physical reset button**: Briefly press the button on the PCB, located under the space bar keycap, to the right of the space bar's switch
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available. On the stock firmware, VIA should allow it to be mapped.
