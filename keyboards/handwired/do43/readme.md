# Do43

![do43](https://i.imgur.com/pyk4MFk.jpg)

40% keyboard hand-modified to include an OLED display.

* Keyboard Maintainer: [Rocco Jiang](https://github.com/roccojiang)
* Hardware Supported: Do43 PCB, ATmega32U4
* Hardware Availability: [Taobao](https://item.taobao.com/item.htm?spm=a230r.1.14.16.513153eeQna2Bz&id=647976555089)

Make example for this keyboard (after setting up your build environment):

    make handwired/do43:default

Flashing example for this keyboard:

    make handwired/do43:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Short the `RST` and `GND` pins of the Pro Micro on the back of the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
