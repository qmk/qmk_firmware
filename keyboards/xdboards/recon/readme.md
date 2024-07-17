# xdboards/recon

![xdboards/recon](https://xdboards.xyz/cdn/shop/files/20240522-132208.jpg?v=1716784494&width=1445)

A split low profile keyboard with hotswap sockets that is built around the Sea-Picro microcontroller for it's dedicated RGB pin.

* Keyboard Maintainer: [Daniel Weeks](https://github.com/Xanimos)
* Hardware Supported: Recon PCB, Sea-Picro, backwards compatibility with ProMicro pin layout.
* Hardware Availability: [xdboards.xyz shop](https://www.xdboards.xyz)

Make example for this keyboard (after setting up your build environment):

    make xdboards/recon:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the side of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Boot Magic**: Hold down the boot magic key while plugging in the USB cable


## Setup for non Sea-Picro microcontrollers

Solder the "Pro-Micro Compatibility" jumper on the bottom of both boards.

In your keymap directory:
  - add/modify a `rules.mk` file and insert `CONVERT_TO = <Desired Converter>` see [QMK Documentation](https://docs.qmk.fm/#/feature_converters)
  - add/modify a `config.h` file and insert `#define WS2812_DI_PIN D3`


## Setup for Underglow rgb only


Solder the "Per-Key RGB Skip" jumper on the bottom of both boards. Do not install per key RGBs.

In your keymap directory:
  - add/modify a `config.h` file and insert 
    ```
    #define RGB_MATRIX_SPLIT { 5, 5 }
    #define RGB_MATRIX_LED_COUNT 10
    ```
  