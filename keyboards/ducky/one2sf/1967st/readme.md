# One 2 SF (DKON1967ST)

A 65% keyboard by Ducky.

* Keyboard Maintainer: [f7urry](https://github.com/f7urry)
* Hardware Supported: Ducky One 2 SF RGB (DKON1967ST), NUC123SD4AN0 + MBI5043GP
  * VIA still WIP.
  * RGB LEDs are currently disabled until the driver is merged.
  * DIP switches are disabled due to hardware incompatibilities 

## Compiling the Firmware:

    make ducky/one2sf/1967st/ansi:default
    make ducky/one2sf/1967st/iso:default

## Accessing Bootloader Mode

To enter the 1967ST bootloader to flash, boot the keyboard while holding D+L.

## Flashing the Firmware:

There are then two ways to flash the keyboard:

    pip install --user nuvoton-isp
    nuvoisp -f ducky_one2sf_1967st_ansi_default.bin

Alternatively you can use elfmimi's [nu-isp-cli](https://lib.rs/crates/nu-isp-cli) which is more complete than nuvoisp and allows flashing .hex files as well.

    cargo install nu-isp-cli
    nu-isp-cli flash ducky_one2sf_1967st_ansi_default.bin

    or

    make ducky/one2sf/1967st/ansi:default:flash
    make ducky/one2sf/1967st/iso:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
