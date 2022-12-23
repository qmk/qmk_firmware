# navpad 1.0 with Helix (Right hand side)

![10_helix_r](https://imgur.com/ehTI37h.jpg)

Navpad connected with helix keyboard (Right Side)

* Keyboard Maintainer: [yushakobo](https://github.com/yushakobo)
* Hardware Supported: Navpad 1.0 PCB and Helix PCB, Pro Micro
* Hardware Availability: https://shop.yushakobo.jp/products/navpad-10

Make example for this keyboard (after setting up your build environment):
    
    make yushakobo/navpad/10_helix_r:default

Flashing examples for this keyboard...

Helix side:
    
    make yushakobo/navpad/10_helix_r:default:avrdude-split-right
    
Navpad side:

    make yushakobo/navpad/10_helix_r:default:avrdude-split-left

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
