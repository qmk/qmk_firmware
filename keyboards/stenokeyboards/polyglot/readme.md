# Polyglot

The [Polyglot](https://stenokeyboards.com/products/polyglot-keyboard) is a keyboard by StenoKeyboards that allows both steno and qwerty typing.

![The Polyglot](https://i.imgur.com/sqBRED1.jpg)

-   Hardware Supported:
    -   The Polyglot
-   Hardware Availability: [https://www.stenokeyboards.com](https://www.stenokeyboards.com)
-   Uses the rp2040 chip

# Bootloader

Enter the bootloader by:

-   **Physical boot button**:
    -   First, unplug the Polyglot.
    -   Then press and hold the button on the back of the PCB marked "B" while you plug in the keyboard. This will register the keyboard as a storage device on the computer.
    -   Copy and paste the .uf2 file in the top directory of the device. Once done, it will automatically reboot the keyboard.

Make examples for this keyboard (after setting up your build environment):

    qmk compile -kb stenokeyboards/polyglot -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
