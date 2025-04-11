# handwired/bad_numpad

![handwired/bad_numpad](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [LucaFrankfurt](https://github.com/LucaFrankfurt)
* Hardware Supported: handwired, Micro Pro
* Hardware Availability: [*Pro Micro Aliexpress*](https://de.aliexpress.com/item/1005006742987619.html?spm=a2g0o.order_list.order_list_main.11.1bd65c5fNnE3iV&gatewayAdapt=glo2deu)

Make example for this keyboard (after setting up your build environment):

    make handwired/bad_numpad:default

Flashing example for this keyboard:

    make handwired/bad_numpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
