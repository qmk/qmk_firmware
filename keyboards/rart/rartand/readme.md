# Rartand

![Top](https://user-images.githubusercontent.com/30220306/107148148-4b9b4a80-6984-11eb-9e2b-d0f6be4419de.png)

A 50% Mechanical Keyboard ( 60% exclude number row ) with Atmega328p with trough hole component, based on [IMKG](https://www.facebook.com/groups/indomechanicalkeyboard/) (Indonesia Mechanical Keyboard Group).

* Keyboard Maintainer: [Alabahuy](https://github.com/alabahuy)
* Hardware Supported: RARTAND PCB, Mini USB, OLED, ATMEGA328p with vusb
* Hardware Availability: Private GB 

Make example for this keyboard (after setting up your build environment):

    make rart/rartand:default

Flashing example for this keyboard:

    make rart/rartand:default:flash

## Bootloader
use usbasploader in hgsw repository.
https://github.com/hsgw/USBaspLoader/tree/plaid

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
