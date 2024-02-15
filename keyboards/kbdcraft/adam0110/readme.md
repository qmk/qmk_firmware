# KBDCraft Core64 / Adam0110

The updated version (03.02.2024) of the Adam64. It was introduced with KBDCraft's new Lilith board, based on the Core64 PCB type-a, which allows inter-PCB communication with other modules.

![Lilith](https://img-va.myshopline.com/image/store/1660550082582/DSC01026.png)

A 64-key mechanical keyboard comprised of Legos, with a typing angle of 5.5° with the Lilith case.

* Keyboard Maintainer: The QMK Community (@bodobraegger)
* Hardware Supported: STM32F401
* Hardware Availability: 
  * https://kbdcraft.store/products/lilith
  * https://kbdcraft.store/products/adam

Make example for this keyboard (after setting up your build environment):

    make kbdcraft/adam0110:default

Flashing example for this keyboard:

    make kbdcraft/adam0110:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
