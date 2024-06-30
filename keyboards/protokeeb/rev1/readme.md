# Protokeeb Rev1

![Protokeeb](https://i.imgur.com/RsSBoJg.jpg)

The Protokeeb is a versatile 16-key (4 x 4) Numpad/Macropad/MIDI device designed by A-Tech Officials. It is perfect for anyone looking to get started with custom keyboards. This open-source hardware project is based on a Raspberry Pi Pico development board, making it easy to learn, build, and modify. Designed for developers and enthusiasts alike, the Protokeeb features per-key south-facing ARGB LEDs and much more.

For more information, visit the [Protokeeb GitHub page](https://github.com/atechofficials/protokeeb).

-   **Keyboard Maintainer:** [A-Tech Officials](https://github.com/atechofficials)
-   **Hardware Supported:** Protokeeb Keyboard PCB v1.x, Raspberry Pi Pico, Raspberry Pi Pico W, Waveshare RP2040-Plus
-   **Hardware Availability:** [ProtoKeeb](https://github.com/atechofficials/protokeeb)

## Default Protokeeb Layout

![Protokeeb Layout Image](https://i.imgur.com/e0RlllX.png)

The default layout comes pre-flashed on every Protokeeb and consists of two layers:

-   Layer 1: 16-key numpad, excluding the `NUM LOCK` key.
-   Layer 2: RGB LED control and keyboard boot options.
-   Layer 3: Media control, quick launch application and other options.
-   Layer 4: Function Keys.

Make example for this keyboard (after setting up your build environment):

    make protokeeb/rev1:default

Flashing example for this keyboard:

    make protokeeb/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset:** Press and hold the top left key (row-0, column-0) before plugging-in the keyboard into your PC/Laptop.

-   **Physical reset buttons:** Briefly press and hold both the left (Bootsel) and right (Reset) tactile push buttons located on the top left side of the Protokeeb rev1 PCB. Keep holding the left (Bootsel) button, release the right (Reset) button, then release the left (Bootsel) button after 3-5 seconds to enter bootloader mode.

-   **Keycode in Layout:** Press and hold the 0-key (row-4, column-1) then press the key mapped to `QK_BOOT` (Plus + key, row-4, column-4) to enter bootloader mode.
