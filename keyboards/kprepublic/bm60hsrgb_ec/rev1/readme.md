# BM60HSRGB_EC/rev1

A 60% hotswap inswitch RGB keyboard with an encoder from KP Republic. 

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: BM60HSRGB_EC/rev1
* Hardware Availability: [KP Republic](https://kprepublic.com/products/bm60ec-bm60-ec-rgb-60-gh60-hot-swappable-custom-mechanical-keyboard-pcb-programmed-qmk-via-rgb-switch-type-c-rotary-knob)

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Make example for this keyboard (after setting up your build environment):

    make kprepublic/bm60hsrgb_ec/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
