# Brick

A 40% ortholinear Planck-shaped keyboard with bottom blockers for Cervello. Created by Pauper.

* Keyboard Maintainer: [Juno Nguyen](https://github.com/JunoNgx)
* Hardware Availability: [P3D Store](https://p3dstore.com/collections/invisibolt-acrylic-cases/products/cervello-invisibolt-acrylic-keyboard-case-and-pcb)

Make example for this keyboard (after setting up your build environment):

    make brick:default

Flashing example for this keyboard:

    make brick:default:flash
    
## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down Escape and plug in the keyboard.
* **Physical reset button**: Briefly press the reset button below the pro-micro.
* **Keycode in layout**: The `QK_BOOT` key can be found by holding `FUNC` in between the space bars and pressing `ESC`.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
