# YMD75 / MT84

75% keyboard from YMDK. YMDK sell the board and name it "YMD75", however revision 1 of the PCB has "MT84" printed on both sides.

* Keyboard Maintainer: [Wayne K Jones](github.com/WarmCatUK)
* Hardware Supported: 
   - rev1 (ATmega32a) 
   - rev2 (ATmega32a) 
   - rev3 (ATmega32u4)
* Hardware Availability: <https://www.aliexpress.com/item/32812690592.html>

Make example for this keyboard (after setting up your build environment):

    make ymd75/rev1:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make ymd75/rev1:default:flash

**Reset Key**: Hold down the key located at *Key below the top right key*, commonly programmed as *Backspace* while plugging in the keyboard. On PCB revision 2, enter the bootloader by holding `L_CTRL` while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
