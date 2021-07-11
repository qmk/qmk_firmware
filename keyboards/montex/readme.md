# IDOBAO MONTEX

A hotswap numpad from IDOBAO.
    
## Support:

* Keyboard Maintainer: [NachoxMacho](https://github.com/NachoxMacho)
* Hardware Supported: IDOBAO MONTEX
* Hardware Availability: [IDOBAO](https://www.idobao.net/products/ldobao-montex-pad-hot-swappable-mechanical-keyboard-kit)


To jump to the bootloader, the default in the repository and stock on the board is to hold the 4th key on the top row and tap the first key in the top row. 
On some stock keyboard firmware, the top and second from the top row pins have been reversed so you may need to press those keys on the second row.
If none of that works, there is a reset button on the PCB underside which you can access by removing the back plate.
Then press the button labeled SW2 located between the 2 upper LEDs.

Make example for this keyboard (after setting up your build environment):

    make montex:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
