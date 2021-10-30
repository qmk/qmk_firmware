# 40rmie

![40rmie](https://i.imgur.com/KtS2UOa.jpg)

*The 40rmie, pronounced "forty-or-me" or "For-me" is a 40%ish keyboard designed by KuroTheCrazy. This board features base kit compatibility with a half numrow, partial fn row, nav cluster, and arrow keys, for perfect ease of use in gaming and work. *

* Keyboard Maintainer: [KuroTheCrazy](https://github.com/kurothecrazy)
* Hardware Supported: *40rmie v2 PCB*
* Hardware Availability: *https://p3dstore.com/products/40rmie-pcb-only?_pos=5&_sid=7abb756e4&_ss=r&variant=40371281232056*

Make example for this keyboard (after setting up your build environment):

    make 40rmie:default

Flashing example for this keyboard:

    make 40rmie:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available