# NCR-80

![NCR-80](https://i.imgur.com/kAjbAPLl.jpg)

> Re-imagination of the classic rebranded Cherry G81-3000 by NCR

NCR-80 is an affordable keyboard kit inspired by iconic vintage keyboards.

* Keyboard Maintainer: QMK Community
* Hardware Supported:
  * NCR-80 R2 PCBs (ATmega32U4, atmel-dfu)
* Hardware Availability:
  * R2 Hotswap: [AliExpress](https://www.aliexpress.com/item/1005003345941543.html) [Taobao 淘宝](https://item.taobao.com/item.htm?id=657482028672)
  * R2 Solder: [AliExpress](https://www.aliexpress.com/item/1005003364462523.html) [Taobao 淘宝](https://item.taobao.com/item.htm?id=657482028672)

Make example for this keyboard (after setting up your build environment):

    make mt/ncr80/r2/hotswap:default
    make mt/ncr80/r2/solder:default

Flashing example for this keyboard:

    make mt/ncr80/r2/hotswap:default:flash
    make mt/ncr80/r2/solder:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.
