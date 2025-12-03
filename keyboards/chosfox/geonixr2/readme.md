# Chosfox Geonix R2

A customizable 47-key keyboard.

* Hardware Supported: Chosfox Geonix R2 PCB with es32fs026 microcontroller

Make example for this keyboard (after setting up your build environment):

    make chosfox/geonixr2:default

Flashing example for this keyboard:

    make chosfox/geonixr2:default:flash

The keyboard supports VIA natively. Use the provided `VIA_Mapping_GeonixR2.JSON` file to configure it in VIA.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
