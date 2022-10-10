# antipode/vero

![antipode/vero](https://i.imgur.com/znKP8XQh.jpeg)

AKB Vero - Vero means true. This keyboard brings you a truly great typing experience in a true HHKB layout. With its 6U spacebar and asymmetrical blockers it brings the classic design of the HHKB to MX keyboards.

* Keyboard Maintainer: [Antipode](https://antipode.no)
* Hardware Supported: AKB Vero PCB
* Hardware Availability: https://www.antipode.no/products/akb-vero

Make example for this keyboard (after setting up your build environment):

    make antipode/vero:default

Flashing example for this keyboard:

    make antipode/vero:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
