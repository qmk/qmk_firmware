# Bacca70

![Bacca70](https://imgur.com/TQMALjwh.png)

The Bacca70 is a winkeyless (WKL) 60% layout that includes a F-row. It's classy, hefty and it was designed by Chewwy (of MechsOnDeck) and BlindAssassin.

* Keyboard Maintainer: [keebnewb](https://github.com/thompson-ele)  
* Hardware Supported: Bacca70 PCB and the ortholinear variant the DeBaccaBean PCB
* Hardware Availability: [3DKeebs](https://3dkeebs.com/)

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB. The button is next to the MCU.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available. For the default keymap it is on the right alt key on the second layer.

## Make example for this keyboard (after setting up your build environment):

    make bacca70:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
