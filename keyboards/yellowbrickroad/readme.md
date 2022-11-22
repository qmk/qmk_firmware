# yellowbrickroad

![yellowbrickroad](https://i.imgur.com/sy1wYZoh.jpg)

"There’s no place like home.” I designed this keyboard since I wanted to go back to Kansas, LOL.

yellowbrickroad is a MIDI keyboard which has 53 keys (= 4 octaves+ ) placed spirally. Raspberry Pi Pico is used as the "brain" of yellowbrickroad.

Size: 20 cm (approx 8 inches) x 23 cm (approx 9 inches).
It fits in an A4 / Letter size paper.

* Keyboard Maintainer: [3araht](https://github.com/yourusername)
* Hardware Supported: yellowbrickroad keyboard, a MIDI keyboard.
* Hardware Availability: [Yushakobo](https://shop.yushakobo.jp/collections/keyboard/products/3442), [BOOTH](https://3araht.booth.pm/). Click [here](https://www.tenso.com/en/static/lp_shop_booth) for BOOTH overseas shipping!

Make example for this keyboard (after setting up your build environment):

    make yellowbrickroad:default

Flashing example for this keyboard:

    make yellowbrickroad:default:flash

Run this while Raspberry Pi Pico is in bootloader mode.
## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly double-tap the reset button on the side of the PCB
* **Physical BOOTSEL button**: Press the BOOTSEL button and hold it while you connect a micro USB cable to your computer.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
