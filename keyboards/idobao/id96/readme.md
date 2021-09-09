# Idobao ID96

![Idobao ID96](https://cdn.shopify.com/s/files/1/0382/1348/4675/products/96.png?v=1620272768)

96-key Keyboard from Idobao. The PCB for this board is also commonly used in the Drop NYM96 and YMDK Melody96

Keyboard Maintainer: [Vino Rodrigues](https://github.com/vinorodrigues)  
Hardware Supported: Idobao ID96  
Hardware Availability: [Idobao ID96](https://www.idobao.net/collections/90/products/idobao-id96-aluminum-keyboard-kit)

Make example for this keyboard (after setting up your build environment):

    make idobao/id96:default

or

    qmk compile -kb idobao/id96 -km default

You can also use VIA / Vial for key mapping.  For this use the `via` keymap:

    make idobao/id96:via

or

    qmk compile -kb idobao/id96 -km via


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

---

## This build also supports [VIA](https://caniusevia.com/)...

...but VIA does not support it.

VIA will not detect the keyboard in it's default state - you will also need the VIA KLE JSON file for *"sideloading"* the keyboard into VIA.

*(You will need to load this file each time you start VIA.)*

In VIA, use *"Import Keymap"* and load the file: `id96_via_sideload_kle.json`.
