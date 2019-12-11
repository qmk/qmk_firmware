# YMD75 / MT84

75% keyboard from YMDK. YMDK sell the board and name it "YMD75", however the PCB has "MT84" printed on both sides.

* Keyboard Maintainer: [Wayne K Jones](github.com/WarmCatUK)
* Hardware Supported: YMD75/MT84 with the ATmega32a chip.
* Hardware Availability: <https://www.aliexpress.com/item/32812690592.html>

Make example for this keyboard (after setting up your build environment):

    make ymd75:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make ymd75:default:flash

**Reset Key**: Hold down the key located at *Key below the top right key*, commonly programmed as *Backspace* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
