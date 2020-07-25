# Plaid-Pad
<img src="https://i.imgur.com/Jovhxpr.jpg" width="400">
<img src="https://i.imgur.com/V82cMqq.png" width="400">

A 4x4 numpad with only through hole components.  
It's a great companion to the Plaid keyboard by [hsgw](https://github.com/hsgw/) and heavily inspired by it.

* Keyboard Maintainer: BenRoe [GitHub](https://github.com/BenRoe) / [Twitter](https://twitter.com/keycapsss)
* Hardware Supported: ATmega328P with VUSB ([see Bootloader section](#Bootloader))
* Hardware Availability: [Keycapsss.com](https://keycapsss.com)

Make example for this keyboard (after setting up your build environment):

    make keycapsss/plaid_pad:default

Flashing example for this keyboard:

    make keycapsss/plaid_pad:default:flash

## Bootloader
- same usbasploader as Plaid ([Instruction](https://github.com/hsgw/plaid/blob/master/doc/en/bootloader.md), [Repository](https://github.com/hsgw/USBaspLoader/tree/plaid))

---

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
