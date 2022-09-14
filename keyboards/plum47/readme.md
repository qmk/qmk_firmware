# plum47

![plum47](https://i.imgur.com/t3rjsWIh.png)

Plum47 is a 4-row, 12-column (47 key) ortholinear keyboard sold domestically in Japan as a 
home build kit.  It features MX sockets for hot-swap keyswitch support, and a bezel-less
acrylic sandwich case.  The controller is a Pro Micro.

* Keyboard Developer: [Masayuki Takagi](https://github.com/takagi)
* Keyboard submitted by [Andrew Hamilton](https://github.com/awh-tokyo)
* Hardware Supported: plum47 keyboard kit including PCB and Pro Micro controller
* Hardware Availability: https://shop.yushakobo.jp/products/consign_plum47

Make example for this keyboard (after setting up your build environment):

    make plum47:default

Flashing example for this keyboard:

    make plum47:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader as follows:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
