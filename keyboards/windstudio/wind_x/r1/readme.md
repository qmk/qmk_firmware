# WindX R1 by Windstudio

![Windstudio](https://windstudio.store)

A large layout keyboard without the function keys. [More info on geekhack.org](https://geekhack.org/index.php?topic=114767.0)

-   Keyboard Maintainer: [Christian C. Berclaz](https://github.com/chrisgve)
-   Hardware Supported: Wind X R1

Make example for this keyboard (after setting up your build environment):

    make windstudio/wind_x/r1:default

Flashing example for this keyboard:

    make windstudio/wind_x/r1:default:flash

See the [build environment setup](getting_started_build_tools) and the [make instructions](getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
