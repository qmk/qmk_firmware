# Anvil Native

The Native is a hot-swap 75% board with per-key LED ligthing in the Anvil brand lineup. 

* Keyboard maintainer: [ebastler](https://github.com/ebastler)
* Hardware supported: Anvil Native ISO/ANSI
* Hardware availability: Buy at [nvil.gg](https://www.nvil.gg/products/native-custom-keyboard-iso-de-ansi-de)

Enter Bootloader: 

* Bootmagic: Keep ESC (top left key) pressed while plugging the board in
* Physical reset button on the bottom of the PCB

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb teleport/native/iso -km default
    qmk compile -kb teleport/native/ansi -km default

If you want the default keymap with all features present on the board when sold, pick the `perfmode` keymaps instead:

    qmk compile -kb teleport/native/iso -km perfmode
    qmk compile -kb teleport/native/ansi -km perfmode

Flash example for this keyboard:

    qmk flash -kb teleport/native/iso -km default
    qmk flash -kb teleport/native/ansi -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
