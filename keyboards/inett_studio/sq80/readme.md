# FOX × iNETT Studio SQUARE 80%

![sq80](https://i.imgur.com/LM1aSMEh.jpg)

_A TKL keyboard from the iNETT Studio's SQUARE series._

-   Keyboard Maintainer: [Wraul](https://github.com/Wraul)
-   Hardware Supported: The QMK compatible hot swappable PCB offered during the GB
-   Hardware Availability: [Geekhack Group Buy](https://geekhack.org/index.php?topic=100769.0)

Make example for this keyboard (after setting up your build environment):

    make inett_studio/sq80:default

Flashing example for this keyboard:

    make inett_studio/sq80:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The PCB is delivered with a forked version of QMK.  
At this moment it is not apparent if the stock firmware comes with a keybinding for entering the bootloader.

Enter the bootloader with the stock firmware:

-   **Physical reset button**: Briefly press the button on the back of the PCB

After flashing it is possible to enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the escape key and plug in the keyboard
-   **Physical reset button**: Briefly press the button on the back of the PCB
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
