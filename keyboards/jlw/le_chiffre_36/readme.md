# Le Chiffre 36

![Le Chiffre 36](https://i.imgur.com/jIdWOQN.png)

A 36 key version of the Le Chiffre. The 3 thumb layout matches the Le Capybara (the thumb keys are 1-1-1.25 on the left hand and 1.25-1-1 on the right hand).

* Keyboard Maintainer: [JLW](https://github.com/josh-l-wang)
* Hardware Supported: Le Chiffre 36
* Hardware Availability: [JLW Keyboards](https://www.jlw-kb.com/products/le-chiffre-36-key-pcb)

Make example for this keyboard (after setting up your build environment):

    make jlw/le_chiffre_36:default

Flashing example for this keyboard:

    make jlw/le_chiffre_36:default:flash

See the [build environment setup](getting_started_build_tools) and the [make instructions](getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
