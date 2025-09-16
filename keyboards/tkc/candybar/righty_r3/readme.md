# TheKey.Company Candybar

![Candybar](https://cdn.shopify.com/s/files/1/1679/2319/products/CBR3CollectionHERO_720x.jpg)

The Key Company Candybar is a staggered 40% board with a numpad utilizing the ATmega32u4 microcontroller.

* Keyboard Maintainer: [Terry Mathews](https://github.com/TerryMathews/)
* Hardware Supported: TKC Candybar
* Hardware Availability: [TheKey.Company](https://thekey.company/products/candybar-round-3)

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (default Escape key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB

Make example for this keyboard (after setting up your build environment):

    make tkc/candybar/righty_r3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
