# Idobao ID96

![Idobao ID96](https://cdn.shopify.com/s/files/1/0382/1348/4675/products/96.png?v=1620272768)

96-key Keyboard from Idobao. The PCB for this board is also commonly used in the Drop NYM96 and YMDK Melody96

* Keyboard Maintainer: [Vino Rodrigues](https://github.com/vinorodrigues)
* Hardware Supported: Idobao ID96
* Hardware Availability: [Idobao ID96](https://www.idobao.net/collections/90/products/idobao-id96-aluminum-keyboard-kit)

Make example for this keyboard (after setting up your build environment):

    make idobao/id96:default

Flashing example for this keyboard:

    make idobao/id96:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
