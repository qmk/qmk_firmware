# jiro42

![](https://booth.pximg.net/bb17ac0b-4e99-4a60-ba71-4ce5f6ba0553/i/6600959/98e51e1c-0b17-43bc-af7b-3d8e80a5c02a.jpg)

4 x 12 split keyboard.42keys,low profile key switch,jiro42 footprint is kailh v2

-   Keyboard Maintainer: [tm](https://github.com/tm)
-   Hardware Supported: atmega32u4
-   Hardware Availability: [BOOTH](https://hirotomi.booth.pm/items/6600959)

Make example for this keyboard (after setting up your build environment):

    make jiro42:default

Flashing example for this keyboard:

    make jiro42:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
