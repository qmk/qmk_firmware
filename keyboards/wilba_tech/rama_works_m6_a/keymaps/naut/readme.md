# naut's Rama Works M6-A Layout

Arrows layer
![naut's M6-A keymap layer 0](https://i.imgur.com/ZiT5iM0.jpg)

Media layer
![naut's M6-A keymap layer 1](https://i.imgur.com/oFoWuDM.jpg)

Arrows keys on layer 0 when using a keyboard that's 60% or less and Media keys on layer 1 when using a keyboard greater than 65%.

* Keymap Maintainer: [naut](https://github.com/nautxx)

Make example for this keymap (after setting up your build environment):

    make wilba_tech/rama_works_m6_a:naut

Flashing example for this keyboard:

    make wilba_tech/rama_works_m6_a:naut:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
