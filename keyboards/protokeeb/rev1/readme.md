# Protokeeb

![Protokeeb]()

A 16-key (4 x 4) Numpad/Macropad/Midi device designed by A-Tech Officials for easily getting started in the field of custom keyboards.
Learn, build, modify easily as the Protokeeb is an open-source hardware project.
The PCB is based on a Raspberry Pi Pico development board.
Designed for developers and enthusiasts who wants to begin their journey in custom keyboards and keyboard firmware.
Per key south facing ARGB LED and much more.
For more info visit https://github.com/atechofficials/protokeeb

-   Keyboard Maintainer: [A-Tech Officials](https://github.com/atechofficials)
-   Hardware Supported: Protokeeb Keyboard PCB v1.x, Raspberry Pi Pico, Raspberry Pi Pico W, Waveshare RP2040-Plus
-   Hardware Availability: [atechofficials.com](https://atechofficials.com)

![Protokeeb Layout Image]()

# Default Protokeeb Layout

This is the default layout that comes flashed on every Protokeeb.
The deafult layout consists of 2 layers.
1st layer for the 16-key numpad, excluding the NUM LOCK key.
2nd layer for RGB LED control and keyboard boot options.

Make example of this keyboard (after setting up your build environment):

    make protokeeb:default

Flashing example for this keyboard:

    make protokeeb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Physical pcb buttons**: Briefly press and hold both the left and right (Bootsel and Reset) tactile push button located on the top left side of the Protokeeb, then keep holding the left (Bootsel) push button and release/let go the right (Reset) push button and then after 3-5 seconds also release/let go the left (Bootsel) push button to enter the bootloader mode.
-   **Bootmagic**: Press and hold the top left key (row-0, column-0) before plugging-in the keyboard to your PC/Laptop/host to enter the bootloader.
-   **Keycode in layout**: Press and hold the FN Key (row-4, column-1) then press the key mapped to `QK_BOOT` i.e ENTER Key (row-4, column-4) to enter the bootloader mode.
