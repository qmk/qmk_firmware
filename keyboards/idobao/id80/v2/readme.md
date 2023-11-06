# IDOBAO ID80

![ID80](https://i.imgur.com/977ENjph.png)

A 75% hotswap keyboard from IDOBAO.

## ANSI support *(v1 & v2)*:

* Keyboard Maintainer: [Sergey Vlasov](https://github.com/sigprof)
* Hardware Supported:
    * IDOBAO ID80v1
    * IDOBAO ID80v2
* Hardware Availability: [IDOBAO.net](https://idobao.net/search?type=product&q=ID80*), [AliExpress](https://www.aliexpress.com/store/5072109/search?origin=y&SearchText=ID80)

Make example for this keyboard (after setting up your build environment):

    make idobao/id80/v2/ansi:default

To compile for the **v1** please use:

    make idobao/id80/v2:default BACKLIGHT_ENABLE=no
    
## ISO support *(v2-iso)*:

* Keyboard Maintainer: [Carsten Rose](https://github.com/cwr10010)
* Hardware Supported: IDOBAO ID80v2
* Hardware Availability: [IDOBAO](https://www.idobao.net/products/idobao-id80v2-75-hot-swappable-mechanical-keyboard-kit)

Make example for this keyboard (after setting up your build environment):

    make idobao/id80/v2/iso:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Escape key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available *(default is [Fn]+[Esc])*
