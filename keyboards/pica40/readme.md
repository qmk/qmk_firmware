# pica40

![pica40](https://i.imgur.com/CKImjAPh.jpg)

A family of 40-key split ortholinear keyboards with rotary encoder.

-   Keyboard Maintainer: [zzeneg](https://github.com/zzeneg)
-   Hardware Supported: Pica40 PCBs, Pro Micro (rev1), XIAO RP2040/nRF52840 (rev2)
-   Hardware Availability: [GitHub](https://github.com/zzeneg/pica40)

Make example for this keyboard (after setting up your build environment):

    make pica40:default
    make pica40/rev1:default

Flashing example for this keyboard:

    make pica40:default:flash
    make pica40/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
-   **Keycode in layout**: Press the key mapped to `RESET` if it is available
