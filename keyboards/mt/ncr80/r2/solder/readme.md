# NCR-80

![NCR-80](https://i.imgur.com/kAjbAPLl.jpg)

> Re-imagination of the classic rebranded Cherry G81-3000 by NCR

NCR-80 is an affordable keyboard kit inspired by iconic vintage keyboards.

* Keyboard Maintainer: QMK Community
* Hardware Supported: ATmega32U4
* Hardware Availability: [AliExpress](https://www.aliexpress.com/item/1005003364462523.html) [Taobao 淘宝](https://item.taobao.com/item.htm?id=657482028672)

Make example for this keyboard (after setting up your build environment):

    make ncr80/solder:default
    
Flashing example for this keyboard:

    make ncr80/solder:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).