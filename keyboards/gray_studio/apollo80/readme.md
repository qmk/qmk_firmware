# APOLLO 80

80% / TKL keyboard with a 5.5 degree angle ran by Airpotter. PCB Manufactured by DEMO Studio and Keyboard manufactured by Gray Studio.

-   Keyboard Maintainer: [Chris Beswick](https://github.com/ChrisBeswick/)
-   Hardware Supported: Stock / Default Apollo80 PCB
-   Hardware Availability: [Geekhack GB](https://geekhack.org/index.php?topic=110033.0)
-   Group Buy Location: [Graystudio.club](https://graystudio.club/products/gb-space80-apollo)

How to build this firmware using QMK MSYS

    qmk compile -kb gray_studio/apollo80 -km default

Make example for this keyboard (after setting up your build environment using make):

    make gray_studio/apollo80:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Physical reset button**: Bridge the pads labelled 'RE' underneath the Space Bar.
-   **Keycode in layout**: Hold MO(1) and press ESC (If you've changed bindings from the default, this may not be the case)
