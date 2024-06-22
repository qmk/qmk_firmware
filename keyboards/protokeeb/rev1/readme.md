# Protokeeb

![Protokeeb](https://i.imgur.com/RsSBoJg.jpg)

The Protokeeb is a versatile 16-key (4 x 4) Numpad/Macropad/Midi device designed by A-Tech Officials. It is perfect for anyone looking to get started with custom keyboards. This open-source hardware project is based on a Raspberry Pi Pico development board, making it easy to learn, build, and modify. Designed for developers and enthusiasts alike, the Protokeeb features per-key south-facing ARGB LEDs and much more.

For more information, visit the [Protokeeb GitHub page](https://github.com/atechofficials/protokeeb).

-   **Keyboard Maintainer:** [A-Tech Officials](https://github.com/atechofficials)
-   **Hardware Supported:** Protokeeb Keyboard PCB v1.x, Raspberry Pi Pico, Raspberry Pi Pico W, Waveshare RP2040-Plus
-   **Hardware Availability:** [ProtoKeeb](https://github.com/atechofficials/protokeeb)

![Protokeeb Layout Image](https://i.imgur.com/e0RlllX.png)

## Default Protokeeb Layout

The default layout comes pre-flashed on every Protokeeb and consists of two layers:

-   Layer 1: 16-key numpad, excluding the NUM LOCK key.
-   Layer 2: RGB LED control and keyboard boot options.

To build the default layout, use the following command after setting up your build environment:

```go
make protokeeb:default
```

To flash the default layout, use:

```go
make protokeeb:default:flash
```

For more information, see the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide). If you're new to QMK, start with the [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

You can enter the bootloader in three ways:

-   **Bootmagic**: Press and hold the top left key (row-0, column-0) before plugging-in the keyboard to your PC/Laptop/host.

-   **Physical PCB buttons**: Briefly press and hold both the left (Bootsel) and right (Reset) tactile push buttons located on the top left side of the Protokeeb. Keep holding the left (Bootsel) button, release the right (Reset) button, then release the left (Bootsel) button after 3-5 seconds to enter bootloader mode.

-   **Keycode in Layout**: Press and hold the FN Key (row-4, column-1) then press the key mapped to `QK_BOOT` (ENTER Key, row-4, column-4) to enter bootloader mode.
