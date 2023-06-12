# The Uni v1 and v2

![Uni v2](https://i.imgur.com/hIIK8xN.jpg)

-   Keyboard Maintainer: [Peter](https://github.com/petercpark)
-   Link to Keyboard Files: [The_Uni](https://github.com/petercpark/The_Uni) (For personal use only)
-   Hardware Supported:
    -   The Uni v1 and v2 (pro_micro)
-   Hardware Availability: [https://www.stenokeyboards.com](https://www.stenokeyboards.com)

# Bootloader

Enter the bootloader by:

-   **Physical reset button**: On the Uni v3, briefly press the button on the back of the PCB.
-   **Reset Pads**: Uni v1 and v2 have pins/pads you must short instead (RST to GND).

Make examples for this keyboard (after setting up your build environment):

    make stenokeyboards/the_uni/pro_micro:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
