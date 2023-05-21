# tn_alice

![tn_alice](https://imgur.com/a/9xCNjZz)

An Alice style board with arrowkeys made based on the Owlab Spring.

* Keyboard Maintainer: [Thong](https://github.com/thong-phn)
* Hardware Supported: TN Alice PCB 
* Hardware Availability: [Taobao](https://item.taobao.com/item.htm?id=691101549736&ft=t&toSite=main)

Make example for this keyboard (after setting up your build environment):

    make tn_alice:default

Flashing example for this keyboard:

    make tn_alice:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB (SW1)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Modding the underglow RGB

![tn_alice_underglow](https://imgur.com/yxfHrVs)