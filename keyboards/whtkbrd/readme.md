# Whtkbrd

![Whtkbrd](https://i.imgur.com/xQbjgjSh.jpeg)

Split keyboard for Kailh Choc switches based on STM32F072. Heavily inspired by [Keyseebee](https://github.com/TeXitoi/keyseebee).

-   Keyboard Maintainer: [Alexander Metz](https://github.com/wahtak)
-   Hardware Supported: [Whtkbrd](https://oshwlab.com/whtk/keeb1)
-   Hardware Availability: Fabrication with JLCPCB

## Flashing intructions

Build the keyboard firmware for the default layout (after setting up your build environment):

    make whtkbrd:default

Enter the bootloader by holding down the `BOOT` switch while pressing the `RESET` switch.

Flash the resulting `.bin` onto the keyboard with a utility like `dfu-util`. Alternatively, you can build and flash using:

    make whtkbrd:default:flash

## More information

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
