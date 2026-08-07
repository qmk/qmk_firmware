# werk.technica one

![WT One Moloko](https://i.imgur.com/4Bvywra.png)

From looks to sound and feel, Werk One was designed as a cost is no object flagship product. A modular 75% exploded profile keyboard kit with hybrid gasket mount array and AEK-styled classic side profile curve.

In a world of minimalism, Werk One is our tribute to the sophistication of art deco and 70’s futurism.

* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: Rev1 solder and hotswap PCB (both work with `default` and `via` keymaps, but not all keymap positions are available on hotswap PCBs)
* Hardware Availability: [Groupbuy](https://werktechnica.com/)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb werk_technica/one -km default

Flash example for this keyboard (after setting up your build environment):

    qmk flash -kb werk_technica/one -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
Enter the bootloader in 2 ways:
* Bootmagic reset: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* Physical reset button: Hold for approx. 1 second to enter Bootloader
