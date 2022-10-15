# Twig50

![Twig50](https://user-images.githubusercontent.com/12627081/185365257-03a4904b-8432-445b-9eca-67f2aff57cd9.jpg "Sample build")

Handwired 50 key with Proton C.

* Keyboard Maintainer: [Takeshi Noda](https://github.com/nodatk)
* Hardware Supported: Proton C
* Hardware Availability: Sorry, not available for now

Layout data is available [here](http://www.keyboard-layout-editor.com/#/gists/8df4caf51c8d57e4069e2ae19965f02c).

Make example for this keyboard (after setting up your build environment):

    make handwired/twig/twig50:default

Flashing example for this keyboard:

    make handwired/twig/twig50:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
