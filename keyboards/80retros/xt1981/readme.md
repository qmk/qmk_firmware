# 80Retros XT1981

A 70% mechanical keyboard with a C64-inspired retro aesthetic, gasket-mounted with a flex-cut PCB.

* Keyboard Maintainer: [awprice](https://github.com/awprice)
* Hardware Supported: 80Retros XT1981
* Hardware Availability: [StacksKB](https://stackskb.com/store/80retros-xt1981-frl-tkl-diy-kit-pre-order/), [KeyproKB](https://keyprokb.com/products/80retros-game1989-xt1981-barebone)

Make example for this keyboard (after setting up your build environment):

    make 80retros/xt1981:default

Flashing example for this keyboard:

    make 80retros/xt1981:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader by using one of the following:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Holding the physical reset button on the top of the PCB, under the spacebar, while plugging in the USB cable.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
