# Paper Crane Keyboards Gerald65

![gerald65](https://i.imgur.com/Qh9cLeEh.jpeg)

A 65% ergonomic acrylic keyboard emphasizing customizability.

* Keyboard Maintainer: [PaperCraneKeyboards](https://github.com/PaperCraneKeyboards)
* Hardware Supported: Gerald65 PCB
* Hardware Availability: [Paper Crane Keyboards](https://papercranekeyboards.com/)

Make example for this keyboard (after setting up your build environment):

    make papercranekeyboards/gerald65:default

Flashing example for this keyboard:

    make papercranekeyboards/gerald65:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB (located in the center)
* **Keycode in layout**: Press the key mapped to `RESET` if it is available. To do this, hold down the key to the right of the left spacebar (1u key in the center of bottom row), and then also press the key in the top right (by default, the delete key).

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
