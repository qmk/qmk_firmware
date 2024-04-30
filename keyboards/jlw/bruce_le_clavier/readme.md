# Bruce le Clavier

Please note that Bruce le Clavier is a keyboard, not a human, and is also not Bruce the Keyboard.

Bruce the Keyboard is a column staggered unibody split 35-key board created by [jlw](github.com/josh-l-wang), with the option to replace the middle key for an EC11 rotary encoder (with or without switch function).

This keyboard has RGB, 3.3V, and GND pins broken out if you wish to add an LED strip.

![Bruce le Clavier](https://i.imgur.com/qL9WHW4.jpg)

* Keyboard Maintainer: [jlw](https://github.com/josh-l-wang)
* Hardware Supported: [Bruce le Clavier and Cases](https://github.com/josh-l-wang/Bruce-the-Keyboard-the-Resources)
* Hardware Availability: [jlw-kb.com](https://jlw-kb.com)

Make example for this keyboard (after setting up your build environment):

    make jlw/bruce_le_clavier:default

Flashing example for this keyboard:

    make jlw/bruce_le_clavier:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Hold button on the back of the PCB while plugging in the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available




# Ceci est le micrologiciel pour Bruce le clavier

Notez bien que Bruce le clavier n'est pas un humain.

Bruce le clavier est un clavier de 35 touches colonnaire créé par [jlw](github.com/josh-l-wang). Il y a une option d'utiliser un encodeur rotatif au centre.

* Maintaineur de clavier: [jlw](https://github.com/josh-l-wang)
* Matériel supporté: [Bruce le Clavier and Cases](https://github.com/josh-l-wang/Bruce-the-Keyboard-the-Resources)
* Matériel disponibilité: [jlw-kb.com](https://jlw-kb.com)

Exemple de « make » (après avoir installé votre environnement de développement):

    make jlw/bruce_le_clavier:default
    
Exemple de flash pour ce clavier:

    make jlw/bruce_le_clavier:flash
    