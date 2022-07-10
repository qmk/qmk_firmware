# The Uni

​
![Layout](https://docs.stenokeyboards.com/images/uni-layout.png)
![The Uni v2](https://github.com/petercpark/The_Uni/blob/main/Pics/uni%20v2/uni-v2.JPG?raw=true)

A compact unibody split ortholinear keyboard made specifically for stenography.

-   Keyboard Maintainer: [Peter](https://github.com/petercpark)
-   Link to Keyboard Files (pro_micro version): [https://github.com/petercpark/The_Uni](https://github.com/petercpark/The_Uni)
-   Hardware Supported:

    -   The Uni v1 and v2 (pro_micro)
    -   The Uni v3 (usb_c)

-   Hardware Availability: [https://www.stenokeyboards.com](https://www.stenokeyboards.com)

# Bootloader

Enter the bootloader by:

* **Physical reset button**: On the Uni v3, briefly press the button on the back of the PCB.
* **Reset Pads**: Uni v1 and v2 have pins/pads you must short instead (RST to GND).

Make examples for this keyboard (after setting up your build environment):

    make the_uni/pro_micro:default

    make the_uni/usb_c:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
