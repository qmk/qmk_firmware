# NCR-80

![NCR-80](https://ae01.alicdn.com/kf/H534a128591c34b138cc1cd19dcce98cfP.jpg)

> Re-imagination of the classic rebranded Cherry G81-3000 by NCR

NCR-80 is an affordable keyboard kit inspired by iconic vintage keyboards.

* Keyboard Maintainer: QMK Community
* Hardware Supported: ATmega32U4
* Hardware Availability: [AliExpress](https://www.aliexpress.com/item/1005003345941543.html)

Make example for this keyboard (after setting up your build environment):

    make ncr80:default
    
Flashing example for this keyboard:

    make ncr80:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
