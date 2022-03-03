# naut's Rama Works M60-A Layout

Typing
![naut's M60-A keymap layer 0](https://i.imgur.com/K1qxACo.jpg)

Miscellaneous
![naut's M60-A keymap layer 1](https://i.imgur.com/ZOITKdD.jpg)

RGB lighting
![naut's M60-A keymap layer 2](https://i.imgur.com/LzJfJCr.jpg)

Keyboard lockout
![naut's M60-A keymap layer 3](https://i.imgur.com/Z7XT8BO.jpg)

HHKB style base layer and Fn1 layer. Fn2 to control the rgb led's. Fn3 turns off key input so you can mash buttons to your heart's content.

* Keymap Maintainer: [naut](https://github.com/nautxx)  

Make example for this keyboard (after setting up your build environment):

    make wilba_tech/rama_works_m60_a:naut

Flashing example for this keyboard:

    make wilba_tech/rama_works_m60_a:naut:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
