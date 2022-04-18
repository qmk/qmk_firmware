# BM60HSRGB_EC

A 60% hotswap inswitch RGB keyboard with rotary encoder from KP Republic. 

* Keyboard Maintainer: [luisgit9](https://github.com/luisgit9)
* Hardware Supported: BM60HSRGB_EC/rev2
* Hardware Availability: [KP Republic](https://kprepublic.com/products/bm60ec-bm60-ec-rgb-60-gh60-hot-swappable-custom-mechanical-keyboard-pcb-programmed-qmk-via-rgb-switch-type-c-rotary-knob)

Make example for this keyboard (after setting up your build environment):

    for rev2: make kprepublic/bm60hsrgb_ec/rev2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways in rev2 board:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the Escape key in the default layout) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` (MO(1) + Backspace in the default layout)
