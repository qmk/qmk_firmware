# Kawayo

![Kawayo Board](https://cdn.shopify.com/s/files/1/0281/3122/9834/products/Kawayoo_1024x1024@2x.jpg?v=1650025682)

A board dedicated to Nakiri Ayame from Nakirigumi. 65% with top blocker.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot) and the Mecha Team
* Hardware Supported: Kawayo
* Hardware Availability: [Mecha Store](https://mecha.store)

Make example for this keyboard (after setting up your build environment):

    make kawayo:default
    make kawayo:via

If in Vial environment:

    make kawayo:vial

Flashing example for this keyboard:

    make kawayo:default:flash
    make kawayo:via:flash

If in Vial environment:

    make kawayo:vial:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Power up the board while having the `Reset/Boot0` pad shorted.

* **Keycode in layout**: Press the `GRV` key on layer 1 which is mapped to `RESET`
