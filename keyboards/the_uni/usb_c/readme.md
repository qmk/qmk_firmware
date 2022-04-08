# The Uni v3 Firmware

-   Keyboard Maintainer: [Peter](https://github.com/petercpark)
-   Link to Keyboard Files: Not Available
-   Hardware Supported:
    -   The Uni v3 (usb_c)
-   Hardware Availability: [https://www.stenokeyboards.com](https://www.stenokeyboards.com)

## Bootloader

Enter the bootloader by:

* **Physical reset button**: On the Uni v3, briefly press the button on the back of the PCB.
* **Reset Pads**: Uni v1 and v2 have pins/pads you must short instead (RST to GND).

Make examples for this keyboard (after setting up your build environment):

    make the_uni/usb_c:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
