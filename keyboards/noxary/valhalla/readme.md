# Noxary Valhalla

![valhalla](https://cdn.shopify.com/s/files/1/0071/6377/3043/products/BG_AngleL_a247224d-f9ca-4093-b0de-df776e34b02d_900x.jpg?v=1598742611)

An ergonomic 65% by Noxary

* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: proprietary PCB
* Hardware Availability: [Noxary](https://noxary.co/collections/valhalla). As of november 17, the group buy has ended.


## How to flash

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: press the button on the front of the PCB, next to caps lock, for at least five seconds
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

## Compile firmware

Make example for this keyboard (after setting up your build environment):

    make noxary/valhalla:default

To directly flash the PCB after it is put into a DFU state, use

    make noxary/valhalla:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
